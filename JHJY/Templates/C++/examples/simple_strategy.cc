
#ifdef _WIN32
#include <Windows.h>
#endif

#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "md_api.h"
#include "strategy_api.h"
#include "trade_api.h"

using namespace std;

const char* kStockAccount = "6814";
const char* kSHProductId = "SH.601211";

const int kMaxOrderCount = 3;
int orderCount = 0;

#ifdef _WIN32
#define strncpy strncpy_s
#endif

typedef struct t_Orderid {
    int ntime;          //下单行情时间
    int res;            //保留
    char sorderid[32];  //委托号
} T_ORDERID;

vector<T_ORDERID> g_orderids;

// 返回当前日期时间，格式为YYYYMMDDhhmmss
static uint64_t datetime_now() {
    struct tm tmval;
    time_t time_now = time(NULL);
#ifdef _WIN32
    errno_t err = localtime_s(&tmval, &time_now);
    if (err != 0) {
        return err > 0 ? -err : err;
    }
#else
    errno = 0;
    struct tm* ret = localtime_r(&time_now, &tmval);
    if (ret == NULL) {
        return errno > 0 ? -errno : errno;
    }
#endif

    uint64_t ndate = (tmval.tm_year + 1900) * 10000 + (tmval.tm_mon + 1) * 100 +
                     tmval.tm_mday;
    uint64_t ntime = tmval.tm_hour * 10000 + tmval.tm_min * 100 + tmval.tm_sec;
    return ndate * 1000000 + ntime;
}

// 返回当前日期时间，格式为YYYY-MM-DD hh:mm:ss
static string str_datetime_now() {
    struct tm tmval;
    time_t time_now = time(NULL);
#ifdef _WIN32
    errno_t err = localtime_s(&tmval, &time_now);
    if (err != 0) {
        return "";
    }
#else
    errno = 0;
    struct tm* ret = localtime_r(&time_now, &tmval);
    if (ret == NULL) {
        return "";
    }
#endif

    char szTemp[32];
    snprintf(szTemp, sizeof(szTemp), "%04d-%02d-%02d %02d:%02d:%02d",
             tmval.tm_year + 1900, tmval.tm_mon + 1, tmval.tm_mday,
             tmval.tm_hour, tmval.tm_min, tmval.tm_sec);
    return szTemp;
}

// 证券Tick行情回调处理函数
void OnSecurityTick(SecurityTickData* res, void* user_data) {
    // 根据Tick行情，使用Tick成交价下单
    if (res->match > 0 && orderCount < kMaxOrderCount) {
        //1天下单3次：9：25集合竞价结束下单 10：00下单  14：30下单

        if ((res->time > 92458000 && res->time < 92503000) ||
            (res->time > 95959000 && res->time < 100003000) ||
            (res->time > 142959000 && res->time < 143003000)) {
            int rc = 0;
            //char order_id[128];
            ostringstream osstream;

            uint64_t price = res->ask_price[0];
            if (price == 0)
                price = res->high_limited;

			OrderReq req;
			memset(&req, 0x00, sizeof(OrderReq));
			strncpy(req.symbol, res->symbol,strlen(res->symbol));
			req.order_type = OrderType_LMT;
			req.side = OrderSide::OrderSide_Bid;
			req.volume = 100;
			req.price = price;
			req.hedge_flag = HedgeFlag::HedgeFlag_Placeholder;

			


			rc = td_order(kStockAccount, AccountType_Stock, &req, 1);

           /* rc = td_open_long(kStockAccount, AccountType_Stock, res->symbol,
                              price, 100, OrderType_LMT, order_id,
                              sizeof(order_id));*/
            if (0 == rc) {
                //g_orderids.push_back(order_id);

                T_ORDERID tod;
                memset(&tod, 0, sizeof(tod));
                strncpy(tod.sorderid, req.order_id, sizeof(tod.sorderid));
                tod.ntime = res->time;
                g_orderids.push_back(tod);

                osstream << "td_open_long, order_id: " << req.order_id
                         << ", symbol: " << res->symbol
                         << ", price: " << res->match / 10000.0
                         << ", volume: " << 100;
                strategy_log(StrategyLogLevel_Info, osstream.str().data());
            } else {
                osstream << "td_open_long failed, code: " << rc
                         << ", msg: " << hft_strerror_utf8(rc);
                strategy_log(StrategyLogLevel_Error, osstream.str().data());
            }

            orderCount++;
        }
    }
}

