#include <iostream>
#include <vector>
#include <queue>
#include <climits>

/*
поиск кратчайших расстояний от выбранной стартовой вершины до всех других вершин в графе:
1. выбираем старт вершину и опр расстояния до всех остальных
2. очередь для поиска в ширину.
3. со стартовой вершины посещаем соседние вершины и обновляем расстояния, если находим более короткий путь
4. пока не посетим все вершины или не обработаем все достижимые вершины - продолжаем
5. получаем кратчайшие расстояния от стартовой вершины до всех остальных
 */

using namespace std;

struct Edge {
    int dest;
    int weight;
};

struct Graph {
    int V;
    vector<vector<Edge>> adj;

    Graph(int vertices) : V(vertices), adj(vertices) {}
};

//метод добавления ребра в граф
void addEdge(Graph& graph, int beg, int dest, int weight) {
    graph.adj[beg].push_back({dest, weight});
    graph.adj[dest].push_back({beg, weight}); //для неориентированного графа
}

//метод поиска кратчайших путей из заданной вершины
vector<int> BFSShortestPath(const Graph& graph, int startVertex) {
    vector<int> distance(graph.V, INT_MAX); //устанавливаем бесконечные расстояния
    distance[startVertex] = 0; //расстояние от самой себя равно 0

    queue<int> q;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        for (const Edge& edge : graph.adj[currentVertex]) {
            int neighborVertex = edge.dest;
            int edgeWeight = edge.weight;

            if (distance[neighborVertex] == INT_MAX) {
                //в1 раз когда мы достигаем соседней вершины, устанавливаем расстояние
                distance[neighborVertex] = distance[currentVertex] + edgeWeight;
                q.push(neighborVertex);
            }
        }
    }

    return distance;
}

int main() {
    int V, E;
    cout << "enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "enter edge (beg dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest, weight;
        cin >> beg >> dest >> weight;
        addEdge(graph, beg, dest, weight);
    }

    int startVertex;
    cout << "enter starting vertex: ";
    cin >> startVertex;

    vector<int> shortestDistances = BFSShortestPath(graph, startVertex);

    cout << "shortest distances from a vertex " << startVertex << "to other peaks:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "vertex " << i << ": " << shortestDistances[i] << endl;
    }

    return 0;
}
