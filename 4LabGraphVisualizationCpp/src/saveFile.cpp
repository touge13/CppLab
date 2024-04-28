#include "../include/saveFile.h"

void saveFile(int width, int height, std::ofstream& file, std::vector<uint8_t>& pixels) {
    for(int i = 0; i < height; i++) {
        //запись
        for(int j = 0; j < width; j++) {
            int index = 3 * (i * width + j);
            file.write(reinterpret_cast<const char*>(&pixels[index]), 3);
        }
        //выравнивание до разрешения кратности 4 
        for(int j = 0; j < (4 - (width * 3) % 4) % 4; j++) {
            char padding = 0;
            file.write(&padding, 1);
        }
    }

    file.close();
    std::cout << "Image created successfully\n";
}