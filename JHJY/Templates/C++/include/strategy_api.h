/**
 * @file    strategy_api.h
 * @brief   hftsdk 策略运行相关API定义
 */

#ifndef HFT_SDK_STRATEGY_API_H__
#define HFT_SDK_STRATEGY_API_H__

#include "common.h"

/**
 * 策略日志级别定义
 */
enum StrategyLogLevel {
  StrategyLogLevel_Debug = 1,   /// 调试日志
  StrategyLogLevel_Info,        /// 信息日志
  StrategyLogLevel_Warn,        /// 警告日志
  StrategyLogLevel_Error        /// 错误日志
};

/**
 * 策略退出原因定义
 */
enum StrategyExitReason {
  StrategyExitReason_Api = 0,         /// 调用退出API
  StrategyExitReason_Client,          /// 客户端请求退出
  StrategyExitReason_Error,           /// 发生错误，退出执行
  StrategyExitReason_BacktestFinish,  /// 回测结束，退出执行
  StrategyExitReason_AutoExit,        /// 策略到达事先设置的自动退出时间，自动退出
};

/**
 * 策略执行状态定义
 */
enum StrategyExecStatus {
  StrategyExecStatus_Ok = 0,        /// 策略正常执行
  StrategyExecStatus_Initializing,  /// 策略库初始化中
  StrategyExecStatus_LineError,     /// 行情或交易线路出现异常
  StrategyExecStatus_Term,          /// 策略已退出执行
};

/**
 * 策略执行模式定义
 */
enum StrategyExecMode {
  StrategyExecMode_Backtest = 1,    /// 回测
  StrategyExecMode_Emulate = 2,     /// 模拟
  StrategyExecMode_LiveTrade = 3,   /// 实盘
};


/**
 * 读取策略配置文件，初始化策略API接口。
 * 
 * @param config_dir    策略配置文件目录，默认是当前可执行程序目录，编码为utf8
 * @param log_dir       策略日志文件目录，默认是当前可执行程序目录，编码为utf8
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_init(const char* config_dir = nullptr,
                          const char* log_dir = nullptr);

/**
 * 创建策略配置参数字典，用来保存策略初始化配置参数。
 *
 * @return              返回策略配置参数字典
 */
HFT_API void* strategy_config_dict_create();

/**
 * 销毁策略配置参数字典。
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_config_dict_destroy(void* config_dict);

/**
 * 向策略配置参数字典写入给定配置参数。
 *
 * @param name          配置参数名
 * @param value         配置参数值
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_config_dict_set_param(
    void* config_dict, const char* name, const char* value);

/**
 * 使用给定的配置参数字典初始化策略API接口。
 *
 * @param config_dict   策略配置参数字典
 * @param log_dir       策略日志文件目录，默认是当前可执行程序目录，编码为utf8
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_init_with_config_dict(
    void* config_dict, const char* log_dir = nullptr);

/**
 * 退出并停止策略运行。该函数调用后strategy_run接口将退出运行。
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_exit();

/**
 * 策略退出事件回调函数定义。
 *
 * @param reason        退出原因
 * @param user_data     用户自定义参数
 */
typedef void (*StrategyExitCallback)(int reason, void* user_data);

/**
 * 设置策略退出事件回调函数
 *
 * @param cb            策略退出事件回调方法
 * @param user_data     用户自定义参数
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_set_exit_callback(StrategyExitCallback cb,
                                       void* user_data);

/**
 * 定时器回调方法定义。
 *
 * @param interval      定时器触发间隔(毫秒)，精确到毫秒
 * @param user_data     用户自定义参数
 */
typedef void (*StrategyTimerCallback)(int interval, void* user_data);

/**
 * 设置定时器回调方法
 *
 * @param cb            定时器回调方法
 * @param user_data     用户自定义参数
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_set_timer_callback(StrategyTimerCallback cb,
                                        void* user_data);

/**
 * 设置定时器触发时间间隔。
 *
 * @param interval      定时器触发间隔(毫秒)，精确到毫秒
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_set_timer(int interval);

/**
 * 取消指定时间间隔定时器。
 *
 * @param interval      定时器触发间隔(毫秒)，精确到毫秒
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_clear_timer(int interval);

/**
 * 交易日定时任务回调方法定义。
 *
 * @param time          定时任务执行时间: HHMMSS，精确到秒
 * @param user_data     用户自定义参数
 */
typedef void (*StrategyDayScheduleTaskCallback)(int time, void* user_data);

