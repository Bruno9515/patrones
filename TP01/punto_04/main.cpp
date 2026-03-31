#include "biblioteca.h"

int main() {

    shared_ptr<ElementoMusical> c1 = make_shared<Cancion>("Song A", "Artista 1", 200);
    shared_ptr<ElementoMusical> c2 = make_shared<Cancion>("Song B", "Artista 2", 180);
    shared_ptr<ListaReproduccion> lista1 = make_shared<ListaReproduccion>("Favoritas");
    shared_ptr<ListaReproduccion> lista2 = make_shared<ListaReproduccion>("Mix");

    lista1->agregar(c1);
    lista1->agregar(c2);

    lista2->agregar(lista1); 

    lista2->mostrarInfo();
    cout << endl;

    lista2->reproducir();


    return 0;
}