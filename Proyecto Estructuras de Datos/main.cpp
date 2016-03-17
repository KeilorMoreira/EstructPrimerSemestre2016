#include <iostream>
#include <string.h>


using namespace std;
// Aqui van las estructuras que vamos a trabajar

struct Cantones{
	string nombre;
	string provincia;
	struct Cantones *sig;//Lista doble
	struct Cantones *ant;
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


struct Programas{//Lista circular con insercion al inicio
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



void insertarCantones(string nombre, string provincia ){///Funcion que inserta doblemente ordenado en la lista

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
	cout<<"\nPuesto agregado correctamente:";

}

void datosPuestos(){
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




void menu(){
    int opcion = 0;
    while(true){

        cout<<"\n1. Insertar canton.  ";
        cout<<"\n2. Insertar puestos.  ";
        cout<<"\n3. Imprimir puestos.  ";
        cout<<"\n6. Salir.  ";

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
    }
}

int main(){
	menu();
	datosCantones();
	datosPuestos();
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
	
	
		
   insertarPuestos("Contador", 123);//datos predefinidos de puestos
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






