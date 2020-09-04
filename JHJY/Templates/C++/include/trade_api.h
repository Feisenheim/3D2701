/**
 * @file    trade_api.h
 * @brief   hftsdk 交易相关API定义
 */

#ifndef HFT_SDK_TRADE_API_H__
#define HFT_SDK_TRADE_API_H__

#include "trade_def.h"

/**
 * 批量下单，同步异步使用一个接口
 *
 * @param account_id    资金账户id
 * @param account_type  资金账户类型，见AccountType定义
 * @param orders        传入委托请求对象数组，返回后台系统生成的内部订单id
 * @param reqnum        委托请求对象个数
 * @param async         是否异步，0：同步下单(默认)，非0：异步下单(需在OrderReq明细中返回order_id)
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_order(const char* account_id, AccountType account_type,
                     OrderReq* orders, int reqnum, int async = 0);

/**
 * 逆回购下单，同步异步使用一个接口
 *
 * @param account_id    资金账户id
 * @param account_type  资金账户类型，见AccountType定义
 * @param symbol        标的代码，例如SH.204001, SZ.131810，目前仅支持1天期
 * @param price         委托价，逆回购为利率扩大1万倍
 * @param volume        委托量，单位为张，上海单笔最少1000张或是其整数倍，深圳单笔最少10张或是其整数倍
 * @param order_id      输出参数，同步下单立即返回后台系统生成的内部订单id，异步下单返回为空
 * @param length        传入的order_id内存长度
 * @param cl_order_id   NULL为同步下单，非NULL值为异步下单
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_reverse_repurchase(const char* account_id,
                                  AccountType account_type, const char* symbol,
                                  uint64_t price, int volume, char* order_id,
                                  int length, const char* cl_order_id = NULL);

/**
 * 批量撤单，支持撤销单个和多个订单，同步异步使用一个接口
 *
 * @param account_id    资金账户id
 * @param account_type  资金账户类型，见AccountType定义
 * @param order_ids     传入系统返回的订单id，格式为order1,order2,order3
 * @param cancel_list   返回的撤单详情列表，传入非NULL，表示同步请求
 * @param count         返回的撤单详情列表长度
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件
 */
HFT_API int td_cancel_order(const char* account_id, AccountType account_type,
                            const char* order_ids,
                            CancelDetail** cancel_list = NULL,
                            int* count = NULL);

