import random
from http.client import HTTPConnection

def task(asks):
    results = [""] * 4
    connection = HTTPConnection(host='127.0.0.1', port=7777)
    values01 = ask([asks[0], asks[1]], connection)
    values12 = ask([asks[1], asks[2]], connection)
    values13 = ask([asks[1], asks[3]], connection)
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
    args = [""] * 4
    for i in range(4):
        args[i] = input()
    res = task(args)
    print("\n".join(res))

if __name__ == "__main__":
    main()
