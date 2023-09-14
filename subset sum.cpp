#include <iostream>
#include <vector>

using namespace std;

vector<int> greedySubsetSum(int N) {
    vector<int> subset;

    while (N > 0) {
        int largestPowerOfTwo = 1;
        while (largestPowerOfTwo * 2 <= N) {
            largestPowerOfTwo *= 2;
        }

        subset.push_back(largestPowerOfTwo);
        N -= largestPowerOfTwo;
    }

    return subset;
}

int main() {
    system("chcp 65001");

    int N;
    cout << "введите число N: ";
    cin >> N;

    vector<int> subset = greedySubsetSum(N);

    cout << "сумма подмножеств: ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
