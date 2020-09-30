"""
Решения задач пробного раунда онлайн-чемпионата по программированию Yandex Сup в категории Бэкенд.
https://contest.yandex.ru/yacup/
"""


def A():
    """
    Даны две строки строчных латинских символов: строка J и строка S.
    Нужно проверить, какое количество символов из S входит в J.

    Статус: принята
    """
    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        j = f_in.readline().strip()
        s = f_in.readline().strip()

        j = set(j)
        count = 0
        for c in s:
            if c in j:
                count += 1
        f_out.write(f'{count}')


def B():
    """
    Чтобы точно проснуться с утра, Алексей каждый вечер заводит N будильников на своём телефоне.
    Каждый будильник устроен таким образом, что он звонит каждые X минут с того момента времени,
    на который его завели. Например, если будильник был заведён на момент времени ti, то он
    будет звонить в моменты времени ti, ti+X, ti+2⋅X и так далее. При этом если какие-то два
    будильника начинают звонить в один момент времени, то отображается только один из них.
    Известно, что прежде чем проснуться, Алексей каждое утро слушает ровно K будильников, после
    чего просыпается. Определите момент времени, когда Алексей проснётся.

    Статус: проходит часть тестов, не проходит по времени
    """
    from math import inf
    from bisect import bisect_left, insort

    class SortedList:
        def __init__(self):
            self._items = []
            self.len = 0

        def add(self, item):
            insort(self._items, item)
            self.len += 1

        def __contains__(self, item):
            i = bisect_left(self._items, item)
            return i != self.len and self._items[i] == item

        def __getitem__(self, item):
            return self._items[item]

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n, x, k = map(int, f_in.readline().split())
        t_list = list(map(int, f_in.readline().split()))
        t_list.sort()

        t_unique = SortedList()
        t0 = inf
        # X и K могут быть сколь угодно большими, алгоритм должен вычислять ответ,
        # а не получать его "эксперементально"
        for t in t_list:
            if t > t0:
                break
            new_t = t % x
            if new_t in t_unique:
                continue
            t_unique.add(new_t)
            k += t // x  # приводим все будильники в интервал [0, X), чтоб потом проще вычислять время
            k1, k2 = divmod(k-1, t_unique.len)
            t0 = x * k1 + t_unique[k2]
        f_out.write(f'{t0}')


def C():
    """
    Сначала Вася объявляет, сколько очков нужно набрать, чтобы игра закончилась.
    Затем Петя берет карточки, на которых написаны целые неотрицательные числа,
    и начинает выкладывать их на стол одну за другой. Если на карточке число,
    кратное пяти, то Вася получает одно очко. Если на карточке число, кратное
    трем, то одно очко получает Петя. Если на карточке число, не кратное ни трем,
    ни пяти, или наоборот, кратное им обоим, то очков не получает никто.

    Статус: принята
    """
    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        k, n = map(int, f_in.readline().split())
        cards = map(int, f_in.readline().split())

        V, P = 0, 0
        for card in cards:
            mod3, mod5 = card % 3 == 0, card % 5 == 0
            if mod3 == mod5:
                continue
            elif mod3:
                P += 1
            else:
                V += 1

            if V == k:
                res = 'Vasya'
                break
            elif P == k:
                res = 'Petya'
                break
        else:
            if V > P:
                res = 'Vasya'
            elif P > V:
                res = 'Petya'
            else:
                res = 'Draw'

        f_out.write(res)


def D():
    """
    Система должна обнаружить номер m первого коммита, сломавшего тесты. Этот
    номер обладает следующим свойством: все коммиты с номерами, меньшими m,
    успешно проходят тесты, а коммиты с номерами, большими либо равными m,
    тесты не проходят.

    Статус: принята
    """

    n = int(input())
    lb = 1
    ub = n
    while True:
        curr = lb + (ub - lb) // 2
        print(curr, flush=True)
        res = input().strip()  # хоть в доках и написано, что input убирает перевод строки в конце, но что-то остается
        if res == '1':
            # надо искать справа
            lb = curr + 1
        elif res == '0':
            # надо искать слева
            ub = curr
        else:
            raise ValueError()
        if ub == lb:
            break
    print(f'! {ub}', flush=True)


def E():
    """
    Сеть компании состоит из серверов. Серверы соединены друг с другом в кластеры.
    Каждый сервер может скачивать файлы только с серверов в его кластере.
    Составьте программу, которая сообщать, из каких источников определённый
    сервер может скачать необходимый файл.

    Статус: принята
    """
    from collections import defaultdict

    def cluster(graph, root):
        """Наодит узлы кластера, которому принадлежит root"""
        visited = set()
        queue = [root, ]
        while queue:
            root = queue.pop()
            queue.extend(n for n in graph[root] if n not in visited)
            visited.add(root)

        return visited

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n = int(f_in.readline())

        net = defaultdict(set)  # для каждого узла множество смежных
        for _ in range(n):
            a, b = f_in.readline().split()
            net[a].add(b), net[b].add(a)

        # разобъем сеть на кластеры
        clusters = dict()
        for n, subnet in net.items():
            if n not in clusters:
                c = cluster(net, n)
                for subling in c:
                    clusters[subling] = c

        q = int(f_in.readline())
        for _ in range(q):
            target, _ = f_in.readline().split()
            sources = f_in.readline().split()

            c = clusters[target]
            # Серверы следует выводить в том порядке, в котором они перечислены
            # в описании соответствующего запроса во входных данных.
            res = [n for n in sources if n in c]
            if res:
                f_out.write(f'{len(res)} {" ".join(res)}\n')
            else:
                f_out.write('0\n')


def F():
    """
    Необходимо осуществить GET-запрос к серверу по указанному номеру порта,
    передав значения чисел a и b в значениях одноимённых параметров запроса.
    Сервер ответит JSON-массивом из целых чисел. Сумму этих чисел необходимо
    распечатать в выходной файл.

    Статус: принята
    """
    import requests

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        url = f_in.readline().strip() + ':' + f_in.readline().strip()
        a, b = f_in.readline().strip(), f_in.readline().strip()

        res = requests.get(url, params={'a': a, 'b': b})
        arr = map(int, res.json())
        f_out.write(f'{sum(arr)}')


def G():
    """
    Вам дана база, в которой с помощью запроса CREATE TABLE tmp (ID INT NOT NULL)
    была создана таблица tmp и затем заполнена данными. Нужно написать запрос,
    возвращающий единственную строчку, содержащую в себе ровно один столбец res:
    количество уникальных записей в этой таблице.

    Ответ: SELECT COUNT(DISTINCT id) as res FROM tmp;
    Статус: принята
    """
    pass


if __name__ == '__main__':
    E()
    