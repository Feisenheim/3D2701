import datetime
import string
from WindPy import w
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import os

matplotlib.rc('font', **{'size': 8})

Industry_Code_SW_Level1 = ['6102000000000000', '6103000000000000', '6104000000000000', '6105000000000000', '6106010000000000',
                           '6106020000000000', '6107010000000000', '6107000000000000', '1000012579000000', '1000012588000000',
                           '6111000000000000', '6113000000000000', '6114000000000000', '6120000000000000', '6101000000000000',
                           '6112000000000000', '6116000000000000', '6108000000000000', '6123000000000000', '1000012613000000',
                           '1000012612000000', '6122010000000000', '1000012611000000', '1000012601000000', '6117000000000000',
                           '6121000000000000', '6115000000000000', '6118000000000000']


Industry_Name_SW_Level1 = ['Mining',           'Chemicals',             'Steel',               'Non-ferrous Metal', 'Construction Materials',
                           'Construction',     'Electrical Equipments', 'Machinery',           'Defense',           'Autos',
                           'Home Appliance',   'Textiles & Apparels',   'Light manufacturing', 'Commerce',          'Agriculture',
                           'Food & Beverage',  'Facilities',            'Electronics',         'Generals....',      'Non-Banking Financials',
                           'Banks',            'Media',                 'Telecoms',            'Computing',         'Logistics',
                           'Leisure Serivces', 'Health Care',           'Real Estate']

w.start()
if w.isconnected():
    [today_y, today_m, today_d] = [int(e) for e in datetime.datetime.today().strftime('%Y-%m-%d').split('-')]
    date_now = datetime.date(today_y, today_m, today_d)

    date_pre_d = date_now + datetime.timedelta(days=-3)
    date_pre_w = date_now + datetime.timedelta(days=-10)
    date_pre_m = date_now + datetime.timedelta(days=-30)
    date_pre_y = date_now + datetime.timedelta(days=-365)
    date_columns = [date_pre_y, date_pre_m, date_pre_w, date_pre_d, date_now]
    date_col = ['date_pre_y', 'date_pre_m', 'date_pre_w', 'date_pre_d', 'date_now']
    m = pd.DataFrame(index=Industry_Code_SW_Level1)
    for i in range(5):
        wind_data = w.wsee(Industry_Code_SW_Level1, "sec_close_tswavg", "tradeDate={0};DynamicTime=1".format(date_columns[i].strftime('%Y%m%d')))
        m[date_col[i]] = pd.DataFrame(wind_data.Data[0], index=Industry_Code_SW_Level1)


    m['daily_growth'] = m['date_now']/m['date_pre_d'] - 1
    m['weekly_growth'] = m['date_now']/m['date_pre_w']-1
    m['monthly_growth'] = m['date_now']/m['date_pre_m']-1
    m['yearly_growth'] = m['date_now']/m['date_pre_y']-1

    plt.subplot(141)
    plt.barh(Industry_Code_SW_Level1, m['yearly_growth'])
    plt.title('Yearly Changes', fontproperties="SimSun")
    plt.subplot(142)
    plt.barh(Industry_Code_SW_Level1, m['monthly_growth'].values)
    plt.title('Monthly Changes', fontproperties="SimSun")
    plt.tick_params(labelleft=False, left=False)
    plt.subplot(143)
    plt.barh(Industry_Code_SW_Level1, m['weekly_growth'].values)
    plt.title('10-day Changes', fontproperties="SimSun")
    plt.tick_params(labelleft=False, left=False)
    plt.subplot(144)
    plt.barh(Industry_Code_SW_Level1, m['daily_growth'].values)
    plt.title('3-day Changes', fontproperties="SimSun")
    plt.tick_params(labelleft=False, left=False)

    plt.show()
