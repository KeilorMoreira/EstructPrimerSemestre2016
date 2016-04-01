#include <iostream>
#include <string.h>
#include<stdio.h>
#include<sstream>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>

using namespace std;

//Prototipos
struct Cantones*buscarCanton(string);
struct Puestos*buscarPuestos(string);
struct Formacion*buscarFormacion(string);
struct Capacitaciones*buscarCapacitaciones(string);
struct Convenios*buscarConvenios(string);
struct Infraestructura *buscarInfraestructura(string);





// ###########################  ESTRUCTURAS QUE SE RELACIONAN A LA ESTRUCTURA PRINCIPAL CANTONES ################ //

struct Programas{//Lista circular con insercion al inicio
    string ID;
	string nombre;
	string tipo;
	string fecha;
	string lugar;
	string hora;
	struct Programas *sig;
	Programas(string Id, string nom , string tip, string fe, string lu, string ho){
	    ID = Id;
		nombre = nom;
		tipo = tip;
		fecha = fe;
		lugar = lu;
		hora = ho;
		sig = NULL;
	}
}*listaProgramas;// Puntero de Programas

struct Infraestructura{//Lista doble con insercion al final
    string nombre;
	string administrada;
	string compartida;
	struct Infraestructura *ant, *sig;
	struct sublista_Infraestructura *Sub_Infra; // Nodo de enlace
	Infraestructura(string nombre, string adm,  string com){
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

// ##   Estructuras que se relacionan con MiembrosComite ## //
struct Puestos{//Lista simple insercion al inicio
	string nombre;//nombre
	struct Puestos *sig;
	struct miembrosComite *enlaceM;// aqui conecta el struct de miembroscomite con el struct de de puestos por medio de un enlace
	Puestos(string nom){
		nombre = nom;
		sig = NULL;
	}
}*listaPuestos;// Puntero de puestos

struct Formacion{ // Lista simple
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
}*listaCapacitaciones;// puntero capacitacion


//   #################### ESTRUCTURAS DE ENLACE ################# //

//Enlace cantones - programas
struct En_Programas{
    struct Programas *enlace;
    struct En_Programas *sig;
};
// Enlace cantones - Infraestructura
struct sublista_Infraestructura{
    //string nombre;
    //string ubicacion;
    struct Cantones *enlace;
    struct sublista_Infraestructura *sig;
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

void insertarInfraestructura (string nombrCant,string nombrInfra){
    struct Cantones *tempCant = buscarCanton(nombrCant);
    struct Infraestructura *tempInf = buscarInfraestructura(nombrInfra);
    if((tempCant != NULL) && (tempInf != NULL)){
        struct sublista_Infraestructura *nn = new sublista_Infraestructura();
        nn->enlace = tempCant; // Nodo de enlace dentro de nn de tipo sublista_Infraestructura(sublista) se relaciona al nodo de canton correspondiente.
        nn->sig = tempInf->Sub_Infra; // Nodo de enlace dentro de nodo tipo Infraenstructura (En_infra) se relaciona al sig dentro del nodo tipo sublista_Infraestructura (sig).
        tempInf->Sub_Infra = nn; // se corre el primero de sublista_Infraestructura (sublista)
    }
};

/*
struct asignarPrograma(){
    struct Programas *

};


struct asignarConvenio(){

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

// ############ ESTRUCTURA IMPRIMIR ########### //
void imprimir(string lista){

    if(lista == "cant"){ // Cantones, lista doble.
        struct Cantones *temp = listaCantones;
        if (temp == NULL){

            cout<<"La lista se encuentra vacia";
            return;
            }
        system("cls");
        cout<<"\n~~~~~~~~~~~~~~~~  CANTONES ~~~~~~~~~~~~~~~~"<<endl;
        while(temp != NULL){

                cout<<"Nombre:   \t"<<temp->nombre<<endl;
                cout<<"Provincia:\t"<<temp->provincia<<endl<<endl;
                temp= temp->sig;
                }
        cout<<"~~~~~~~~~~~~~~~~      UL     ~~~~~~~~~~~~~~~~"<<endl;
        system("pause");
        return;
    }

    else if(lista == "prog"){ // Programas, lista circular.
        struct Programas *temp = listaProgramas;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        do{
            if(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                cout<<"Fecha: "<<temp->fecha<<endl;
                cout<<"Lugar: "<<temp->lugar<<endl;
                cout<<"Hora: "<<temp->hora<<endl;
                temp = temp->sig;
            }
        }while(temp != listaProgramas);
        return;
    }

    else if(lista == "infr"){ // Infraestructuras, lista doble.
        struct Infraestructura *temp = listaInfraestructura;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Administrada: "<<temp->administrada<<endl;
                cout<<"Compartida: "<<temp->compartida<<endl;
                temp= temp->sig;
                }
        return;


    }

    else if(lista == "conv"){ // Convenios, lista simple.
        struct Convenios *temp = listaConvenios;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                temp= temp->sig;
                }
        return;

    }

    else if(lista == "miem"){ // MiembrosComite, lista simple.
        struct MiembrosComite *temp = listaMiembros;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                cout<<"ID: "<<temp->identificador<<endl;
                temp= temp->sig;
                }
        return;
    }

    else if(lista == "pues"){ // Puestos, lista simple.
        struct Puestos *temp = listaPuestos;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                temp= temp->sig;
                }
        return;

    }

    else if(lista == "form"){ // Formacion, lista simple.
        struct Formacion *temp = listaFormacion;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                temp= temp->sig;
                }
        return;

    }

    else if(lista == "capa"){ // Capacitaciones
        struct Capacitaciones *temp = listaCapacitaciones;
        if (temp == NULL){
            cout<<"La lista se encuentra vacia";
            return;
            }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                temp= temp->sig;
                }
        return;

    }

}

// #############################   METODOS VARIOS ############################ //

//  --- Cantones --- //
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
	fflush(stdin);
	cout<<"Ingrese el nombre del canton: ";
	getline(cin,nom);
	fflush(stdin);
	cout<<"\nIngrese el nombre de la provincia del canton: "<<endl;
	getline(cin,p);
	insertarCantones(nom , p);//Aqui los atrapa llamado la funcion insertarCantones
}

struct Cantones *buscarCanton (string nombre){
    struct Cantones *temp = listaCantones; // nodo temporal tipo Cantones
    if(temp == NULL)
        return NULL;
    do{
        if (temp->nombre == nombre) //si el atributo nombre del nodo es igual a variable nombre.
            return temp; // retorno nodo
        temp = temp->sig; //avanzo al siguiente nodo
    }while(temp != listaCantones); // hago lo anterior mientras nodo temporal sea diferente al primer nodo, o sea se puede recorrer toda la lista
    return NULL; // en caso de no coincidir ningun nodo, retorna NULL
};

/*
void imprimirCantones(){
        struct Cantones *temp = listaCantones;
        if (temp == NULL){
            cout<<"La lista de cantones se encuentra vacia";
            return;
        }
        while(temp != NULL){
                cout<<"Nombre: "<<temp->nombre<<endl;
                cout<<"Provincia: "<<temp->provincia<<endl;
                temp= temp->sig;
        }
        return;
}
*/

//  --- Puestos --- //
/*
void imprimirPuestos(struct Puestos*primero){//funcion que imprime
    struct Puestos*temp=primero;
    if(temp==NULL)
        cout<<"\nNo hay Puestos\n";
    else{
        cout<<"Nombre\t\tID\t\t\t"<<endl;
        while(temp!=NULL){
            cout<<"\n"<<temp->nombre<<"\t\t"<<endl;
            temp=temp->sig;
        }
    }
    cout<<"------------ULTIMA LINEA-----------------";
}
*/

void insertarPuestos(string nom){//inserta al inicio de la lista simple
    struct Puestos*buscador=buscarPuestos(nom);
    if(buscador!=NULL)
        cout<<"\nEse puesto ya existe\n";
    else{
        struct Puestos*nuevoPuesto=new Puestos(nom);
        nuevoPuesto->sig=listaPuestos;
        listaPuestos=nuevoPuesto;
        //cout<<"\n\nEl Puesto "<<nuevoPuesto->nombre<<" ha sido insertado";
    }
}

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
	cout<<"\nNombre del puesto: "<<endl;
	cin>>nom;
	cout<<"Puesto agregado\n";

	insertarPuestos(nom);

}

//  --- Formacion Profesional --- //
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
            //cout<<"\n\nLa formacion ha sido insertado";
        }
    }
}

