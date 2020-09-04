import datetime
import string
from WindPy import w
import pandas as pd
import os

dataDirectory = os.getcwd()+"\\Data"

stockList = pd.DataFrame(pd.read_excel(dataDirectory+"\\stocks.xlsx", header=0))
outputFile = open(dataDirectory+"\\output.xlsx","w")

fields = ["CLOSE", "PE_TTM"]
outputData = pd.DataFrame()
d = datetime.date.today()

w.start()

if w.isconnected():

    for n1 in range(stockList.size):
        windData = w.wsd(stockList.iat[n1, 0], fields, d, d,)
        r = list()
        r.append(stockList.iat[n1, 0])
        for l in windData.Data:
            print(type(l))
            r.append(l)
            #r.append("{:.2f}".format(l))
        print(r)
        outputData.append(r)
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
