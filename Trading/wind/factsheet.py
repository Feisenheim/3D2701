import datetime
import string
from WindPy import w
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

########################################################################################################################
########################################################################################################################
def pe_data(ticker, date_begin, date_end):
    data_wind = w.wsd(ticker, 'ipo_date', date_begin, date_end, "ruleType=10;")
    if data_wind.Data[0][0] > datetime.datetime(date_begin):
        date_begin = data_wind.Data[0][0]
    data_wind = w.wsd(ticker, 'sec_name, pe_ttm, val_pe_percentile', date_begin, date_end, "ruleType=10;")

    try:
        pe_ttm = ['%.2f' % e for e in data_wind.Data[1]]
        pe_percentile = ['%.2f' % e for e in data_wind.Data[2]]
        name = data_wind.Data[0]
        print('Name: {0}'.format(name[0]))
        print(pe_ttm)
        print(pe_percentile)
        print('The most recent PE percentile is {0}'.format(pe_percentile[-1]))

    except:
        print('asdfasdfasdfasdfasdfasdfasdfasdfasdfasdf')


def generate_factsheet(tickers):

    factsheet = pd.DataFrame()
    date = datetime.datetime.today().strftime('%Y-%m-%d')
    y = int(date.split('-')[0])
    for i in range(tickers.size):
        ticker = tickers.iat[i, 0]
        col = [w.wss(ticker, "sec_name", "unit=1;rptDate={0};rptType=1".format(date.strip('-'))).Data[0][0]]

        for j in range(5):
            rD = '{0}1231'.format(str(y-5+j))
            data_wind = w.wss(ticker, "tot_oper_rev, wgsd_yoy_tr, np_belongto_parcomsh, wgsd_yoynetprofit, wgsd_yoynetprofit_deducted","unit=1;rptDate={0};rptType=1".format(rD))
            for e in data_wind.Data:
                col.append(e[0])

        factsheet = factsheet.append(pd.DataFrame([col], index=[ticker], columns=['证券简称',
                                                                                  '{0}总收入'.format(y - 5),
                                                                                  '{0}总收入 yoy'.format(y - 5),
                                                                                  '{0}归母'.format(y - 5),
                                                                                  '{0}归母 yoy'.format(y - 5),
                                                                                  '{0}归母扣非 yoy'.format(y - 5),
                                                                                  '{0}总收入'.format(y - 4),
                                                                                  '{0}总收入 yoy'.format(y - 4),
                                                                                  '{0}归母'.format(y - 4),
                                                                                  '{0}归母 yoy'.format(y - 4),
                                                                                  '{0}归母扣非 yoy'.format(y - 4),
                                                                                  '{0}总收入'.format(y - 3),
                                                                                  '{0}总收入 yoy'.format(y - 3),
                                                                                  '{0}归母'.format(y - 3),
                                                                                  '{0}归母 yoy'.format(y - 3),
                                                                                  '{0}归母扣非 yoy'.format(y - 3),
                                                                                  '{0}总收入'.format(y - 2),
                                                                                  '{0}总收入 yoy'.format(y - 2),
                                                                                  '{0}归母'.format(y - 2),
                                                                                  '{0}归母 yoy'.format(y - 2),
                                                                                  '{0}归母扣非 yoy'.format(y - 2),
                                                                                  '{0}总收入'.format(y - 1),
                                                                                  '{0}总收入 yoy'.format(y - 1),
                                                                                  '{0}归母'.format(y - 1),
                                                                                  '{0}归母 yoy'.format(y - 1),
                                                                                  '{0}归母扣非 yoy'.format(y - 1),
                                                                                  ]))
        factsheet=factsheet[['证券简称',
                             '{0}总收入'.format(y - 5),
                             '{0}总收入'.format(y - 4),
                             '{0}总收入'.format(y - 3),
                             '{0}总收入'.format(y - 2),
                             '{0}总收入'.format(y - 1),
                             '{0}总收入 yoy'.format(y - 5),
                             '{0}总收入 yoy'.format(y - 4),
                             '{0}总收入 yoy'.format(y - 3),
                             '{0}总收入 yoy'.format(y - 2),
                             '{0}总收入 yoy'.format(y - 1),
                             '{0}归母'.format(y - 5),
                             '{0}归母'.format(y - 4),
                             '{0}归母'.format(y - 3),
                             '{0}归母'.format(y - 2),
                             '{0}归母'.format(y - 1),
                             '{0}归母 yoy'.format(y - 5),
                             '{0}归母 yoy'.format(y - 4),
                             '{0}归母 yoy'.format(y - 3),
                             '{0}归母 yoy'.format(y - 2),
                             '{0}归母 yoy'.format(y - 1),
                             '{0}归母扣非 yoy'.format(y - 5),
                             '{0}归母扣非 yoy'.format(y - 4),
                             '{0}归母扣非 yoy'.format(y - 3),
                             '{0}归母扣非 yoy'.format(y - 2),
                             '{0}归母扣非 yoy'.format(y - 1),]]
    factsheet.to_excel(dataDirectory + "\\output.xlsx")
    s = factsheet.loc['601100.SH']
    plt.subplot(221)
    plt.title('Total Revenue', fontname="Arial")
    plt.plot(s[1:5], 'r-->')
    plt.subplot(222)
    plt.plot(s[6:10], 'y--*')
    plt.subplot(223)
    plt.plot(s[11:15], 'r--<')
    plt.subplot(224)
    plt.plot(s[16:20], 'b--*')
    plt.show()
    #print(factsheet)
    return factsheet
########################################################################################################################
########################################################################################################################


dataDirectory = os.getcwd()+"\\Data"
tickers = pd.DataFrame(pd.read_excel(dataDirectory+"\\stocks.xlsx", header=0))
outputFile = open(dataDirectory+"\\output.xlsx","w")


w.start()
if w.isconnected():
    generate_factsheet(tickers)
   # for i in range(tickers.size):
   #     date_begin = "2015-11-01"
   #     date_end = "2020-11-10"
   #     pe_data(tickers.iat[i, 0], date_begin, date_end)
   # pe_data('300014.SZ', date_begin, date_end)
   #   #   r = list()
   #    #  r.append(stockList.iat[n1, 0])
       # for l in windData.Data:
        #    print(type(l))
         #   r.append(l)
            #r.append("{:.2f}".format(l))
        #print(r)
        #outputData.append(r)
        #print(outputData)


     #   print(pd.DataFrame(windData.Data))
     #   outputData.append(pd.DataFrame(windData.Data))
    #print(outputData)


    #outputData.to_excel(dataDirectory + "\\output.xlsx")
        #windData
        #outputData = pd.DataFrame(w.wsd(stockList.iat[0, 0], "CLOSE, PE_TTM", "2020-05-16", "2020-06-02", ).Data[0])
        #outputData.to_excel(dataDirectory+"\\output.xlsx")
        #print(w.wsd(stockList.iat[n,0], "CLOSE", "2019-06-01", "2020-06-02",).Data)
        #print(w.wsd("601318.SH", "CLOSE", "2019-06-01", "2020-06-02",).Times)



