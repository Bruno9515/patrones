#include "biblioteca.h"

int main(){
	Cliente cliente;
	OrdenAscendente asc;
	OrdenDescendente dsc;
	int arreglo[] = {1,5,3,10,95};
	
	escribir(arreglo, 5);
	cliente.setOrdenar(&asc);
	cliente.ordenarArreglo(arreglo, 5 );
	cliente.setOrdenar(&dsc);
	cliente.ordenarArreglo(arreglo, 5);
	escribir(arreglo, 5);
	
	return 0;
;}
	