/**
 * 设置交易日定时任务回调方法
 *
 * @param cb            交易日定时任务回调方法
 * @param user_data     用户自定义参数
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_set_day_schedule_task_callback(
    StrategyDayScheduleTaskCallback cb, void* user_data);

/**
 * 设置给定时间执行的交易日定时任务。
 *
 * @param time          定时任务执行时间: HHMMSS，精确到秒
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_set_day_schedule_task(int time);

/**
 * 取消指定执行时间的交易日定时任务。
 *
 * @param time          定时任务执行时间: HHMMSS，精确到秒
 *
 * @return              成功返回0，失败返回错误码，错误码定义在error.h文件中
 */
HFT_API int strategy_clear_day_schedule_task(int time);

/**
* 策略参数设置回调方法定义。
*
* @param params_json   策略参数(json字符串格式)
* @param user_data     用户自定义参数
*/
typedef void (*StrategyParamsSettingCallback)(
    const char* params_json, void* user_data);

/**
 * 设置策略参数设置回调方法。
 *
 * @param cb            策略参数设置回调方法
 * @param user_data     用户自定义参数
 */
HFT_API int strategy_set_params_setting_callback(
    StrategyParamsSettingCallback cb, void* user_data);

/**
 * 报告策略参数。
 * 一般在策略启动时通过该API向客户端报告策略运行参数，
 * 设置一次即可，策略运行过程中可通过客户端修改运行参数，
 * 更新后的参数存在内存中，不落地磁盘
 *
 * @param params_json   策略参数(json字符串格式)
 */
HFT_API int strategy_report_params(const char* params_json);

/**
 * 报告自定义策略指标。
 * 可以在策略运行过程中实时通过该接口向客户端报告自定义策略指标，
 * 通过客户端界面查看当前的策略指标数据。
 *
 * @param params_json   策略指标(json字符串格式)
 */
HFT_API int strategy_report_indexes(const char* indexes_json);

/**
 * 同步模式下: 调用接口的线程阻塞执行策略事件循环，直到策略正常退出或者异常终止。
 *             所有策略回调函数(包括行情，交易接口回调)都会在调用线程中调用。
 * 异步模式下: 开启单独的线程执行策略事件循环，直到策略正常退出或者异常终止。
 *             所有策略回调函数(包括行情，交易接口回调)都会在新开启线程中调用。
 *
 * @param async         0 - 同步模式, 非0 - 异步模式
 *
 * @return              正常退出返回0，异常退出返回错误码，
 *                      错误码定义在error.h文件中
 */
HFT_API int strategy_run(int async = 0);

/**
 * 执行一次策略事件处理循环。
 *
 * @param timeout       等待下一个事件超时时间(毫秒)。
 *                      0 - 不等待，-1 - 无限等待直到下一个事件触发。
 * 
 * @return              正常退出返回0，异常退出返回错误码，
 *                      错误码定义在error.h文件中
 */
HFT_API int strategy_poll(int timeout = -1);

/**
 * 获取当前策略执行状态。
 * 
 * @return              策略执行状态，参考StrategyExecStatus定义。
 */
HFT_API int strategy_get_exec_status();

/**
 * 获取当前日期时间: 对于回测模式 - 返回回测执行当前日期时间，
 * 对于实盘和模拟模式返回当前机器的系统时间。
 *
 * @param o_date        输出日期(YYYYMMDD)。
 * @param o_time        输出时间(HHMMSSmmm)。
 *
 * @return              正常退出返回0，异常退出返回错误码，
 *                      错误码定义在error.h文件中
 */
HFT_API int strategy_get_datetime(int* o_date, int* o_time);

/**
 * 获取当前时间(单位毫秒): 对于回测模式 - 返回回测执行到当前位置，
 * 回测时间线中经过的毫秒数，对于实盘和模拟模式返回系统启动到当前
 * 时间点经过的毫秒数。
 *
 * @return              当前时间(单位毫秒)。
 */
HFT_API int64_t strategy_get_millseconds();

/**
 * 记录策略日志，日志文件最终编码格式为utf8
 *
 * @param level         日志级别
 * @param message       日志消息，默认输入的是utf8编码
 * @param is_gbk        当输入日志为gbk时传入true，默认是false
 */
HFT_API void strategy_log(StrategyLogLevel level, const char* message,
                          bool is_gbk = false);

/**
 * 策略退出原因字符形式，方便输出日志查看
 * 
 * @param reason        策略退出原因
 */
HFT_API const char* strategy_exit_reason(int reason);

/**
 * 策略运行状态字符形式，方便输出日志查看
 * 
 * @param status        策略运行状态
 */
HFT_API const char* strategy_exec_status(int status);

/**
 * 策略运行模式字符形式，方便输出日志查看
 * 
 * @param status        策略运行模式
 */
HFT_API const char* strategy_exec_mode(int exec_mode);

/**
 * 返回策略配置，json格式
 */
HFT_API const char* strategy_json_config();

#endif  // HFT_SDK_STRATEGY_API_H__