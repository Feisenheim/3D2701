# -*- coding: utf-8 -*-
# SMA

from sparkquant import *
import talib
import numpy as np


def init(context):
    # 设置这个策略当中会用到的参数，在策略中可以随时调用，这个策略使用长短均线，我们在这里设定长线和短线的区间，
    # 在调试寻找最佳区间的时候只需要在这里进行数值改动
    context.SHORT = 5
    context.LONG = 10
    context.SYMBOL = 'SZ.000002'  # 使用的合约编号
    context.ACCOUNT_ID = '6814'  # 报单时指定的账号
    context.VOLUME = 100  # 每次的报单数量

    print('订阅合约...')
    subscribe([context.SYMBOL + '.tick'])  # 订阅行情数据

    # order_volume(context.ACCOUNT_ID, context.SYMBOL, context.VOLUME, 22)


def on_tick(context, tick_dict):
    # 接收tick数据
    print('\n接收tick数据：' + str(tick_dict))

    # 因为策略需要用到均线，所以需要读取历史数据，获取当前时间前N个tick的最新价,转成ndarray数据类型
    data = history_n([context.SYMBOL], "tick", context.LONG+1, "", ['match'])
    if len(data[context.SYMBOL]) <= 0:
        # 回测过程中，会出现前n次返回为空的情况，需过滤
        return
    # 获取指定合约、指定长度的历史行情数据list
    prices = data[context.SYMBOL][:, 0]

    # 使用talib计算长短两根均线，均线以array的格式表达
    short_avg = talib.SMA(prices, context.SHORT)
    long_avg = talib.SMA(prices, context.LONG)
    # 如果短均线从上往下跌破长均线，也就是在目前的行情短线平均值低于长线平均值，而上一个行情的短线平均值高于长线平均值
    if short_avg[-1] < long_avg[-1] and short_avg[-2] > long_avg[-2]:
        print('卖出指定数量证券\n')
        order_price = tick_dict['bid_price'][0]  # 使用bid_price的1档价格
        order_volume(context.ACCOUNT_ID, context.SYMBOL, context.VOLUME * -1, order_price)

    # 如果短均线从下往上突破长均线，为入场信号
    if short_avg[-1] > long_avg[-1] and short_avg[-2] < long_avg[-2]:
        print('\n买入指定数量证券：\n')
        order_price = tick_dict['ask_price'][0]  # 使用ask_price的1档价格
        order_volume(context.ACCOUNT_ID, context.SYMBOL, context.VOLUME, order_price)


def on_order_status(context, order):
    # 如何接收订单状态变化事件
    print('\n收到订单状态变化：\n', order)


def on_execution_report(context, exec_report):
    # 如何接收成交回报事件
    print('\n收到成交回报： \n', exec_report)


if __name__ == '__main__':
    # 如何开始运行策略
    run(init=init,
        on_tick=on_tick,
        on_bar=None,
        on_order_status=on_order_status,
        on_execution_report=on_execution_report,
        config_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        log_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        is_async=True)
