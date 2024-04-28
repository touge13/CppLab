#ifndef saveFile_h
#define saveFile_h


#include <iostream>
#include <fstream>
#include <vector>

void saveFile(int width, int height, std::ofstream& file, std::vector<uint8_t>& pixels);

#endif