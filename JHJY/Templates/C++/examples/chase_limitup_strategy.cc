/*! \mainpage 简介

&emsp;&emsp;策略示例-2<br>
&emsp;&emsp;编写简单的追涨停策略？所有错误码详细见error.h头文件<br>
<br>
<br>
\ref page_datatype <br><br>
\ref page_struct	<br><br>
\ref page_interface	<br><br>
\ref page_errcode	<br>  <br>
<CENTER> 国泰君安证券股份有限公司</CENTER>
<CENTER> 2018年6月 by mahui</CENTER>
*/

#ifdef _WIN32
#include <Windows.h>
#endif

/*! \包含头文件
<br>
\ref 编写策略必须包含以下3个头文件<br><br>
\ref md_api.h         行情接口API，用于获取实时行情、历史行情API
\ref trade_api.h      交易接口API，用于交易下单、撤单、策略持仓查询
\ref strategy_api.h   策略模板API，用于初始化策略运行环境、协助策略运行
*/
#include "md_api.h"
#include "strategy_api.h"
#include "trade_api.h"

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

#ifdef _WIN32
#define strncpy strncpy_s
#define snprintf _snprintf_s
#endif

const char* TRADE_ACCOUNT = "5580";
const char* TEST_CODE = "SH.601211";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  策略逻辑
//（1）订阅沪深市场所有标的的tick数据
//（2）择股逻辑：a)标的价格涨7%及上；b)5日均线在10日均线以上；c)非ST股票；满足以上条件的标的加入择股池
// (3) 择时逻辑：当择股池中的标的涨至9.5%及以上时，委托买入固定金额5万，30秒如未成交，则撤单
// (4) 出场逻辑：早盘开盘9：30出仓前一天买入的标的
// 注意：策略运行时可使用的资金由客户端设置分配，策略运行时只需要查询策略可用资金即可。
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct t_OrdMsg {
    char sorderid[40];  //订单编号
    time_t tordtime;    //订单委托时间
    bool bfinished;     //订单是否终止状态
} T_ORDMSG;

typedef struct t_InitData {
    int nDate;  //上市场起始日期
                //other
} T_INITDATA;  //日初时初始化好当日需要使用的信息，避免盘中时临获取降低效率

typedef unordered_map<std::string, std::string>
    MAP_SELECT;  //择股后的存储对象
typedef unordered_map<std::string, T_ORDMSG> MAP_ORDER;  //存储已下单信息
typedef unordered_map<std::string, T_INITDATA> MAP_INITDATA;

class example_strategy {
   public:
    example_strategy() {}
    ~example_strategy() {}

    /////////////////////////////////////////////////////////////////////////
    ///行情回调函数
    //////////////////////////////////////////////////////////////////////////
    //收到证券tick行情数据回调函数
    //说明：指数、期货、期权、分钟K线有相应的回调函数原型，请参见API头文件，其中对于分钟K线，所有品种的结体一致
    //@param res 证券tick数据行情结构体（价格均放大了10000倍）
    //@param user_data 设置回调时用户传入的参数，回调函数原样抛出

