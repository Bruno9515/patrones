#include "biblioteca.h"

int main() {
    LogManager& logger = LogManager::getInstance("mi_log.txt");
	LogManager& logger2 = LogManager::getInstance();

    logger.log("INFO", "Programa iniciado");
    logger2.log("ERROR", "Algo salió mal");

    // comprobar que es la misma instancia
    if (&logger == &logger2) {
        std::cout << "Es la misma instancia\n";
    };

    return 0;
};
