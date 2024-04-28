#ifndef algorithm_h
#define algorithm_h

#include <vector>
#include <cmath>

//-----------------------нормальное расположение вершин------------

struct Edge {
    int u;
    int v;
    Edge(int u, int v) : u(u), v(v) {}
};

//функция для преобразования списка рёбер в список смежности
std::vector<std::vector<int> > edgesToAdjacencyList(const std::vector<Edge> edges);

//вектор в двумерном пространстве
struct planeVector {
    int dx, dy;

    planeVector() : dx(0), dy(0) {}
    planeVector(double x, double y) : dx(x), dy(y) {};

    inline double norm() const {
        return sqrt(dx * dx + dy * dy);
    }
};

//точка в двумерном пространстве
struct Point {
    int x;
    int y;
    int num;
    
    Point() : x(0), y(0) {}
    Point(double x, double y, int num) : x(x), y(y), num(num) {}
};

//алгоритм расстановки вершин
class fruchtermanReingold {
public:
    fruchtermanReingold(const std::vector<std::vector<int> > &adjList, double k = 30.0);
    void operator()(std::vector<Point>& positions);

private:
    const std::vector<std::vector<int> > adjList;
    const double k;
    const double kSquared;
    double temp;
    std::vector<Edge> edges;
    std::vector<planeVector> power;
};



//-----------------------центруем и масштабируем граф-----------------

void centerGraph(int V, std::vector<Point>& vertexCoords, int width, int height);
void scaleGraph(int V, std::vector<Point>& vertexCoords, int width, int height, int vertexSize);

#endif