/*
void imprimirFormacion(struct Formacion*primero){//Imprime la lista de formacion
    struct Formacion*temp=primero;
    if(temp==NULL)
        cout<<"\nNo hay Formaciones\n";
    else{//imprime los datos de cada formacion
        cout<<"\nNombre\n"<<endl;
        while(temp!=NULL){
            cout<<"\n"<<temp->nombre<<endl;
            temp=temp->sig;
        }
    }
    cout<<"------------ULTIMA LINEA-----------------";
}
*/

struct Formacion*buscarFormacion(string n){
    if(listaFormacion==NULL){//si no hay formacion
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
    return NULL;//no encontro la formacion
}

void datosFormacion(){
	string nom;
	cout<<"\n Nombre de la formacion\n";
	cin>>nom;
	cout<<"\nFormacion agregada correctamente\n";



	insertarFormacion(nom);
}


//  --- Capacitaciones --- //
void insertarCapacitacion(string nom){//Funcion que inserta al inicio de la lista simple de capacitaciones
   struct Capacitaciones*buscador=buscarCapacitaciones(nom);
   if(buscador!=NULL)
   cout<<"\nEsa capacitacion ya existe\n";//Valida si hay datos repetidos
    else{
	struct Capacitaciones*nuevoCapacitaciones=new Capacitaciones(nom);
	nuevoCapacitaciones->sig=listaCapacitaciones;
	listaCapacitaciones=nuevoCapacitaciones;
    }
}

/*
void imprimirCapacitaciones(struct Capacitaciones*primero){//funcion que imprime
    struct Capacitaciones*temp=primero;
    if(temp==NULL)
        cout<<"\nNo hay Capacitaciones\n";
    else{
        cout<<"Nombre\t\tID\t\t\t"<<endl;
        while(temp!=NULL){
            cout<<"\n"<<temp->nombre<<"\t\t"<<endl;
            temp=temp->sig;
        }
    }
    cout<<"------------ULTIMA LINEA-----------------";
}
*/

struct Capacitaciones *buscarCapacitaciones(string nom){
    if(listaCapacitaciones==NULL){
        return NULL;
    }
    else{
        struct Capacitaciones*temp=listaCapacitaciones;
        while(temp!=NULL){
            if(temp->nombre==nom){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
}

void datosCapacitacion(){// funcion que pide los datos de capacitacion
	string nom;
	cout<<"\nNombre de la Capacitacion\n";
	cin>> nom;

	insertarCapacitacion(nom);
}

void insertarConvenios(string nom){//Funcion que inserta al inicio de la lista simple de convenios
   struct Convenios*buscador=buscarConvenios(nom);
   if(buscador!=NULL)
   cout<<"\nEse convenio ya existe\n";//Valida si hay datos repetidos
    else{
	struct Convenios*nuevoConvenio=new Convenios(nom);
	nuevoConvenio->sig=listaConvenios;
	listaConvenios=nuevoConvenio;
    }
}

/*
void imprimirConvenios(struct Convenios*primero){//funcion que imprime los convenios
    struct Convenios*temp=primero;
    if(temp==NULL)
        cout<<"\nNo hay Convenios\n";
    else{
        cout<<"Nombre\t\tID\t\t\t"<<endl;
        while(temp!=NULL){
            cout<<"\n"<<temp->nombre<<"\t\t"<<endl;
            temp=temp->sig;
        }
    }
    cout<<"------------ULTIMA LINEA-----------------";
}
*/

struct Convenios *buscarConvenios(string nom){
    if(listaConvenios==NULL){
        return NULL;
    }
    else{
        struct Convenios*temp=listaConvenios;
        while(temp!=NULL){
            if(temp->nombre==nom){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
}

void datosConvenios(){
	string nom;
	cout<<"\nEscriba el nombre del convenio\n";
	cin>>nom;
	cout<<"\nSe agregado correctamente\n";

	insertarConvenios(nom);
}

//  --- MiembrosComite --- //
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

struct MiembrosComite *buscarMiembro(int ID){
    if(listaMiembros==NULL){
        return NULL;
    }
    else{
        struct MiembrosComite*temp=listaMiembros;
        while(temp!=NULL){
            if(temp->identificador==ID){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;

};

//  --- Programas --- //
/*
struct Programas *buscarPrograma(){



};
*/

struct Programas * insertar( struct Programas * Lista, string Id, string nomp , string tip, string fe, string lu , string ho){ //Funcion que inserta los programas (nodos) a la lista circular al inicio
    struct Programas * nn = new Programas(Id, nomp, tip, fe, lu, ho);
    if(Lista == NULL){
        Lista = nn;
        Lista->sig = Lista;//se hace circular
        }
    else{// se insertará al inicio de la lista circular
        struct Programas *temp = Lista;
        while(temp->sig!= Lista)
            temp= temp->sig;
        nn->sig = Lista;
        temp->sig = nn;
        Lista = nn;
        {
        	return Lista;//retorna la lista modificada, osea con un elemento más
		}
    }

    cout<<"\nSe agregado correctamente";
        {
    }
}

void datosProgramas(){
	string nomp;
	string tip;
	string fe;
	string lu;
	string ho;
	string ID;
	cout<<"\nEscriba el nombre del programa\n";
	getline(cin,nomp);
	cout<<"\nEscriba el tipo del programa\n";
	getline(cin,tip);
	cout<<"\nFecha del programa\n";
	getline(cin,fe);
	cout<<"\nEscriba el nombre del lugar\n";
	getline(cin,lu);
	cout<<"\nHora del programa a realizar\n";
	getline(cin,ho);
	cout<<"\nSe agregado correctamente"<<endl;

    listaProgramas = insertar(listaProgramas, ID, nomp , tip, fe, lu , ho);
    }

/*
void imprimirProgramas(){
    struct Programas * temp = listaProgramas; //Se establece un nodo temporal igual al primer nodo
    for(;temp!=NULL; temp = temp->sig){ // Se encicla el for para que recorra la lista.
        cout<<temp->nombrePrograma<<endl;
        cout<<temp->fecha<<endl;
        cout<<temp->lugar<<endl;
        cout<<temp->hora<<endl;
        if(temp->sig == listaProgramas) // Punto de parada cuando el nodo siguiente sea igual al primero.
            return;
    }
}
*/

//  --- Infraestructuras --- //



struct Infraestructura *buscarInfraestructura(string nomb){
    if(listaConvenios==NULL){
        return NULL;
    }
    struct Infraestructura* temp = listaInfraestructura;
    do{
        if(temp->nombre == nomb)
            return temp;
        temp = temp->sig;
    }while(temp != NULL);
    return NULL;
};






void cargarDatos(){
	// ########### Datos precargados ################ //
	insertarCantones("Sarapiqui","Heredia");//Datos predefinos de canton y su provincia
	insertarCantones("Santo Domingo","Heredia");
	insertarCantones("San Isidro","Heredia");
	insertarCantones("Puerto Viejo","Heredia");
	insertarCantones("Upala","Alajuela");
	insertarCantones("Barva","Heredia");
	insertarCantones("Santa Barbara","Heredia");
	insertarCantones("San Carlos","Alajuela");
	insertarCantones("San Ramon","Alajuela");
	insertarCantones("Santa Barbara","Heredia");
	imprimir("cant");

	//
    insertarPuestos("Contador");//datos predefinidos de puestos y su identificador
    insertarPuestos("Gerente");
    insertarPuestos("Presidente");
    insertarPuestos("Contadora");
    insertarPuestos("Visepresidente");
    insertarPuestos("Fiscal");
    insertarPuestos("Secretaria");
    insertarPuestos("Tesorero");
    insertarPuestos("Informatico");
    //imprimirPuestos(listaPuestos);

    //
	listaProgramas = insertar(listaProgramas, "Cod_01","Natacion" , "Deportivo", "mayo 14", "piscina TEC" , "10:00 am");
	listaProgramas = insertar(listaProgramas, "Cod_02","Yoga" , "Recreativo", "mayo 14", "Polideportivo TEC" , "11:00 am");
	listaProgramas = insertar(listaProgramas, "Cod_03","Futbol sala" , "Deportivo" , "mayo 15", "CanchaTEC" , "8:00 am");
    //
    insertarFormacion("Programador");
    insertarFormacion("Doctorado");
    insertarFormacion("Maestria");
    insertarFormacion("Segundaria");
    insertarFormacion("Kinder");
    insertarFormacion("Telematica");
    insertarFormacion("Licensiatura");
    insertarFormacion("Bachiderato");
    insertarFormacion("Universetaria");
    insertarFormacion("Colegio");
    //imprimirFormacion(listaFormacion);
}






void menuAdministracion(){
    int opcion = 0;
    while(true){
        cout<<"\n[1]  Insertar Cantón.";
        cout<<"\n[2]  Eliminar Cantón.";
        cout<<"\n[3]  Imprimir Cantones.\n- - - - - - - - - - - - - -";

        cout<<"\n[4]  Insertar Puesto.";
        cout<<"\n[5]  Eliminar Puesto.";
        cout<<"\n[6]  Imprimir Puestos.";

        cout<<"\n[7]  Insertar Capacitación.";
        cout<<"\n[8]  Eliminar Capacitación.";
        cout<<"\n[9]  Imprimir Capacitaciones.";

        cout<<"\n[10] Insertar Miembro de Comité.";
        cout<<"\n[11] Eliminar Miembro de Comité.";
        cout<<"\n[12] Imprimir Miembros de los Comité.";

        cout<<"\n[13] Insertar Programa.";
        cout<<"\n[14] Eliminar Programa.";
        cout<<"\n[15] Imprimir Programas.";

        cout<<"\n[16] Insertar Formación Académica.";
        cout<<"\n[17] Eliminar Formación Académica.";
        cout<<"\n[18] Imprimir Formación Académica.";

        cout<<"\n[19] Insertar Convenio.";
        cout<<"\n[20] Eliminar Convenio.";
        cout<<"\n[21] Imprimir Convenios.";

        cout<<"\n[22] Insertar Infraestructura.";
        cout<<"\n[23] Eliminar Infraestructura.";
        cout<<"\n[24] Imprimir Infraestructuras.";

        cout<<"\n[-1] Salir.";
        cin >> opcion;

        if(opcion == 1){
            datosCantones();
        }
        else if(opcion == 2){
            datosPuestos();
        }
        else if(opcion == 3){
            //imprimirPuestos();
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
            //imprimirProgramas();
		}
		else if(opcion ==8){
			datosFormacion();
	    }
		else if(opcion == 9){
            insertarConvenios("CCSS");
            insertarConvenios("INA");
            insertarConvenios("TEC");
            //imprimirConvenios(listaConvenios);
		}
		else if(opcion == 10){
			cargarDatos();
			system("cls");
		}
		else if(opcion == -1){
            return ;
		}
    }
}

void menuConsultas(){

}

void menuReportes(){

}

void menu(){//funcion del men aqui se maneja lo que el usuario desea realizar
    int opcion = 0;
    while(true){
        cout<<"\n[1]  Menu de Administrador.";
        cout<<"\n[2]  Menu de Consultas.";
        cout<<"\n[3]  Menu de Reportes.\n";
        cout<<"\n[-1] Salir del Programa.\n- - - - - - - - - - - - - -\n>>> ";
        cin >> opcion;

        if(opcion == 1){
            menuAdministracion();
        }
        else if(opcion == 2){
            menuConsultas();
        }
        else if(opcion == 3){
            menuReportes();
        }
        else if(opcion == -1){
            return;
        }
    }

}




int main(){
	//cargarDatos();
    menu();
	return 0;
}
