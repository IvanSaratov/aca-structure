#include <iostream>
#include <vector>
#include "../helpers/random.h"

using namespace std;

template <typename T>
void countingSort(vector<T> &array)
{
    T min, max;
    max = min = array[0];
    //Пробегаемся по всем элементам и ищем самый маленький и самый большой элемент в массиве
    //Для того что бы мы могли установить размер вспомогательного массива.
    for (size_t i = 1; i < array.size(); i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }

        if (array[i] > max)
        {
            max = array[i];
        }
    }

    //Заполняем наш счетчик нулями
    vector<T> counts(max - min + 1, 0);

    //Пробегаемся по главмному массиву, и увеличиваем соотвествующие значения
    for (size_t i = 0; i < array.size(); i++)
    {
        counts[array[i] - min]++;
    }

    //Перезаполняем наш массив заного, пробегаясь по всем счетчикам
    // counts[i] - показывает сколько раз встречалось то или иное число
    size_t index = 0;
    for (size_t i = 0; i < counts.size(); i++)
    {
        for (size_t j = 0; j < counts[i]; j++)
        {
            array[index++] = i + min;
        }
    }
}

int main()
{
    Random R(1, 10);
    vector<size_t> *array = R.GetVectorLong(10);

    cout << "Начальный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    //Сортируем
    countingSort(*array);

    cout << "Отсортированный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    return 0;
}