#include "../include/sendErrorResponse.h"
#include "../include/logger.h"

#include <fstream>
#include <sys/socket.h>

void sendFile(int clientSocket, const std::string& path) {
    std::ifstream file("../" + path);
    if (!file.is_open()) {
        logMessage("File " + path + " Not Found");
        sendErrorResponse(clientSocket, 404, "Not Found", "File Not Found");
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";
    response += content;
    send(clientSocket, response.data(), response.length(), 0);
}
