#include "../include/handleClient.h"
#include "../include/sendFileList.h"
#include "../include/sendFile.h"
#include "../include/editFile.h"
#include "../include/uploadFile.h"
#include "../include/deleteFile.h"
#include "../include/sendErrorResponse.h"
#include "../include/logger.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno> // Для доступа к errno
#include <cstring> // Для доступа к функции strerror

// Определение глобальной переменной-семафора
sem_t sem;

// Флаг для сигнала потокам о завершении работы
std::atomic<bool> shouldTerminate(false);

void handleClient(int clientSocket) {

    // Проверка флага о необходимости завершения работы
    if (shouldTerminate.load()) {
        close(clientSocket);
        return;
    }

    std::string request; // Создаем пустую строку для хранения запроса
    char buffer[1024]; // Буфер для чтения данных из сокета
    int valread; // Переменная для хранения количества считанных байт

    // Чтение данных из сокета по частям до тех пор, пока не будет прочитан весь запрос
    while ((valread = read(clientSocket, buffer, 1024)) > 0) {
        request.append(buffer, valread); // Добавляем считанные данные к общему запросу
        // Если считаны все данные, выходим из цикла чтения
        // это значит, что больше данных нет, и мы выходим из цикла
        if (valread < 1024) {
            break;
        }
    }
    
    if (valread <= 0) {
        logMessage("Error reading from socket " + std::string(strerror(errno)));
        close(clientSocket);
        return;
    }

    // Разбор запроса
    // Извлечение метода запроса
    std::string method = request.substr(0, request.find(" "));

    // Извлечение пути из запроса
    size_t path_start = request.find(" ");
    size_t path_end = request.find(" ", path_start + 1);
    std::string path = request.substr(path_start + 1, path_end - path_start - 1);

    // Удаление слеша в начале пути
    if (!path.empty() && path[0] == '/')
        path.erase(0, 1);

    if (method == "GET") {
        // Обработка GET-запросов
        if (path.empty()) { // Если путь пустой (корневой), отправить список файлов
            // Отправка списка файлов
            sendFileList(clientSocket);
        } else if (path.find("edit/") == 0) {            
            // Извлечение имени файла из пути
            std::string filename = path.substr(5); // Удаляем "edit/" из пути
            // Редактирование файла
            editFile(clientSocket, filename);
        } else {
            // Отправка запрошенного файла
            sendFile(clientSocket, path);
        }
    } else if (method == "POST") {
        // Обработка POST-запросов
        if (path == "upload") {
            // Обработка запроса на загрузку файла
            uploadFile(clientSocket, request);
        } else if (path.find("delete/") == 0) { // Если путь начинается с /delete/, это запрос на удаление файла
            std::string filename = path.substr(7); // Извлекаем имя файла из пути
            deleteFile(filename); // Удаляем файл
            // Отправляем успешный ответ клиенту
            std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nFile " + filename + " deleted successfully";
            send(clientSocket, response.data(), response.length(), 0);
        } else {
            // Неверный путь для POST-запроса
            logMessage("Invalid path for POST request");
            sendErrorResponse(clientSocket, 404, "Not Found", "Invalid path for POST request");
        }
    } else {
        // Неподдерживаемый метод
        logMessage("Method " + method + " not supported");
        sendErrorResponse(clientSocket, 405, "Method Not Allowed", "Method not supported");
    }

    close(clientSocket);
    
    // Увеличение счетчика семафора
    sem_post(&sem);
}
