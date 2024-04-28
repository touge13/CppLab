#ifndef imageConfig_h
#define imageConfig_h

#include <iostream>

//картинка
int width = 600;
int height = 600;
int vertexSize = 6; // Диаметр вершины
int numIteration = 100; //количество итераций при расстановке вершин
//цвет фона 
uint8_t backgroundColorR = 255;
uint8_t backgroundColorG = 255;
uint8_t backgroundColorB = 255;

//bmp header
int fileSize = 54 + 3 * width * height; 
int dataOffset = 54; 
int headerSize = 40; 
short planes = 1; 
short bpp = 24; 
int compression = 0; 
int dataSize = 3 * width * height; 
int hResolution = 0; 
int vResolution = 0; 
int colors = 0; 
int importantColors = 0; 

#endif