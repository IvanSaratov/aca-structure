#include <vector>
#include <time.h>
#include <cmath>

#ifndef RANDOM_H
#define RANDOM_H

class Random
{
private:
    double min, max;

public:
    Random()
    {
        srand(time(NULL));

        this->max = 100;
        this->min = 0;
    }

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

    void SetMinMax(double min, double max)
    {
        this->min = min;
        this->max = max;
    }

    double GetMin()
    {
        return this->min;
    }

    double GetMax()
    {
        return this->max;
    }

    int NextInt(int min, int max)
    {
        return min + rand() % (max - min + 1);
    }

    int NextInt()
    {
        return NextInt((int)this->min, (int)this->max);
    }

    size_t NextLong(size_t min, size_t max)
    {
        return min + rand() % (max - min + 1);
    }

    size_t NextLong()
    {
        return NextLong((size_t)this->min, (size_t)this->max);
    }

    double NextDouble(double min, double max, int precision = 2)
    {
        double value;

        value = rand() % (int)pow(10, precision);
        value = min + (value / pow(10, precision)) * (max - min);

        return value;
    }

    double NextDouble(int precision = 2)
    {
        return NextDouble(this->min, this->max, precision);
    }

    int *GetArrayInt(int count = 10)
    {
        int *A = new int[count];
        for (int i = 0; i < count; i++)
        {
            A[i] = NextInt();
        }

        return A;
    }

    double *GetArrayDouble(int count = 10, int precision = 2)
    {
        double *A = new double[count];
        for (int i = 0; i < count; i++)
        {
            A[i] = NextDouble(precision);
        }

        return A;
    }

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