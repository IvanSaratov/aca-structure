#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdio>

using namespace std;

vector<size_t> prefix_function(const string& s) {
    vector<size_t> pi(s.length(), 0);

    for (size_t i = 1; i < s.length(); i++) {
        size_t j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        }
        else {
            pi[i] = j;
        }
    }

    return pi;
}

int main() {
	SetConsoleOutputCP(1251);   // Устанавливаем кодировку для windows

    string word, subword;
    cout << "Введите изначальную строку: ";
    cin >> word;
    cout << "Введите подстроку: ";
    cin >> subword;

    vector<size_t> pi = prefix_function(subword + '#' + word);

    int sub_len = subword.length();

    for (size_t i = 0; i < word.length(); i++) {
        if (pi[sub_len + 1 + i] == sub_len) {
            cout << word << "[" << i - sub_len + 1 << ".." << i << "] = " << subword << endl;
        }
    }
}