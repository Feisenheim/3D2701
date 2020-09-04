/**
 * @file    md_api.h
 * @brief   hftsdk 行情相关API定义
 */

#ifndef HFT_SDK_MD_API_H__
#define HFT_SDK_MD_API_H__

#include "md_def.h"

/******* 获取历史行情相关接口 Begin ****************************************/

/**
 * 获取指定时间段的证券历史Tick数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   证券代码列表，以逗号分开的市场.证券代码，如"sh.600726,sz.000729"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param std           获取的证券tick数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_security_ticks(const char* symbol_list, const char* begin_time,
                               const char* end_time, SecurityTickData** std,
                               int* count);
/*
 * 获取指定时间段的指数历史Tick数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   指数代码列表，以逗号分开的市场.证券代码，如"sh.000001,sz.399992"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param itd           获取的指数tick数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_index_ticks(const char* symbol_list, const char* begin_time, 
                            const char* end_time, IndexTickData** itd, 
                            int* count);
/**
 * 获取指定时间段的期货历史Tick数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   期货代码列表，以逗号分开的市场.证券代码，如"cffex.if1803,cffex.ic1806"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param ftd           获取的期货tick数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_futures_ticks(const char* symbol_list, const char* begin_time,
                              const char* end_time, FuturesTickData** ftd,
                              int* count);
/**
 * 获取指定时间段的期权历史Tick数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   期权代码列表，以逗号分开的市场.证券代码，如"shop.10210201,shop.1201021"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param otd           获取的期权tick数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_options_ticks(const char* symbol_list, const char* begin_time,
                              const char* end_time, OptionsTickData** otd,
                              int* count);

/**
 * 获取指定时间段的历史逐笔行情数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   证券代码列表，以逗号分开的市场.证券代码，如"sh.600000,sz.300033"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param tbts          获取的逐笔行情数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_tickbyticks(const char* symbol_list, const char* begin_time,
                            const char* end_time, TickByTickData** tbts, 
                            int* count);

/**
 * 获取指定时间段的历史委托队列数据，接口支持单个代码或多个代码组合获取数据。
 *
 * @param symbol_list   证券代码列表，以逗号分开的市场.证券代码，如"sh.600000,sz.300033"
 * @param begin_time    开始时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 9:0:0"
 * @param end_time      结束时间，YYYY/MM/DD hh:mm:ss,如"2017/07/05 10:0:0"
 * @param oqs           获取的委托队列数据
 * @param count         获取的数据个数
 * @return              成功返回0，失败返回错误码
 */
HFT_API int get_orderqueues(const char* symbol_list, const char* begin_time,
                            const char* end_time, OrderQueueData** oqs,
                            int* count);

/**
 * 获取指定时间段的历史K线数据，
 * 支持任意分钟或天的证券K线数据获取.
 *
 * @param  symbol_list 证券代码列表，以逗号分开的市场.证券代码，如"sh.601211,sz.000001"
 * @param  begin_date  开始日期，如"2017/1/3"
 * @param  end_date    结束日期，如"2017/10/12",当基于分钟K线计算时日期跨度不能大于1年，基于日线计算则不受限制
 * @param  frequency   计算频率，单位"min"表示分钟K线，比如"5min","15min","30min", 大于1min且 120min % xmin == 0. 单位"day"表示日，比如"5day","10day","30day",大于0即可。可以为"1min"或"1day"。
 * @param  fq          复权方式（前复权"before"、后复权"after"、不复权"none"）
 * @param  skd         获取的K线数据
 * @param  count       获取的K线数据个数
 * @return             成功返回0，失败返回错误码
 */
HFT_API int get_security_kdata(const char* symbol_list, const char* begin_date,
                               const char* end_date, const char* frequency,
                               const char* fq, SecurityKdata** skd, int* count);

