#include "../include/editFile.h"
#include "../include/sendErrorResponse.h"
#include "../include/logger.h"

#include <fstream>
#include <iostream>
#include <sys/socket.h>

void editFile(int clientSocket, const std::string& filename) {
    std::string filenameWithoutQuestionMark;
    if (!filename.empty() && filename.substr(filename.length() - 1) == "?") {
        filenameWithoutQuestionMark = filename.substr(0, filename.length() - 1);
    } else {
        filenameWithoutQuestionMark = filename;
    }

    // Проверка наличия файла
    std::ifstream file("../files/" + filenameWithoutQuestionMark);
    if (file.is_open()) {
        // Чтение содержимого файла
        std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // Формирование HTML-страницы с текстовым полем, содержащим содержимое файла
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
        response += "<!DOCTYPE html><html><head><title>Edit File</title></head><body>";
        response += "<h1>Edit File: " + filenameWithoutQuestionMark + "</h1>";
        response += "<form method=\"post\" action=\"/upload\">";
        response += "<textarea name=\"file_content\" rows=\"10\" cols=\"50\">" + file_content + "</textarea><br>";
        
        // Удаляем ".txt" в конце строки filenameWithoutQuestionMark
        if (!filenameWithoutQuestionMark.empty() && filenameWithoutQuestionMark.length() >= 4 && filenameWithoutQuestionMark.substr(filenameWithoutQuestionMark.length() - 4) == ".txt") {
            std::string filenameWithoutDuplicatingExtension = filenameWithoutQuestionMark.substr(0, filenameWithoutQuestionMark.length() - 4);
            response += "<input type=\"hidden\" name=\"file_name\" value=\"" + filenameWithoutDuplicatingExtension + "\">";
        } else {
            response += "<input type=\"hidden\" name=\"file_name\" value=\"" + filenameWithoutQuestionMark + "\">";
        }
        response += "<input type=\"submit\" value=\"Save\">";
        response += "</form></body></html>";

        // Отправка HTML-страницы клиенту
        send(clientSocket, response.data(), response.length(), 0);
        logMessage("File " + filenameWithoutQuestionMark + " is being edited...");
    } else {
        // Если файл не найден, отправить ошибку 404
        logMessage("File " + filenameWithoutQuestionMark + " Not Found");
        sendErrorResponse(clientSocket, 404, "Not Found", "File Not Found");
    }
}
