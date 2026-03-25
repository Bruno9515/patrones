#include <iostream>
#include <fstream> // Para manipular archivos
#include <ctime>


class LogManager {
private:
    static LogManager* instancia;
    std::string ruta;

    LogManager(std::string rutaArchivo) {
        ruta = rutaArchivo;
    }

public:
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    static LogManager* getInstance(std::string rutaArchivo = "log.txt") {
        if (instancia == nullptr) {
            instancia = new LogManager(rutaArchivo);
        }
        return instancia;
    }

    void log(std::string tipo, std::string mensaje) {
        std::ofstream archivo(ruta, std::ios::app);

        std::time_t ahora = time(0);
        std::string fecha = ctime(&ahora);

        archivo << fecha << " [" << tipo << "] " << mensaje << std::endl;

        archivo.close();
    }
};
