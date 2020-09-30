"""
Решения задач пробного раунда онлайн-чемпионата по программированию Yandex Сup в категории Машинное обучение.
https://contest.yandex.ru/yacup/
"""


def A():
    """
    Аппроксимировать (в смысле мин. средней квадратичной ошибкой) входной
    набор данных ступенчатой функцией вида:
        f(x): a if x < c else b
    Сатус: проходит часть тестов, ошибка в тесте 5
    """
    import numpy as np

    def move_var(x):
        n = np.arange(1, len(x)+1)
        x_2 = np.cumsum(x * x) / n
        x_ = np.cumsum(x) / n
        return x_2 - x_ * x_

    with open('stump.in', 'r') as f_in, open('stump.out', 'w') as f_out:
        n = int(f_in.readline())
        data = np.fromstring(f_in.read(), sep=' ').reshape((n, 2)).T
        x, y = data[0, :], data[1, :]
        idx = np.argsort(x)
        x, y = x[idx], y[idx]
        # a, b - должны быть средние значения y в данных промежутках
        # квадратичная ошибка - дисперсия y в данных промежутках
        # найдём c как точку разбивающую выборку на две с наменьшей суммарной дисперсией
        if n <= 3:
            a, b, c = y[0], y[-1], x[1]
        else:
            v = move_var(y) + move_var(y[::-1])[::-1]
            i = np.argmin(v) + 1
            a, b, c = y[:i].mean(), y[i:].mean(), x[i]
        f_out.write(f'{a:.6f} {b:.6f} {c:.6f}')


def B():
    """
    Для x, y из https://yadi.sk/d/RXnmNGp4PZnMrg найти a, b, c
    для аппрокисимации:
        y = (a * sin(x) + b * ln(x)) ^ 2 + c * x ^ 2
    Ответ:
        np.pi, np.e, 4
    :return:
    """
    import numpy as np
    import pandas as pd
    from scipy.optimize import least_squares

    df = pd.read_csv('data.csv', names=['x', 'y'])
    x, y = df.x.values, df.y.values

    def f(k):
        return (k[0] * np.sin(x) + k[1] * np.log(x)) ** 2 + k[2] * x ** 2 - y

    res = least_squares(f, np.ones(3))
    print(res.x)


if __name__ == "__main__":
    A()
    