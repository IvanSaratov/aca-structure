#include <iostream>
#include "../helpers/random.h"
#include <Windows.h>
#include <cstdio>

using namespace std;

template <typename T>
void quickSort(T* array, size_t left, size_t right)
{
    //���� ��������� �� ��������� ���� �����
    if (left < right)
    {
        //���� ����������� �������
        size_t mid = array[(left + right) / 2];

        size_t i = left;
        size_t j = right;
        //�������� �������� ������� �������
        while (i <= j)
        {
            //���� ����� �� ��� ������� ������������� �������
            while (array[i] < mid)
                i++;
            while (array[j] > mid)
                j--;

            //����� ��� �������� ������� ������������ �������� ��������
            if (i <= j)
                swap(array[i++], array[j--]);
        }

        // ��������� ����� �����
        quickSort(array, left, j);
        // ��������� ������ �����
        quickSort(array, i, right);
    }
}

int main()
{
    SetConsoleOutputCP(1251);   // ������������� ��������� ��� windows

    Random R(1, 50);
    //������ �������
    const int n = 20;
    int* array = R.GetArrayInt(n);

    cout << "��������� ������:" << endl;
    cout << "[";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i];
        if (i != n - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    //���������
    //�������� � ������� � ���������� ��������
    quickSort(array, 0, n - 1);

    cout << "��������������� ������:" << endl;
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