#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

//опр, является ли точка p1 меньше точки p2 с учетом их полярного угла относительно начальной точки
bool comparePoints(const Point& p1, const Point& p2) {
    //вычисляем разницу между углами от начальной точки
    int orientation = (p1.x * p2.y) - (p2.x * p1.y);

    //если угол между p1 и p2 положительный, то p1 идет раньше p2
    if (orientation > 0) return true;

    //если угол между p1 и p2 отрицательный, то p2 идет раньше p1
    if (orientation < 0) return false;

    //если угол между p1 и p2 равен нулю, выбираем точку с меньшей дистанцией к начальной точке
    return (p1.x * p1.x + p1.y * p1.y) < (p2.x * p2.x + p2.y * p2.y);
}

//вычисляет выпуклую оболочку и возвращает её в виде вектора точек
vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();

    //находим начальную точку с наименьшей y-координатой
    int pivot = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[pivot].y || (points[i].y == points[pivot].y && points[i].x < points[pivot].x)) {
            pivot = i;
        }
    }

    //начальную точку в начало вектора
    swap(points[0], points[pivot]);

    //сортируем остальные точки по полярному углу относительно начальной точки
    sort(points.begin() + 1, points.end(), comparePoints);

    //стек для построения выпуклой оболочки
    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);

    //выпуклая оболочка
    for (int i = 2; i < n; i++) {
        while (hull.size() > 1) {
            Point top = hull.top();
            hull.pop();
            Point secondTop = hull.top();

            //проверка является ли следующая точка точкой оболочки
            if (((points[i].x - secondTop.x) * (top.y - secondTop.y)) - ((top.x - secondTop.x) * (points[i].y - secondTop.y)) <= 0) {
                //если точка не является частью оболочки, удаляем последнюю точку из стека
                continue;
            }

            //возвращаем точку в стек
            hull.push(top);
            break;
        }

        //добавляем следующую точку в стек
        hull.push(points[i]);
    }

    //переводим точки из стека в вектор
    vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }

    return result;
}

int main() {
    int n;
    cout << "enter the number of points: ";
    cin >> n;

    vector<Point> points(n);

    cout << "enter the coordinates of the points (x, y)" << endl;
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    //находим выпуклую оболочку
    vector<Point> convexHullPoints = convexHull(points);

    cout << "convex hull points:" << endl;
    for (const Point& p : convexHullPoints) {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}
