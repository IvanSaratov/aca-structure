#include <vector>
#include <time.h>
#include <cmath>

#ifndef RANDOM_H
#define RANDOM_H

/**
 * Доплнительный класс для рандомизации и заполнения массива случайными данными
 * 
 * Работает только с векторами
 * Принимает в себя int и double значения
 */
class Random
{
private:
    double min, max;

public:
    /**
     * Стандартный конструктор, по умолчанию устанавливает границы в диапазоне от 0 до 100
     */
    Random()
    {
        srand(time(NULL));

        this->max = 100;
          this->min = 0;
    }

    /**
	 *   Конструктор double значений
     *
     *   @param min нижняя граница
	 *	 @param max верхняя граница
     */
    Random(double min, double max)
    {
        srand(time(NULL));

        if (max > min)
        {
            this->min = max;
            this->max = min;
        }
        else
        {
            this->max = max;
            this->min = min;
        }
    }

    /**
     * Конструктор для int
     * 
     * @param min нижняя граница
     * @param max верхняя граница
    */
    Random(int min, int max)
    {
        srand(time(NULL));

        if (max < min)
        {
            this->min = (double)max;
            this->max = (double)min;
        }
        else
        {
            this->max = (double)max;
            this->min = (double)min;
        }
    }

    ~Random() {}

    /**
     * Функция задает значения для границ
     * 
     * Работает с double
     * 
     * @param min нижняя граница
     * @param max верхняя граница
    */
    void SetMinMax(double min, double max)
    {
        this->min = min;
        this->max = max;
    }

    /**
     * @return возвращает нижнюю границу
    */
    double GetMin()
    {
        return this->min;
    }

    /**
     * @return возвращает верхнюю границу
    */
    double GetMax()
    {
        return this->max;
    }

    /**
     * Функция генерации произвольного Int числа
     * 
     * @param min нижняя граница
     * @param max верхняя граница
     * 
     * @return случайно int число
    */
    int NextInt(int min, int max)
    {
        return min + rand() % (max - min + 1);
    }

    /**
     * Функция генерации произвольного Int числа от заданных в классе границ
     * 
     * @return случайно int число
    */
    int NextInt()
    {
        return NextInt((int)this->min, (int)this->max);
    }

    /**
     * Функция генерации произвольного Long числа
     * 
     * @param min нижняя граница
     * @param max верхняя граница
     * 
     * @return возвращает случайное Long число
    */
    size_t NextLong(size_t min, size_t max)
    {
        return min + rand() % (max - min + 1);
    }

    /**
     * Функция генерации произвольного Long числа от заданных в классе границ
     * 
     * @return возвращает случайное Long число
    */
    size_t NextLong()
    {
        return NextLong((size_t)this->min, (size_t)this->max);
    }

    /**
     * Функция генерации произвольного Double числа
     * 
     * @param min нижняя граница
     * @param max верхняя граница
     * @param precision точность генерации после запятой
     * 
     * @return возвращает случайное Double число
    */
    double NextDouble(double min, double max, int precision = 2)
    {
        double value;

        value = rand() % (int)pow(10, precision);
        value = min + (value / pow(10, precision)) * (max - min);

        return value;
    }

    /**
     * Функция генерации произвольного Double числа от заданных в классе границ
     * 
     * @param precision точность генерации после запятой
     * 
     * @return возвращает случайное Double число
    */
    double NextDouble(int precision = 2)
    {
        return NextDouble(this->min, this->max, precision);
    }

    /**
     * Создает случайны целочисленный массив в памяти и возвращает на него указатель
     * 
     * @param count размер массива
     * 
     * @return возвращает указатель на массив в памяти
    */
    int *GetArrayInt(int count = 10)
    {
        int *A = new int[count];
        for (int i = 0; i < count; i++)
        {
            A[i] = NextInt();
        }

        return A;
    }

    /**
     * Создает случайны вещественный массив в памяти и возвращает на него указатель
     * 
     * @param count размер массива
     * @param precision точность после запятой
     * 
     * @return возвращает указатель на массив в памяти
    */
    double *GetArrayDouble(int count = 10, int precision = 2)
    {
        double *A = new double[count];
        for (int i = 0; i < count; i++)
        {
            A[i] = NextDouble(precision);
        }

        return A;
    }

    /**
     * Создает вектор целочисленных значений Long и возвращает на него указатель
     * 
     * @param count размер вектора
     * 
     * @return возвращает указатель на вектор
    */
    std::vector<size_t> *GetVectorLong(size_t count = 10)
    {
        std::vector<size_t> *A = new std::vector<size_t>(count);

        for (size_t i = 0; i < count; i++)
        {
            (*A)[i] = NextLong();
        }

        return A;
    }
};

#endif