    static void OnSecurityTick(SecurityTickData* res, void* user_data) {
        //printf("收到行情[%s],价格[%d]\n", res->symbol, res->match);

        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoSecurityTick(res);
        }
    }
    //实时行情连接状态回调函数
    static void OnMDStatusChange(int conn_status, void* user_data) {
        //printf("OnMDStatusChange conn_status[%d]\n", conn_status);
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoMDStatusChange(conn_status);
        }
    }
    /////////////////////////////////////////////////////////////////////////
    ///交易相关回调函数
    //////////////////////////////////////////////////////////////////////////

    // 成交回报回调处理函数
    static void OnTradeReport(const Trade* trade, void* user_data) {
        //printf("成交回报[%s],原委托量[%d],成交量[%d],成交金额[%I64d]\n", trade->symbol, trade->order_volume, trade->volume, trade->turnover);
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoTradeReport(trade);
        }
    }

    // 委托应答回调处理函数
    static void OnOrderRsp(const OrderRsp* order_rsp, int count,
                           void* user_data) {
        //printf("委托应答，异步序号[%s],委托号[%s],错误码[%d]，错误消息[%s]\n", order_return->cl_order_id, order_return->order_id, order_return->err_code, order_return->err_msg);
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoOrderRsp(order_rsp, count);
        }
    }

    // 委托状态回调处理函数
    static void OnOrderStatus(const Order* res, void* user_data) {
        //printf("[%s]委托状态发生变化，status[%d]\n", res->symbol, res->order_status);
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoOrderStatus(res);
        }
    }

    // 定时回调处理函数
    static void OnStrategyTimer(int interval, void* user_data) {
        //printf("定时器回调函数,回调时间间隔[%d]秒\n", interval / 1000);
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoStrategyTimer(interval);
        }
    }

    //每日定时执行任务
    static void OnStrategyDayScheduleTask(int time, void* user_data) {
        if (user_data != NULL) {
            example_strategy* pStrategy = (example_strategy*)user_data;
            pStrategy->DoStrategyDayScheduleTask(time);
        }
    }

   private:
    //由于回调函数属于静态函数，不能使用实例中的变量，所以需要调转一下，以下函数与回调函数对应

    void DoSecurityTick(SecurityTickData* res) {
        //a)标的价格涨7%及上；b)5日均线在10日均线以上；c)非ST股票；d)上市时间大于6个月，满足以上条件的标的加入择股池
        // (3) 择时逻辑：当择股池中的标的涨至9.5%及以上时，委托买入固定金额5万，30秒如未成交，则撤单

        if (_mapinit.find(res->symbol) == _mapinit.end()) {
            return;
        }

        if (res->match <= 0)
            return;
        //计算涨跌幅
        double dupdown =
            (((int)res->match - (int)res->pre_close) * 1.0) / res->pre_close;

        MAP_SELECT::iterator it = _mapSelect.find(res->symbol);
        if (it != _mapSelect.end())  //择时入场
        {
            if (dupdown >= 0.095f) {
                //入仓5万完金额,以卖一价格买入(注：行情中的价格均放大了10000倍)
                //计算价格
                uint64_t price = 0;
                if (res->ask_price[0] == 0) {
                    price = res->high_limited;  //取涨停价
                } else {
                    price = res->ask_price[0];
                }
                //计算委托量,注意整数股
                int vol =
                    (static_cast<int>((50000.0 / (price / 10000.0))) / 100) *
                    100;
                //同步下单
                if (_mapOrder.find(res->symbol) != _mapOrder.end())
                    return;  //当日已经下单过的订单不需要再下单
               /* char sorderid[64] = {
                    0,
                };*/
                int nsize = 64;


				OrderReq req;
				memset(&req, 0x00, sizeof(OrderReq));
				strncpy(req.symbol, res->symbol, strlen(res->symbol));
				req.order_type = OrderType_LMT;
				req.side = OrderSide::OrderSide_Bid;
				req.volume = 100;
				req.price = price;
				req.hedge_flag = HedgeFlag::HedgeFlag_Placeholder;

				int rc = td_order(TRADE_ACCOUNT, AccountType_Stock, &req, 1);

               /* int rc = td_open_long(
                    TRADE_ACCOUNT, AccountType::AccountType_Stock, res->symbol,
                    price, vol, OrderType::OrderType_LMT, sorderid, nsize);*/
                if (rc != 0) {
                    //委托失败打日志
                    strategy_log(StrategyLogLevel::StrategyLogLevel_Error,
                                 hft_strerror_utf8(rc));
                    return;
                } else {
                    char stmp[128] = {
                        0,
                    };
                    snprintf(stmp, sizeof(stmp), "[%s]委托下单完成，委托编号[%s]",
                             res->symbol, req.order_id);
                    strategy_log(StrategyLogLevel::StrategyLogLevel_Info, stmp);

                    T_ORDMSG oms;
                    memset(&oms, 0x00, sizeof(T_ORDMSG));
                    strncpy(oms.sorderid, req.order_id, strlen(req.order_id));
                    oms.bfinished = false;
                    oms.tordtime = time(NULL);
                    _mapOrder.insert(
                        std::pair<std::string, T_ORDMSG>(res->symbol, oms));
                }
            }

        } else  //择股,a)标的价格涨7%及上；c)非ST股票；
        {
            //如果未在备选池，则进行择股
            if (dupdown > 0.07f)  //a)标的价格涨7%及上；c)非ST股票(ST涨跌5%)；
            {
                _mapSelect.insert(std::pair<std::string, std::string>(
                    res->symbol, res->symbol));
            }
        }
    }
    //实时行情连接状态回调函数
    void DoMDStatusChange(int conn_status) {
        printf("OnMDStatusChange conn_status[%d]\n", conn_status);
    }
    /////////////////////////////////////////////////////////////////////////
    ///交易相关回调函数
    //////////////////////////////////////////////////////////////////////////

    // 成交回报回调处理函数
    void DoTradeReport(const Trade* trade) {
        //printf("成交回报[%s],原委托量[%d],成交量[%d],成交金额[%I64d]\n", trade->symbol, trade->order_volume, trade->volume, trade->turnover);
    }

    // 委托应答回调处理函数
    void DoOrderRsp(const OrderRsp* order_rsp, int count) {
        // for (int i = 0; i < count; ++i) {
        // 	printf("委托应答，异步序号[%s],委托号[%s],错误码[%d]，错误消息[%s]\n",
        // 		order_rsp[i].cl_order_id, order_rsp[i].order_id,
        // 		order_rsp[i].err_code, order_rsp[i].err_msg);
        // }
    }

    // 委托状态回调处理函数
    void DoOrderStatus(const Order* res) {
        //printf("[%s]委托状态发生变化，status[%d]\n", res->symbol, res->order_status);
    }

    // 定时回调处理函数
    void DoStrategyTimer(int interval) {
        //printf("定时器回调函数,回调时间间隔[%d]秒\n", interval / 1000);

        //30秒如未成交，则撤单

        time_t tnow = time(NULL);
        //如超过30秒未成交，则撤单

        for (MAP_ORDER::iterator it = _mapOrder.begin(); it != _mapOrder.end();
             it++) {
            if (tnow - it->second.tordtime > 30 &&
                (!it->second.bfinished))  //委托下单超过30秒了
            {
                Order order;
                memset(&order, 0x00, sizeof(Order));
                int rc = td_get_order(it->second.sorderid, &order);
                if (rc == 0) {
                    if (it->second.bfinished == false &&
                        (order.order_status == OrderStatus::OrderStatus_New ||
                         order.order_status ==
                             OrderStatus::OrderStatus_PartiallyFilled)) {
                        //撤单操作

                        int rc = td_cancel_order(TRADE_ACCOUNT,
                                                 AccountType::AccountType_Stock,
                                                 it->second.sorderid);
                        if (rc == 0) {
                            strategy_log(
                                StrategyLogLevel::StrategyLogLevel_Error,
                                "撤单报单成功");
                        }
                    }
                    it->second.bfinished = true;
                }
            }
        }
    }

    void DoStrategyDayScheduleTask(int time) {
        if (85500 == time)  //当日初始化任务发生
        {
            if (_mapSelect.size() > 0)
                _mapSelect.clear();
            if (_mapOrder.size() > 0)
                _mapOrder.clear();
            if (_mapinit.size() > 0)
                _mapinit.clear();
            PreInitData();
        } 
		else if (93000 == time)  //已经到达9：30，卖出持仓
        {
          
        }
    }
