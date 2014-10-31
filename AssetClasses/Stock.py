# coding=gbk
#import numpy module

import os
import codecs
import datetime

import matplotlib.pyplot as py_plot
import matplotlib.finance as finance_plot


class Stock():
# This is the class for Stock

    # daily quotes of a stock, each quote contains the sequence
    # [date, open price, highest price, lowest price, close price, daily volume, total trading amount]
    quotes = []

    def __init__(self):
    # Initializer
        print("A stock object is created.")

    def import_stock_data_from_zszq(self, path, identifier):
    # This method loads trading data of a specified stock from Zhaoshang Securities data

        # path of the data source
        if path[-1] == "/":
            path = path + identifier + ".txt"
        else:
            path = path + "/" + identifier + ".txt"

        # read data
        if os.path.isfile(path):
            file_input = codecs.open(path, "r", "gbk").readlines()
        else:
            raise IOError("File Not Found.")

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
            pdate = finance_plot.date2num(datetime.datetime.strptime(data[header["date"]].strip(), "%Y/%m/%d"))
            popen = float(data[header["open"]].strip())
            phighest = float(data[header["highest"]].strip())
            plowest = float(data[header["lowest"]].strip())
            pclose = float(data[header["close"]].strip())
            pvolume = float(data[header["volume"]].strip())
            ptotal = float(data[header["total"]].strip())

            self.quotes.append([pdate, popen, phighest, plowest, pclose, pvolume, ptotal])

        print("Quotes of stock {0} from date {1} to {2} have been loaded".format(identifier, datetime.date.fromordinal(int(self.quotes[0][0])), datetime.date.fromordinal(int(self.quotes[-1][0]))))
        return 0


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

    def japanese_candle_chart(self, date_start, date_end):
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
    #stock.import_stock_data_from_zszq("/wrong", "SH600674")
    stock.japanese_candle_chart()