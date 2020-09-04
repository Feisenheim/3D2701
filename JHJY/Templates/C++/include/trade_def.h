﻿/**
 * @file    trade_def.h
 * @brief   hftsdk 交易相关数据结构定义
 */

#ifndef HFT_SDK_TRADE_DEF_H__
#define HFT_SDK_TRADE_DEF_H__

#include "common.h"

/**
 * 市场类型名字，与行情保持一致
 */
#define MARKET_SH "SH";                 // 上海交易所
#define MARKET_SZ "SZ";                 // 深圳交易所
#define MARKET_CFFEX "CFFEX";           // 中金所
#define MARKET_CZCE "CZCE";             // 郑商所
#define MARKET_DCE "DCE";               // 大商所
#define MARKET_SHFE "SHFE";             // 上期所
#define MARKET_HK "HK";                 // 香港交易所
#define MARKET_SGE "SGE";               // 金交所
#define MARKET_CFETS "CFETS";           // 外汇交易中心
#define MARKET_SHOP "SHOP";             // 上海交易所期权
#define MARKET_SZOP "SZOP";             // 深圳交易所期权

/**
 * 订单状态定义
 */
enum OrderStatus {
  OrderStatus_PendingNew = 1,           // 订单待报
  OrderStatus_New = 2,                  // 订单已报
  OrderStatus_PartiallyFilled = 3,      // 订单部分成交
  OrderStatus_Filled = 4,               // 订单全部成交
  OrderStatus_PendingCancel = 5,        // 撤单待报
  OrderStatus_Canceling = 6,            // 已报待撤
  OrderStatus_CancelFilled = 7,         // 订单已撤销
  OrderStatus_PartiallyCanceled = 8,    // 部成部撤
  OrderStatus_Rejected = 9,             // 订单已拒绝
};

/**
* 订单类型定义
*/
enum OrderType {
  OrderType_LMT = 1,                    // 限价委托
  OrderType_BOC = 2,                    // 对手方最优价格，深圳证券交易所
  OrderType_BOP = 3,                    // 本方最优价格，深圳证券交易所
  OrderType_B5TC = 4,                   // 最优五档剩余转撤销，上海/深圳证券交易所
  OrderType_B5TL = 5,                   // 最优五档剩余转限价，上海证券交易所
  OrderType_IOC = 6,                    // 即时成交剩余转撤销，深圳证券交易所
  OrderType_AON = 7,                    // 全额成交或撤销，深圳证券交易所
};

/**
 * 买卖方向定义
 */
enum OrderSide {
  OrderSide_Bid = 1,                    // 证券、基金、债券普通买入
  OrderSide_Ask = 2,                    // 证券、基金、债券普通卖出
  OrderSide_Long_Open = 3,              // 期货、期权多头开仓
  OrderSide_Long_Close = 4,             // 期货、期权多头平仓
  OrderSide_Short_Open = 5,             // 期货、期权空头开仓
  OrderSide_Short_Close = 6,            // 期货、期权空头平仓
  OrderSide_Today_Long_Close = 8,       // 上期所期货今仓多头平仓
  OrderSide_Today_Short_Close = 10,     // 上期所期货今仓空头平仓
  OrderSide_PreDay_Long_Close = 11,     // 上期所期货昨仓多头平仓
  OrderSide_PreDay_Short_Close = 12,    // 上期所期货昨仓空头平仓
  OrderSide_Margin_Bid = 13,            // 证券、基金、债券融资买入
  OrderSide_Margin_Ask = 14,            // 证券、基金、债券融券卖出
  OrderSide_Reverse_Repurchase = 19,    // 逆回购
  OrderSide_Repurchase = 26,            // 正回购
  OrderSide_IPO_Bid = 27,               // 新股申购
  OrderSide_AHFPT_Bid = 28,             // 科创板盘后定价买入
  OrderSide_AHFPT_Ask = 29,             // 科创板盘后定价卖出
};

// 持仓类型
enum PositionSide {
  PositionSide_Long = 1,                // 多仓
  PositionSide_Short = 2,               // 空仓
};

/**
 * 成交回报类型定义
 */
enum TradeReportType {
  TradeReportType_Normal = 1,           // 普通回报
  TradeReportType_Cancel = 2,           // 撤单回报
  TradeReportType_Abolish = 3,          // 普通废单回报
  TradeReportType_InsideCancel = 4,     // 内部撤单回报，还未到交易所便被撤下来
  TradeReportType_CancelAbolish = 5,    // 撤单废单回报
};

/**
 * 资金账户类型定义
 */
enum AccountType {
  AccountType_Placeholder = 0,
  AccountType_Stock = 1,                // 股票
  AccountType_Futures = 2,              // 期货
  AccountType_Options = 3,              // 期权
  AccountType_Margin = 4,               // 融资融券
  AccountType_SHHK_Stock = 5,           // 沪港通
  AccountType_SZHK_Stock = 6,           // 深港通
  AccountType_ExtFund = 7,              // 场外基金
  AccountType_Gold = 8,                 // 黄金
  AccountType_Forex = 9,                // 外汇
};

