#include <iostream>
#include <vector>
#include "../helpers/random.h"
#include <Windows.h>
#include <cstdio>

using namespace std;

template<typename T>
void radix_sort(vector<T>& array) {
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

    // Сортируем по разрядам числа 123 - три разряда
    for (size_t divider = 1; divider <= max; divider *= 10) {
        for (size_t i = 0; i < array.size(); i++) {     // Проходимся по всему массиву
            size_t no = array[i] / divider % 10;    // Находим первую цифру
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
    SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

    Random R(1, 50);
    vector<size_t>* array = R.GetVectorLong(15);    // Вектор случайны целых чисел

    // Выводи начальный массив
    cout << "Начальный массив:" << endl;
    cout << "[";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i];
        if (i != (*array).size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // Сортируем
    radix_sort(*array);

    // Выводим отсортированный массив
    cout << "Отсортированный массив:" << endl;
    cout << "[";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i];
        if (i != (*array).size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}