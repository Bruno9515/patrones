#include <iostream>
#include <vector>


class Caja;

class Estado{
	public:
		virtual void escanearProducto(Caja* caja, double precio) = 0;
		virtual void abonarCompra(Caja* caja);
		virtual void finalizarCompra(Caja* caja);
		void 
}

class Caja{
	private:
		Estado* estado;
		vector<double> productos;
		double total;
	public;
		Caja(Estado* e): estado(e), total(0){}
		
		void setEstado(Estado* e){
			estado = e;
		}
		void agregarProducto(double precio){
			productos.push_back(precio);
			total += precio;
		}
		void reiniciar(){
			productos.clear();
			total = 0;
		}
		void getTotal(){
			return total;
		}
		void escanearProducto(double precio){
			estado->escanearProducto(this, precio);
		}			
		void abonarCompra(){
			estado->abonarCompra(this);
		}
		void finalizarCompra(){
			estado->finalizarCompra(this);
		}
}

class EsperandoClientes: public Estado{
	public:		
		virtual void escanearProducto(Caja* caja, double precio){			 
			std::cout << "Primer producto escaneado";
			caja->agregarProducto(precio);
			caja->setEstado(new EscaneandoProductos());
		};
		virtual void abonarCompra(Caja* caja){
			std::cout << "No se encuentra una compra en proceso";
		};
		virtual void finalizarCompra(Caja* caja){
			std::cout << "No se encuentra una compra en proceso";
		};
};

class EscaneandoProductos: public Estado{
	public:		
		virtual void escanearProducto(Caja* caja, double precio){
			caja->agregarProducto(precio);
			std::cout << "Producto escaneado";
		};
		
		virtual void abonarCompra(Caja* caja){
			caja->setEstado(new ProcesarPagos());
		};
		
		virtual void finalizarCompra(Caja* caja){
			std::cout << "Compra finalizada";
			caja->reiniciar();
			caja->setEstado(new EsperandoClientes);
		};
};
class ProcesarPagos: public Estado{
	public:		
		virtual void escanearProducto(Caja* caja, double precio){
			std::cout << "En proceso de pago";
		};
		
		virtual void abonarCompra(Caja* caja){
			std::cout << "En proceso de pago";
		};
		
		virtual void finalizarCompra(Caja* caja){
			std::cout << "Compra finalizada";
			caja->reiniciar();
			caja->setEstado(new EsperandoClientes);
		};
};
