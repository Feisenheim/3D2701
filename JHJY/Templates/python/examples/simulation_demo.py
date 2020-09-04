# -*- coding: utf-8 -*-
#

from sparkquant import *


def init(context):
    if context.run_mode == 1:
        context.timer_interval1 = 36000000
        context.timer_interval2 = 53000000
        context.timer_interval3 = 54000000
    else:
        context.timer_interval1 = 2000
        context.timer_interval2 = 3000
        context.timer_interval3 = 4000

    context.day_time1 = int(context.now.strftime('%H%M%S')) + 10  # 当前时间加10秒，转换为整数
    context.day_time2 = context.day_time1 + 10
    context.day_time3 = context.day_time2 + 10

    print('获取策略配置信息...')
    print('\trun_mode: ' + str(context.run_mode))
    print('\tstrategy_id: ' + context.strategy_id)
    print('\trun_id: ' + context.run_id)
    print('\tsys_account_id: ' + context.sys_account_id)
    print('\tlog_level: ' + str(context.log_level))

    print('\n使用subscribe...')
    # context.symbols = ['SZ.000002.ZW'] 深圳逐笔委托
    # context.symbols = ['SZ.000002.ZC'] 沪深逐笔成交
    # context.symbols = ['SZ.000002.tick']
    # context.symbols = ['SZ.000002.tick', 'CFFEX.IF1812.tick', 'SH.600000.bar']
    context.symbols = ['SH.600000.bar']
    subscribe(context.symbols)

    print('\n查询当前订阅的所有合约...')
    print(context.universe)
    print('\n使用定时任务...')
    print('\tSchedule a timer with interval {0}ms'.format(context.timer_interval1))
    schedule(strategy_timer_schedule1, timer_type='timer', interval=context.timer_interval1)

    print('\tSchedule a timer with interval {0}ms'.format(context.timer_interval2))
    schedule(strategy_timer_schedule2, timer_type='timer', interval=context.timer_interval2)

    print('\tSchedule a timer with interval {0}ms'.format(context.timer_interval3))
    schedule(strategy_timer_schedule3, timer_type='timer', interval=context.timer_interval3)

    print('\n使用每日定时任务...')
    print('\tSchedule a day timer at {0}'.format(context.day_time1))
    schedule(strategy_day_schedule1, timer_type='day', time=context.day_time1)

    print('\tSchedule a day timer at {0}'.format(context.day_time2))
    schedule(strategy_day_schedule2, timer_type='day', time=context.day_time2)

    print('\tSchedule a day timer at {0}'.format(context.day_time3))
    schedule(strategy_day_schedule3, timer_type='day', time=context.day_time3)

    print('\n使用log...')
    log.error('\terror')
    log.warn('\twarn')
    log.info('\tinfo')
    log.debug('\tdebug')

    # print('\n查询合约信息...')
    # print('\t' + str(get_instrument_info('SH.600000')))
    # print('\t' + str(get_instrument_info('SZ.000001', '2018/2/14')))
    # print('\t' + str(get_instrument_info('CFFEX.IF1812')))
    #
    # print('\n查询当天合约代码列表信息...')
    # code_list = get_instrument_list(CodeTable.HS300)
    # print('\t合约代码数量：' + str(len(code_list)))

    print('\n将错误代码转化为错误消息...')
    print('\n错误代码2104的错误消息为:' + to_error_message(2104))

    # 目前回测模式下不支持在init中下单
    if context.run_mode != 1:
        print('\n发送一个限价单...')
        error_no, order_id = order_volume('6814', 'SZ.000002', 100, price=25)
        if error_no:
            print('\tError: ' + to_error_message(error_no))

    print('\n发送一个撤单请求...')
    order_ids = ['01201808311025020000002113']
    cancel_order('6814', order_ids)

    print('\n获取资金账户的资金数据...')
    cash_data = context.cash()
    print('\tCash: ' + str(cash_data))

    print('\n获取某个合约的持仓信息...')
    position_data = context.position("SH.600000")
    print('\tPosition: ' + str(position_data))

    print('\n获取多条持仓信息...')
    positions_data = context.positions()
    print('\tPositions: ' + str(positions_data))

    print('\n获取指定多个标的持仓信息...')
    positions_data = context.positions(symbols=['SZ.000002', 'SH.600000'])
    print('\tPositions: ' + str(positions_data))

    print('\n获取报单信息...')
    order_id = "01201810121426130000000246"
    order_data = context.order(order_id)
    print("\tOrder: " + str(order_data))

    print('\n获取多条报单信息...')
    orders_data = context.orders(1, 10)
    print("\tOrders: " + str(orders_data))

    print('\n获取成交信息...')
    order_id = "01201809060955290000000421"
    trade_data = context.trades(order_id)
    print("\tTrade: " + str(trade_data))

    print('\n[默认字段]获取指定日期的历史tick行情信息...')
    fields = ["date", "time", "open", "high1", "low"] # fields指定字段，如果输入字段不存在，返回值为None
    data_tick = history(['SZ.000002', 'SH.600000'], "1tick", "2018/08/06 10:0:0", "2018/08/06 10:0:05",
                        ndarray_format=False)
    print("\tdata_tick: " + str(data_tick))

    print('\n[默认字段]获取指定日期的历史k线行情信息...')
    data_kline = history('SZ.000002', "1day", "2018/08/06", "2018/08/08", ndarray_format=False)
    print("\tdata_kline: " + str(data_kline))

    print('\n[默认字段]获取指定日期前的n条历史tick行情信息...')
    data_tick_n = history_n(['SZ.000001'], "1tick", 3, ndarray_format=False)
    print("\tdata_tick_n: " + str(data_tick_n))

    print('\n[默认字段]获取指定日期前的n条历史k线行情信息...')
    data_kline_n = history_n(['SZ.000002', 'SH.600000'], "1day", 3, "2018/08/06 10:0:05", ndarray_format=False)
    print("\tdata_kline_n: " + str(data_kline_n))

    print('\n[指定字段]获取指定日期的历史tick行情信息...')
    fields = ["date", "time", "open", "high1", "low"] # fields指定字段，如果输入字段不存在，返回值为None
    data_tick = history(['SZ.000002', 'SH.600000'], "1tick", "2018/08/06 10:0:0", "2018/08/06 10:0:05", fields)
    print("\tdata_tick: " + str(data_tick))

    print('\n[指定字段]获取指定日期的历史k线行情信息...')
    data_kline = history(['SZ.000002'], "1day", "2018/08/06", "2018/08/08", fields)
    print("\tdata_kline: " + str(data_kline))

    print('\n[指定字段]获取指定日期前的n条历史tick行情信息...')
    data_tick_n = history_n(['SZ.000001'], "1tick", 3, "2018/08/06 10:0:05", fields)
    print("\tdata_tick_n: " + str(data_tick_n))

    print('\n[指定字段]获取指定日期前的n条历史k线行情信息...')
    data_kline_n = history_n(['SZ.000002', 'SH.600000'], "1day", 3, "2018/08/06 10:0:05", fields)
    print("\tdata_kline_n: " + str(data_kline_n))


