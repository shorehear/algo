//поиск количества и состава компонент связности в заданном графе с использованием поиска в глубину

#include <iostream>
#include <vector>
#include <stack>
#include <windows.h>


/*
1. создаем список компонент связности и массив для отслеживания посещенных вершин
2. для каждой непосещенной вершины в графе:
начинаем новую компоненту связности
используем поиск в глубину для поиска всех связанных вершин
помечаем посещенные вершины и добавляем их в компоненту
3. возвращаем список компонент связности, где каждая компонента содержит связанные вершины
*/

using namespace std;

struct Graph {
    int V; //количество вершин
    vector<vector<int>> adj; //список смежности

    Graph(int vertices) : V(vertices), adj(vertices) {}

    //метод добавления ребра в граф
    void addEdge(int beg, int dest) {
        adj[beg].push_back(dest);
        adj[dest].push_back(beg); //для неориентированного графа
    }

    //метод поиска компонент связности
    vector<vector<int>> findConnectedComponents() {
        vector<bool> visited(V, false); //массив для отслеживания посещенных вершин
        vector<vector<int>> components; //список компонент связности

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                vector<int> component; //компонента связности
                stack<int> s;
                s.push(i);
                visited[i] = true;

                while (!s.empty()) {
                    int currentVertex = s.top();
                    s.pop();
                    component.push_back(currentVertex);

                    for (int neighbor : adj[currentVertex]) {
                        if (!visited[neighbor]) {
                            s.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }

                components.push_back(component);
            }
        }

        return components;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int V, E;
    cout << "введите количество вершин и рёбер: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "введите рёбра (beg dest):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest;
        cin >> beg >> dest;
        graph.addEdge(beg, dest);
    }

    vector<vector<int>> connectedComponents = graph.findConnectedComponents();

    cout << "количество компонент связности: " << connectedComponents.size() << endl;
    cout << "состав компонент связности:" << endl;

    for (int i = 0; i < connectedComponents.size(); i++) {
        cout << "компонента " << i + 1 << ": ";
        for (int vertex : connectedComponents[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}//10 11