// 证券K线行情回调处理函数
void OnSecurityKdata(SecurityKdata* res, void* user_data) {
    // 根据K线行情，使用这一分钟开盘价下单
    if (orderCount < kMaxOrderCount) {
    }
}

void OnTickbytickData(TickByTickData* tbt, void* user_data) {
    ostringstream oss;
    int32_t channel_no = 0;
    int64_t seq = 0;
    if (tbt->type == '0') {
        channel_no = tbt->data.entrust.channel_no;
        seq = tbt->data.entrust.seq;
    } else {
        channel_no = tbt->data.trade.channel_no;
        seq = tbt->data.trade.seq;
    }

    oss << "OnTickbytickData: " << tbt->type << " " << tbt->symbol << " "
        << channel_no << ":" << seq;
    strategy_log(StrategyLogLevel_Info, oss.str().data());
}

void OnIndexTickCallback(IndexTickData* res, void* user_data) {
    //处理指数行情
}

// 市场日期变更回调处理函数
void OnDateUpdate(DateUpdateData* dud, void* user_data) {
    ostringstream oss;
    oss << "OnDateUpdate: market: " << dud->market << ", date: " << dud->date;

    strategy_log(StrategyLogLevel_Info, oss.str().data());
    std::cout << "OnDateUpdate: market: " << dud->market
              << ", date: " << dud->date << endl;
}

// 成交回报回调处理函数
void OnTradeReport(const Trade* trade, void* user_data) {
    // 输出成交回报到strategy目录的日志中
    ostringstream osstream;
    osstream << "OnTradeReport: " << endl
             << "\tstrategy_id: " << trade->strategy_id << endl
             << "\trun_id: " << trade->run_id << endl
             << "\torder_id: " << trade->order_id << endl
             << "\tcl_order_id: " << trade->cl_order_id << endl
             << "\tsymbol: " << trade->symbol << endl
             << "\taccount_id: " << trade->account_id << endl
             << "\taccount_type: " << trade->account_type << endl
             << "\tdate: " << trade->date << endl
             << "\ttrade_seqno: " << trade->trade_seqno << endl
             << "\tside: " << trade->side << endl
             << "\torder_type: " << trade->order_type << endl
             << "\texec_type: " << trade->exec_type << endl
              << "\texec_id: " << trade->exec_id << endl
             << "\tvolume: " << trade->volume << endl
             << "\tprice: " << trade->price << endl
             << "\tturnover: " << trade->turnover << endl
             << "\ttransact_time: " << trade->transact_time;
    strategy_log(StrategyLogLevel_Info, osstream.str().data());
}

// 委托应答回调处理函数
void OnOrderRsp(const OrderRsp* order_rsp, int count, void* user_data) {
    // 输出委托应答到strategy目录的日志中
    ostringstream osstream;
    for (int i = 0; i < count; ++i) {
        osstream.str("");
        osstream << "OrderRsp: " << endl
                 << "\torder_id: " << order_rsp[i].order_id << endl
                 << "\tcl_order_id: " << order_rsp[i].cl_order_id << endl
                 << "\terr_code: " << order_rsp[i].err_code << endl
                 << "\terr_msg: " << order_rsp[i].err_msg;
        strategy_log(StrategyLogLevel_Info, osstream.str().data());
    }
}

