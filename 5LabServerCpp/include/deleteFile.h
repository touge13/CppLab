#ifndef DELETEFILE_H
#define DELETEFILE_H

#include <string>
#include <mutex>

extern std::mutex mtx;

void deleteFile(const std::string& filename);

#endif
