#include <iostream>
#include <vector>

using namespace std;

//Тревиальная версия за O(n3)
vector<size_t> prefix_triv(string s)
{
    size_t n = s.length();
    vector<size_t> pi(n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j <= i; j++)
            if (s.substr(0, j) == s.substr(i - j + 1, j))
                pi[i] = j;

    return pi;
}

//Алгоритм Кнута-Праттом
vector<size_t> prefix_knut(string s)
{
    size_t n = s.length();
    vector<size_t> pi(n);

    for (size_t i = 1; i < n; i++)
    {
        size_t j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }

    return pi;
}

int main()
{
    return 0;
}