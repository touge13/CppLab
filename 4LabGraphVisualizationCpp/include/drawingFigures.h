#ifndef drawingFigures_h
#define drawingFigures_h

#include <iostream>
#include <fstream>
#include <vector>

void drawCircle(std::vector<uint8_t>& pixels, int centerX, int centerY, int radius, int width, int height);
void drawLine(std::vector<uint8_t>& pixels, int x1, int y1, int x2, int y2, int width, int height);
void drawText(std::vector<uint8_t>& pixels, int x, int y, std::string text, int width, int height);

#endif