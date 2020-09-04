/**
 * @file    error.h
 * @brief   hftsdk 错误码定义
 */

#ifndef HFT_SDK_ERROR_H__
#define HFT_SDK_ERROR_H__

#define HFT_SDK_ERRNO_MAP(XX)                                                  \
    XX(SUCCESS, 0, "成功")                                                     \
                                                                               \
    /* OMS错误码  2000~2999 */                                              \
    XX(OMS_MODULE_ERROR_CODE, 2000, "OMS错误码")                               \
    XX(OMS_MEMDB_FAILURE, 2101, "内存数据库操作失败")                          \
    XX(OMS_MEMDB_NOT_INITIALIZED, 2102, "内存数据库未初始化")                  \
    XX(OMS_MEMDB_CLOSEDB_ERROR, 2103, "内存数据库关闭失败")                    \
    XX(OMS_MEMDB_NOT_FOUND, 2104, "内存数据库找不到数据")                      \
    XX(OMS_MEMDB_EXISTED, 2105, "数据库表项已存在")                            \
    XX(OMS_MEMDB_ERROR_INSERT, 2106, "数据库插入失败")                         \
    XX(OMS_MEMDB_ERROR_UPDATE, 2107, "数据库更新失败")                         \
    XX(OMS_BIZ_FAILURE, 2201, "OMS业务失败")                                   \
    XX(OMS_BIZ_SERIALIZE_ERROR, 2202, "消息序列化失败")                        \
    XX(OMS_BIZ_PARSE_ERROR, 2203, "pb消息无法反序列化")                        \
    XX(OMS_BIZ_HTPP_MSGTYPE_INVALID, 2204, "HTPP消息类型错误")                 \
    XX(OMS_BIZ_NO_IN_PARAM, 2205, "没有固定入参")                              \
    XX(OMS_BIZ_NO_OUT_PARAM, 2206, "没有固定出参")                             \
    XX(OMS_BIZ_NO_SESSION_ID, 2207, "没有会话ID")                              \
    XX(OMS_BIZ_NO_SYS_ACCOUNT_ID, 2208, "没有系统账户ID")                      \
    XX(OMS_BIZ_NO_RUN_ID, 2209, "没有运行ID")                                  \
    XX(OMS_BIZ_NO_ACCOUNT_ID, 2210, "没有账户ID")                              \
    XX(OMS_BIZ_ERROR_FID, 2211, "错误的FID")                                   \
    XX(OMS_BIZ_NO_CASH_DETAILS, 2212, "初始化时没有资金列表")                  \
    XX(OMS_BIZ_DB_OPERATION_ERROR, 2213, "数据库操作失败")                     \
    XX(OMS_BIZ_FUND_SIDE_INVALID, 2214, "资金出入方向错误")                    \
    XX(OMS_BIZ_FUND_NOT_ENOUGH, 2215, "资金不足以划出")                        \
    XX(OMS_BIZ_MONEY_NOT_ENOUGH, 2216, "钱不够")                               \
    XX(OMS_BIZ_VOLUME_NOT_ENOUGH, 2217, "券不够")                              \
    XX(OMS_BIZ_CANCEL_STATUS_ERROR, 2218, "撤单的订单状态不对，不能撤单")      \
    XX(OMS_BIZ_ORDER_ERROR, 2219, "柜台返回委托应答失败")                      \
    XX(OMS_BIZ_CANCEL_ERROR, 2220, "柜台返回撤单应答失败")                     \
    XX(OMS_BIZ_EXORDER_NOT_FOUND, 2221,                                        \
       "先收到了成交应答，没有收到委托应答，找不到量化后台委托号")             \
    XX(OMS_BIZ_ZERO_DIVISOR, 2222, "除数为0")                                  \
    XX(OMS_BIZ_NO_SUBSCRIBER, 2223, "没有订阅推送消息")                        \
    XX(OMS_BIZ_ERROR_PAGE_NUM, 2224, "错误的页码")                             \
    XX(OMS_BIZ_ERROR_PAGE_SIZE, 2225, "错误的页大小，为0或是大于最大查询数")   \
    XX(OMS_BIZ_ERROR_QUERY_DATE, 2226, "查询起止日期错误")                     \
    XX(OMS_BIZ_ERROR_INVALID_MAC, 2227, "MAC地址错误")                         \
    XX(OMS_BIZ_NO_ORDER_DETAIL, 2228, "没有委托信息")                          \
    XX(OMS_BIZ_INVALID_MARKET, 2229, "标的市场错误")                           \
    XX(OMS_BIZ_NO_PRODUCT_ID, 2230, "标的代码为空")                            \
    XX(OMS_BIZ_INVALID_PRICE, 2231, "委托价格非法")                            \
    XX(OMS_BIZ_INVALID_QTY, 2232, "委托量非法")                                \
    XX(OMS_BIZ_INVALID_SIDE, 2233, "委托方向非法(非买/卖)")                    \
    XX(OMS_BIZ_NO_ORDER_IDS, 2234, "没有委托单号")                             \
    XX(OMS_BIZ_NO_ORDER_ID, 2235, "委托单号为空")                              \
    XX(OMS_BIZ_NO_EX_ORDER_ID, 2236, "柜台的委托应答中没有柜台ID")             \
    XX(OMS_BIZ_INVALID_MATCH_TYPE, 2237, "成交类型非法")                       \
    XX(OMS_BIZ_INVALID_POSITION_SIDE, 2238, "仓位方向非法(非多非空)")          \
    XX(OMS_BIZ_NO_ORDER, 2239, "没有该笔委托记录")                             \
    XX(OMS_BIZ_ORDER_TABLE_ERROR, 2240,                                        \
       "委托表存在问题，出现了两笔以上的委托")                                 \
    XX(OMS_BIZ_FUTURE_CLOSE_VOLUME_NOT_ENOUGH, 2241, "期货平仓仓位不够")       \
    XX(OMS_BIZ_FUTURE_CLOSE_TODAY_VOLUME_NOT_ENOUGH, 2242,                     \
       "期货平今仓仓位不够")                                                   \
    XX(OMS_BIZ_FUTURE_CLOSE_PREDAY_VOLUME_NOT_ENOUGH, 2243,                    \
       "期货平昨仓仓位不够")                                                   \
    XX(OMS_BIZ_MARGIN_NOT_FOUND, 2244, "保证金率未设置")                       \
    XX(OMS_BIZ_MARGIN_LONG_NOT_FOUND, 2245, "多头保证金率未设置")              \
    XX(OMS_BIZ_MARGIN_SHORT_NOT_FOUND, 2246, "空头保证金率未设置")             \
    XX(OMS_BIZ_FUND_TOO_BIG, 2247, "金额过大")                                 \
    XX(OMS_BIZ_FUND_IS_NEGATIVE, 2248, "金额为负数")                           \
    XX(OMS_BIZ_NO_CONTRACT_MULTIPLY, 2249, "没有合约乘数")                     \
    XX(OMS_BIZ_NOT_OPENNING, 2250, "非交易时间段")                             \
    XX(OMS_BIZ_ERROR_POSITION_VOLUME, 2251, "初始化时持仓数量非法")            \
    XX(OMS_BIZ_NOT_ACCOUNT_ORDERS, 2252, "非该账户的委托")                     \
    XX(OMS_BIZ_NOT_RUN_ID_ORDERS, 2253, "非该实例的委托")                      \
    XX(OMS_BIZ_CANNOT_IDENTIFY_SEC_TYPE, 2254, "无法识别证券类型")             \
    XX(OMS_BIZ_NOT_FUTURE, 2255, "不是期货")                                   \
    XX(OMS_BIZ_PRODUCT_ACCOUNTTYPE_ORDERSIDE_NOT_MATCH, 2256,                  \
       "标的类型,账户和委托方向不匹配")                                        \
    XX(OMS_BIZ_INVALID_ORDER_TYPE, 2257, "非法的委托类型")                     \
    XX(OMS_BIZ_ORDER_IS_TERMINAL, 2258, "该委托已结束")                        \
    XX(OMS_BIZ_OUT_UP_DOWN_LIMITE, 2259, "超过涨跌停价")                       \
    XX(OMS_BIZ_SELF_MATCHED_ORDER, 2260, "不得对敲")                           \
    XX(OMS_BIZ_NOT_INITIALIZED, 2270, "OMS未初始化完成")                       \
    XX(OMS_BIZ_INSTANCE_EXIST, 2271, "实例已存在，不得再次初始化")             \
    XX(OMS_BIZ_IN_BLACK_LIST, 2272, "在证券黑名单中")                          \
                                                                               \
    /* Manager错误码  3000-3999 */                                          \
    XX(ERR_PARSE_FAILED, 3000, "PB解析失败")                                   \
    XX(ERR_MSMTYPE_ID, 3001, "无效功能号")                                     \
    XX(ERR_INIT_DB, 3002, "初始化内存数据库失败")                              \
    XX(ERR_MEMDB_NOT_INIT, 3003, "内存数据库没有初始化操作")                   \
    XX(ERR_WRONG_FID, 3004, "错误的fid")                                       \
    XX(ERR_NO_RECORD, 3005, "没有记录")                                        \
    XX(ERR_PAGE_NUM_PAGE_SIZE, 3006, "page_num和page_size的值必须大于1. ")     \
    XX(ERR_EMPTY_MOBILE, 3007, "手机号不能为空")                               \
    XX(ERR_NO_AUTHENTICATION, 3008,                                            \
       "找不到登陆信息，可能后台服务重启，请重新登陆一次")                     \
    XX(ERR_NOT_FOUND_CPU_DISK_SEQNO, 3009,                                     \
       "没有找到cpu_serial_no和disk_serial_no相关信息，可能传的值不对")        \
    XX(ERR_CLOUD_LOGINOUT, 3010, "云机登出失败，可能没有登陆过")               \
    XX(ERR_NO_CLOUD_LOGIN, 3011, "请先做云机登陆")                             \
    XX(ERR_PARAMS, 3012, "参数错误")                                           \
    XX(ERR_EMPTY_STRATEGY_ID, 3013, "策略ID是空的")                            \
    XX(ERR_NOT_FOUND_MAC_DISK_SEQNO, 3014,                                     \
       "没有找到mac_address和disk_serial_no相关信息，请确认传值是否正确!")     \
    XX(ERR_EMPTY_MAC_ADDRESS, 3015, "mac_address不能是空的")                   \
    XX(ERR_EMPTY_CPU_SERIAL_NO, 3016, "cpu_serial_no不能是空的")               \
    XX(ERR_EMPTY_DISK_SERIAL_NO, 3017, "disk_serial_no不能是空的")             \
    XX(ERR_EMPTY_IN_PARAM, 3018, "in_param成员缺失")                           \
    XX(ERR_EMPTY_STKTYPE_OR_MARKET, 3019, "证券类型和市场类型不能同时为空")    \
    XX(ERR_DB_OPT_TYPE, 3020, "数据库操作标志只支持添加或删除")                \
    XX(ERR_EMPTY_BLACK_LIST, 3021, "黑名单列表为空")                           \
    XX(ERR_STKCODE_TOO_LONG, 3022, "证券代码太长")                             \
    XX(ERR_STKCODE_ALREADY_EXIST, 3023, "证券代码已经存在")                    \
    XX(ERR_STKCODE_NOT_EXIST, 3024, "证券代码不存在")                          \
    XX(ERR_INSERT_STK_BLACK_LIST, 3025, "插入证券代码失败")                    \
    XX(ERR_UPDATE_STK_BLACK_LIST, 3026, "更新证券代码失败")                    \
    XX(ERR_DB_SELECT_FAILED, 3199, "数据库查询失败")                           \
    XX(ERR_STRATEGY_ID, 3200, "策略id可能不正确")                              \
    XX(ERR_WRONG_RUN_MODE, 3201, "策略运行模式不正确")                         \
    XX(ERR_RUN_MODE_VALUE, 3202, "运行模式错误")                               \
    XX(ERR_RUN_ID_VALUE, 3203, "实例ID不能为空")                               \
    XX(ERR_EMPTY_STRATEGY_OR_RUN_ID, 3204, "错误的策略ID或实例ID为空，请确认") \
    XX(ERR_INSERT_STRATEGY, 3205, "保存策略ID失败")                            \
    XX(ERR_INSERT_LIVETRADE, 3206, "插入实例表失败")                           \
    XX(ERR_INSTANCE_ALREADY_RUNED, 3207, "策略的实例已经运行过不能被删除")     \
    XX(ERR_DELETE_STRATEGY_FAILED, 3208, "删除策略失败")                       \
    XX(ERR_STRATEGY_ID_EMPTY, 3209, "策略ID不能为空")                          \
    XX(ERR_STRATEGY_ID_A_RUN_ID_EMPTY, 3210, "策略ID和实例ID不能同时为空")     \
    XX(ERR_UPDATE_LIVETRADE_FAILED, 3211, "更新实例表失败")                    \
    XX(ERR_INSTANCE_HIS_RUN, 3212, "实例已经运行过不能被删除")                 \
    XX(ERR_UPDATE_INSTANCE_STATUS, 3213, "更新实例状态失败")                   \
    XX(ERR_WRONG_INSTANCE_STATUS, 3214, "错误的实例状态")                      \
    XX(ERR_NOT_FOUND_STRATEGY, 3215, "没找到策略ID对应的策略信息")             \
    XX(ERR_OVER_MAX_INSTANCE_NUM, 3216, "超过最大可创建实例个数")              \
    XX(ERR_EXIST_INVAILD_ACCOUNT, 3217, "存在非法帐号")                        \
    XX(ERR_EXIST_RUNNING_RUN_ID, 3218, "运行中的实例不能删除")                 \
    XX(ERR_RUN_ID_NOT_FOUND, 3299, "实例ID不存在，即未能在实例表时找到")       \
    XX(ERR_EXIST_SYS_ID, 3300, "系统帐号已经存在")                             \
    XX(ERR_ALREADY_LOCKED, 3301, "资金账号绑定失败，原因是该资金帐号被锁定")   \
    XX(ERR_ALREADY_FROZEN, 3302, "资金账户绑定失败，原因是该资金帐号被冻结")   \
    XX(ERR_NOT_EXIST_SYS_ID, 3303, "系统帐号不存在")                           \
    XX(ERR_ALREADY_BIND, 3304,                                                 \
       "资金帐号绑定失败，原因是该资金帐号已经被绑定过")                       \
    XX(ERR_BIND_FLAG, 3305, "资金帐号绑定失败，原因是绑定标志错误")            \
    XX(ERR_ACCOUNT_TYPE, 3306, "资金帐号类型错误")                             \
    XX(ERR_ALREADY_UNBIND, 3307,                                               \
       "资金帐号解绑失败， 原因是未找到该资金帐号的绑定信息")                  \
    XX(ERR_DEL_SYS_ACCOUNT, 3308, "删除系统帐号绑定信息出错")                  \
    XX(ERR_INSERT_SYS_ACCOUNT, 3309, "插入系统帐号绑定信息失败")               \
    XX(ERR_EMPTY_SYS_ACCOUNT, 3310, "系统帐号ID不能为空")                      \
    XX(ERR_NOT_STOCK_ACCOUNT, 3311, "第一次资金帐号登陆必须是股票帐号")        \
    XX(ERR_ACCOUNT_TYPE_PK, 3312, "这个资金帐号类型已经绑定过了")              \
    XX(ERR_LAST_ACCOUNT, 3313, "最后一个帐号不能被解绑")                       \
    XX(ERR_NOT_IMPLEMENT_ACCOUNT_TYPE, 3314,                                   \
       "这种类型的资金帐号的绑定还未实现")                                     \
    XX(ERR_UNKNOWN_ACCOUNT_TYPE, 3315, "未知的资金帐号类型")                   \
    XX(ERR_LOGIN_TYPE, 3316, "错误的资金帐号类型")                             \
    XX(ERR_EMPTY_ACCOUNT, 3317, "资金帐号、资金帐号类型必填")                  \
    XX(ERR_NOT_FOUND_SYS_ID, 3318, "找不到系统帐号")                           \
    XX(ERR_NOT_FOUND_XT_ACCT, 3319, "没找到迅投帐号")                          \
    XX(ERR_ACCOUNT_HAS_SYS_ID, 3320,                                           \
       "被绑定的资金帐号存在系统帐号，如果要作绑定，请先注销该资金帐号")       \
    XX(ERR_LOGINOUT_SYS_ACCOUNT, 3321, "注销资金帐号的系统帐号失败")           \
    XX(ERR_NOT_WHITE_LIST, 3322, "该帐号禁止登陆，请先授权")                   \
    XX(ERR_OVER_LOGIN_ERR_TIMES, 3323, "登陆失败次数已经达到上限")             \
    XX(ERR_MAC_NO_AUTHORITY, 3324, "MAC地址未授权")                            \
    XX(ERR_EMPTY_CUST_ORG_ID, 3325, "营业部代码不能为空")                      \
    XX(ERR_NOT_NET_SIGN, 3326, "未完成网签,请先作网签业务")                    \
    XX(ERR_BIND_FLAG_VALUE, 3399, "错误的绑定标志")                            \
                                                                               \
    /* 行情服务错误码  7000~7999 */                                     \
    XX(ERR_MSG_UNKNOWN, 7000, "未知系统错误")                                  \
    XX(ERR_KDC_ARGS, 7001, "历史行情请求参数错误")                             \
    XX(ERR_KDC_MKPKG, 7002, "历史行情打包报文错误")                            \
    XX(ERR_KDC_CHANNEL, 7003, "历史行情通道错误，到服务器的连接通道不可用")    \
    XX(ERR_KDC_GETPKG, 7004, "历史行情get报文错误")                            \
    XX(ERR_KDC_PARSEPKG, 7005, "历史行情解包报文错误")                         \
    XX(ERR_KDC_SERVER, 7006, "历史行情服务方错误")                             \
    XX(ERR_KDC_BREAKBYUSER, 7007, "历史行情用户中断")                          \
    XX(ERR_KDC_FAILED, 7008, "历史行情应用层失败，服务方服务失败")             \
    XX(ERR_KDC_HANDLE, 7009, "历史行情错误的客户端handle")                     \
    XX(ERR_KDC_CONNECT, 7010, "历史行情服务连接失败")                          \
    XX(ERR_KDC_TIMEOUT, 7011, "历史行情请求超时")                              \
    XX(ERR_SIPE_ERRHANDLE, 7012, "实时行情错误的客户端handle")                 \
    XX(ERR_SIPE_TCPCONNECTERR, 7013, "实时行情TCP连接错误")                    \
    XX(ERR_SIPE_PROXY_CONNECTERR, 7014, "实时行情代理连接错误")                \
    XX(ERR_SIPE_PROXY_AUTHERR, 7015, "实时行情代理验证错误")                   \
    XX(ERR_SIPE_DISCONNECT, 7016, "实时行情连接断开")                          \
    XX(ERR_SIPE_TCPIOERR, 7017, "实时行情TCP IO错误")                          \
    XX(ERR_SIPE_TIMEOUT, 7018, "实时行情连接超时")                             \
    XX(ERR_SIPE_VERSION, 7019, "实时行情版本错误")                             \
    XX(ERR_SIPE_NOUSER, 7020, "实时行情无此账号")                              \
    XX(ERR_SIPE_USERAUTH, 7021, "实时行情用户验证错误")                        \
    XX(ERR_SIPE_SUBSCRIBETAG, 7022, "实时行情订阅标签错误")                    \
    XX(ERR_SIPE_CONNECT_FAILED, 7023, "实时行情连接失败")                      \
                                                                               \
    /* 交易API错误码 8000~8999 */                                         \
    XX(ERR_TD_INTERNAL, 8000, "系统内部错误")                                  \
    XX(ERR_TD_INVALID_PARAM, 8001, "参数非法")                                 \
    XX(ERR_TD_NETWORK_TIMEOUT, 8002, "网络超时")                               \
    XX(ERR_TD_NETWORK_SEND_FAIL, 8003, "消息发送失败")                         \
    XX(ERR_TD_INVALID_PKG, 8004, "非法协议包")                                 \
    XX(ERR_TD_PACK_FAIL, 8005, "打包失败")                                     \
    XX(ERR_TD_UNPACK_FAIL, 8006, "解包失败")                                   \
    XX(ERR_TD_NO_MEM, 8007, "内存不够")                                        \
    XX(ERR_TD_INVALID_SYMBOL, 8008, "非法标的ID")                              \
    XX(ERR_TD_INIT_ERROR, 8009, "交易服务内部初始化错误")                      \
    XX(ERR_TD_NOT_CONNECT, 8010, "交易服务未连接")                             \
    XX(ERR_TD_LOGIN_FAIL, 8011, "资金账户登录失败")                            \
    XX(ERR_TD_NOT_INIT, 8012, "交易服务未初始化")                              \
    XX(ERR_TD_NO_DATA, 8013, "没有数据")                                       \
    XX(ERR_TD_SUBSCRIBE_REPORT, 8014, "订阅委托和成交回报失败")                \
    XX(ERR_TD_INVALID_ACCOUNT, 8015, "交易账号相关字段非法")                   \
                                                                               \
    /* 策略模板 9000~9999 */                                               \
    XX(ERR_LIB_INTERNAL, 9000, "系统内部错误")                                 \
    XX(ERR_LIB_INVALID_PARAM, 9001, "请求参数非法")                            \
    XX(ERR_LIB_INVALID_STATE, 9002, "非法的当前状态")                          \
    XX(ERR_LIB_TIMEOUT, 9003, "操作超时")                                      \
    XX(ERR_LIB_SEND_FAIL, 9004, "消息发送失败")                                \
    XX(ERR_LIB_INVALID_PKG, 9005, "非法协议包")                                \
    XX(ERR_LIB_PACK_FAIL, 9006, "打包失败")                                    \
    XX(ERR_LIB_UNPACK_FAIL, 9007, "解包失败")                                  \
    XX(ERR_LIB_NO_MEM, 9008, "内存不够")                                       \
    XX(ERR_LIB_LOGIN_FAIL, 9009, "网关登录失败")                               \
    XX(ERR_LIB_LOAD_CONFIG_FAIL, 9010, "加载配置文件失败")                     \
    XX(ERR_LIB_LOAD_MD_LIB_FAIL, 9011, "加载行情动态库失败")                   \
    XX(ERR_LIB_LOAD_TD_LIB_FAIL, 9012, "加载交易动态库失败")                   \
    XX(ERR_LIB_TERM, 9013, "策略库已退出")                                     \
    XX(ERR_LIB_RUN_MODE_NOT_SUPPORTED, 9014,                                   \
       "配置文件或客户端设置的run_mode不支持")                                 \
    XX(ERR_LIB_LOCAL_DB_OP_FAIL, 9015, "操作本地数据库失败")                   \
    XX(ERR_LIB_INVALID_DATE_TIME_FORMAT, 9016, "时间格式不对")                 \
    XX(ERR_LIB_LARGER_THAN_BACKTEST_CUR_TIME, 9017,                            \
       "时间超过当前回测时间，回测时不能使用未来数据")                         \
    XX(ERR_LIB_INVALID_ACCOUNT_LIST, 9018, "策略使用的资金账号列表不能为空")   \
    XX(ERR_LIB_CONVERT_CHAR_ENCODING_FAIL, 9019, "字符编码转换失败")

typedef enum {
#define XX(name, code, _) name = code,
    HFT_SDK_ERRNO_MAP(XX)
#undef XX
} HFT_SDK_ERROR;

#endif  // HFT_SDK_ERROR_H__
