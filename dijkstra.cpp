#include <iostream>
#include <limits.h>

using namespace std;

//колво вершин в графе
#define V 6

//метод поиска вершины с минимальным расстоянием из набора вершин, которые еще не включены в дерево кратчайших путей
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

//метод вывода построенного массива расстояний
void printSolution(int dist[])
{
    cout << "vertex \t distance from beg" << endl;
    for (int i = 0; i < V; i++)
        cout << i << " \t\t" << dist[i] << endl;
}

void dijkstra(int graph[V][V], int beg)
{
    int dist[V]; //выходной массив, в котором dist[i] будет содержат кратчайшее расстояние от начальной вершины до i

    bool sptSet[V]; //sptSet[i] будет true, если вершина i включена в дерево кратчайших путей или кратчайшее расстояние от начальной вершины до i уже окончательно установлено

    //опр все расстояния как бесконечность, а sptSet[] как false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    //расстояние от начальной вершины до самой себя всегда равно 0
    dist[beg] = 0;

    //кратчайший путь для всех вершин
    for (int count = 0; count < V - 1; count++)
    {
        //выбираем вершину с минимальным расстоянием из набора еще не обработанных вершин. в1 раз u всегда = начальной вершине
        int u = minDistance(dist, sptSet);

        //выбраная вершина обработана
        sptSet[u] = true;

        //апдейт расстояния до соседних вершин выбранной вершины
        for (int v = 0; v < V; v++)
        {
            // апдейт dist[v] если вершина v еще не включена в sptSet, существует ребро от u к v, и общий вес пути от начальной вершины до v через u меньше текущего значения dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printSolution(dist);
}

int main()
{
    int graph[V][V] = {{0, 4, 0, 0, 0, 0},
                       {4, 0, 8, 0, 0, 0},
                       {0, 8, 0, 7, 0, 4},
                       {0, 0, 7, 0, 9, 14},
                       {0, 0, 0, 9, 0, 10},
                       {0, 0, 4, 14, 10, 0}};

    dijkstra(graph, 0);

    return 0;
}