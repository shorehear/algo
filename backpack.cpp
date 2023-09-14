#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight;
    int value;
};

int backpack(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    system("chcp 65001");

    int capacity;
    cout << "введите грузоподъемность рюкзака: ";
    cin >> capacity;

    int n;
    cout << "введите количество предметов: ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "введите вес и стоимость предмета " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    int maxTotalValue = backpack(items, capacity);

    cout << "максимальная суммарная стоимость: " << maxTotalValue << endl;

    return 0;
}
