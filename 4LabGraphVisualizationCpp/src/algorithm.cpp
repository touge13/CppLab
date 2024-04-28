#include "../include/algorithm.h"

//-----------------------нормальное расположение вершин------------

//функция для преобразования списка рёбер в список смежности
std::vector<std::vector<int> > edgesToAdjacencyList(const std::vector<Edge> edges) {
    int maxVertex = -1;
    for (const auto& edge : edges) {
        maxVertex = std::max(maxVertex, std::max(edge.u, edge.v));
    }

    //увеличим размер adjacencyList до максимального номера вершины + 1
    std::vector<std::vector<int> > adjacencyList(maxVertex + 1);
    for (const auto& edge : edges) {
        adjacencyList[edge.u].push_back(edge.v);
        adjacencyList[edge.v].push_back(edge.u);
    }

    return adjacencyList;
}

//функция для расстановки вершин  
void fruchtermanReingold::operator()(std::vector<Point>& positions) {
    planeVector start;
    start.dx = 0;
    start.dy = 0;

    fill(power.begin(), power.end(), start);

    //сила отталкивания между парами вершин
    for (int vID = 0; vID < adjList.size(); vID++) {
        for (size_t otherID = vID + 1; otherID < adjList.size(); ++otherID) {
            planeVector delta;
            delta.dx = positions[vID].x - positions[otherID].x;
            delta.dy = positions[vID].y - positions[otherID].y;

            double distance = delta.norm();
            if (distance != 0.0) {
                double repulsion = k * k / distance;
                power[vID].dx += delta.dx / distance * repulsion;
                power[vID].dy += delta.dy / distance * repulsion;
                power[otherID].dx -= delta.dx / distance * repulsion;
                power[otherID].dy -= delta.dy / distance * repulsion;
            }
        }
    }

    //вычисляем притягивающие силы
    for(size_t vID = 0; vID < adjList.size(); ++vID) {
        for (size_t adjID : adjList[vID]) {
            if (adjID > vID) {
                planeVector delta;
                delta.dx = positions[vID].x - positions[adjID].x;
                delta.dy = positions[vID].y - positions[adjID].y;

                double distance = delta.norm();
                if (distance != 0.0) {
                    double attraction = distance * distance / k;
                    power[vID].dx -= delta.dx / distance * attraction;
                    power[vID].dy -= delta.dy / distance * attraction;
                    power[adjID].dx += delta.dx / distance * attraction;
                    power[adjID].dy += delta.dy / distance * attraction;
                }
            }
        }
    }

    //максимальное движение ограничено текущей температурой
    for (int vID = 0; vID < adjList.size(); vID++) {
        double powerNorm = power[vID].norm();
        if (powerNorm < 1.0) {
            continue;
        }
        double cappedPowerNorm = std::min(powerNorm, temp);
        planeVector cappedPower;
        cappedPower.dx = power[vID].dx / powerNorm * cappedPowerNorm;
        cappedPower.dy = power[vID].dy / powerNorm * cappedPowerNorm;

        positions[vID].x += cappedPower.dx;
        positions[vID].y += cappedPower.dy;
    }
    //остываем
    if (temp > 1) {
        temp *= 0.97;
    } else {
        temp = 1;
    }
}

//-----------------------центруем и масштабируем граф-----------------

void centerGraph(int V, std::vector<Point>& vertexCoords, int width, int height) {
    //находим максимальные и минимальные значения координат всех вершин
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    for (int i = 0; i < V; ++i) {
        if (vertexCoords[i].x < minX) {
            minX = vertexCoords[i].x;
        }
        if (vertexCoords[i].x > maxX) {
            maxX = vertexCoords[i].x;
        }
        if (vertexCoords[i].y < minY) {
            minY = vertexCoords[i].y;
        }
        if (vertexCoords[i].y > maxY) {
            maxY = vertexCoords[i].y;
        }
    }

    //находим центр графа
    double centerX = (maxX + minX) / 2;
    double centerY = (maxY + minY) / 2;
    
    //смещаем центр графа в координаты (width/2,height/2)
    double offsetX = (width / 2) - centerX;
    double offsetY = (height / 2) - centerY;

    //смещаем граф
    for (int i = 0; i < V; ++i) {
        double newX = vertexCoords[i].x + offsetX;
        double newY = vertexCoords[i].y + offsetY;
        vertexCoords[i].x = newX;
        vertexCoords[i].y = newY;
    }
}

void scaleGraph(int V, std::vector<Point>& vertexCoords, int width, int height, int vertexSize) {
    //находим максимальные и минимальные значения координат всех вершин
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    for (int i = 0; i < V; ++i) {
        if (vertexCoords[i].x < minX) {
            minX = vertexCoords[i].x;
        }
        if (vertexCoords[i].x > maxX) {
            maxX = vertexCoords[i].x;
        }
        if (vertexCoords[i].y < minY) {
            minY = vertexCoords[i].y;
        }
        if (vertexCoords[i].y > maxY) {
            maxY = vertexCoords[i].y;
        }
    }

    //находим центр графа
    double centerX = (maxX + minX) / 2;
    double centerY = (maxY + minY) / 2;

    //проверяем, выйдет ли граф за пределы изображения
    int flag = 3;
    for (int i = 0; i < V; ++i) {
        double newX3 = centerX + (vertexCoords[i].x - centerX) * 3;
        double newY3 = centerY + (vertexCoords[i].y - centerY) * 3;
        if ((newX3 + vertexSize / 2) > width || (newX3 - vertexSize / 2) < 0 || (newY3 + vertexSize / 2) > height || (newY3 - vertexSize / 2) < 0) {
            flag = 2;
            break;
        }
    }
    for (int i = 0; i < V; ++i) {
        double newX2 = centerX + (vertexCoords[i].x - centerX) * 2;
        double newY2 = centerY + (vertexCoords[i].y - centerY) * 2;
        if ((newX2 + vertexSize / 2) > width || (newX2 - vertexSize / 2) < 0 || (newY2 + vertexSize / 2) > height || (newY2 - vertexSize / 2) < 0) {
            flag = 1;
            break;
        }
    }

    //масштабируем граф
    if (flag == 3) {
        for (int i = 0; i < V; ++i) {
            double newX = centerX + (vertexCoords[i].x - centerX) * 3;
            double newY = centerY + (vertexCoords[i].y - centerY) * 3;
            vertexCoords[i].x = newX;
            vertexCoords[i].y = newY;
        }
    } else if (flag == 2) {
        for (int i = 0; i < V; ++i) {
            double newX = centerX + (vertexCoords[i].x - centerX) * 2;
            double newY = centerY + (vertexCoords[i].y - centerY) * 2;
            vertexCoords[i].x = newX;
            vertexCoords[i].y = newY;
        }
    }
}

fruchtermanReingold::fruchtermanReingold(const std::vector<std::vector<int> >& g, double k)
    : adjList(g)
    , k(k)
    , kSquared(k * k)
    , temp(10 * sqrt(g.size()))
    , power(adjList.size()) {}