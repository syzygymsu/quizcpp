https://contest.yandex.ru/ yacup /contest/19811/problems

A  
На различных мероприятиях команда стажировок регулярно разыгрывает призы в лотерею.
Организаторы выбирают 10 случайных различных чисел от 1 до 32.
Каждому участнику выдается лотерейный билет, на котором записаны 6
различных чисел от 1 до 32. Билет считается выигрышным, если в нем есть не менее 3
выбранных организаторами числа.
Напишите программу, которая будет сообщать, какие билеты выигрышные.
    
   
B  
Для каждой строки в своей базе данных найти самую короткую её подстроку,
состоящую хотя бы из двух символов и являющуюся палиндромом. Если таких
подстрок несколько, выбрать лексикографически минимальную.


C  
На плоскости n фигур (круги и прямоугольники). Возможно ли провести одну
прямую, которая разделит каждую фигуру пополам (на две фигуры равной площади)?


D  
Даны массив a длины n и массив b длины m. Все элементы обоих массивов — цифры
от 0 до 9 включительно. Составим по этим массивам таблицу c размера n×m, где
элемент в i-й строке и j-м столбце определяется формулой ci,j=ai*10^9+bj.
Рассмотрим всевозможные пути из клетки c1,1 в клетку cn,m, состоящие только
из перемещений вниз и вправо. Среди всех этих путей выберите такой, что сумма
чисел в посещённых клетках максимальна, и выведите эту сумму.


E  
Распределённая сеть состоит из n вычислительных узлов, соединённых с помощью
помощью n−1 кабелей. Расстоянием между двумя узлами назовем минимальное
количество соединений на цепочке от одного узла к другому.
После выбора узлов-хранилищ, для каждого узла сети определяется
ближайшее к нему хранилище. Ненадёжностью сети он называет максимальное
значение этой величины по всем узлам.
Какие узлы выбрать, чтобы ненадёжность сети была минимальна?


F
Дан белый клетчатый листок размером n×m клеток. Сначала Альфред раскрашивает
некоторые клетки в чёрный цвет, после чего Георг должен снова перекрасить все
клетки в белый. Для этого Георг сколько угодно раз проделывает следующую операцию:
  - Поместить карандаш в левый нижний угол листка, после чего нарисовать путь
    в верхний правый угол листка. Путь должен проходить только по границам клеток,
    кроме того, передвигать карандаш можно только вправо и вверх.
  - Перекрасить все клетки листка, расположенные под нарисованным путём, в противоположный цвет.
За какое минимальное число операций Георг сможет перекрасить лист в белый?


D2
Имеется числовая последовательность, на первом шаге состоящая из двух чисел 1
. На каждом шаге следующем шаге между каждыми двумя соседними элементами добавляется новый элемент, равный их сумме. После первых нескольких шагов последовательность выглядит следующим образом:

1 1
121
13231
143525341
На собеседовании Алексей хочет попросить кандидата написать программу, которая по заданному числу n будет определять, сколько раз число n будет встречаться в последовательности на n-м шаге?
