#include <iostream>
#include <vector>


class Caja;

class Producto{
	private:
		std::string nombre;
		double precio;
		bool supervision;
	public:
		Producto(std::string e, double x, bool s): nombre(e),precio(x), supervision(s){};
		
		std::string getNombre(){
			return nombre;
		};
		
		double getPrecio(){
			return precio;
		};
		
		bool getSupervision(){
			return supervision;
		};
		
		void mostrarInformacion(){
			std::cout << nombre << " : " << precio << std::endl;
		};
		
		Producto* getProducto(){
			return this;
		};
		~Producto() {};		
};		
		

class Estado{
	public:
		virtual void escanearProducto(Caja*, Producto*) = 0;
		virtual void abonarCompra(Caja*) = 0;
		virtual void finalizarCompra(Caja*) = 0;
		virtual ~Estado() {};
};

class EsperandoClientes: public Estado{
	public:
		void escanearProducto(Caja*, Producto*) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class EscaneandoProductos: public Estado{
	public:
		void escanearProducto(Caja*, Producto*) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class ProcesarPagos: public Estado{
	public:
		void escanearProducto(Caja*, Producto*) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
};

class RequiereSupervision: public Estado{
	public:
		void escanearProducto(Caja*, Producto*) override;
		void abonarCompra(Caja*) override;
		void finalizarCompra(Caja*) override;
		void validando(Caja*, Producto*, int);
};

class Caja{
	private:
		Estado* estado;
		Producto* productoPendiente;
		
		EsperandoClientes esperando;
		EscaneandoProductos escaneando;
		ProcesarPagos pagando;
		RequiereSupervision supervisando;
		
		std::vector<Producto*> productos;
		double total;
	public:
		Caja(): estado(&esperando), total(0){};
		
		void setEstado(Estado* e){
			estado = e;
		};
		
		void setProductoPendiente(Producto* producto){
			productoPendiente = producto;
		};
		
		Estado* getEstado(){
			return estado;
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
		
		void agregarProducto(Producto* producto){
			productos.push_back(producto);
			total += producto->getPrecio();
		};
		
		void mostrarProductos(){
			for (int i = 0; i < (int)productos.size(); i++) {
				productos[i]->mostrarInformacion();
			};
		};
		
		void reiniciar(){
			productos.clear();
			total = 0;
		};
		
		double getTotal(){
			return total;
		};
		
		void escanearProducto(Producto* producto) {
			estado->escanearProducto(this, producto);
		};
	
		void validarSupervisor(int codigo) {
			if (codigo == 1234) {
				std::cout << "Supervisor validado\n";
				estado = getEscaneando();
				this->agregarProducto(productoPendiente);
			} else {
				std::cout << "Codigo incorrecto\n";
			};
		};
						
		void abonarCompra(){
			estado->abonarCompra(this);
		};
		
		void finalizarCompra(){
			estado->finalizarCompra(this);
		};
};

//EsperandoClientes	
void EsperandoClientes::escanearProducto(Caja* caja, Producto* producto){	 
	std::cout << "Escaneando primer producto\n";	
			
	if (producto->getSupervision()) {
  		std::cout << "Producto requiere supervision\n";
		caja->setEstado(caja->getSupervisando());
		caja->setProductoPendiente(producto);
	} else {
		caja->setEstado(caja->getEscaneando());
		caja->agregarProducto(producto);
	};
};

void EsperandoClientes::abonarCompra(Caja* caja){
	std::cout << "No se encuentra una compra en proceso\n";
};

void EsperandoClientes::finalizarCompra(Caja* caja){
	std::cout << "No se encuentra una compra en proceso\n";
};


//EscaneandoProductos
void EscaneandoProductos::escanearProducto(Caja* caja, Producto* producto){	 
 	if (producto->getSupervision()) {
  		std::cout << "Producto requiere supervision\n";
		caja->setEstado(caja->getSupervisando());
		caja->setProductoPendiente(producto);
	} else {
		caja->agregarProducto(producto);
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
void ProcesarPagos::escanearProducto(Caja* caja, Producto* producto){	 
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
void RequiereSupervision::escanearProducto(Caja* caja, Producto* producto){
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

void RequiereSupervision::validando(Caja* caja, Producto* producto, int codigo){
	std::cout <<"Validando\n";
	caja->validarSupervisor(codigo);
};


