#include "biblioteca.h"


int main(){
    SessionManager& manager = SessionManager::getInstance(2);
    manager.IniciarSesion(15,"1551");
    manager.IniciarSesion(21,"2112");
    manager.IniciarSesion(7,"77");
    manager.CerrarSesion(1);
    manager.IniciarSesion(21,"2112");
    cout << manager.ValidarSesion(1)<< endl;
    cout << manager.ValidarSesion(2)<< endl;
    manager.CerrarSesion(2);
    manager.CerrarSesion(3);
    return 0;
};