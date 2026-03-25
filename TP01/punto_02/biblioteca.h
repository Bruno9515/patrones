#include <iostream>
#include <vector>


class Caja;

class Estado{
	public:
		virtual void escanearProducto(Caja*, double, bool) = 0;
		virtual void abonarCompra(Caja*) = 0;
		virtual void finalizarCompra(Caja*) = 0;
		virtual ~Estado() {};
};

class EsperandoClientes: public Estado{
	public:
		void escanearProducto(Caja*, double, bool) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class EscaneandoProductos: public Estado{
	public:
		void escanearProducto(Caja*, double, bool) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class ProcesarPagos: public Estado{
	public:
		void escanearProducto(Caja*, double, bool) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class RequiereSupervision: public Estado{
	public:
		void escanearProducto(Caja*, double, bool) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class Caja{
	private:
		Estado* estado;
		
		EsperandoClientes esperando;
		EscaneandoProductos escaneando;
		ProcesarPagos pagando;
		RequiereSupervision supervisando;
		
		std::vector<double> productos;
		double total;
	public:
		Caja(): estado(&esperando), total(0){};
		
		void setEstado(Estado* e){
			estado = e;
		};
		
		EsperandoClientes* getEsperando() { 
			return &esperando; 
		};
		
		EscaneandoProductos* getEscaneando() { 
			return &escaneando; 
		};
		
		ProcesarPagos* getPagando() { 
			return &pagando; 
		};
		
		RequiereSupervision* getSupervisando() { 
			return &supervisando; 
		};
		
		void agregarProducto(double precio){
			productos.push_back(precio);
			total += precio;
		};
		
		void reiniciar(){
			productos.clear();
			total = 0;
		};
		
		double getTotal(){
			return total;
		};
		
		void escanearProducto(double precio, bool requiereSupervision=false) {
			estado->escanearProducto(this, precio, requiereSupervision);
		};
					
		void abonarCompra(){
			estado->abonarCompra(this);
		};
		
		void finalizarCompra(){
			estado->finalizarCompra(this);
		};
		
		void validarSupervisor(int codigo);
};

//EsperandoClientes	
void EsperandoClientes::escanearProducto(Caja* caja, double precio, bool requiereSupervision){	 
	std::cout << "Primer producto escaneado\n";
	caja->agregarProducto(precio);
			
	if (requiereSupervision) {
		caja->setEstado(caja->getSupervisando());
	} else {
		caja->setEstado(caja->getEscaneando());
	};
};

void EsperandoClientes::abonarCompra(Caja* caja){
	std::cout << "No se encuentra una compra en proceso\n";
};

void EsperandoClientes::finalizarCompra(Caja* caja){
	std::cout << "No se encuentra una compra en proceso\n";
};


//EscaneandoProductos
void EscaneandoProductos::escanearProducto(Caja* caja, double precio, bool requiereSupervision){	 
 	if (requiereSupervision) {
  		std::cout << "Producto requiere supervision\n";
		caja->setEstado(caja->getSupervisando());
	} else {
		caja->agregarProducto(precio);
		std::cout << "Producto escaneado\n";
	};
};
		
		
void EscaneandoProductos::abonarCompra(Caja* caja){			
	std::cout << "Total a pagar: " << caja->getTotal() << std::endl;
	caja->setEstado(caja->getPagando());
};

void EscaneandoProductos::finalizarCompra(Caja* caja){
	std::cout << "Compra cancelada\n";
	caja->reiniciar();
	caja->setEstado(caja->getEsperando());
};


//ProcesarPagos
void ProcesarPagos::escanearProducto(Caja* caja, double precio, bool requiereSupervision){	 
	std::cout << "En proceso de pago\n";
};
		
void ProcesarPagos::abonarCompra(Caja* caja){
	std::cout << "En proceso de pago\n";
};
		
void ProcesarPagos::finalizarCompra(Caja* caja){
	std::cout << "Compra finalizada\n";
	caja->reiniciar();
	caja->setEstado(caja->getEsperando());
};


//RequiereSupervision
void RequiereSupervision::escanearProducto(Caja* caja, double precio, bool requiereSupervision){
	std::cout << "Esperando supervisor\n";
};

void RequiereSupervision::abonarCompra(Caja* caja){
	std::cout << "No se puede pagar\n";
};

void RequiereSupervision::finalizarCompra(Caja* caja){
	std::cout << "Compra cancelada\n";
	caja->reiniciar();
	caja->setEstado(caja->getEsperando());
};




void Caja::validarSupervisor(int codigo) {
    if (codigo == 1234) {
        std::cout << "Supervisor validado\n";
        estado = getEscaneando();
    } else {
        std::cout << "Codigo incorrecto\n";
    };
};
