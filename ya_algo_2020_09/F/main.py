import requests
import sys


if __name__ == '__main__':
    url = sys.stdin.readline().strip()
    port = int(sys.stdin.readline().strip())
    a = int(sys.stdin.readline().strip())
    b = int(sys.stdin.readline().strip())

    request_url = "{}:{}?a={}&b={}".format(url, port, a, b)
    response = requests.get(url=request_url).json()
    res = 0
    for num in response:
        res += int(num)
    print(res)
