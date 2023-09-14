#include <iostream>
#include <vector>
#include <algorithm>

/*
алгоритм нахождения минимального остовного дерева (покрывающего дерева) во взвешенном графе
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


bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

//метод нахождения корня вершины в наборе
int find(vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

//метод объединения двух поддеревьев
void Union(vector<int>& parent, int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void KruskalMST(Graph& graph) {
    vector<Edge> result; //минимальное остовное дерево
    int i = 0; //индекс текущего результата
    int e = 0; //индекс текущего ребра

    //сортируем ребра по весу в неубывающем порядке
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    //выделяем память для хранения родительских вершин
    vector<int> parent(graph.V, -1);

    //количество ребер в минимальном остовном дереве равно V-1
    while (e < graph.V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];

        int x = find(parent, nextEdge.beg);
        int y = find(parent, nextEdge.dest);

        //если включение данного ребра не создаст цикл, включаем его
        if (x != y) {
            result.push_back(nextEdge);
            Union(parent, x, y);
            e++;
        }
    }

    //выводим ребра минимального остовного дерева
    cout << "minimum spanning tree edges:" << endl;
    for (const Edge& edge : result) {
        cout << edge.beg << " - " << edge.dest << " (" << edge.weight << ")" << endl;
    }
}

int main() {
    int V, E;
    //выводим количество вершин и ребер
    cout << "enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V, E);

    //вводим ребра
    cout << "enter edges (beg dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest, weight;
        cin >> beg >> dest >> weight;
        graph.edges.push_back({beg, dest, weight});
    }

    //находим минимальное остовное дерево и выводим его ребра
    KruskalMST(graph);

    return 0;
}
