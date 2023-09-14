#include <windows.h>
#include <iostream>
#include <vector>
#include <stack>

//алгоритм поиска количества и состава сильно связных компонент в ориентированном графе с использованием поиска в глубину

using namespace std;

/*
1. поиск в глубину на исходном графе, сохраняя вершины в стеке в порядке завершения. запоминаем порядок завершения для каждой вершины
2. переворачиваем граф, создаем обратный, меняя направление всех рёбер исходного
3. поиск в глубину на обратном графе, начиная с вершин в порядке завершения первого поиска. каждый запуск поиска формирует сильно связную компоненту
4. пполучаем список сильно связных компонент и их состав
*/

struct Graph {
    int V; //количество вершин
    vector<vector<int>> adj; //список смежности

    Graph(int vertices) : V(vertices), adj(vertices) {}

    //метод добавления ребра в граф
    void addEdge(int beg, int dest) {
        adj[beg].push_back(dest);
    }

    //1 шаг
    void firstDFS(int vertex, vector<bool>& visited, stack<int>& s) {
        visited[vertex] = true;

        for (int neighbor : adj[vertex]) {
            if (!visited[neighbor]) {
                firstDFS(neighbor, visited, s);
            }
        }

        s.push(vertex);
    }

    //2 шаг
    void secondDFS(int vertex, vector<bool>& visited, vector<int>& component) {
        visited[vertex] = true;
        component.push_back(vertex);

        for (int neighbor : adj[vertex]) {
            if (!visited[neighbor]) {
                secondDFS(neighbor, visited, component);
            }
        }
    }

    //метод нахождения сильно связных компонент
    vector<vector<int>> findStronglyConnectedComponents() {
        vector<bool> visited(V, false);
        stack<int> s;

        //первый поиск, сохраняя вершины в стеке в порядке завершения
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                firstDFS(i, visited, s);
            }
        }

        //переворачиваем граф (меняем направление рёбер)
        Graph reversedGraph(V);
        for (int i = 0; i < V; i++) {
            for (int neighbor : adj[i]) {
                reversedGraph.addEdge(neighbor, i);
            }
        }

        //снова опр массив посещенных вершин
        visited.assign(V, false);

        vector<vector<int>> stronglyConnectedComponents;

        //второй поиск на обратном графе, обрабатывая вершины из стека
        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            if (!visited[currentVertex]) {
                vector<int> component;
                reversedGraph.secondDFS(currentVertex, visited, component);
                stronglyConnectedComponents.push_back(component);
            }
        }

        return stronglyConnectedComponents;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int V, E;
    cout << "введите количество вершин и рёбер: ";
    cin >> V >> E;

    Graph graph(V);

    cout << "введите рёбра (н, к):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest;
        cin >> beg >> dest;
        graph.addEdge(beg, dest);
    }

    vector<vector<int>> stronglyConnectedComponents = graph.findStronglyConnectedComponents();

    cout << "количество сильно связных компонент: " << stronglyConnectedComponents.size() << endl;
    cout << "состав сильно связных компонент:" << endl;

    for (int i = 0; i < stronglyConnectedComponents.size(); i++) {
        cout << "компонента " << i + 1 << ": ";
        for (int vertex : stronglyConnectedComponents[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
