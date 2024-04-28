#ifndef createImage_h
#define createImage_h

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "saveFile.h"
#include "drawingFigures.h"
#include "algorithm.h"

void createResultImage (int V, std::vector<Edge> edges, std::vector<uint8_t>& pixels, std::vector<Point>& vertexCoords, int width, int height, int vertexSize);
void createImage(int V, std::vector<Edge> edges);

#endif