#include <iostream>

class Orden {
	public:
		void ordenar(int arr[], int n);
		virtual bool comparacion(int a, int b) = 0;
};

void Orden::ordenar(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparacion(arr[j], arr[j + 1])) {
				int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
			};
		};
	};
};

class OrdenAscendente : public Orden {
	public:
		bool comparacion(int a, int b) override{
			return a > b;
		};
};


class OrdenDescendente : public Orden {
	public:
		bool comparacion(int a, int b) override{
			return a < b;
		};
};


class Cliente {
private:
    Orden* orden;

public:
    void setOrdenar(Orden* o) {
        orden = o;
    }

    void ordenarArreglo(int arr[], int n) {
        orden->ordenar(arr, n);
    }
};

void escribir(int arr[], int n){
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	};
	std::cout << std::endl;
};

