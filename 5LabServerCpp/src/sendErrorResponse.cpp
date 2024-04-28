#include "../include/sendErrorResponse.h"

#include <sys/socket.h>

void sendErrorResponse(int clientSocket, int errorCode, const std::string& errorStatus, const std::string& errorMessage) {
    std::string response = "HTTP/1.1 " + std::to_string(errorCode) + " " + errorStatus + "\nContent-Type: text/plain\nContent-Length: " + std::to_string(errorMessage.length()) + "\n\n" + errorMessage;
    send(clientSocket, response.data(), response.length(), 0);
}