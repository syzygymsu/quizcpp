import random
from http.client import HTTPConnection

def read_input():
    import fileinput
    asks = []
    for line in fileinput.input():
        asks.append(line.strip())
        if len(asks) == 4:
            return asks,


def task(asks):
    results = [""] * 4
    ask0, ask1, ask2, ask3 = asks

    connection = HTTPConnection(host='127.0.0.1', port=7777)
    values01 = ask([ask0, ask1], connection)
    values12 = ask([ask1, ask2], connection)
    values13 = ask([ask1, ask3], connection)
    connection.close()

    if len(values01 & values12 & values13) != 1:
        value1 = random.choice(list(values01))
    else:
        value1 = (values01 & values12 & values13).pop()
    results[1] = value1
    results[0] = (values01 - {value1}).pop() if len(values01 - {value1}) == 1 else value1
    results[2] = (values12 - {value1}).pop() if len(values12 - {value1}) == 1 else value1
    results[3] = (values13 - {value1}).pop() if len(values13 - {value1}) == 1 else value1
    return results


def ask(asks, connection):
    connection.request('MEW', '/', headers={'x-cat-variable': f'{asks[0]},{asks[1]}'})
    values = connection.getresponse().headers.get_all('x-cat-value')
    return set(values)

def main():
    args = read_input()
    res = task(*args)
    print("\n".join(res))

if __name__ == "__main__":
    main()