// 委托状态回调处理函数
void OnOrderStatus(const Order* res, void* user_data) {
    // 输出委托状态到strategy目录的日志中
    ostringstream osstream;
    osstream << "OnOrderStatus: " << endl
             << "\tstrategy_id: " << res->strategy_id << endl
             << "\trun_id: " << res->run_id << endl
             << "\torder_id: " << res->order_id << endl
             << "\tcl_order_id: " << res->cl_order_id << endl
             << "\tsymbol: " << res->symbol << endl
             << "\taccount_id: " << res->account_id << endl
             << "\taccount_type: " << res->account_type << endl
             << "\tprice: " << res->price << endl
             << "\tmarketdata_time: " << res->marketdata_time << endl
             << "\tcreate_time: " << res->create_time << endl
             << "\tupdate_time: " << res->update_time << endl
             << "\tside: " << res->side << endl
             << "\torder_status: " << res->order_status << endl
             << "\tfilled_volume: " << res->filled_volume << endl
             << "\tfilled_turnover: " << res->filled_turnover;
    strategy_log(StrategyLogLevel_Info, osstream.str().data());
}

// 行情服务状态回调
void OnMdStatusChange(int conn_status, void* user_data) {
    ostringstream osstream;
    osstream << "OnMdStatusChange: " << conn_status;
    strategy_log(StrategyLogLevel_Info, osstream.str().data());
}

// 定时回调处理函数
void OnStrategyTimer(int interval, void* user_data) {
    ostringstream osstream;

    // 定时任务中只调用一次get_security_ticks，作为示例
    static bool security_ticks_called = false;
    if (!security_ticks_called) {
        security_ticks_called = true;
        SecurityTickData* sd = NULL;
        int count = 0;
        int ret = get_security_ticks("SH.600000,SZ.000001", "2020-1-2 10:0:0",
                                     "2020-1-2 16:0:0", &sd, &count);

        osstream.str("");
        osstream << "get_security_ticks: " << ret << ", count:" << count
                 << ", sd: " << sd;
        strategy_log(StrategyLogLevel_Info, osstream.str().data());

       
        strategy_log(StrategyLogLevel_Info, osstream.str().data());
    }

    // 定时任务中只调用一次get_security_kdata，作为示例
    static bool security_kdata_called = false;
    if (!security_kdata_called) {
        security_kdata_called = true;
        SecurityKdata* sd = NULL;
        int count = 0;
        int ret = get_security_kdata("SH.600000", "2018/6/1", "2018/6/1",
                                     "1min", "none", &sd, &count);

        osstream.str("");
        osstream << "get_security_kdata: " << ret << ", count:" << count
                 << ", sd: " << sd;
        strategy_log(StrategyLogLevel_Info, osstream.str().data());
    }

    if (interval == 5000) {
        // 每5秒钟更新一次参数和自定义指标
        char szJsonContent[256];
        snprintf(szJsonContent, sizeof(szJsonContent),
                 "[{\"key\":\"DateTime\", \"name\":\"DateTime\", "
                 "\"type\":\"datetime\", "
                 "\"value\":\"%s\"}, {\"key\":\"OrderNum\", "
                 "\"name\":\"OrderNum\", \"type\":\"int\", \"value\":%zu}]",
                 str_datetime_now().data(), g_orderids.size());
        strategy_report_indexes(szJsonContent);
        strategy_report_params(szJsonContent);
    }
}

void OnDayTaskCallback(int time, void* user_data) {
    ostringstream osstream;
    std::cout << "OnDayTaskCallback: " << time << std::endl;

    orderCount = 0;  //置0，让当天又可以下单交易
    if (g_orderids.size() > 0)
        g_orderids.clear();

    osstream << "OnDayTaskCallback: " << time;
    strategy_log(StrategyLogLevel_Info, osstream.str().data());
}

