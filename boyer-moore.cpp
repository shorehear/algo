#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
алг сравнивает образец с текстом справа налево и если находит несовпадение, использует таблицы для определения
наибольшего возможного сдвига для минимизации количества сравнений

является эффективным благодаря тому, что использует инфу о совпавших и несовпавших символах, чтобы сделать
наибольший возможный сдвиг образца при поиске, уменьшая количество сравнений (=> поэтому эффективен в больших тестах)
*/
using namespace std;

const int ALPHABET_SIZE = 256;

//метод создания таблицы сдвигов для плохих символов
void computeBadCharTable(const string& pattern, vector<int>& badCharTable) {
    int patternLength = pattern.length();
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        badCharTable[i] = patternLength;
    }
    for (int i = 0; i < patternLength - 1; i++) {
        badCharTable[static_cast<int>(pattern[i])] = patternLength - 1 - i;
    }
}

//метод создания таблицы сдвигов для хороших суффиксов
void computeGoodSuffixTable(const string& pattern, vector<int>& goodSuffixTable) {
    int patternLength = pattern.length();
    vector<int> suffixLengths(patternLength, 0);

    //заполняем таблицу сдвигов для суффиксов
    for (int i = patternLength - 2; i >= 0; i--) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[patternLength - 1 - i + j]) {
            j--;
        }
        suffixLengths[i] = i - j;
    }

    //заполняем таблицу сдвигов для хороших суффиксов
    for (int i = 0; i < patternLength - 1; i++) {
        int j = patternLength - 1 - suffixLengths[i];
        goodSuffixTable[j] = patternLength - 1 - i;
    }
}

void searchBoyerMoore(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    vector<int> badCharTable(ALPHABET_SIZE);
    vector<int> goodSuffixTable(patternLength, patternLength);

    computeBadCharTable(pattern, badCharTable);
    computeGoodSuffixTable(pattern, goodSuffixTable);

    int shift = 0;
    while (shift <= textLength - patternLength) {
        int j = patternLength - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            cout << "найдено совпадение на позиции " << shift << endl;
            shift += goodSuffixTable[0];
        } else {
            int badCharShift = max(1, j - badCharTable[static_cast<int>(text[shift + j])]);
            int goodSuffixShift = goodSuffixTable[j + 1];
            shift += max(badCharShift, goodSuffixShift);
        }
    }
}

int main() {
    system("chcp 65001");

    string text, pattern;
    cout << "введите текст: ";
    cin >> text;
    cout << "введите образец: ";
    cin >> pattern;

    searchBoyerMoore(text, pattern);

    return 0;
}
