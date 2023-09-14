#include <iostream>
#include <vector>
#include <queue>
#include <climits>

/*
алгоритм для нахождения минимального остовного дерева во взвешенном графе, работает на уровне вершин
*/

using namespace std;

struct Edge {
    int dest, weight;
};

struct Graph {
    int V;
    vector<vector<Edge>> adj;

    Graph(int v) : V(v), adj(v) {}

    //добавляем ребра в граф
    void addEdge(int beg, int dest, int weight) {
        adj[beg].push_back({dest, weight});
        adj[dest].push_back({beg, weight});
    }
};

//вершина и ее вес
struct Vertex {
    int v, weight;
};

//сравниваем веса для приоритетной очереди вершин
struct CompareVertex {
    bool operator()(const Vertex& v1, const Vertex& v2) {
        return v1.weight > v2.weight;
    }
};

//метод поиска минимального остовного дерева
void PrimMST(Graph& graph) {
    int V = graph.V;
    vector<bool> inMST(V, false); //включена ли вершина в минимальное остовное дерево
    vector<int> key(V, INT_MAX);  //мин веса для вершин
    vector<int> parent(V, -1);    //родительские вершины

    //старт с первой вершины
    key[0] = 0;

    //приоритетная очередь для хранения вершин и их весов
    priority_queue<Vertex, vector<Vertex>, CompareVertex> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();

        inMST[u] = true;

        //перебор смехных вершин и апдейт ключей
        for (const Edge& edge : graph.adj[u]) {
            int v = edge.dest;
            int weight = edge.weight;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({v, key[v]});
            }
        }
    }

    //вывод рёбер минимального остовного дерева
    cout << "minimum spanning tree edges:" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " (" << key[i] << ")" << endl;
    }
}

int main() {
    int V, E;
    cout << "enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "enter edges (beg dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest, weight;
        cin >> beg >> dest >> weight;
        graph.addEdge(beg, dest, weight);
    }

    //находим минимальное остовное дерево и выводим его рёбра
    PrimMST(graph);

    return 0;
}
