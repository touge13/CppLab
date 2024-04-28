#include "../include/sendFileList.h"
#include "../include/logger.h"

#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>

void sendFileList(int clientSocket) {
    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    response += "<!DOCTYPE html><html><head><title>File List</title></head><body><h1>Files on the server:</h1>";

    // Получение списка файлов
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("../files")) != NULL) {
        // Перебор всех файлов в каталоге "files"
        while ((ent = readdir(dir)) != NULL) {
            // Игнорирование . и ..
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            // Создание ссылки на каждый файл с кнопками для просмотра, скачивания, удаления и редактирования
            response += "<p><a href=\"/files/" + std::string(ent->d_name) + "\">" + std::string(ent->d_name) + "</a> [<a href=\"/files/" + std::string(ent->d_name) + "\" download>download</a>]<form method=\"post\" action=\"/delete/" + std::string(ent->d_name) + "\"> <input type=\"hidden\" name=\"_method\" value=\"DELETE\"><input type=\"submit\" value=\"delete\"></form></p>";
            response += "<form method=\"get\" action=\"/edit/" + std::string(ent->d_name) + "\"> <input type=\"submit\" value=\"edit\"></form></p>";
        }
        closedir(dir);
    } else {
        // Если не удается открыть каталог
        logMessage("Failed to open directory");
        response += "<p>Failed to open directory</p>";
    }

    // Форма для загрузки файла
    response += "<form method=\"post\" action=\"/upload\">\
                <textarea name=\"file_content\" rows=\"10\" cols=\"50\"></textarea><br>\
                <input type=\"text\" name=\"file_name\" placeholder=\"Enter file name\"><a>.txt </a>\
                <input type=\"submit\" value=\"Upload Text\">\
            </form>";

    response += "</body></html>";

    // Отправка списка файлов клиенту
    send(clientSocket, response.data(), response.length(), 0);
}