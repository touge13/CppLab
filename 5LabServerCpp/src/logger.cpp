#include "../include/logger.h"

#include <fstream>
#include <ctime>
#include <iostream>

void logMessage(const std::string& message) {
    std::ofstream logfile("server.log", std::ios::app);
    if (logfile.is_open()) {
        // Получаем текущее время
        std::time_t now = std::time(nullptr);
        // Преобразуем время в строку
        std::string timestamp = std::ctime(&now);
        // Убираем символ новой строки в конце времени
        timestamp.pop_back();
        // Записываем сообщение и временную метку в лог-файл
        logfile << "[" << timestamp << "] " << message << std::endl;
        logfile.close();
    } else {
        std::cerr << "Error opening log file" << std::endl;
    }
}
