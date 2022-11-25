#include <iostream>
#include <vector>
#include "../helpers/random.h"
#include <Windows.h>
#include <cstdio>

using namespace std;

template <typename T>
void heapify(T* array, int n, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && array[l] > array[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && array[r] > array[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(array[i], array[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(array, n, largest);
    }
}

template <typename T>
void heapSort(T* array, int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(array[0], array[i]);

        // вызываем процедуру heapify на уменьшенной куче
		heapify(array, i, 0);
    }
}

int main()
{
    SetConsoleOutputCP(1251);

    Random R(1, 50);
    size_t n = 20;
    int* array = R.GetArrayInt(n);

    cout << "Начальный массив:" << endl;
    cout << "[";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i];
		if (i != n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    //Сортируем
    //Начинаем с первого и последнего элемента
    heapSort(array, n);

    cout << "Отсортированный массив:" << endl;
    cout << "[";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i];
        if (i != n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}