#include <iostream>
#include <vector>
#include <limits.h>

/*
алгоритм нахождения кратчайших путей из одной вершины до всех остальных вершин во взвешенном графе,
даже если в графе присутствуют рёбра с отрицательным весом (при условии, что нет отрицательных циклов)
*/

using namespace std;

struct Edge {
    int beg, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) : V(v), E(e) {}
};

void BellmanFord(Graph& graph, int beg) {
    int V = graph.V;
    int E = graph.E;
    vector<int> dist(V, INT_MAX); //определяем расстояние до вершин как бесконечность
    dist[beg] = 0; //расстояние до начальной вершины равно 0

    //обновляем расстояния V-1 раз, где V - количество вершин
    for (int i = 0; i < V - 1; i++) {
        //перебираем все рёбра и обновляем расстояния, если находим более короткий путь
        for (int j = 0; j < E; j++) {
            int u = graph.edges[j].beg;
            int v = graph.edges[j].dest;
            int weight = graph.edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    //проверяем наличие отрицательных циклов
    for (int i = 0; i < E; i++) {
        int u = graph.edges[i].beg;
        int v = graph.edges[i].dest;
        int weight = graph.edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "graph contains a negative cycle!" << endl;
            return;
        }
    }

    //выводим кратчайшие расстояния до всех вершин
    cout << "shortest distances from the top " << beg << " to all other vertex:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "vertex " << i << ": " << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V, E);

    cout << "enter edge (beg dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest, weight;
        cin >> beg >> dest >> weight;
        graph.edges.push_back({beg, dest, weight});
    }

    int beg;
    cout << "enter starting vertex: ";
    cin >> beg;

    //находим кратчайшие пути и выводим расстояния
    BellmanFord(graph, beg);

    return 0;
}
