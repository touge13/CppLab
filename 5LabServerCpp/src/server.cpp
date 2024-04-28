#include "../include/server.h"
#include "../include/handleClient.h"
#include "../include/logger.h"

// Ограничение на количество потоков
const int MAX_THREADS = 100;

void server() {
    // Создание семафора
    sem_init(&sem, 0, MAX_THREADS);

    // Создание сокета
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        logMessage("Error creating socket");
        return;
    }

    // Структура для хранения адреса сервера
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    int port = 8080;
    address.sin_port = htons(port); // Порт 8080

    // Привязка сокета к адресу и порту
    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        logMessage("Binding failed");
        return;
    }

    // Прослушивание порта
    if (listen(serverSocket, 5) < 0) {
        logMessage("Listening failed");
        return;
    }

    logMessage("Server listening on port " + std::to_string(port));
    std::cout << "Server listening on port " << port << " ...\n";

    std::vector<std::thread> threads;

    while (true) {
        // Проверка флага о необходимости завершения работы
        if (shouldTerminate.load()) {
            break;
        }

        // Принятие входящего соединения
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            logMessage("Accept failed");
            return;
        }

        // Ожидание доступности семафора (места для нового потока)
        sem_wait(&sem);

        // Обработка клиента в отдельном потоке
        threads.emplace_back(handleClient, clientSocket);
    }

    // Закрытие сокета сервера (никогда не будет достигнуто)
    close(serverSocket);

    // Уничтожение семафора
    sem_destroy(&sem);

    // Дожидаемся завершения работы всех потоков
    for (auto& thread : threads) {
        thread.join();
    }
}

// Функция для остановки сервера
void stopServer() {
    // Установка флага о необходимости завершения работы
    shouldTerminate.store(true);
}
