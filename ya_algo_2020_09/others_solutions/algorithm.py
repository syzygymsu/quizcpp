"""
Решения задач пробного раунда онлайн-чемпионата по программированию Yandex Сup в категории Алгоритм.
https://contest.yandex.ru/yacup/
"""

from time import time


def A():
    """
    На различных мероприятиях команда стажировок регулярно разыгрывает призы в лотерею.
    Организаторы выбирают 10 случайных различных чисел от 1 до 32.
    Каждому участнику выдается лотерейный билет, на котором записаны 6
    различных чисел от 1 до 32. Билет считается выигрышным, если в нем есть не менее 3
    выбранных организаторами числа.
    Напишите программу, которая будет сообщать, какие билеты выигрышные.
    Сатус: принято
    """
    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        lototron = set(f_in.readline().split())
        n = int(f_in.readline())
        for _ in range(n):
            ticket = set(f_in.readline().split())
            if len(ticket & lototron) >= 3:
                res = 'Lucky'
            else:
                res = 'Unlucky'
            f_out.write(res+'\n')


def B():
    """
    Для каждой строки в своей базе данных найти самую короткую её подстроку,
    состоящую хотя бы из двух символов и являющуюся палиндромом. Если таких
    подстрок несколько, выбрать лексикографически минимальную.
    Сатус: принято
    """

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        data = f_in.read()
        # полиндромы длиной > 3 обязаны содержать в себе полиндром меньшей длины
        # неободимо проверить полиндромы только длины 2 и 3
        res = min(
            (a+b for a, b in zip(data, data[1:]) if a == b),
            default=''
        )
        if not res:
            res = min(
                (a+b+c for a, b, c in zip(data, data[1:], data[2:]) if a == c),
                default='-1'
            )
        f_out.write(res)


def C():
    """
    На плоскости n фигур (круги и прямоугольники). Возможно ли провести одну
    прямую, которая разделит каждую фигуру пополам (на две фигуры равной площади)?
    Сатус: принято
    """

    def cross_prod(c1, c2, c3):
        """Для трёх точек на плоскости считаем векторное произведение"""
        a1, a2 = c2[0] - c1[0], c2[1] - c1[1]
        b1, b2 = c3[0] - c1[0], c3[1] - c1[1]
        return a1*b2 - a2*b1

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n = int(f_in.readline())
        centers = []
        for _ in range(n):
            target_type, *data = map(int, f_in.readline().split())
            # прямая делит круг и прямоугольник на две равных части тогда и только
            # тогда, когда проходит через центр фигуры
            # координаты центров умножим на 2, чтоб работать только с целыми числами
            if target_type == 0:  # круг
                center = data[1] * 2, data[2] * 2
            else:  # прямоугольник
                center = data[0] + data[4], data[1] + data[5]

            if len(centers) == 0:
                centers.append(center)
            elif len(centers) < 2 and centers[0] != center:
                # если мы добавим две одинаковые точки, то будем проводить
                # прямую через 2 точки, что сделать всегда возможно
                centers.append(center)
            elif len(centers) == 2 and cross_prod(center, *centers) != 0:
                # три точки лежат на одной прямой тогда и только тогда, когда
                # векторное произведение двух векторов равно нулю
                res = 'No'
                break
        else:
            res = 'Yes'
        f_out.write(res)


def D():
    """
    Даны массив a длины n и массив b длины m. Все элементы обоих массивов — цифры
    от 0 до 9 включительно. Составим по этим массивам таблицу c размера n×m, где
    элемент в i-й строке и j-м столбце определяется формулой ci,j=ai⋅10^9+bj.
    Рассмотрим всевозможные пути из клетки c1,1 в клетку cn,m, состоящие только
    из перемещений вниз и вправо. Среди всех этих путей выберите такой, что сумма
    чисел в посещённых клетках максимальна, и выведите эту сумму.
    Сатус: принято
    """

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n, m = map(int, f_in.readline().split())
        a = list(map(int, f_in.readline().split()))
        b = list(map(int, f_in.readline().split()))
        # количество посещенных клеток не зависит от пути
        # вес одного элемента a больше, чем всего массива b, тогда:
        # -мы должны идти вдоль максимальных элементов а,
        # -переходить на другой a_max должны вдоль максимальных элементов b

        a_max = max(a)
        b_max = max(b)

        i_left, i_right = a.index(a_max), a[::-1].index(a_max)
        res_a = sum(a) + (m - 1) * a_max
        res_b = sum(b) + i_left * b[0] + (n - i_left - i_right - 1) * b_max + i_right * b[-1]

        if res_a == 0:
            f_out.write(f'{res_b}')
        else:
            f_out.write(f'{res_a}{res_b:0>9n}')


