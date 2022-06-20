#include <iostream>
#include "../helpers/random.h"

using namespace std;

template <typename T>
void quickSort(T *array, size_t left, size_t right)
{
    //Пока указатели не пересекли друг друга
    if (left < right)
    {
        //Ищем центральный элемент
        size_t mid = array[(left + right) / 2];

        size_t i = left;
        size_t j = right;
        //Начинаем сдвигать границы массива
        while (i <= j)
        {
            //Если нашли не тот элемент останавливаем границы
            while (array[i] < mid)
                i++;
            while (array[j] > mid)
                j--;

            //Меням два элемента местами относительно среднего элемента
            if (i <= j)
                swap(array[i++], array[j--]);
        }

        quickSort(array, left, j);
        quickSort(array, i, right);
    }
}

int main()
{
    Random R(1, 200);
    //Размер массива
    const int n = 20;
    int *array = R.GetArrayInt(n);

    cout << "Начальный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i] << ", ";
    }
    cout << "]" << endl;

    //Сортируем
    //Начинаем с первого и последнего элемента
    quickSort(array, 0, n - 1);

    cout << "Отсортированный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i] << ", ";
    }
    cout << "]" << endl;

    return 0;
}