#include "biblioteca.h"

LogManager* LogManager::instancia = nullptr;


int main() {
    LogManager* log1 = LogManager::getInstance("mi_log.txt");
    LogManager* log2 = LogManager::getInstance();

    log1->log("INFO", "Inicio del sistema");
    log2->log("ERROR", "Fallo en login");

    // comprobar que es la misma instancia
    if (log1 == log2) {
        std::cout << "Es la misma instancia\n";
    }

    return 0;
}
