[Вернуться на главную](../README.md)

# Красно-черное дерево

[Код программы](main.cpp)

![Пример вывода](images/result.png)

Красно-черные деревья относятся к сбалансированным бинарным деревьям поиска. Как и бинарное дерево, крачно-черное обладает свойствами:
1. Оба поддерева являются бинарными деревьями поиска.
2. Для каждого узла с ключом __k__ выполняется критерий упорядочения: ключи всех левых потомков <= __k__ < ключи всех правых потомков.

Так же добавляя свои свойства:
1. Каждый узел окрашен либо в красный, либо в черный цвет (в структуре данных узла появляется дополнительное поле – бит цвета).
2. Корень окрашен в черный цвет.
3. Листья(так называемые NULL-узлы) окрашены в черный цвет.
4. Каждый красный узел должен иметь два черных дочерних узла. Нужно отметить, что у черного узла могут быть черные дочерние узлы. Красные узлы в качестве дочерних могут иметь только черные.
5. Пути от узла к его листьям должны содержать одинаковое количество черных узлов(это черная высота).

## Вставка элементов

Вставка в красно-черное дерево начинается со вставки элемента, как в обычном бинарном дереве поиска. Только здесь элементы вставляются в позиции NULL-листьев. Вставленный узел всегда окрашивается в красный цвет. Далее идет процедура проверки сохранения свойств красно-черного дерева $1-5$.

Свойство 1 не нарушается, поскольку новому узлу сразу присваивается красный цвет.

Свойство 2 нарушается только в том случае, если у нас было пустое дерево и первый вставленный узел (он же корень) окрашен в красный цвет. Здесь достаточно просто перекрасить корень в черный цвет.

Свойство 3 также не нарушается, поскольку при добавлении узла он получает черные листовые NULL-узлы.

В основном встречаются 2 других нарушения:

1) Красный узел имеет красный дочерний узел (нарушено свойство $4$).

2) Пути в дереве содержат разное количество черных узлов (нарушено свойство $5$).