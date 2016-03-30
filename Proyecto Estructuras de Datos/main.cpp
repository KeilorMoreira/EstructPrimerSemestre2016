#include <iostream>
#include <string.h>
#include<stdio.h>
#include<sstream>
#include <cstdlib>

using namespace std;

//Prototipos para validar
struct Puestos*buscarPuestos(string);
struct Formacion*buscarFormacion(string);



// ###########################  ESTRUCTURAS QUE SE RELACIONAN A LA ESTRUCTURA PRINCIPAL CANTONES ################ //

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

// #####   Estructuras que se relacionan con MiembrosComite ##### //

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
struct Capacitaciones{//lista simple
	string nombre;
	struct Capacitaciones *sig;
	Capacitaciones(string  nom){
		nombre = nom;
		sig = NULL;
	}
}*listaCapacitacion;// puntero capacitacion


//   #################### ESTRUCTURAS DE ENLACE ################# //

//Enlace cantones - programas
struct En_Programas{
    struct Programas *enlace;
    struct En_Programas *sig;
};
// Enlace cantones - Infraestructura
struct En_Infraestructura{
    struct Infraestructura *enlace;
    struct En_Infraestructura *sig;
};
//Enlace cantones - convenios
struct En_Convenios{
    struct Convenios *enlace;
    struct En_Convenios *sig;
};
// Enlace miembrosComite - Capacitaciones
struct En_Capacitaciones{
    struct Capacitaciones * enlace;
    struct En_Capacitaciones *sig;
};

// #################### ESTRUCTURAS DE ASIGNACION RELACIONAL ################# //

/*
struct asignarPrograma(){




};


struct asignarConvenio(){

};

struct asignarInfraestructura(){

};

struct asignarCapacitacion(){

};
*/

// ####################  ESTRUCTURA PRINCIPAL CANTONES #######################//
/*

Debido a que la estructura Cantones esta se relaciona con todas las demas estructuras
se decidio dejarla entre sus respectivas estructuras tipo enlace y los metodos generales relacionados.

*/
struct Cantones{
	string nombre;
	string provincia;
	struct Cantones *ant, *sig;           //Punteros de lista doble
	struct En_Programas *En_Pro;          //Enlaces a Programas
	struct En_Infraestructura *En_Infra;  //Enlaces a Infraestructura
	struct En_Convenios *En_Conv;         //Enlaces a Convenios

	Cantones(string nom, string p){ // Constructor
		nombre = nom;
		provincia = p;
		sig = NULL; // Inicializador puntero
		ant = NULL; // Inicializador puntero

	}

}*listaCantones;//Primero de la estructura cantones

// ######################   METODOS VARIOS ######################## //

void insertarCantones(string nombre, string provincia ){///Funcion que inserta doblemente ordenado en la lista

	if (listaCantones==NULL){
        struct Cantones * nn = new Cantones(nombre,provincia);//aqui inserta los cantones
		listaCantones = nn;

		// cout<<"Se agrego el Canton"<<endl;
		return;
	}
    else{
	struct Cantones * nn = new Cantones(nombre,provincia);

	if (nombre< listaCantones->nombre)
	{
		nn->sig= listaCantones;
		listaCantones->ant=nn;
		listaCantones = nn;
		// cout<<"Se agrego el Canton"<<endl;
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
			// cout<<"Se agrego el Canton"<<endl;
		}
		else
		{
			temp2->sig= nn;
			nn->ant= temp2;
			// cout<<"Se agrego el Canton"<<endl;
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
    struct Puestos*buscador=buscarPuestos(nom);
    if(buscador!=NULL)
        cout<<"\nEse puesto ya existe\n";
    else{
        struct Puestos*nuevoPuesto=new Puestos(nom,id);
        nuevoPuesto->sig=listaPuestos;
        listaPuestos=nuevoPuesto;
        cout<<"\n\nEl Puesto "<<nuevoPuesto->nombre<<" ha sido insertado";
    }
}
	// cout<<"\nPuesto agregado correctamente:";
struct Puestos *buscarPuestos(string nom){
    if(listaPuestos==NULL){
        return NULL;
    }
    else{
        struct Puestos*temp=listaPuestos;
        while(temp!=NULL){
            if(temp->nombre==nom){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
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


void insertarFormacion(string n){//Insercion al final de una lista simple
        struct Formacion*buscador=buscarFormacion(n);
    if(buscador!=NULL)
        cout<<"\nEsa formacion ya existe\n";
    else{
        struct Formacion*nuevoFormacion=new Formacion(n);
        if(listaFormacion==NULL){
            nuevoFormacion->sig=listaFormacion;
            listaFormacion=nuevoFormacion;
        }
        else{
            struct Formacion*temp=listaFormacion;
            while(temp->sig!=NULL){
                temp=temp->sig;
            }
            temp->sig=nuevoFormacion;
            cout<<"\n\nLa formacion ha sido insertado";
        }
    }
}

struct Formacion*buscarFormacion(string n){
    if(listaFormacion==NULL){//si no hay circuitos
        return NULL;
    }
    else{
        struct Formacion*temp=listaFormacion;
        while(temp!=NULL){
            if(temp->nombre==n){
                return temp;//retorna esa formacion
            }
            temp=temp->sig;
        }
    }
    return NULL;//no encontro el circuito
}

void datosFormacion(){
	string nom;
	cout<<"\n Nombre de la formacion\n";
	cin>>nom;
	cout<<"\Formacion agregada correctamente\n";

	insertarFormacion(nom);
}




void insertarCapacitacion(string nom){//Funcion que inserta al inicio de la lista simple de capacitaciones
	struct Capacitaciones * nn = new Capacitaciones(nom);

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

void imprimirProgramas(){
    struct Programas * temp = listaProgramas;
    for(;temp != NULL; temp = listaProgramas->sig){
        cout<<temp->nombrePrograma<<"  "<<temp->Id<<endl;
        cout<<temp->fecha<<endl;
        cout<<temp->lugar<<endl;
        cout<<temp->hora<<endl;
    }

}

string nombrePrograma;
	string fecha;
	string lugar;
	string hora;





void menu(){//funcion del men aqui se maneja lo que el usuario desea realizar
    int opcion = 0;
    while(true){

        cout<<"\n1. Insertar Canton.  ";
        cout<<"\n2. Insertar Puestos.  ";
        cout<<"\n3. Imprimir Puestos.  ";
        cout<<"\n4  Insertar Capacitacion. ";
        cout<<"\n5  Insertar Miembro del comite.";
        cout<<"\n6  Insertar Programas.";
        cout<<"\n7  Insertar formacion.";
        cout<<"\n8. Salir.  ";

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
        else if(opcion == 4){
        	datosCapacitacion();
        }
        else if(opcion == 5){
        	datosMiembroComite();
        }
        else if(opcion == 6){
        	datosProgramas();
		}
		else if(opcion ==7){
			datosFormacion();
		}
		else if(opcion == 8){
            return ;
		}
    }

}

int main(){

    // ########### Datos precargados ################ //
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
	//

	listaProgramas = insertar("Natacion" , "mayo 14", "piscina TEC" , "10:00 am", listaProgramas);
	listaProgramas = insertar("Ajedres" , "mayo 14", "Polideportivo TEC" , "11:00 am", listaProgramas);
	listaProgramas = insertar("Futbol sala" , "mayo 15", "CanchaTEC" , "8:00 am", listaProgramas);


	//

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
    //



    menu();

	return 0;
}
