#ifndef HANDLECLIENT_H
#define HANDLECLIENT_H

#include <semaphore.h>
#include <atomic>

// Объявление глобальной переменной-семафора
extern sem_t sem;

// Флаг для сигнала потокам о завершении работы
extern std::atomic<bool> shouldTerminate;

void handleClient(int clientSocket);

#endif