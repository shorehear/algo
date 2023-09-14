#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool isConnected(vector<vector<int>>& graph, int V) {
    vector<bool> visited(V, false);

    //находим первую непосещенную вершину и начинаем из неё
    int startVertex = 0;
    for (int i = 0; i < V; i++) {
        if (graph[i].size() > 0) {
            startVertex = i;
            break;
        }
    }

    stack<int> st; //хранит вершины графа в алгоритме нахождения эйлерова графа
    st.push(startVertex);
    visited[startVertex] = true;

    while (!st.empty()) { //выполняем, пока стек непустой
        int u = st.top();
        st.pop();

        for (int v : graph[u]) {
            if (!visited[v]) {
                st.push(v);
                visited[v] = true;
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i] && graph[i].size() > 0) {
            return false;
        }
    }

    return true;
}

void findEulerCycle(vector<vector<int>>& graph, int V) {
    if (!isConnected(graph, V)) {
        cout << "graph is not connected, there is no Eulerian cycle." << endl;
        return;
    }

    vector<int> inDegree(V, 0); //отслеживание степеней вершин в графе
    vector<int> outDegree(V, 0); //отслеживание невходящих
    vector<vector<int>> tempGraph = graph; //копия графа

    //вычисляем входящие и исходящие степени вершин
    for (int u = 0; u < V; u++) {
        outDegree[u] = graph[u].size();
        for (int v : graph[u]) {
            inDegree[v]++;
        }
    }

    //начинаем с вершины с нечетной степенью (если есть), или с любой вершины
    int startVertex = 0;
    for (int u = 0; u < V; u++) {
        if (outDegree[u] % 2 == 1) {
            startVertex = u;
            break;
        }
        if (outDegree[u] > 0) {
            startVertex = u;
        }
    }

    stack<int> st;
    vector<int> result; //здесь будет храниться эйлеров цикл

    st.push(startVertex);

    while (!st.empty()) {
        int u = st.top();

        if (outDegree[u] == 0) {
            result.push_back(u);
            st.pop();
        } else {
            int v = tempGraph[u].back();
            tempGraph[u].pop_back();
            outDegree[u]--;
            inDegree[v]--;
            st.push(v);
        }
    }

    cout << "euler cycle in a graph:" << endl;
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main() {
    int V, E;
    cout << "enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> graph(V);

    cout << "enter edge (beg dest):" << endl;
    for (int i = 0; i < E; i++) {
        int beg, dest;
        cin >> beg >> dest;
        graph[beg].push_back(dest);
        graph[dest].push_back(beg); //граф неориентированный, добавляем обратное ребро
    }

    findEulerCycle(graph, V);

    return 0;
}
