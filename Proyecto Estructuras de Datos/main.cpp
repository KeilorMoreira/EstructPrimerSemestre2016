#include <iostream>
#include <string.h>


using namespace std;
// Aqui van las estructuras que vamos a trabajar

struct Cantones{
	string nombre;
	string provincia;
	struct curso *sig;
	struct curso *ant;
	Cantones(string n , string p){
		nombre = n;
		provincia = p;
		sig = NULL;
		ant = NULL;
		
	}
		
}*listaCantones;//Puntero de la estructura cantones 


struct Puestos{//Lista simple
	string nombre;//nombre
	struct Puestos *sig;
	struct MiembrosComite *enlaceM;// aqui conecta el struct de miembroscomite con el struct de de puestos por medio de un enlace
	Puestos(string nom){
		nombre = nom;
		sig = NULL;
	}
}*listaPuestos;// Puntero de puestos

struct Formacion{
	string nombre;
	struct Formacion *sig;
	struct MiembrosComite *enlaceM;// aqui conecta el struct de miembroscomite con el struct de formacion por medio de un enlace 
	Formacion(string nom){
		nombre = nom;
		sig = NULL;
	}
}*listaFormacion;// puntero de formacion

// estructuras de capacitacion 
struct Capacitacion{
	string nombre;
	string lugar;
	struct Capacitacion *sig;
	Capacitacion(string nom , string lu){
		nombre = lugar ;
		lugar = lugar;
		sig = NULL;
		
	}
}*listaCapacitacion;// puntero capacitacion

struct MiembrosComite{
	string nombre ;
	int identificador;
	struct MiembrosComite *sig;
	MiembrosComite(string nom, int Id ){
		nombre = nom;
		identificador = Id;
		sig = NULL;
		
	}
	
}*listaMiembros;//Puntero miembros Comite


struct Programas{//Lista circular con insercion al inicio
	string nombre;
	string fecha;
	string lugar;
	string hora;
	struct Programas *sig;
	Programas(string nom , string fe, string lu, string ho){
		nombre = nom;
		fecha = fe;
		lugar = lu;
		hora = ho;
		sig = NULL;
		
	}
	
}*listaProgramas;// Puntero de Programas

struct Infraestructura{//Lista doble con insercion al final
	string nombre;
	string ubicacion;
	string tipoInfraestructura;
	struct Infraestructura *sig;
	struct Infraestructura *ant;
	Infraestructura(string nom,  string ubi, string ti){
		nombre = nom;
		ubicacion = ubi;
		tipoInfraestructura = ti;
		sig = NULL;
		ant = NULL;
		
	}
}*listaInfraestructura;//Puntero de infraestructura

struct Convenios{
	string nombre ;
	string ubicacion ;
	struct Convenios *sig;
	Convenios(string nom , string ubi){
		nombre = nom;
		ubicacion = ubi;
		sig = NULL;
		
	}
}*listaConvenios;



int main(){
	return 0;
}
