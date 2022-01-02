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

    values01 = ask([ask0, ask1])
    values12 = ask([ask1, ask2])
    values13 = ask([ask1, ask3])

    if len(values01 & values12 & values13) != 1:
        value1 = random.choice(list(values01))
    else:
        value1 = (values01 & values12 & values13).pop()
    results[1] = value1
    results[0] = (values01 - {value1}).pop() if len(values01 - {value1}) == 1 else value1
    results[2] = (values12 - {value1}).pop() if len(values12 - {value1}) == 1 else value1
    results[3] = (values13 - {value1}).pop() if len(values13 - {value1}) == 1 else value1
    return results



def ask(asks):
    headers = {}
    headers["x-cat-variable"] = asks[0]
    headers["x-CAT-variable"] = asks[1]

    connection = HTTPConnection("127.0.0.1:7777")
    connection.request("MEW", "/", headers=headers)
    response = connection.getresponse()
    response_headers = response.getheaders()

    results = []
    for key, value in response_headers:
        if key.lower() == "x-cat-value":
            assert value
            results.append(value)

    assert results
    return set(results)




def main():
    args = read_input()
    res = task(*args)
    print("\n".join(res))



# ans = task(['request0', "request1", "request2", "request3"])
# print(ans)

if __name__ == "__main__":
    main()
