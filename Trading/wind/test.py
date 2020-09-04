import requests


url = "http://www.baidu.com/s?rtt=1&cl=2&tn=news&word=%E9%98%BF%E9%87%8C%E5%B7%B4%E5%B7%B4"


headers = {"User-Agent":"Chrome/80.0.3987.122"}
a = requests.get(url, headers)
print(a.text)