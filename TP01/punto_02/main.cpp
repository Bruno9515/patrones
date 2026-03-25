#include "biblioteca.h"


int main() {
    Caja caja;
    Producto producto1("Jugo Cachito",5000,0);
    Producto producto2("Milagato",20000,0);
    Producto producto3("Vino Cacho",8000,1);
    Producto producto4("Galletas",4000,0);

    caja.escanearProducto(&producto1);
    caja.escanearProducto(&producto2);
    caja.mostrarProductos();
    caja.abonarCompra();

    caja.finalizarCompra();

    std::cout << "\n--- Caso con supervision fallida---\n";

    caja.escanearProducto(&producto3);
    caja.escanearProducto(&producto1); // no deberia poder

    caja.validarSupervisor(12345);

    caja.escanearProducto(&producto1);
    caja.mostrarProductos();
    caja.abonarCompra();
    caja.finalizarCompra();

    std::cout << "\n--- Caso con supervision correcta---\n";

    caja.escanearProducto(&producto3);
    caja.escanearProducto(&producto4);

    caja.validarSupervisor(1234);

    caja.escanearProducto(&producto4);
    caja.mostrarProductos();
    caja.abonarCompra();
    caja.finalizarCompra();
    
    return 0;
}