void OnExit(int reason, void* user_data) {
    // 退出回调做一些资源回收等最终操作
    ostringstream osstream;
    osstream << "OnExit, reason: " << strategy_exit_reason(reason);
    const string& message = osstream.str();
    cout << message << endl;
    strategy_log(StrategyLogLevel_Info, message.data());
    std::cout << "OnExit, reason: " << strategy_exit_reason(reason);
}

#ifdef _WIN32
bool CtrlHandler(DWORD fdwctrltype) {
    switch (fdwctrltype) {
            // handle the ctrl-c signal.
        case CTRL_C_EVENT:
            strategy_exit();
            return (true);

        default:
            return false;
    }
}
#endif

int main(int argc, const char* argv[]) {
// 处理命令行CTRL-C退出信号
#ifdef _WIN32
    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)) {
        cout << "ERROR: Could not set console control handler" << endl;
        strategy_log(StrategyLogLevel_Error,
                     "ERROR: Could not set console control handler");
        return 1;
    }
#endif

    // async = 1表示启动一个新线程执行事件循环
    // async = 0表示主线程执行事件循环，主线程会在strategy_run运行一个循环
    int async = 1;

    // 初始化策略
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

    cout << "strategy_init success" << endl;
    strategy_log(StrategyLogLevel_Info, "strategy_init success");

    // 设置交易相关回调事件处理函数
    td_set_trade_report_callback(OnTradeReport, NULL);
    td_set_order_rsp_callback(OnOrderRsp, NULL);
    td_set_order_status_callback(OnOrderStatus, NULL);

    // 设置实时行情回调事件处理函数
    md_set_status_change_callback(OnMdStatusChange, NULL);

    // 设置行情回调函数
    md_set_security_tick_callback(OnSecurityTick, NULL);  //证券tick行情回调
    md_set_index_tick_callback(OnIndexTickCallback, NULL);
    md_set_security_kdata_callback(OnSecurityKdata, NULL);  //证券分钟K线回调
    md_set_tickbytick_callback(OnTickbytickData, NULL);

    md_set_date_update_callback(OnDateUpdate, NULL);  //日期变化回调

    // 设置定时任务回调处理函数
    strategy_set_timer_callback(OnStrategyTimer, NULL);

    // 设置策略退出回调处理函数
    strategy_set_exit_callback(OnExit, NULL);

    // 设置一个5s定时任务
    strategy_set_timer(5000);

    strategy_set_day_schedule_task_callback(OnDayTaskCallback, NULL);
    strategy_set_day_schedule_task(85000);

    // 订阅一个Tick，多个K线行情
    md_subscribe("SH.601211.tick,SH.601211.bar,SH.000001.index");

    // 运行策略
    rc = strategy_run(async);
    if (rc != 0) {
        osstream.str("");
        osstream << "strategy_run failed: " << rc
                 << ", msg: " << hft_strerror_utf8(rc);
        cout << "strategy_run failed: " << rc
             << ", msg: " << hft_strerror(rc) << endl;
        strategy_log(StrategyLogLevel_Error, osstream.str().data());
    } else {
        cout << "strategy_run success" << endl;
        strategy_log(StrategyLogLevel_Info, "strategy_run success");
    }

    // 主线程等待策略线程退出
    while (strategy_get_exec_status() != StrategyExecStatus_Term) {
        // sleep 500ms
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

OnProgramExit:
    if (strategy_get_exec_status() != StrategyExecStatus_Term) {
        rc = strategy_exit();
        if (rc != 0) {
            osstream.str("");
            osstream << "strategy_exit failed: " << rc
                     << ", msg: " << hft_strerror_utf8(rc);
            cout << "strategy_exit failed: " << rc
                 << ", msg: " << hft_strerror(rc) << endl;
            strategy_log(StrategyLogLevel_Info, osstream.str().data());
        } else {
            cout << "strategy_exit success" << endl;
            strategy_log(StrategyLogLevel_Info, "strategy_exit success");
        }
    }
    return 0;
}