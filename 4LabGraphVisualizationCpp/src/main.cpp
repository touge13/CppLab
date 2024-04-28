#include <iostream>
#include <fstream>
#include <vector>

#include "../include/createImage.h"

int main() {
    std::string path;
    std::cout << "Enter the path to the input file (hint: \"../conversion/input.txt\"): ";    
    std::cin >> path;

    std::ifstream inputFile(path); //файл со входными данными
    if(!inputFile) {
        std::cout << "Файл не найден";
    }

    //вытаскиваем данные с файла
    int V, E;
    inputFile >> V >> E;
    
    std::vector<Edge> edges;
    edges.reserve(E);

    for(int i = 0; i < E; i++) {
        int u, v;
        inputFile >> u >> v;
        edges.push_back(Edge(u, v));
    }

    createImage(V, edges);   
    return 0;
}