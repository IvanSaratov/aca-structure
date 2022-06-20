#include <iostream>
#include <vector>
#include "../helpers/random.h"

using namespace std;

template <typename T>
void heapify(vector<T> &array, size_t root, size_t bottom)
{
    size_t maxChild;
    bool done = false;

    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (array[root * 2] > array[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;

        if (array[root] < array[maxChild])
            swap(array[root], array[maxChild]);
        else
            done = true;
    }
}

template <typename T>
void heapSort(vector<T> &array)
{
    for (size_t i = (array.size() / 2); i >= 0; i--) {
        heapify(array, i, array.size() - 1);
    }
    //Проходимся сверху вниз по одному элементу
    for (size_t i = array.size() - 1; i >= 1; i--)
    {
        swap(array[0], array[i]);

        heapify(array, 0, i - 1);
    }
}

int main()
{
    Random R(1, 200);
    vector<size_t> *array = R.GetVectorLong(20);

    cout << "Начальный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    //Сортируем
    //Начинаем с первого и последнего элемента
    heapSort(*array);

    cout << "Отсортированный массив:" << endl;
    cout << "[ ";
    for (size_t i = 0; i < (*array).size(); i++)
    {
        cout << (*array)[i] << ", ";
    }
    cout << "]" << endl;

    return 0;
}