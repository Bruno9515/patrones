#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;
int id_global = 0;

struct Usuario{
    int id;
    string nombre;
    string password;
};

class Session{
    private:
        int id_sesion;
        string nombre;
    public:
        Session (int id, string nombre): id_sesion(id), nombre(nombre){};
        int getId() const{
            return this->id_sesion;
        };
        string getNombre() const{
            return this->nombre;
        };
};

class SessionManager{
    private:
        SessionManager(int cantidad){
            usuarios.push_back({1,"Jorge","11"});
            usuarios.push_back({15,"Bruno","1551"});
            usuarios.push_back({21,"Ruben","2112"});
            usuarios.push_back({7,"Carla","77"});            
            cantidad_maxima = cantidad;
        };
        vector<Session> sesiones_activas;
        vector<Usuario> usuarios;
        int cantidad_maxima;
        int cantidad_sesiones_activas;
			
		SessionManager(const SessionManager&) = delete;
		SessionManager& operator=(const SessionManager&) = delete;

        void ModificarSesionesActivas(string operando){
            int cambio = (operando == "+") ? 1 : -1;
            this->cantidad_sesiones_activas += cambio;
        };

    public:
		static SessionManager& getInstance(int cantidad) {
			static SessionManager instancia(cantidad);
			return instancia;
		};


        void IniciarSesion(int id, string pass){
            if(!ValidarSesion(id) && this->cantidad_sesiones_activas < this->cantidad_maxima){
                vector<Usuario>::iterator resultado = find_if(usuarios.begin(), usuarios.end(),[=](const Usuario& s){
                    return (s.id == id) && (s.password == pass);
                });
                if(resultado != usuarios.end()){
                    id_global = id_global + 1;                    
                    sesiones_activas.push_back(Session(id_global,resultado->nombre));
                    ModificarSesionesActivas("+");
                    cout << "Sesion iniciada" << endl;
                }else{
                    cout << "Datos incorrectos" << endl;
                }
            }else{ 
                cout << "Sesion no iniciada, ";
                if(this->cantidad_sesiones_activas >= this->cantidad_maxima) {
                    cout << "cantidad maxima de sesiones concurrentes alcanzada" << endl;
                }else{
                    cout << "ya se encuentra iniciada una sesion con ese id" << endl;
                }
            };
        };

        vector<Session>::iterator  BuscarSesion(int id) {
            return std::find_if(
                sesiones_activas.begin(),
                sesiones_activas.end(),
                [id](const Session& s) {
                    return s.getId() == id;
                }
            );
        }
        void CerrarSesion(int id_sesion){
            vector<Session>::iterator auxiliar = BuscarSesion(id_sesion);
            if(auxiliar != sesiones_activas.end()){
                sesiones_activas.erase(auxiliar);
                this->ModificarSesionesActivas("-");          
                cout << "Sesion cerrada con exito." << endl;
            }else{ 
                cout << "No se encontro sesion activa con el id ingresado." << endl;
            };
        };

        bool ValidarSesion(int id_sesion){            
            return BuscarSesion(id_sesion) != sesiones_activas.end();
        };


};