def strategy_timer_schedule1(context):
    print("\nstrategy_timer_schedule1:时间间隔为{0}ms的定时器被调用".format(context.timer_interval1))

    print('\t取消定时任务...')
    print("\t时间间隔为{0}ms的定时器被取消".format(context.timer_interval1))
    unschedule(timer_type='timer', interval=context.timer_interval1)


def strategy_timer_schedule2(context):
    print("\nstrategy_timer_schedule2: 时间间隔为{0}ms的定时器被调用".format(context.timer_interval2))


def strategy_timer_schedule3(context):
    print("\nstrategy_timer_schedule3:时间间隔为{0}ms的定时器被调用".format(context.timer_interval3))


def strategy_day_schedule1(context):
    print("\nstrategy_day_schedule1:时间为{0}ms的Day定时器被调用".format(context.day_time1))

    print('\t取消每日定时任务...')
    print("\t时间为:{0}ms的每日定时器被取消".format(context.day_time1))
    unschedule(timer_type='day', time=context.day_time1)


def strategy_day_schedule2(context):
    print("\nstrategy_day_schedule2:时间为{0}ms的Day定时器被调用".format(context.day_time2))


def strategy_day_schedule3(context):
    print("\nstrategy_day_schedule3:时间为{0}ms的Day定时器被调用".format(context.day_time3))


def on_bar(context, bar_dict):
    # 如何接收bar数据
    print('\n收到bar数据：\n' + str(bar_dict))


def on_tick(context, tick_dict):
    # 如何接收tick数据  都转成字符串形式
    print('\n收到tick数据:' + str(tick_dict))
    print('datetime: ' + str(context.now))


def on_order_status(context, order):
    # 如何接收订单状态变化事件
    print('\n收到订单状态变化：\n' + str(order))


def on_execution_report(context, exec_report):
    # 如何接收成交回报事件
    print('\n收到成交回报： \n' + str(exec_report))


if __name__ == '__main__':
    # 如何开始运行策略
    run(init=init,
        on_bar=on_bar,
        on_tick=on_tick,
        on_order_status=on_order_status,
        on_execution_report=on_execution_report,
        config_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        log_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        is_async=True)
