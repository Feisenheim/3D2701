import datetime
import string
from WindPy import w
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


def generate_factsheet(ticker):
    date = datetime.datetime.today().strftime('%Y-%m-%d')
    y = int(date.split('-')[0])
    for i in range(3):
        rD = '{0}1231'.format(str(y-i-1))
        data_wind = w.wss(ticker, "tot_oper_rev", "unit=1;rptDate={0};rptType=1".format(rD))
        print('{:,.2f}'.format(float(data_wind.Data[0][0])))
########################################################################################################################
########################################################################################################################


dataDirectory = os.getcwd()+"\\Data"

tickers = pd.DataFrame(pd.read_excel(dataDirectory+"\\stocks.xlsx", header=0))
outputFile = open(dataDirectory+"\\output.xlsx","w")


w.start()
if w.isconnected():
    generate_factsheet('300014.SZ')
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



