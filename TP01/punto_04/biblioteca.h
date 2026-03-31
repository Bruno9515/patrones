#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class ElementoMusical {
protected:
    string nombre;

public:
    ElementoMusical(string nombre) : nombre(nombre) {}

    virtual void reproducir() = 0;
    virtual int getDuracion() = 0;

    void renombrar(string nuevoNombre) {
        nombre = nuevoNombre;
    };

    virtual void mostrarInfo() = 0;

    virtual ~ElementoMusical() {} 
};

class Cancion : public ElementoMusical {
private:
    string artista;
    int duracion; 

public:
    Cancion(string nombre, string artista, int duracion)
        : ElementoMusical(nombre), artista(artista), duracion(duracion) {};

    void reproducir() override {
        cout << "Reproduciendo canción: " << nombre << endl;
    };

    int getDuracion() override {
        return duracion;
    };

    void mostrarInfo() override {
        cout << "Canción: " << nombre << " - " << artista
             << " (" << duracion << " seg)" << endl;
    };
};

class ListaReproduccion : public ElementoMusical {
private:
    vector<shared_ptr<ElementoMusical>> elementos;

public:
    ListaReproduccion(string nombre) : ElementoMusical(nombre) {};

    void agregar(shared_ptr<ElementoMusical> elem) {
        elementos.push_back(elem);
    };

    void quitar(shared_ptr<ElementoMusical> elem) {
        for (auto it = elementos.begin(); it != elementos.end(); ++it) {
            if (*it == elem) {
                elementos.erase(it);
                break;
            };
        };
    };

    void reproducir() override {
        cout << "Reproduciendo lista: " << nombre << endl;
        for (auto e : elementos) {
            e->reproducir();
        };
    };

    int getDuracion() override {
        int total = 0;
        for (auto e : elementos) {
            total += e->getDuracion();
        }
        return total;
    };

    void mostrarInfo() override {
        cout << "Lista: " << nombre
             << " | Duración total: " << getDuracion() << " seg" << endl;

        for (auto e : elementos) {
            e->mostrarInfo();
        };
    };
};


