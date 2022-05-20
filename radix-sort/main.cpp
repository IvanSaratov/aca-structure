#include <iostream>
#include <vector>
#include "../helpers/random.h"

using namespace std;

template<typename T>
void radix_sort(vector<T> &array) {
    //Находим максимальный элемент в массиве
    T max = array[0];
    for (size_t i = 0; i < array.size(); i++) {
        if (max < array[i]) {
            max = array[i];
        }
    }

    //Разрядность системы
    const size_t raz = 10;

    //Создаем массив для сортировки
    vector<vector<T>> tmp(raz);
    for (size_t i = 0; i < raz; i++) {
        tmp[i].resize(array.size());
    }

    vector<T> sizes(tmp.size());

    for (size_t divider = 1; divider <= max; divider *= 10) {
        for (size_t i = 0; i < array.size(); i++) {
            size_t no = array[i] / divider % 10;
            tmp[no][sizes[no]++] = array[i];
        }

        size_t index = 0;
        for (size_t i = 0; i < tmp.size(); i++) {
            for (size_t j = 0; j < sizes[i]; j++) {
                array[index++] = tmp[i][j];
            }
            sizes[i] = 0;
        }
    }
}

int main()
{
    Random R(1, 200);
    vector<size_t> *array = R.GetVectorLong(15);

    cout << "Начальный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    //Сортируем
    radix_sort(*array);

    cout << "Отсортированный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    return 0;
}