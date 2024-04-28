#ifndef SENDERRORRESPONSE_H
#define SENDERRORRESPONSE_H

#include <string>

void sendErrorResponse(int clientSocket, int errorCode, const std::string& errorStatus, const std::string& errorMessage);

#endif