/**
 * 撤单标识
 */
enum CancelFlag {
  CancelFlag_False = 1,                   // 假，不是撤单
  CancelFlag_True = 2,                    // 真，是撤单
};

/**
 * 交易类型定义
 */
enum CreditType {
  CreditType_Normal = 1,                // 普通交易
  CreditType_CashLoan = 2,              // 融资交易
  CreditType_SecurityLoan = 3,          // 融券交易
};

/**
 * 投机套保标识
 */
enum HedgeFlag {
  HedgeFlag_Placeholder = 0,
  HedgeFlag_Speculation = 1,          // 投机
  HedgeFlag_Hedge = 2,                // 套保
  HedgeFlag_Arbitrage = 3,            // 套利
};

/**
 * 订单数据类型
 */
typedef struct t_Order {
  char strategy_id[LEN_ID];             // 策略id
  char run_id[LEN_ID];                  // 策略运行id，代表策略的一次运行对应的id，即回测/模拟/实盘id
  char order_id[LEN_ID];                // 后台系统生成的内部订单id
  char cl_order_id[LEN_ID];             // 订单的客户方id
  char symbol[LEN_SYMBOL];              // 交易标的，格式为市场.证券ID或市场.合约ID

  char account_id[LEN_ACCOUNT_ID];      // 用户资金账户id
  int16_t account_type;                 // 用户资金账户类型

  int32_t date;                         // 订单创建日期，格式：YYYYMMDD
  int32_t trade_seqno;                  // 交易序号，即批次号
  int16_t order_status;                 // 订单状态，参考OrderStatus定义
  int16_t order_type;                   // 订单类型，参考OrderType定义
  int16_t side;                         // 买/卖，参考OrderSide定义
  int16_t credit_type;                  // 信用类型，参考CreditType定义
  int32_t volume;                       // 订单数量
  uint64_t price;                       // 订单委托价，扩大1万倍
  int32_t filled_volume;                // 订单累计已完成数量
  uint64_t filled_turnover;             // 订单累计已完成金额，扩大1万倍
  int32_t filled_price;                 // 成交均价，扩大1万倍
  int64_t filled_market_value;          // 成交合约价值，扩大1万倍
  int32_t margin_ratio;                 // 保证金比率，扩大1万倍
  int64_t marketdata_time;              // 触发订单的行情时间，精确到微秒，格式HHMMSSmmmuuu
  int64_t create_time;                  // 订单创建时间，精确到微秒，格式HHMMSSmmmuuu
  int64_t update_time;                  // 订单更新时间，精确到微秒，格式HHMMSSmmmuuu
  int64_t finish_time;                  // 订单完成时间，精确到微秒，格式HHMMSSmmmuuu

  int16_t cancel_flag;                  // 撤单标识，参考CancelFlag定义
  int32_t cancel_volume;                // 撤单量
  int32_t cancel_cnt;                   // 撤单次数
  HedgeFlag hedge_flag;                 // 组合投机套保标志，用于期货交易
  char comb_id[LEN_COM_ID];             // 组合投机套保编号，用于期货交易
  char plate[LEN_PLATE];                // 期权交易板块

  int32_t err_code;                     // 订单委托错误码
  char err_msg[LEN_ERR_MSG];            // 订单委托错误消息
} Order;

/**
 * 批量下单使用的订单请求类型
 */
typedef struct t_OrderReq {
  char order_id[LEN_ID];                // 后台系统生成的内部订单id，接口返回时填上
  char cl_order_id[LEN_ID];             // 订单的客户方id，异步下单时用户需要填上唯一id，以便委托响应时区分
  char symbol[LEN_SYMBOL];              // 交易标的，格式为市场.证券ID或市场.合约ID

  int16_t order_type;                   // 订单类型，参考OrderType定义
  int16_t side;                         // 买/卖，参考OrderSide定义
  int32_t volume;                       // 订单数量
  uint64_t price;                       // 订单委托价，限价单使用，市价填写0，扩大1万倍
  int16_t hedge_flag;                   // 期货投机、套利、套保标志，参考HedgeFlag定义
  char ext_info[LEN_EXT_INFO];          // 委托需要带入的扩展信息，格式为：key1=v1&key2=v2
                                        // 目前支持的key有comb_id（UFX期货组合编号），plate（期权板块）
} OrderReq;

/**
 * 成交数据类型
 */
