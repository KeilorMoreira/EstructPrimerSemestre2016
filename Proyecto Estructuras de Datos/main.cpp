#include <iostream>
#include <string.h>//importa la libreria de string
#include <stdlib.h>
#include <cstring>


using namespace std;
// Aqui van las estructuras que vamos a trabajar

struct Cantones{
	string nombre;
	string provincia;
	struct Cantones *sig;//Lista doble
	struct Cantones *ant;
	struct MiembrosComite *enlaceM;//enlazado con la estructura miembros del comite
	Cantones(string nom, string p){
		nombre = nom;
		provincia = p;
		sig = NULL;
		ant = NULL;
		
	}
		
}*listaCantones;//Puntero de la estructura cantones 


struct Puestos{//Lista simple insercion al inicio
	string nombre;//nombre
	int Id;
	struct Puestos *sig;
	struct MiembrosComite *enlaceM;// aqui conecta el struct de miembroscomite con el struct de de puestos por medio de un enlace
	Puestos(string nom, int id){
		nombre = nom;
		Id = id;
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
struct Capacitacion{//lista simple
	string nombre;
	struct Capacitacion *sig;
	Capacitacion(string  nom){
		nombre = nom;
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





struct Programas{//Lista circular con insercion el inicio
	string nombrePrograma;
	string fecha;
	string lugar;
	string hora;
	struct Programas *sig;
	Programas(string nom , string fe, string lu, string ho){
		nombrePrograma = nom;
		fecha = fe;
		lugar = lu;
		hora = ho;
		sig = NULL;
		
	}
	
}*listaProgramas;// Puntero de Programas

struct Infraestructura{//Lista doble con insercion al final
	string administrada;
	string compartida;
	struct Infraestructura *sig;
	struct Infraestructura *ant;
	Infraestructura(string adm,  string com){
		administrada = adm;
		compartida = com;
		sig = NULL;
		ant = NULL;
		
	}
}*listaInfraestructura;//Puntero de infraestructura

struct Convenios{
	string nombre ;
	struct Convenios *sig;
	Convenios(string nom){
		nombre = nom;
		sig = NULL;
		
	}
}*listaConvenios;



void insertarCantones(string nombre, string provincia ){///Funcion que inserta cantones doblemente ordenado

	if (listaCantones==NULL){
        struct Cantones * nn = new Cantones(nombre,provincia);//aqui inserta los cantones
		listaCantones = nn;
		cout<<"Se agrego el Canton"<<endl;
		return;
	}
    else{
	struct Cantones * nn = new Cantones(nombre,provincia);

	if (nombre< listaCantones->nombre)
	{
		nn->sig= listaCantones;
		listaCantones->ant=nn;
		listaCantones = nn;
		cout<<"Se agrego el Canton"<<endl;
	}
	else
	{
		struct Cantones * temp1 = listaCantones;
		struct Cantones * temp2;
		while ( (temp1!=NULL) and (nombre> temp1->nombre) )	
		{														
			temp2 = temp1;
			temp1 = temp1->sig;
		}
		if (temp1!=NULL)
		{
			nn->sig = temp1;
			nn->ant = temp1->ant;
			temp1->ant->sig = nn;
			temp1->ant= nn;
			cout<<"Se agrego el Canton"<<endl;
		}
		else
		{
			temp2->sig= nn;
			nn->ant= temp2;
			cout<<"Se agrego el Canton"<<endl;
		}
	}
}

}

void datosCantones(){//funcion que pide los datos para agregar un canton y provincia
	string nom;
	string p;
	cout<<"\nIngrese el nombre del canton: "<<endl;
	cin>>nom;
	cout<<"\nIngrese el nombre de la provincia del canton: "<<endl;
	cin>>p;
	
	insertarCantones(nom , p);//Aqui los atrapa llamado la funcion insertarCantones
}

void insertarPuestos(string nom , int id){//inserta al inicio de la lista simple
	struct Puestos * nn = new Puestos(nom, id);
	
	nn->sig = listaPuestos;
	listaPuestos = nn;
	cout<<"\nPuesto agregado correctamente\n";

}

void datosPuestos(){//pide los datos al usuario de los puestos que desea 
	string nom;
	int id;
	cout<<"\nNombre del puesto: "<<endl;
	cin>>nom;
	cout<<"\nIdentificador del puesto: "<<endl;
	cin>>id;
	
	insertarPuestos(nom, id);

}


void imprimirPuestos(){//funcion para imprimri la lista de puestos
    struct Puestos * temp = listaPuestos;
    while(temp != NULL){
        cout<<temp->nombre<<"  "<<temp->Id<<endl;
        temp = temp->sig;
    }
    cout<<"\n-------------------Fin de lista de puestos--------------\n\n";
}


void insertarCapacitacion(string nom){//Funcion que inserta al inicio de la lista simple de capacitaciones 
	struct Capacitacion * nn = new Capacitacion(nom);
	
	nn->sig = listaCapacitacion;
	listaCapacitacion = nn;
	cout<<"\n Capacitacion agregado correctamente\n";
	

}

void datosCapacitacion(){// funcion que pide los datos de capacitacion
	string nom;
	cout<<"\nNombre de la Capacitacion\n";
	cin>> nom;
	
	insertarCapacitacion(nom);
}


void insertarMiembrosComite(string nom, int Id){//funcion que inserta al inicio los miembros del comite
	struct MiembrosComite * nn = new MiembrosComite(nom, Id);
	nn->sig = listaMiembros;
	listaMiembros = nn;
	cout<<"\n Miembro del comite agregado correctamente\n";
}

void datosMiembroComite(){//Funcion que pide los datos a los miembros del comite
	string nom;
	int Id;
	cout<<"\nNombre del miembro del comite\n";
	cin>>nom;
	cout<<"\nIdentificador del miembro del comite\n";
	cin>>Id;
	
	insertarMiembrosComite(nom,Id);
}


string nombrePrograma;
	string fecha;
	string lugar;
	string hora;

//Funcion que inserta los programas la lista circular al inicio
struct Programas * insertar(string nomp , string fe, string lu , string ho, struct Programas * Lista){
    struct Programas * nn = new Programas(nomp,fe,lu,ho);
    if(Lista == NULL){
        Lista = nn;
        Lista->sig = Lista;//se hace circular

    }
    else{// se insertará al inicio de la lista circular

        struct Programas *ultimo = Lista;
        while(ultimo->sig!= Lista)
            ultimo= ultimo->sig;

        ultimo->sig = nn;
        nn->sig = Lista;
        Lista = nn;
        {
        	return Lista;//retorna la lista modificada, osea con un elemento más
		}
    }
    
    cout<<"\nSe agregado correctamente";
}

void datosProgramas(){
	string nomp;
	string fe;
	string lu;
	string ho;
	cout<<"\nEscriba el nombre del programa\n";
	cin>>nomp;
	cout<<"\nFecha del programa\n";
	cin>>fe;
	cout<<"\nEscriba el nombre del lugar\n";
	cin>>lu;
	cout<<"\nHora del programa a realizar\n";
	cin>>ho;
	cout<<"\nSe agregado correctamente"<<endl;
	
    struct Programas * insertar(string nomp , string fe, string lu , string ho, struct Programas * Lista);
    }

void menu(){//funcion del men aqui se maneja lo que el usuario desea realizar
    int opcion = 0;
    while(true){

        cout<<"\n1. Insertar Canton.  ";
        cout<<"\n2. Insertar Puestos.  ";
        cout<<"\n3. Imprimir Puestos.  ";
        cout<<"\n4  Insertar Capacitacion. ";
        cout<<"\n5  Insertar Miembro del comite.";
        cout<<"\n6  Insertar Programas.";
        cout<<"\n7. Salir.  ";

        cin >> opcion;

        if(opcion == 1){
            datosCantones();
        }
        else if(opcion == 2){
            datosPuestos();
        }
        else if(opcion == 3){
            imprimirPuestos();
         }
        else if(opcion ==4){
        	datosCapacitacion();
    }
        else if(opcion ==5){
        	datosMiembroComite();
    }
        else if(opcion ==6){
        	datosProgramas();
		}
		}

        }

int main(){
	menu();
	datosCantones();
	datosPuestos();
	datosCapacitacion();
	datosMiembroComite();
	datosProgramas();
	imprimirPuestos();
	
	
	insertarCantones("Sarapiqui","Heredia");//Datos predefinos de canton y su provincia
	insertarCantones("Santo Domigo","Heredia");
	insertarCantones("San Isidro","Heredia");
	insertarCantones("Puerto Viejo","Heredia");
	insertarCantones("Upala","Alajuela");
	insertarCantones("Barva","Heredia");
	insertarCantones("Santa Barbara","Heredia");
	insertarCantones("San Carlos","Alajuela");
	insertarCantones("San Ramon","Alajuela");
	insertarCantones("Santa Barbara","Heredia");
	
	
		
   insertarPuestos("Contador", 123);//datos predefinidos de puestos y su identificador
   insertarPuestos("Gerente", 124);
   insertarPuestos("Presidente", 125);
   insertarPuestos("Contadora", 126);
   insertarPuestos("Visepresidente", 127);
   insertarPuestos("Fiscal", 923);
   insertarPuestos("Secretaria", 153);
   insertarPuestos("Secretaria", 523);
   insertarPuestos("Tesorero", 323);
   insertarPuestos("Informatico", 122);
   
   
	return 0;
}
