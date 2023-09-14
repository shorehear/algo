#include <iostream>
#include <vector>
#include <algorithm>

/*
алгоритм на определение возможности раскраски графа с заданным числом цветов (k) так
чтоб никакие две смежные вершины не имели один и тот же цвет
 */
using namespace std;

//проверка на возможность раскраски графа k цветами
bool canColorGraph(vector<vector<int>>& graph, vector<int>& color, int v, int k) {
    int V = graph.size();
    for (int c = 1; c <= k; c++) {
        bool isSafe = true;
        for (int i = 0; i < V; i++) {
            if (graph[v][i] && color[i] == c) {
                isSafe = false;
                break;
            }
        }
        if (isSafe) {
            color[v] = c;
            if (v == V - 1 || canColorGraph(graph, color, v + 1, k)) {
                return true;
            }
            color[v] = 0;
        }
    }
    return false;
}

bool colorGraph(vector<vector<int>>& graph, int k) {
    int V = graph.size();
    vector<int> color(V, 0);
    if (!canColorGraph(graph, color, 0, k)) {
        cout << "невозможно раскрасить граф с " << k << " цветами." << endl;
        return false;
    }
    cout << "граф раскрашен с " << k << " цветами:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "вершина " << i << " -> цвет " << color[i] << endl;
    }
    return true;
}

int main() {
    system("chcp 65001");

    int V, E;
    cout << "введите количество вершин и ребер: ";
    cin >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "введите ребра (формат: вершина1 вершина2):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1; // для неориентированного графа
    }

    int k;
    cout << "введите количество цветов (k): ";
    cin >> k;

    colorGraph(graph, k);

    return 0;
}
