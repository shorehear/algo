#include <iostream>
#include <vector>
#include <string>

/*
поиск всех вхождений подстроки в тексте. алг использует вычисленную таблицу сдвигов, чтобы избежать лишних сравнений символов
1.таблица сдвигов:
    1. создаем таблицу с нулями
    2. сравниваем символы образца и определяем макс совпадающий префикс и суффикс
    3. заполняем таблицу этой инфой
2. создаем индексы для текста (i) и образца (j) в 0
3. сравниваем символы текста и образца по индексам i и j
если символы совпадают, увеличиваем i и j на 1
если j достигает конца образца, находим вхождение образца в тексте, сохраняем его позицию и обновляем j с таблицей сдвигов
если символы не совпадают и j не равно 0, обновляем j с таблицей сдвигов
если символы не совпадают и j равно 0, увеличиваем i на 1
4. повтор до завершения
*/

using namespace std;

//метод создания таблицы сдвигов для подстроки
vector<int> computeLPS(const string& pattern) {
    const int patternLength = pattern.length();
    vector<int> lps(patternLength, 0);
    int len = 0; //длина текущего префикса-суффикса

    int i = 1;
    while (i < patternLength) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

//метод поиска всех вхождений образца в тексте
void searchPattern(const string& text, const string& pattern) {
    const int textLength = text.length();
    const int patternLength = pattern.length();
    vector<int> lps = computeLPS(pattern);

    int i = 0; //индекс в тексте
    int j = 0; //индекс в образце

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            int startPosition = i - j;
            cout << "найдено вхождение образца в позиции " << startPosition << endl;
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    system("chcp 65001");

    string text = "ABCABCABDABABABCABCABAB";
    string pattern = "ABCABAB";

    cout << "исходный текст: " << text << endl;
    cout << "образец: " << pattern << endl;

    cout << "результаты поиска:" << endl;
    searchPattern(text, pattern);

    return 0;
}
