#include "biblioteca.h"


int main() {
    Caja caja;

    caja.escanearProducto(100);
    caja.escanearProducto(50);
    caja.abonarCompra();

    caja.finalizarCompra();

    std::cout << "\n--- Caso con supervision fallida---\n";

    caja.escanearProducto(200, true);
    caja.escanearProducto(50); // no deberia poder

    caja.validarSupervisor(12345);

    caja.escanearProducto(50);
    caja.abonarCompra();
    caja.finalizarCompra();

    std::cout << "\n--- Caso con supervision correcta---\n";

    caja.escanearProducto(200, true);
    caja.escanearProducto(50); // no deberia poder

    caja.validarSupervisor(1234);

    caja.escanearProducto(50);
    caja.abonarCompra();
    caja.finalizarCompra();
    
    return 0;
}