/**
 * 获取某个时间段内的代码表信息，包含各种股票列表、基金列表、指数列表、债券列表、期货列表和期权列表
 *
 * @param  codetab     代码表名，比如"HS300"
 * @param  ci          获取的代码信息数据
 * @param  count       获取的代码信息数据个数
 * @param  begin_date  开始日期，比如"2017/1/3",不能为空
 * @param  end_date    结束日期，比如"2017/2/1",不能为空
 * @param  onlycode    是否只需要代码，默认为true，表示只需要代码
 * @return             成功返回0，失败返回错误码
 */
HFT_API int get_codelist(const char* codetab, CodeInfo** ci,
                         int* count, const char* begin_date, 
                         const char* end_date, bool onlycode = true);

/**
* 获取某天的某个代码信息，包含各种股票、期货和期权
*
* @param  code         代码名,形如"市场.代码",比如"SH.600000"
* @param  ci           获取的代码信息数据
* @param  date         指定的日期，比如"2017/1/3",默认为NULL,表示当天
* @return              成功返回0，失败返回错误码
*/
HFT_API int get_codeinfo(const char* code, CodeInfo** ci,
                         const char* date = nullptr);

/**
 * 获取某个市场某段时间的交易日期数据
 *
 * @param  market      交易所代码,比如"SH"
 * @param  begin_date  开始日期，比如"2018/2/5"
 * @param  end_date    结束日期，比如"2018/2/10"
 * @param  td          获取的市场交易日期数据
 * @param  count       获取的市场交易日期数据个数
 * @return             成功返回0，失败返回错误码
 */
HFT_API int get_tradedate(const char* market, const char* begin_date,
                          const char* end_date, TradeDate** td, int* count);

/**
 * 获取某种标的的某段时间的权息数据
 *
 * @param  symbol     证券代码，带交易所代码，如"SH.600000"
 * @param  begin_date 查询开始日期，如"2017/1/3"
 * @param  end_date   查询结束日期，如"2017/10/20"
 * @param  qd         获取的权息数据数组
 * @param  count      获取的权息数据个数
 * @return            成功返回0，失败返回错误码
 */
HFT_API int get_qxdata(const char* symbol, const char* begin_date,
                       const char* end_date, QxData** qd, int* count);

/************************ 获取历史行情相关接口 End ***************************/

/************************ 订阅实时行情相关接口 Begin ***********************/

/**
 * 订阅代码列表的行情。
 *
 * @param  symbol_list 订阅串有三节组成, 分别对应
 *                     交易所.代码.数据类型
 *                     现在K线只支持1分钟K线订阅
 *                     比如"SH.601211.tick,SZ.000002.bar,SH.000001.index,
 *                          SZ.000001.zw,SZ.000001.zc,SZ.000001.fast,SZ.000001.queue"
 *
 * @return             成功返回0，失败返回错误码
 */
HFT_API int md_subscribe(const char* symbol_list);

/**
 * 退订指定代码表的行情。
 *
 * @param  symbol_list 证券代码或交易所代码，其中证券代码包括市场，
 *                     代码和行情数据类型
 *                     比如"SH.601211.tick,SZ.000002.bar,SH.000001.index,
 *                          SZ.000001.zw,SZ.000001.zc,SZ.000001.fast,SZ.000001.queue"
 * @return             成功返回0，失败返回错误码
 */
HFT_API int md_unsubscribe(const char* symbol_list);

/**
 * 退订之前订阅的所有行情。
 *
 * @return             成功返回0，失败返回错误码
 */
HFT_API int md_unsubscribeall();

/**
 * 证券tick级数据行情回调函数定义
 *
 * @param res           回调的证券tick对象
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，
 *                      作为回调函数参数输入
 */
typedef void (*MDSecurityTickCallback)(SecurityTickData* res, void* user_data);

/**
 * 设置证券tick级数据行情事件回调方法
 *
 * @param cb             收到证券tick行情时调用设置的回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void md_set_security_tick_callback(MDSecurityTickCallback cb,
                                           void* user_data);


/**
 * 指数tick级数据行情回调函数定义
 *
 * @param res           回调的指数tick对象
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，
 *                      作为回调函数参数输入
 */
