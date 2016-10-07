import pandas as pd
import numpy as np
import os

dailyPrice = pd.DataFrame(pd.read_excel("D:\\Gulmohar\\300014-daily.xlsx"))
#print(dailyPrice.iloc[1])


def efficiency_ratio():
    d = 1
    while d:
        d = range(1,20,1)
        piece = list(d[1:10])
        print(piece)
        d = 0
    return 0




efficiency_ratio()
