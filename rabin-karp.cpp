#include <iostream>
#include <string>
#include <cmath>

/*
алгоритм использует хеширование для поиска образца в тексте
1. вычисляем хеш образца и первого подстроки текста
2. сравниваем хеши:
если хеши совпадают, проверить образец и подстроку на совпадение
если совпадение найдено, вывести позицию вхождения
если хеши не совпадают, перемещать окно на один символ и пересчитать хеш подстроки
3. повторять до конца
*/

using namespace std;

const int PRIME = 101; // простое число для хеширования

//метод вычисления хеша строки
int hashString(const string& str, int length) {
    int hashValue = 0;
    for (int i = 0; i < length; i++) {
        hashValue += (int)str[i] * pow(PRIME, i);
    }
    return hashValue;
}

//метод поиска образца в тексте
void searchPattern(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    int patternHash = hashString(pattern, patternLength);

    for (int i = 0; i <= textLength - patternLength; i++) {
        string subtext = text.substr(i, patternLength);
        int subtextHash = hashString(subtext, patternLength);

        if (patternHash == subtextHash && pattern == subtext) {
            cout << "найдено вхождение образца в позиции " << i << endl;
        }
    }
}

int main() {
    system("chcp 65001");

    string text = "ABASABBABSBABASBBABA";
    string pattern = "SAB";

    cout << "исходный текст: " << text << endl;
    cout << "образец: " << pattern << endl;

    cout << "результаты поиска:" << endl;
    searchPattern(text, pattern);

    return 0;
}
