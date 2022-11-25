#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdio>

using namespace std;

vector<size_t> prefix_function(const string& s) {
    vector<size_t> pi(s.length(), 0);

    for (size_t i = 0; i < s.length(); ++i) {
        for (size_t j = 0; j <= i; j++) {
            if (s.substr(0, j) == s.substr(i - j + 1, j)) {
                pi[i] = j;
			}
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

    int sub_len = subword.length(); // Длина подстроки

    for (size_t i = 0; i < word.length(); i++) {
        if (pi[sub_len + 1 + i] == sub_len) {
            cout << word << "[" << i - sub_len + 1 << ".." << i << "] = " << subword << endl;
        }
    }
}