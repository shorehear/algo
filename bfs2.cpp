#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>

/*позволяет найти группы вершин, в которых каждая вершина связана с остальными через пути в графе
1. создаем список компонент связности и массив для отслеживания посещенных вершин (изначально все непосещены)
2. для кжадой непосещенной вершины:
создаем новую компоненту связности, с поиском в ширину всех вершин, достижимых из текущей вершины,
помечаем посещенные вершины и добавляем их в текущую компоненту
3. в конце получаем список компонент связности, где каждая компонента - группа вершин, связанных между собой
4. возвращает количество компонент связности и состав каждой компоненты. компоненты - непересекающиеся группы вершин,
где каждая вершина связана с другими внутри своей компоненты
*/

using namespace std;

struct Graph {
    int V; //колво вершин
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
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty()) {
                    int currentVertex = q.front();
                    q.pop();
                    component.push_back(currentVertex);

                    for (int neighbor : adj[currentVertex]) {
                        if (!visited[neighbor]) {
                            q.push(neighbor);
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

//метод для вывода дерева
void printTree(const vector<vector<int>>& tree) {
    for (int i = 0; i < tree.size(); i++) {
        cout << "компонента " << i + 1 << ": ";
        for (int vertex : tree[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }
}

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
    cout << "состав компонент связности (деревья):" << endl;

    printTree(connectedComponents);

    return 0;
} //8 9 // итд