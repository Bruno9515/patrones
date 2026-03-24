#include <iostream>

class Orden {
public:
    void Ordenar(int arr[], int n);
    virtual bool Comparacion(int a, int b) = 0;
};

class OrdenAscendente : public Ordenar {
public:
    bool Comparacion(int a, int b) override;
};
### metodo plantilla 
void OrdenAscendente::ordenar(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
				int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
			}
		}
	}
}

class OrdenDescendente : public Ordenar {
public:
    bool Comparacion(int a, int b) override;
};

void OrdenDescendente::ordenar(int arr[], int n) {
    
}

class Cliente {
private:
    Ordenar* orden;

public:
    void setOrdenar(Ordenar* o) {
        orden = o;
    }

    void ordenarArreglo(int arr[], int n) {
        orden->ordenar(arr, n);
    }
};

int main(){
	std::cout << "Hola" << std::endl;
	return 0;
	}
	
