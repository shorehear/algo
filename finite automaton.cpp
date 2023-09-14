#include <iostream>
#include <vector>
#include <string>

/*
алг поиска по образцу с конечным автоматом строит детерм конечный автомат
(машину, кот может находиться в разных состояниях и переключаться между ними из того, что она видит на входе),
где каждое состояние представляет префикс образца. дальше авт перемещается по тексту, обрабатывая символы и
переходя между состояниями в соответствии с таблицей переходов авт. когда авт достигает конечного состояния,
обозначающего конец образца = что найдено совпадение и его позиция записывается
*/


using namespace std;

//метод построения конечного автомата
vector<vector<int>> buildFiniteAutomaton(const string& pattern) {
    int patternLength = pattern.length();
    vector<vector<int>> dfa(256, vector<int>(patternLength, 0));

    dfa[static_cast<int>(pattern[0])][0] = 1;
    int x = 0;

    for (int j = 1; j < patternLength; j++) {
        for (int c = 0; c < 256; c++) {
            dfa[c][j] = dfa[c][x];
        }
        dfa[static_cast<int>(pattern[j])][j] = j + 1;
        x = dfa[static_cast<int>(pattern[j])][x];
    }

    return dfa;
}

void searchWithFiniteAutomaton(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    vector<vector<int>> dfa = buildFiniteAutomaton(pattern);

    int state = 0;
    for (int i = 0; i < textLength; i++) {
        state = dfa[static_cast<int>(text[i])][state];
        if (state == patternLength) {
            cout << "найдено совпадение на позиции " << i - patternLength + 1 << endl;
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

    searchWithFiniteAutomaton(text, pattern);

    return 0;
}