typedef void (*MDIndexTickCallback)(IndexTickData* res, void* user_data);

/**
 * 设置指数tick级数据行情事件回调方法
 *
 * @param cb             收到指数tick行情时调用设置的回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
HFT_API void md_set_index_tick_callback(MDIndexTickCallback cb, void* user_data);

/**
 * 期货tick级数据行情回调函数定义
 *
 * @param res            回调的期货tick对象
 * @param user_data      用户自定义参数,与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
typedef void (*MDFuturesTickCallback)(FuturesTickData* res, void* user_data);

/**
 * 设置期货tick级数据行情事件回调方法
 *
 * @param cb             收到期货tick行情时调用设置的回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
HFT_API void md_set_futures_tick_callback(MDFuturesTickCallback cb,
                                          void* user_data);

/**
 * 期权tick级数据行情回调函数定义
 *
 * @param res           回调的期权tick对象
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，
 *                      作为回调函数参数输入
 */
typedef void (*MDOptionsTickCallback)(OptionsTickData* res, void* user_data);

/**
 * 设置期权tick级数据行情事件回调方法
 *
 * @param cb             收到期权tick行情时调用设置的回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
HFT_API void md_set_options_tick_callback(MDOptionsTickCallback cb,
                                          void* user_data);


/**
 * @brief 逐笔数据行情回调函数定义
 *
 * @param res           回调的逐笔数据对象
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，
 *                      作为回调函数参数输入
 */
typedef void(*MDTickByTickCallback)(TickByTickData* res, void* user_data);

/**
 * @brief 设置逐笔数据行情事件回调方法
 *
 * @param cb             收到逐笔行情时调用设置的回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
HFT_API void md_set_tickbytick_callback(MDTickByTickCallback cb, void* user_data);


/**
 * 证券K线数据回调函数定义
 *
 * @param res            回调的证券K线数据对象
 * @param user_data      用户自定义参数
 */
typedef void (*MDSecurityKdataCallback)(SecurityKdata* res, void* user_data);

/**
 * 设置证券K线数据行情事件回调方法
 *
 * @param cb             证券K线回调方法
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void md_set_security_kdata_callback(MDSecurityKdataCallback cb,
                                            void* user_data);

/**
* @brief 委托队列数据消息包回调函数定义
*
* @param res            回调的委托队列数据对象
* @param user_data      用户自定义参数
*/
typedef void(*MDOrderQueueCallback)(OrderQueueData* res, void* user_data);

/**
* @brief 设置委托队列数据消息包回调方法
*
* @param cb             委托队列数据回调方法
* @param user_data      用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
*/
HFT_API void md_set_orderqueue_callback(MDOrderQueueCallback cb,
                                        void* user_data);

/**
* 市场日期更新回调函数定义
*
* @param res            回调的市场日期更新数据对象
* @param user_data      用户自定义参数
*/
typedef void(*MDDateUpdateCallback)(DateUpdateData* res, void* user_data);

/**
* 设置市场日期更新行情事件回调方法
*
* @param cb             市场日期更新回调方法
* @param user_data      用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
*/
HFT_API void md_set_date_update_callback(MDDateUpdateCallback cb, void* user_data);

/**
 * 行情连接状态回调函数定义
 *
 * @param conn_status   连接状态,目前状态支持"连接断开或失败"：0、"连接成功"：1
 * @param user_data     用户自定义参数
 */
typedef void (*MDStatusChangeCallback)(int conn_status, void* user_data);

/**
 * 设置行情连接状态的改变事件回调方法，目前支持"连接断开或失败"：0、"连接成功"：1
 *
 * @param cb             行情连接状态改变回调函数
 * @param user_data      用户自定义参数，与回调相关的任意类型数据，
 *                       作为回调函数参数输入
 */
HFT_API void md_set_status_change_callback(MDStatusChangeCallback cb,
                                           void* user_data);


/*************** 订阅实时行情相关接口 End *******************************/

#endif  // HFT_SDK_MD_API_H__