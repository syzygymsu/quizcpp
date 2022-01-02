import http.client as hc


a = input()
b = input()
c = input()
d = input()

connection = hc.HTTPConnection(host='127.0.0.1', port=7777)

connection.request('MEW', '/', headers={'x-cat-variable': f'{a},{c}'})
values = connection.getresponse().headers.get_all('x-cat-value')
connection.request('MEW', '/', headers={'x-cat-variable': f'{b},{d}'})
values1 = connection.getresponse().headers.get_all('x-cat-value')
connection.request('MEW', '/', headers={'x-cat-variable': f'{b},{c}'})
values2 = connection.getresponse().headers.get_all('x-cat-value')

connection.close()

if values2[0] != values2[1]:
    c_answer = 0
    b_answer = 0
    count = 0
    for i in values2:
        if count == 0:
            if i in values1 and i not in values:
                b_answer = i
                values1.remove(i)
            elif i in values and i not in values1:
                c_answer = i
                values.remove(i)
            elif i in values:
                c_answer = i
                values.remove(i)
            elif i in values1:
                b_answer = i
                values1.remove(i)
        else:
            if len(values1) > 1 and i not in values:
                b_answer = i
                values1.remove(i)
            elif len(values) > 1 and i not in values1:
                c_answer = i
                values.remove(i)
            elif len(values) > 1:
                c_answer = i
                values.remove(i)
            elif len(values1) > 1:
                b_answer = i
                values1.remove(i)
        count += 1
else:
    c_answer = b_answer = values2[0]
    values.remove(values2[0])
    values1.remove(values2[0])

a_answer = ''.join(values)
d_answer = ''.join(values1)

print(a_answer)
print(b_answer)
print(c_answer)
print(d_answer)
