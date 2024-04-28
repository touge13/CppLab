#include "../include/uploadFile.h"
#include "../include/sendErrorResponse.h"
#include "../include/urlDecode.h"
#include "../include/logger.h"

#include <fstream>
#include <sys/socket.h>

void uploadFile(int clientSocket, const std::string& request) {
    // Находим содержимое поля file_content в запросе
    size_t content_start = request.find("\r\n\r\n");
    if (content_start == std::string::npos) {
        // Если содержимое не найдено, отправляем ошибку
        logMessage("Invalid file content");
        sendErrorResponse(clientSocket, 400, "Bad Request", "Invalid file content");
        return;
    }
    std::string file_content = request.substr(content_start + 4);

    // Находим позицию начала значения параметра file_content
    size_t file_content_start = request.find("file_content=", content_start);
    if (file_content_start == std::string::npos) {
        // Если начало значения не найдено, отправляем ошибку
        logMessage("Invalid file content");
        sendErrorResponse(clientSocket, 400, "Bad Request", "Invalid file content");
        return;
    }
    // Перемещаемся к концу имени параметра
    file_content_start += 13; // Длина "file_content="

    // Находим позицию конца значения параметра file_content
    size_t file_content_end = request.find("&", file_content_start);
    if (file_content_end == std::string::npos) {
        // Если конец значения не найден, используем всю оставшуюся часть запроса
        file_content_end = request.find(" ", file_content_start);
    }

    // Извлекаем содержимое file_content из строки запроса
    file_content = request.substr(file_content_start, file_content_end - file_content_start);

    // Извлекаем содержимое file_content из строки запроса и декодируем его
    file_content = urlDecode(file_content);

    // Находим позицию начала значения параметра file_name
    size_t file_name_start = request.find("file_name=", content_start);
    if (file_name_start == std::string::npos) {
        // Если начало значения не найдено, отправляем ошибку
        logMessage("Invalid file name");
        sendErrorResponse(clientSocket, 400, "Bad Request", "Invalid file name");
        return;
    }
    // Перемещаемся к концу имени параметра
    file_name_start += 10; // Длина "file_name="

    // Находим позицию конца значения параметра file_name
    size_t file_name_end = request.find("&", file_name_start);
    if (file_name_end == std::string::npos) {
        // Если конец значения не найден, используем всю оставшуюся часть запроса
        file_name_end = request.find(" ", file_name_start);
    }

    // Извлекаем содержимое file_name из строки запроса
    std::string file_name = request.substr(file_name_start, file_name_end - file_name_start);

    // Сохраняем содержимое в файл на сервере
    std::ofstream outfile("../files/" + file_name + ".txt");
    if (outfile.is_open()) {
        // Записываем содержимое в файл
        outfile << file_content;
        outfile.close();

        // Отправляем клиенту ответ об успешной загрузке файла
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nFile " + file_name + ".txt" + " uploaded successfully";
        send(clientSocket, response.data(), response.length(), 0);
        logMessage(file_name + ".txt uploaded successfully");
    } else {
        // Ошибка при сохранении файла
        logMessage("Error saving file" + file_name + ".txt");
        sendErrorResponse(clientSocket, 500, "Internal Server Error", "Error Saving File");
    }
}
