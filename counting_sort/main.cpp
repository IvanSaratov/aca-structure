#include <iostream>
#include <vector>
#include "../helpers/random.h"
#include <Windows.h>
#include <cstdio>

using namespace std;

template <typename T>
void countingSort(vector<T>& array)
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

    // Создаем вспомогательный массив
    // Заполняем наш счетчик нулями
    vector<T> counts(max - min + 1, 0);

    // Пробегаемся по главмному массиву, и увеличиваем соотвествующие значения
    for (size_t i = 0; i < array.size(); i++)
    {
        counts[array[i] - min]++;
    }

    // Перезаполняем наш массив заново, пробегаясь по всем счетчикам
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
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

    Random R(0, 10);    // Дополнительный класс для генерации случайных чисел
    vector<size_t>* array = R.GetVectorLong(10);    // Сгенерируем вектор случайных чисел типа Long

    // Покажем изначальный массив
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

    // Функция сортировки
    countingSort(*array);

    // Покажем отсортированный массив
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