/**
 * 撤销全部未完成订单，同步异步使用一个接口
 *
 * @param account_id    资金账户id
 * @param account_type  资金账户类型，见AccountType定义
 * @param trade_seqno   交易序号，即批次号。给0撤全部，给非0值撤指定批次
 * @param cancel_list   返回的撤单详情列表，传入非NULL，表示同步请求
 * @param count         返回的撤单详情列表长度
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_cancel_all_order(const char* account_id,
                                AccountType account_type, int trade_seqno = 0,
                                CancelDetail** cancel_list = NULL,
                                int* count = NULL);

/**
 * 查订单详情
 *
 * @param order_id      后台生成的订单id
 * @param ret_order     返回对应订单详情
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_order(const char* order_id, Order* ret_order);

/**
 * 查策略实例订单列表，支持分页查询
 *
 * @param page_num      page_num表示此次分页请求从哪一页开始，第一页page_num为1
 * @param page_size     输入时：分页个数，输出时：实际返回的订单个数
 *                      ***注意：返回个数小于输入的分页个数时，表示数据已经全部读取完毕***
 * @param ret_orders    返回对应订单对象数组
 * @param total_size    返回的订单列表总条数，若不传入，则不返回
 * @param begin_date    查询开始日期，如果为空或NULL，则为当前交易日，格式为2018/3/1
 * @param end_date      查询结束日期，如果为空或NULL，则为当前交易日，格式为2018/3/1
 *                      end_date必须大于等于begin_date，可以只传begin_date，不可以只传end_date
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_orders(int page_num, int* page_size, Order** ret_orders,
                          int* total_size = NULL, const char* begin_date = NULL,
                          const char* end_date = NULL);

/**
 * 查未完成订单列表，支持分页查询
 *
 * @param page_num      page_num表示此次分页请求从哪一页开始，第一页page_num为1
 * @param page_size     输入时：分页个数，输出时：实际返回的订单个数
 *                      ***注意：返回个数小于输入的分页个数时，表示数据已经全部读取完毕***
 * @param ret_orders    返回对应订单对象数组
 * @param total_size    返回的订单列表总条数，若不传入，则不返回
 * @param date          查询日期,如果为空或NULL，则为当前交易日，格式为2018/3/1
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_open_orders(int page_num, int* page_size, Order** ret_orders,
                               int* total_size = NULL, const char* date = NULL);

/**
 * 查单个订单成交列表
 *
 * @param order_id      后台系统生成的订单id
 * @param ret_trades    返回对应成交列表
 * @param ret_count     实际返回的成交个数
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_trades(const char* order_id, Trade** ret_trades,
                          int* ret_count);

/**
 * 查策略实例成交列表，支持分页查询
 *
 * @param page_num      page_num表示此次分页请求从哪一页开始，第一页page_num为1
 * @param page_size     输入时：分页个数，输出时：实际返回的成交个数
 *                      ***注意：返回个数小于输入的分页个数时，表示数据已经全部读取完毕***
 * @param ret_trades    返回对应成交列表
 * @param total_size    返回的成交列表总条数，若不传入，则不返回
 * @param begin_date    查询开始日期,如果为空或NULL，则为当前交易日，格式为2018/3/1
 * @param end_date      查询结束日期,如果为空或NULL，则为当前交易日，格式为2018/3/1
 *                      end_date必须大于等于begin_date，可以只传begin_date，不可以只传end_date
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_strategy_trades(int page_num, int* page_size,
                                   Trade** ret_trades, int* total_size = NULL,
                                   const char* begin_date = NULL,
                                   const char* end_date = NULL);

/**
 * 查策略实例指定标的持仓，可返回指定资金账号的对应标的持仓
 *
 * @param symbol        标的代码，例如SH.600000, CFFEX.IF1511
 * @param ret_positions 返回对应持仓列表
 * @param count         返回的仓位个数
 * @param account_id    资金账户id，返回指定资金账号指定标的持仓
 * @param account_type  资金账户类型，见AccountType定义
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_position(const char* symbol, Position** ret_positions,
                            int* count, const char* account_id = NULL,
                            AccountType account_type = AccountType_Placeholder);

/**
 * 查策略实例持仓列表，支持分页查询
 *
 * @param page_num      page_num表示此次分页请求从哪一页开始，第一页page_num为1
 * @param page_size     输入时：分页个数，输出时：实际返回的仓位个数
 *                      ***注意：返回个数小于输入的分页个数时，表示数据已经全部读取完毕***
 * @param ret_positions 返回对应持仓列表
 * @param total_size    返回的持仓列表总条数，若不传入，则不返回
 * @param begin_date    查询开始日期,如果为空或NULL，则为当前交易日，格式为2018/3/1
 * @param end_date      查询结束日期,如果为空或NULL，则为当前交易日，格式为2018/3/1
 *                      end_date必须大于等于begin_date，可以只传begin_date，不可以只传end_date
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_positions(int page_num, int* page_size,
                             Position** ret_positions, int* total_size = NULL,
                             const char* begin_date = NULL,
                             const char* end_date = NULL);

/**
 * 查策略实例所有资金账户的资金数据
 *
 * @param ret_cash      返回策略实例资金账户数据列表
 * @param count         返回的资金账户数据个数
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_cash(Cash** ret_cash, int* count);

/**
 * 查策略实例的收益、风险等指标
 *
 * @param ret_indicator 返回策略指定日期的实例的收益、风险指标信息
 * @param date          查询日期,如果为空或NULL，则为当前日期，格式为2018/3/1
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int td_get_indicator(Indicator* ret_indicator, const char* date = NULL);

/**
 * 成交回报事件回调类型
 *
 * @param trade         回调的成交对象
 * @param user_data     用户自定义参数
 */
typedef void (*TradeReportCallback)(const Trade* trade, void* user_data);

/**
 * 设置成交回报事件回调函数
 *
 * @param cb            回调处理函数
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void td_set_trade_report_callback(TradeReportCallback cb,
                                          void* user_data);

/**
 * 订单委托应答事件回调类型
 *
 * @param order_rsp     订单委托应答数组对象
 * @param count         订单委托应答数组个数
 * @param user_data     用户自定义参数
 */
typedef void (*OrderRspCallback)(const OrderRsp* order_rsp, int count,
                                 void* user_data);

/**
 * 设置订单委托应答事件回调函数
 *
 * @param cb            回调处理函数
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void td_set_order_rsp_callback(OrderRspCallback cb, void* user_data);

/**
 * 撤单应答事件回调类型
 *
 * @param cancel_detail 撤单应答数组对象
 * @param count         撤单应答数组个数
 * @param user_data     用户自定义参数
 */
typedef void (*CancelOrderCallback)(const CancelDetail* cancel_detail,
                                    int count, void* user_data);

/**
 * 设置撤单应答事件回调函数
 *
 * @param cb            回调处理函数
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void td_set_cancel_order_callback(CancelOrderCallback cb,
                                          void* user_data);

/**
 * 订单状态变化事件回调类型
 *
 * @param res           回调的订单对象
 * @param user_data     用户自定义参数
 */
typedef void (*OrderStatusCallback)(const Order* res, void* user_data);

/**
 * 设置订单状态变化事件回调函数
 *
 * @param cb            回调处理函数
 * @param user_data     用户自定义参数，与回调相关的任意类型数据，作为回调函数参数输入
 */
HFT_API void td_set_order_status_callback(OrderStatusCallback cb,
                                          void* user_data);

#endif  // HFT_SDK_TRADE_API_H__