public:
   void PreInitData()
	{
        //CodeInfo* pcinfo = NULL;
        //int nCount = 0;
        //int date = 0;
        //int time = 0;

    }

   private:
    MAP_INITDATA _mapinit;  //证券白名单池，上市日期大于6个月
    MAP_SELECT _mapSelect;  //择股备选池 key  value 均为 “市场.代码格式”
    MAP_ORDER
    _mapOrder;  //下单信息 key “市场.代码格式”  value 为 订单编号与订单时间的结构体
};

int main(int argc, const char* argv[]) {
    example_strategy* pStrategy = new example_strategy();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //1、 初始化策略运行环境
    //注意：（1）初始化返回成功，表示行情登录、交易登录均已成功，其中之一失败则表示初始化失败
    //      （2）后续使用过程中，可以通过strategy_get_exec_status接口判断运行环境是否OK
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ostringstream osstream;
    int rc = strategy_init();
    if (0 != rc) {
        osstream << "strategy_init failed: " << rc
                 << ", msg: " << hft_strerror_utf8(rc);
        cout << "strategy_init failed: " << rc
             << ", msg: " << hft_strerror(rc) << endl;
        strategy_log(StrategyLogLevel_Error, osstream.str().data());
        goto OnProgramExit;
    }
    strategy_log(StrategyLogLevel_Info, "strategy_init success");
    printf("strategy_init success\n");

    pStrategy->PreInitData();

    ////////////////////////////////////////////////////////////////////////////////////
    //2、设置策略回调函数（行情、交易均支持事件回调，更快响应）,如不需要，可以不用设置
    ///////////////////////////////////////////////////////////////////////////////////

    // 2.1设置交易相关回调事件处理函数
    td_set_trade_report_callback(example_strategy::OnTradeReport, pStrategy);
    td_set_order_rsp_callback(example_strategy::OnOrderRsp, pStrategy);
    td_set_order_status_callback(example_strategy::OnOrderStatus, pStrategy);

    // 2.2设置实时行情回调事件处理函数
    md_set_status_change_callback(example_strategy::OnMDStatusChange,
                                  pStrategy);
    md_set_security_tick_callback(example_strategy::OnSecurityTick, pStrategy);

    // 2.3 设置定时任务回调处理函数
    strategy_set_timer_callback(example_strategy::OnStrategyTimer, pStrategy);
    strategy_set_day_schedule_task_callback(
        example_strategy::OnStrategyDayScheduleTask, pStrategy);

    //////////////////////////////////////////////////////////////////////////////////////
    // 3、设置定时任务
    /////////////////////////////////////////////////////////////////////////////////////
    strategy_set_timer(1000);               // 1秒执行一次回调函数
    strategy_set_day_schedule_task(85500);  // 每日8:55:00执行一次，用于初始化
    strategy_set_day_schedule_task(
        93000);  // 每日9：30：00执行一次，用于卖出前一日持仓

    //////////////////////////////////////////////////////////////////////////////////////
    // 4、订阅沪深市场tick数据行情
    /////////////////////////////////////////////////////////////////////////////////////
    md_subscribe("SH.*.tick,SZ.*.tick");

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //5、策略运行(此函数运行后，回调函数生效)
    //注意：（1）运行参数0，表示同步运行，调用后函数block，回调函数在主线程中执行调用，在不开新线程的情况下用户可以不用考虑数据共享加锁定问题。
    //      （2）运行参数非0，表示异步运行，调用后函数非block,回调函数在非主线程中执行调用，用户需要考虑共享数据加锁问题。
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 运行策略
    rc = strategy_run(0);

    if (pStrategy) {
        delete pStrategy;
        pStrategy = NULL;
    }

OnProgramExit:
    rc = strategy_exit();
    if (rc != 0) {
        printf("strategy_exit fail:%d\n", rc);
    } else {
        printf("strategy_exit success\n");
    }
    return 0;
}