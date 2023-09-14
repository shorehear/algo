#include <iostream>
#include <vector>

using namespace std;

//метод рекурсивного подсчета способов раскладки
int countWaysToPartition(int N, int K) {
    //если у нас нет предметов или ящиков, то ничего не делать
    if (N == 0 || K == 0) {
        return 1;
    }

    //если у нас больше предметов, чем ящиков, то мы можем либо положить один предмет в текущий ящик,
    //оставив N-1 предметов и K-1 ящик, либо не полагать ничего в текущий ящик, оставив N предметов и K ящиков
    return countWaysToPartition(N - 1, K - 1) + countWaysToPartition(N, K - 1);
}

int main() {
    system("chcp 65001");

    int N, K;
    cout << "введите количество предметов (N): ";
    cin >> N;

    cout << "введите количество ящиков (K): ";
    cin >> K;

    int ways = countWaysToPartition(N, K);

    cout << "количество способов раскладки: " << ways << endl;

    return 0;
}
