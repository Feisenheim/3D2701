# -*- coding: utf-8 -*-
# Buy and Hold


from sparkquant import *


def init(context):
    # 设置这个策略当中会用到的参数，在策略中可以随时调用，这个策略使用买入并持有万科A股票
    context.SYMBOL = 'SZ.000002'   # 使用的合约编号
    context.ACCOUNT_ID = '6814'     # 报单时指定的账号
    context.VOLUME = 100           # 报单数量（股票单位：股，期货单位：手）
    context.fired = False           # 是否已报单

    # 订阅行情数据
    print('订阅合约...')
    subscribe([context.SYMBOL + '.bar'])

    # order_volume(context.ACCOUNT_ID, context.SYMBOL, context.VOLUME, 22)


def on_bar(context, bar_dict):
    print(bar_dict)
    # 接收bar数据，在收到第一个bar行情时买入股票
    if not context.fired:
        print("报单...")
        order_price = bar_dict['close']  # 使用最新价
        order_volume(context.ACCOUNT_ID, context.SYMBOL, context.VOLUME, order_price)
        context.fired = True


def on_order_status(context, order):
    # 如何接收订单状态变化事件
    # 在实盘中，需要考虑报单不能全部成交的情况，并在此处进行追单处理
    print('\n收到订单状态变化：\n', order)


def on_execution_report(context, exec_report):
    # 如何接收成交回报事件
    print('\n收到成交回报： \n', exec_report)


if __name__ == '__main__':
    # 如何开始运行策略
    run(init=init,
        on_bar=on_bar,
        on_order_status=on_order_status,
        on_execution_report=on_execution_report,
        config_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        log_dir=os.path.dirname(os.path.realpath(sys.argv[0])),
        is_async=True)
