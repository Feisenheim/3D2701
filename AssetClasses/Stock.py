# coding=gbk
#import numpy module

from datetime import datetime
import codecs

import matplotlib.pyplot as py_plot
import matplotlib.finance as finance_plot


class Stock():

    quotes = []

    def import_stock_data_from_zszq(self, path, identifier):

        # path of the data source
        path = path + "/" + identifier + ".txt"

        # read data
        file_input = codecs.open(path, "r", "gbk").readlines()

        priceDate = 0
        priceOpen = 0
        priceHighest = 0
        priceLowest = 0
        priceClose = 0
        volume = 0
        total = 0

        # header - id, stock name
        ##header1 = input[0].split(" ")

        # header - date, open, highest, lowest, close, volume, total
        header2 = file_input[1].split("\t")

        # price data
        prices = file_input[2:-1]

        header = {}
       # header indices
        for x in header2:
            if codecs.encode(x.strip(), "gbk") == codecs.encode("日期", "gbk"):
                header["date"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("开盘", "gbk"):
                header["open"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("最高", "gbk"):
                header["highest"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("最低", "gbk"):
                header["lowest"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("收盘", "gbk"):
                header["close"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("成交量", "gbk"):
                header["volume"] = header2.index(x)
            elif codecs.encode(x.strip(), "gbk") == codecs.encode("成交额", "gbk"):
                header["total"] = header2.index(x)



        # generate price vectors
        for day in prices:
            data = day.split("\t")
            priceDate = finance_plot.date2num(datetime.strptime(data[header["date"]].strip(), "%Y/%m/%d"))
            priceOpen = float(data[header["open"]].strip())
            priceHighest = float(data[header["highest"]].strip())
            priceLowest = float(data[header["lowest"]].strip())
            priceClose = float(data[header["close"]].strip())
            volume = float(data[header["volume"]].strip())
            total = float(data[header["total"]].strip())

            self.quotes.append([priceDate, priceOpen, priceHighest, priceLowest, priceClose, volume, total])

    # def import_stock_data_from_zszq(path, identifier):
    #
    #     # path of the data source
    #     path = path + "/" + identifier + ".txt"
    #
    #     # read data
    #     #try:
    #     #file_input = codecs.open(path, "r", "gbk").readlines()
    #     file_input = codecs.open(path, "r", "gbk").readlines()
    #     #except:
    #     #    print("failed to open file")
    #
    #     priceDate = []
    #     priceOpen = []
    #     priceHighest = []
    #     priceLowest = []
    #     priceClose = []
    #     volume = []
    #     total = []
    #
    #     # header - id, stock name
    #     ##header1 = input[0].split(" ")
    #
    #     # header - date, open, highest, lowest, close, volume, total
    #     header2 = file_input[1].split("\t")
    #
    #     # price data
    #     prices = file_input[2:-1]
    #
    #     header = {}
    #    # header indices
    #     for x in header2:
    #         if codecs.encode(x.strip(), "gbk") == codecs.encode("日期", "gbk"):
    #             header["date"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("开盘", "gbk"):
    #             header["open"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("最高", "gbk"):
    #             header["highest"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("最低", "gbk"):
    #             header["lowest"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("收盘", "gbk"):
    #             header["close"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("成交量", "gbk"):
    #             header["volume"] = header2.index(x)
    #         elif codecs.encode(x.strip(), "gbk") == codecs.encode("成交额", "gbk"):
    #             header["total"] = header2.index(x)
    #
    #     # generate price vectors
    #     for day in prices:
    #         data = day.split("\t")
    #         ##priceDate.append(finance_plot.date2num(datetime.strptime(data[header["date"]].strip(), "%Y/%m/%d")))
    #         priceDate.append(datetime.strptime(data[header["date"]].strip(), "%Y/%m/%d"))
    #         priceOpen.append(float(data[header["open"]].strip()))
    #         priceHighest.append(float(data[header["highest"]].strip()))
    #         priceLowest.append(float(data[header["lowest"]].strip()))
    #         priceClose.append(float(data[header["close"]].strip()))
    #         volume.append(float(data[header["volume"]].strip()))
    #         total.append(float(data[header["total"]].strip()))
    #
    #     return [priceDate, priceOpen, priceHighest, priceLowest, priceClose, volume, total]


    def japanese_candle_chart(self):
        # This method takes stock price data and generates the japanese candle chart

        #quotes = []
        #for i in range(len(pdate)):
        #    quotes.append([py_dates.date2num(pdate[i]), popen[i], phighest[i], plowest[i], pclose[i]])

        fig = py_plot.figure()
        ax_candlestick = fig.add_subplot(2, 1, 1)
        finance_plot.candlestick_ohlc(ax_candlestick, self.quotes, width=5, colorup="r", colordown="g")

        ax_volume = fig.add_subplot(2, 1, 2)

        #py_plot.bar(pdate, volume)

        ax_candlestick.xaxis_date()
        ax_candlestick.autoscale_view()
        py_plot.setp(py_plot.gca().get_xticklabels(), rotation=45, horizontalalignment='right')
        py_plot.show()


if __name__ == "__main__":
    stock = Stock()
    stock.import_stock_data_from_zszq("/home/fei/Documents/Me/Computing/Data", "SH600674")
    stock.japanese_candle_chart()