def E():
    """
    Распределённая сеть состоит из n вычислительных узлов, соединённых с помощью
    помощью n−1 кабелей. Расстоянием между двумя узлами назовем минимальное
    количество соединений на цепочке от одного узла к другому.
    После выбора узлов-хранилищ, для каждого узла сети определяется
    ближайшее к нему хранилище. Ненадёжностью сети он называет максимальное
    значение этой величины по всем узлам.
    Какие узлы выбрать, чтобы ненадёжность сети была минимальна?
    Сатус: проходит часть тестов, не проходит по времени
    """
    from collections import defaultdict

    def longest_branch(graph, start, visited=None):
        t = time()
        if visited is None:
            visited = set()
        queue = [(start, 1), ]
        branch = []
        res = []
        while queue:
            root, lvl = queue.pop()
            queue.extend((n, lvl+1) for n in graph[root] if n not in visited)

            if len(branch) >= lvl:
                if len(branch) > len(res):
                    res = branch.copy()
                while len(branch) >= lvl:
                    visited.remove(branch.pop())

            branch.append(root)
            visited.add(root)

        print(time() - t)
        if len(branch) > len(res):
            return branch
        else:
            return res

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n = int(f_in.readline())
        if n <= 3:
            f_out.write('1 2')
            return

        net = defaultdict(list)  # для каждого узла множество смежных
        # связный граф с n узлами и n-1 ребрами - дерево
        for _ in range(n-1):
            a, b = f_in.readline().split()
            net[a].append(b), net[b].append(a)
        # у дерева всегда есть самый длинный путь, который можно найти используя два обхода
        longest_path = longest_branch(net, start='1')
        longest_path = longest_branch(net, start=longest_path[-1])
        # если бы требовалось найти один такой узел, то нужно было брать центр самого длинного пути
        # с двумя узлами: проделеаем это дважды
        n = len(longest_path) - 1
        split = n // 2
        # левая часть и центр
        lp = longest_branch(net, start=longest_path[0], visited={longest_path[n-split+1], })
        split_left = lp[(len(lp) - 1) // 2]
        # правая часть и центр
        lp = longest_branch(net, start=longest_path[-1], visited={longest_path[split-1], })
        split_right = lp[(len(lp) - 1) // 2]
        if split_left == split_right:
            # в случае симмитричного графа у нас может выбраться центральный узел дважды
            split_right = lp[(len(lp) - 1) // 2 + 1]

        f_out.write(f'{split_left} {split_right}')


def E_test_chain():
    N = 200000
    with open('input.txt', 'w') as f:
        f.write(f'{N}\n')
        for i in range(1, N+1):
            f.write(f'{i} {i+1}\n')
    t = time()
    E()
    print(time() - t)


def E_test_tree():
    N = 200000
    with open('input.txt', 'w') as f:
        f.write(f'{N}\n')
        for i in range(2, N+1):
            f.write(f'{i} {i // 2}\n')
    t = time()
    E()
    print(time() - t)


def F():
    """
    Дан белый клетчатый листок размером n×m клеток. Сначала Альфред раскрашивает
    некоторые клетки в чёрный цвет, после чего Георг должен снова перекрасить все
    клетки в белый. Для этого Георг сколько угодно раз проделывает следующую операцию:
      - Поместить карандаш в левый нижний угол листка, после чего нарисовать путь
        в верхний правый угол листка. Путь должен проходить только по границам клеток,
        кроме того, передвигать карандаш можно только вправо и вверх.
      - Перекрасить все клетки листка, расположенные под нарисованным путём, в противоположный цвет.
    За какое минимальное число операций Георг сможет перекрасить лист в белый?
    Сатус: проходит часть тестов, не проходит по времени
    """

    with open('input.txt', 'r') as f_in, open('output.txt', 'w') as f_out:
        n, m, k = map(int, f_in.readline().split())
        if k == 0:
            f_out.write('0')
            return

        # таблицу представим в виде списка закрашенных полей в каждой строке
        rows = [[n+1, ] for _ in range(m)]
        for _ in range(k):
            x, y = map(int, f_in.readline().split())
            # для удобства развернем ось х
            x = n - 1 - x
            rows[y].append(x)

        # упорядочим в строках
        for v in rows:
            v.sort(reverse=True)

        # цвет в правом нижнем уголу
        color = rows[0][-1] == 0  # True - черный, False - белый

        full_rows = 0
        positions = [0] * (m+1)
        positions[-1] = n + 1  # буквально -1ая строка
        iteration = 0
        # выигрыщная стратегия для Георга - жадная, идти с правого нижнего угла
        # до левого верхнего и последовательно перекрашивать цвета
        while full_rows < m:
            for j in range(full_rows, m):
                row = rows[j]
                if color:
                    # слопываем закрашенные ячейки в данной строке
                    while positions[j] == row[-1] and positions[j] < positions[j-1]:
                        positions[j] = row.pop() + 1
                else:
                    # перемещаемся до ближайшей закрашенной ячейке
                    if row[-1] > positions[j-1]:
                        positions[j] = positions[j - 1]
                    else:
                        positions[j] = row[-1]

                if positions[j] == n + 1:
                    full_rows = j + 1
                elif positions[j] == 0:
                    break

            color = not color
            iteration += 1

        iteration -= color  # если закончили на полостью черном поле, последний шаг лишний
        f_out.write(f'{iteration}')


def F_test_stairs():
    # самый плохой случай - лесница вниз. ответ всегда 2N-1
    N = 500
    with open('input.txt', 'w') as f:
        f.write(f'{N} {N} {N}\n')
        for i in range(N):
            f.write(f'{i} {N-1-i}\n')
    t = time()
    F()
    print(time() - t)


if __name__ == "__main__":
    F_test_stairs()
    