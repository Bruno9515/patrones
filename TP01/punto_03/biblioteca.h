#include <iostream>
#include <fstream> // Para manipular archivos
#include <ctime>


class LogManager {
	private:
		LogManager(){};
		std::string ruta;

		LogManager(std::string rutaArchivo) {
			ruta = rutaArchivo;
		};
			
		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;


	public:

		static LogManager& getInstance(std::string rutaArchivo = "log.txt") {
			static LogManager instancia(rutaArchivo);
			return instancia;
		};

		void log(std::string tipo, std::string mensaje) {
			std::ofstream archivo(ruta, std::ios::app);

			std::time_t ahora = time(0);
			std::string fecha = ctime(&ahora);

			archivo << fecha << " [" << tipo << "] " << mensaje << std::endl;

			archivo.close();
		};
};