typedef struct t_Trade {
  char strategy_id[LEN_ID];             // 策略ID
  char run_id[LEN_ID];                  // 策略运行id，代表策略的一次运行对应的id，即回测/模拟/实盘id
  char order_id[LEN_ID];                // 后台系统生成的内部订单id
  char cl_order_id[LEN_ID];             // 订单的客户方id
  char symbol[LEN_SYMBOL];              // 交易标的，格式为市场.证券ID或市场.合约ID
  char account_id[LEN_ACCOUNT_ID];      // 用户资金账户id
  int16_t account_type;                 // 用户资金账户类型
  int32_t date;                         // 成交日期，格式：YYYYMMDD
  int32_t trade_seqno;                  // 交易序号，即批次号
  int16_t side;                         // 买/卖，参考OrderSide定义
  int16_t order_type;                   // 订单类型，参考OrderType定义
  int16_t exec_type;                    // 成交回报类型
  char exec_id[LEN_ID];                 // 成交回报编号
  int32_t volume;                       // 成交数量
  uint64_t price;                       // 成交价格，扩大1万倍
  uint64_t turnover;                    // 成交金额，扩大1万倍
  int64_t market_value;                 // 成交合约市值，扩大1万倍
  uint64_t order_price;                 // 委托价格，扩大1万倍
  int32_t order_volume;                 // 委托数量
  int64_t transact_time;                // 成交时间，精确到微秒，格式HHMMSSmmmuuu
} Trade;

/**
 * 仓位数据类型
 */
typedef struct t_Position {
  char strategy_id[LEN_ID];             // 策略ID
  char run_id[LEN_ID];                  // 策略运行id，代表策略的一次运行对应的id，即回测/模拟/实盘id
  char account_id[LEN_ACCOUNT_ID];      // 用户资金账户id
  int16_t account_type;                 // 用户资金账户类型
  char symbol[LEN_SYMBOL];              // 持仓标的，格式为市场.证券ID或市场.合约ID
  int16_t side;                         // 持仓方向，参考PositionSide定义
  int32_t volume;                       // 总仓量
  int32_t avail_volume;                 // 可用仓量
  int32_t frozen_volume;                // 冻结仓量
  int32_t today_volume;                 // 今仓总量
  int32_t today_frozen_volume;          // 今仓冻结量
  int32_t today_avail_volume;           // 今仓可用量
  int32_t yesterday_volume;             // 昨仓总量
  int32_t yesterday_frozen_volume;      // 昨仓冻结量
  int32_t yesterday_avail_volume;       // 昨仓可用量
  uint32_t avg_cost;                    // 开仓均价，扩大1万倍
  uint32_t hold_cost;                   // 持仓均价，扩大1万倍
  int32_t create_day;                   // 初始建仓日期，格式：YYYYMMDD
  int32_t update_day;                   // 仓位变更日期，格式：YYYYMMDD
  int64_t create_time;                  // 初始建仓时间，精确到微秒，格式HHMMSSmmmuuu
  int64_t update_time;                  // 仓位变更时间，精确到微秒，格式HHMMSSmmmuuu
} Position;

/**
 * 风险收益指标数据类型
 */
typedef struct t_Indicator {
  char run_id[LEN_ID];                  // 策略运行id，代表策略的一次运行对应的id，即回测/模拟/实盘id

  int32_t date;                         // 日期
  int32_t win_count;                    // 盈利次数
  int32_t lose_count;                   // 亏损次数

  double algorithm_return;              // 策略收益率
  double annual_algo_return;            // 策略年化收益率
  double benchmark_return;              // 基准收益率
  double algorithm_volatility;          // 策略波动率
  double benchmark_volatility;          // 基准波动率
  double alpha;                         // Alpha值，表示投资者获得与市场波动无关的回报
  double beta;                          // Beta值，表示投资的系统性风险，反映了策略对大盘变化的敏感性
  double sharpe;                        // 夏普比率，表示每承受一单位总风险，会产生多少的超额报酬，可以同时对策略的收益与风险进行综合考虑
  double sortino;                       // 索提诺比率，表示每承担一单位的下行风险，将会获得多少超额回报
  double information;                   // 信息比率，衡量单位超额风险带来的超额收益
  double win_ratio;                     // 胜率
  double day_win_ratio;                 // 日胜率
  double max_drawdown;                  // 最大回撤
} Indicator;

/**
 * 资金数据类型
 */
typedef struct t_Cash {
  char account_id[LEN_ACCOUNT_ID];      // 用户资金账户id
  int16_t account_type;                 // 用户资金账户类型
  int64_t start_cash;                   // 初始资金
  int64_t cash;                         // 当前资金
  int64_t avail_cash;                   // 可用资金
  int64_t locked_cash;                  // 冻结资金
  int64_t turnover;                     // 累计交易额
  int64_t today_turnover;               // 今日交易额
  int64_t today_close_value;            // 今日卖出券获取的资金额
  int64_t update_time;                  // 帐户更新时间戳
} Cash;

/**
 * 订单委托应答详情
 */
typedef struct t_OrderRsp {
  char order_id[LEN_ID];                // 后台系统生成的内部订单id
  char cl_order_id[LEN_ID];             // 订单的客户方id
  int32_t err_code;                     // 委托错误码
  char err_msg[LEN_ERR_MSG];            // 委托错误消息
} OrderRsp;

/**
 * 撤单详情
 */
typedef struct t_CancelDetail {
  char order_id[LEN_ID];                // 后台系统生成的内部订单id
  char cancel_order_id[LEN_ID];         // 订单对应的撤单委托id
  int32_t err_code;                     // 撤单错误码
  char err_msg[LEN_ERR_MSG];            // 撤单错误消息
} CancelDetail;

#endif  // HFT_SDK_TRADE_DEF_H__
