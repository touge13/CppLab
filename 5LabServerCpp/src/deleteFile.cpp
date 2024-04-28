#include "../include/deleteFile.h"
#include "../include/logger.h"

#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include <fstream>

std::mutex mtx;
std::unordered_map<std::string, std::mutex> fileMutexes; // Словарь мьютексов для каждого файла

void deleteFile(const std::string& filename) {
    std::string filePath = "../files/" + filename;

    std::lock_guard<std::mutex> lock(fileMutexes[filePath]);

    // Проверяем существует ли файл
    if (!std::filesystem::exists(filePath)) {
        logMessage("File does not exist: " + filename);
        return;
    }

    // Удаляем файл
    try {
        std::filesystem::remove(filePath);
        logMessage("File deleted successfully: " + filename);
    } catch (const std::filesystem::filesystem_error& e) {
        logMessage("Error deleting file: " + filename + ", " + e.what());
    }
}