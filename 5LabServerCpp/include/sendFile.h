#ifndef SENDFILE_H
#define SENDFILE_H

#include <string>

void sendFile(int clientSocket, const std::string& path);

#endif
