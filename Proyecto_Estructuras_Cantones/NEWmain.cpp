#include <iostream>
#include <string.h>
#include<stdio.h>
#include<sstream>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <locale.h> // permite utilizar el idioma local, para acentos u otros.



using namespace std;

// ###################  PRIMER ESTRUCTURA RELACIONAL: CANTONES (VER DIAGRAMA DE RELACCION CANTON - COMITES EN DOC EXTERNA) ##################

// Estructura, lista de Cantones del pais.
struct Cantones{ // Lista Doble
	string nombre;
	string provincia;
	struct Cantones *ant, *sig;           //Punteros de lista doble
    struct sublistaMiembros *enlaceSubMiembros;
    struct sublista_Covenios *enlaceConvenios;
    struct sublista_Infraestructura *enlaceInfraestructura;
    struct sublista_Programas *enlaceSublista_Programas;

	Cantones(string nom, string p){ // Constructor
		nombre = nom;
		provincia = p;
		sig = NULL; // Inicializador puntero
		ant = NULL; // Inicializador puntero
		enlaceSubMiembros = NULL;
		enlaceConvenios = NULL;
		enlaceInfraestructura = NULL;
		enlaceSublista_Programas = NULL;
	}

}*PCantones;//Primero de la estructura cantones

//* ------------------------------------Metodos sobre lista Cantones (buscar, insertar, pedirDatos, imprimir, otros)

struct Cantones *buscarCanton (string nombre){
    struct Cantones *temp = PCantones; // nodo temporal tipo Cantones
    if(temp == NULL)
        return NULL;
    do{
        if (temp->nombre == nombre) //si el atributo nombre del nodo es igual a variable nombre.
            return temp; // retorno nodo
        temp = temp->sig; //avanzo al siguiente nodo
    }while(temp != PCantones); // hago lo anterior mientras nodo temporal sea diferente al primer nodo, o sea se puede recorrer toda la lista
    return NULL; // en caso de no coincidir ningun nodo, retorna NULL
};

void insertarCantones(string nombre, string provincia ){///Funcion que inserta doblemente ordenado en la lista

	if (PCantones==NULL){
        struct Cantones * nn = new Cantones(nombre,provincia);//aqui inserta los cantones
		PCantones = nn;

		// cout<<"Se agrego el Canton"<<endl;
		return;
	}
    else{
	struct Cantones * nn = new Cantones(nombre,provincia);

	if (nombre< PCantones->nombre)
	{
		nn->sig= PCantones;
		PCantones->ant=nn;
		PCantones = nn;
		// cout<<"Se agrego el Canton"<<endl;
	}
	else
	{
		struct Cantones * temp1 = PCantones;
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
		//else
		{
			//temp2->sig= nn;
			//nn->ant= temp2;
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
	cout<<"\nIngrese el nombre de la provincia del canton: ";
	getline(cin,p);
	fflush(stdin);
	insertarCantones(nom , p);//Aqui los atrapa llamado la funcion insertarCantones
}

void imprimirCantones(){
    struct Cantones *temp = PCantones;
    if (temp == NULL){
        cout<<"La lista se encuentra vacia.\n";
        system("pause");
        return;
        }
    system("cls");
    cout<<"\n~~~~~~~~~~~~~~~~  LISTA DE CANTONES ~~~~~~~~~~~~~~~~\n"<<endl;
    while(temp != NULL){
            cout<<"Nombre:   \t"<<temp->nombre<<endl;
            cout<<"Provincia:\t"<<temp->provincia<<endl<<endl;
            temp= temp->sig;
                }
    system("pause");
    return;
}
// Estructura, sublista de miebros de un comite cantonal
struct sublistaMiembros{
    int identificador;
    string nombre;
    struct sublistaMiembros *sig;
    struct Formaciones * enlaceFormacion;
    struct sublistaCapacitaciones *enlaceSubCapacitacion;
    struct Puestos * enlacePuesto;
    sublistaMiembros(int ID, string nomb){
        identificador = ID;
        nombre = nomb;
        sig = NULL;
        enlaceFormacion = NULL;
        enlaceSubCapacitacion = NULL;
        enlacePuesto = NULL;
    }
};

// Estructura, sublista de capacitaciones que puede tener un miembro de comite.
struct sublistaCapacitaciones{
    struct sublistaCapacitaciones *sig;
    struct Capacitaciones * enlaceCapacitaciones; // enlace a nodo de la lista capacitaciones.
    sublistaCapacitaciones(){
        sig = NULL;
        enlaceCapacitaciones = NULL;
    }
};
//* ------------------------------------Estructura y Metodos sobre lista Capacitaciones (buscar, insertar, pedirDatos, imprimir, otros)
struct sublista_Infraestructura{// Estructura , sublista de infraestructra de cantones
    struct sublista_Infraestructura *sig ;
    struct Infraestructura *enlaceInfraestructura;//enlace con la estructura infraestructura
    sublista_Infraestructura(){
	sig = NULL;
    enlaceInfraestructura = NULL;
}
};
//
struct Capacitaciones{//lista simple
	string nombre;
	struct Capacitaciones *sig;
	Capacitaciones(string nom){
		nombre = nom;
		sig = NULL;
	}
}*PCapacitaciones;// puntero capacitacion

struct Capacitaciones *buscarCapacitaciones(string nom){
    if(PCapacitaciones==NULL){
        return NULL;
    }
    else{
        struct Capacitaciones*temp=PCapacitaciones;
        while(temp!=NULL){
            if(temp->nombre==nom){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
}

void insertarCapacitacion(string nom){//Funcion que inserta al inicio de la lista simple de capacitaciones
   struct Capacitaciones*buscado=buscarCapacitaciones(nom);
   if(buscado!=NULL)
   cout<<"\nEsa capacitacion ya existe\n";//Valida si hay datos repetidos
    else{
	struct Capacitaciones*nuevoCapacitaciones=new Capacitaciones(nom);
	nuevoCapacitaciones->sig=PCapacitaciones;
	PCapacitaciones=nuevoCapacitaciones;
    }
}

void datosCapacitacion(){// funcion que pide los datos de capacitacion
	string nom;
	fflush(stdin);
	cout<<"\nNombre de la Capacitacion: ";
	getline(cin,nom);
	fflush(stdin);
	insertarCapacitacion(nom);
}

void imprimirCapacitaciones(){
    struct Capacitaciones *temp = PCapacitaciones;
    if (temp == NULL){
        cout<<"La lista se encuentra vacia.\n";
        system("pause");
        return;
        }
    cout<<"\n~~~~~~~~~~~~~~~~  LISTA DE CAPACITACIONES ~~~~~~~~~~~~~~~~\n"<<endl;
    while(temp != NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp= temp->sig;
            }
    system("pause");
    return;

    }



//* ------------------------------------Estructura y Metodos sobre lista Formacion (buscar, insertar, pedirDatos, imprimir, otros)
struct Formaciones{ // Lista simple
	string nombre;
	struct Formaciones *sig;
	Formaciones(string nom){
		nombre = nom;
		sig = NULL;
	}
}*PFormacion;// puntero de formacion

struct Formaciones*buscarFormacion(string n){
    if(PFormacion==NULL){//si no hay formacion
        return NULL;
    }
    else{
        struct Formaciones*temp=PFormacion;
        while(temp!=NULL){
            if(temp->nombre==n){
                return temp;//retorna esa formacion
            }
            temp=temp->sig;
        }
    }
    return NULL;//no encontro la formacion
}

void insertarFormacion(string n){//Insercion al final de una lista simple
        struct Formaciones*buscador=buscarFormacion(n);
    if(buscador!=NULL)
        cout<<"\nEsa formacion ya existe\n";
    else{
        struct Formaciones*nuevoFormacion=new Formaciones(n);
        if(PFormacion==NULL){
            nuevoFormacion->sig=PFormacion;
            PFormacion=nuevoFormacion;
        }
        else{
            struct Formaciones*temp=PFormacion;
            while(temp->sig!=NULL){
                temp=temp->sig;
            }
            temp->sig=nuevoFormacion;
            //cout<<"\n\nLa formacion ha sido insertado";
        }
    }
}

void datosFormacion(){
	string nom;
	fflush(stdin);
	cout<<"\n Nombre de la formacion\n";
	cin>>nom;
	cout<<"\nFormacion agregada correctamente\n";



	insertarFormacion(nom);
}

void imprimirFormaciones(){

    struct Formaciones *temp = PFormacion;
    if (temp == NULL){
        cout<<"La lista se encuentra vacia.\n";
        system("pause");
        return;
        }
    cout<<"\n~~~~~~~~~~~~  LISTA DE FORMACIONES LABORALES ~~~~~~~~~~~~\n"<<endl;
    while(temp != NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp= temp->sig;
            }
    system("pause");
    return;

}


//* ------------------------------------Estructura y Metodos sobre lista Puestos (buscar, insertar, pedirDatos, imprimir, otros)
struct Puestos{//Lista simple insercion al inicio
	string nombre;//nombre
	struct Puestos *sig;
	Puestos(string nom){
		nombre = nom;
		sig = NULL;
	}
}*PPuestos;// Puntero de puestos

struct Puestos *buscarPuestos(string nom){
    if(PPuestos==NULL){
        return NULL;
    }
    else{
        struct Puestos*temp=PPuestos;
        while(temp->sig!=NULL){
            if(temp->nombre==nom){
                    cout<<"Encontrado: "<<temp->nombre<<endl;
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
}

void insertarPuestos(string nom){//inserta al inicio de la lista simple
    struct Puestos*buscador=buscarPuestos(nom);
    if(buscador!=NULL)
    {
      cout<<"\nEse puesto ya existe\n";
      return;
    }

    else{
        struct Puestos*nuevoPuesto=new Puestos(nom);
        nuevoPuesto->sig=PPuestos;
        PPuestos=nuevoPuesto;
        //cout<<"\n\nEl Puesto "<<nuevoPuesto->nombre<<" ha sido insertado";
    }
}

void datosPuestos(){
	string nom;
	fflush(stdin);
	cout<<"\nNombre del puesto: ";
	getline(cin,nom);
	fflush(stdin);
	cout<<"Puesto agregado\n";
	insertarPuestos(nom);

}

void imprimirPuestos(){
    struct Puestos *temp = PPuestos;
    if (temp == NULL){
        cout<<"La lista se encuentra vacia.\n";
        system("pause");
        return;
        }
    cout<<"\n~~~~~~~~~~~~~~~~  LISTA DE PUESTOS ~~~~~~~~~~~~~~~~\n"<<endl;
    while(temp != NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp= temp->sig;
            }
    system("pause");
    return;

}


// ^^^^^  RELACIONES SOBRE SUBLISTAS   ^^^^^^

// Restricciones :  Enlaza un UNICO nodo a las sublistas, 1 puesto con 1 formacion y 1 capacitacion.
void insertarMiembro(string cant,int ID, string nomb, string puest, string form, string cap){
    struct Cantones * cantonBuscado = buscarCanton(cant);
    struct Puestos * puestoBuscado = buscarPuestos(puest);
    struct Formaciones * formacionBuscada = buscarFormacion(form);
    //struct Capacitaciones * capacitacionBuscada = buscarCapacitaciones(cap);

    if( cantonBuscado == NULL){
        cout<<"Canton no encontrado, favor verificar";
        system("pause");
        return;
    }
    if (puestoBuscado == NULL){
        cout<<"Puesto no encontrado, favor verificar";
        system("pause");
        return;
    }
    if(formacionBuscada == NULL){
        cout<<"Formación no encontrado, favor verificar";
        system("pause");
        return;
    }
    //if(capacitacionBuscada == NULL){
        //cout<<"Capacitación no encontrada, favor verificar";
        //system("pause");
       // return;
        //}

        struct sublistaMiembros *nuevoMiembro = new sublistaMiembros(ID,nomb);
        for(;cantonBuscado->enlaceSubMiembros->sig!=NULL;cantonBuscado->enlaceSubMiembros->sig=cantonBuscado->enlaceSubMiembros){
            if(cantonBuscado->enlaceSubMiembros->identificador==ID){
                cout<<"El miembro del cantón ya se encuentra registrado";
                return;
            }
        }// Si sale del for se valida correctamente y no es un dato repetido.



        nuevoMiembro->enlacePuesto = puestoBuscado;
        nuevoMiembro->enlaceFormacion = formacionBuscada;
		
		nuevoMiembro->sig = cantonBuscado->enlaceSubMiembros;
        cantonBuscado->enlaceSubMiembros = nuevoMiembro;
		
		
		

}

void sublistaCapasitaciones(){
	struct Capacitaciones * capacitacionBuscada = buscarCapacitaciones();
	//struct subListaCapacitaciones * nuevoNodo = new sublistaCapasitaciones;
	
	if(capacitacionBuscada == NULL){
        cout<<"Capacitación no encontrada, favor verificar";
        system("pause");
        return;
        }
        
        struct sublistaCapasitaciones *nuevoNodo = new sublistaCapasitaciones();
        for(;capacitacionBuscada->enlaceSubCapacitacion->sig!=NULL;capacitacionBuscada->enlaceSubCapacitacion->sig=capacitacionBuscada->enlaceSubCapacitacion){
            if(capacitacionBuscada->enlaceSubCapacitacion->nombre==nom){
                cout<<"El capasitacion ya se encuentra registrada";
                return;
            }
        }// Si sale del for se valida correctamente y no es un dato repetido.

        
		nuevoNodo->enlaceCapacitaciones = capacitacionBuscada;
		nuevoNodo->sig = nuevoMiembro->enlaceSubCapacitacion;
		nuevoMiembro->enlaceSubCapacitacion = nuevoNodo;
	}

void AgregarNuevoMiembro(){
    int identificacion;
    string nombre, apellidos, puesto, formacion, capacitaciones;
    fflush(stdin);
    cout<<"Digite identificación del nuevo Miembro: "<<endl;
    cin>>identificacion;
    cout<<"Digite el nombre del nuevo Miembro: "<<endl;
    getline(cin,nombre);




}

void impInfoPersoXcanton(){
    struct Cantones * temp = PCantones;
    for(;temp!=NULL;temp->sig=temp){
        cout<<"Canton: ["<<temp->nombre<<"]"<<endl;
        for(;temp->enlaceSubMiembros->sig!=NULL;temp->enlaceSubMiembros->sig = temp->enlaceSubMiembros){
            cout<<"Identificación: "<<temp->enlaceSubMiembros->identificador<<endl;
            cout<<"Nombre Completo: "<<temp->enlaceSubMiembros->nombre<<endl;
            cout<<"Puesto: "<<temp->enlaceSubMiembros->enlacePuesto->nombre<<endl;
            cout<<"Grado académico: "<<temp->enlaceSubMiembros->enlaceFormacion->nombre<<endl;
            for(;temp->enlaceSubMiembros->enlaceSubCapacitacion->sig!=NULL; temp->enlaceSubMiembros->
            enlaceSubCapacitacion->sig=temp->enlaceSubMiembros->enlaceSubCapacitacion){
                    cout<<"Capacitado en: "<<temp->enlaceSubMiembros->enlaceSubCapacitacion->enlaceCapacitaciones->nombre<<endl;
                }


        }

    }




}



//  Clase estructura con sus respectivos metodos
struct Convenios{
	string nombre ;
	struct Convenios *sig;
	Convenios(string nom){
		nombre = nom;
		sig = NULL;

	}
}*PConvenios;

struct Convenios *buscarConvenios(string nom){
    if(PConvenios==NULL){
        return NULL;
    }
    else{
        struct Convenios*temp=PConvenios;
        while(temp!=NULL){
            if(temp->nombre==nom){
                return temp;
            }
            temp=temp->sig;
        }
    }
    return NULL;
}





void insertarConvenios(string nom){//Funcion que inserta al inicio de la lista simple de convenios
   struct Convenios*buscador=buscarConvenios(nom);
   if(buscador!=NULL)
   cout<<"\nEse convenio ya existe\n";//Valida si hay datos repetidos
    else{
	struct Convenios*nuevoConvenio=new Convenios(nom);
	nuevoConvenio->sig=PConvenios;
	PConvenios=nuevoConvenio;
    }
}

void datosConvenios(){
    string nom;
	fflush(stdin);
	cout<<"\nEscriba el nombre del convenio\n";
	getline(cin,nom);
	fflush(stdin);
	cout<<"\nSe agregado correctamente\n";
	insertarConvenios(nom);


}

void imprimirConvenios(){
    struct Convenios *temp = PConvenios;
    if (temp == NULL){
        cout<<"La lista de convenios se encuentra vacia.\n";
        system("pause");
        return;
        }
    cout<<"\n~~~~~~~~~~~~~~~~  LISTA DE Convenios ~~~~~~~~~~~~~~~~\n"<<endl;
    while(temp != NULL){
            cout<<"Nombre: "<<temp->nombre<<endl;
            temp= temp->sig;
            }
    system("pause");
    return;

}

// Sublista simple que se enlace con la clase convenios
struct sublista_Covenios{
    struct sub_Covenios *sig;
    struct Convenios *enlaceC;
    sublista_Covenios(){
    sig = NULL;
}
};




// clase estructura de infraestructura con sus respetivos metodos
struct Infraestructura{//Lista doble con insercion al final
    string nombre;
	string administrada;
	string compartida;
	struct Infraestructura *ant, *sig;
	Infraestructura(string nombre, string adm,  string com){
		administrada = adm;
		compartida = com;
		sig = NULL;
		ant = NULL;

	}
}*PInfraestructura;//Puntero de infraestruc

struct Infraestructura *buscarInfraestructura(string nomb){//Buscar de infraestructura
    if(PInfraestructura==NULL){
        return NULL;
    }
    struct Infraestructura* temp = PInfraestructura;
    do{
        if(temp->nombre == nomb)
            return temp;
        temp = temp->sig;
    }while(temp != NULL);
    return NULL;
};

//insertar al inicio de la lista doble
void insertarInfraestructuras(string nom, string adm,  string com){

    struct Infraestructura *nn = new Infraestructura(nom, adm, com);

    nn->ant = PInfraestructura;

    if (PInfraestructura!= NULL)
        PInfraestructura->sig = nn;

    PInfraestructura = nn;
}

void datosInfraestructura(){//funcion que pide los datos
	string nom;
	string adm;
	string com;
	fflush(stdin);
	cout<<"\nNombre de la infraestructura:\n";
	getline(cin,nom);
	fflush(stdin);
	cout<<"\nNombre de la infraestructura administrada:\n";
	getline(cin,adm);
	fflush(stdin);
	cout<<"\nNombre de la infraestrura compartida:\n";
	getline(cin,com);
	fflush(stdin);
	cout<<"\nInfraestructura agregada correctamente\n";
	insertarInfraestructuras(nom,adm,com);
}

//Estructura de programa y sus metodos
struct Programas{//Lista circular con insercion al inicio
	string tipoPrograma;
	struct Programas *sig;
	Programas( string tip){
	    tipoPrograma = tip;
		sig = NULL;
	}
}*PProgramas;// Puntero de Programas
struct Programas * insertar( struct Programas * Lista, string tip){ //Funcion que inserta los programas (nodos) a la lista circular al inicio
    struct Programas * nn = new Programas(tip);
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
    string tip;
	fflush(stdin);
	cout<<"\nEscriba el tipo del programa\n";
	getline(cin,tip);
	cout<<"\nSe agregado correctamente"<<endl;

    PProgramas = insertar(PProgramas, tip);
    }



struct sublista_Programas{
    string hora;
    string fecha;
    string lugar;
    struct sublista_Programas *sig;
    struct Programas *enlaceProgramas;
    sublista_Programas(string h , string f ,  string lu){
        hora = h;
        fecha = f;
        lugar = lu;
        sig = NULL;
        enlaceProgramas = NULL;
    }
};
// #################################################             CICLO DE  MENUES             ###############################################

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
	//imprimirCantones();
	//
    insertarCapacitacion("Primeros Auxilios");
    insertarCapacitacion("SAP");
    insertarCapacitacion("Ofimatica");
    insertarCapacitacion("Encryptación Digital");
    insertarCapacitacion("Seguridad Documental");
    //imprimirCapacitaciones();
    //
    insertarFormacion("Programador");
    insertarFormacion("Doctorado");
    insertarFormacion("Maestria");
    insertarFormacion("Segundaria");
    insertarFormacion("Kinder");
    insertarFormacion("Licenciatura");
    insertarFormacion("Bachiderato");
    insertarFormacion("Universitaria");
    insertarFormacion("Colegio");
    //imprimirFormaciones();
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
    //imprimirPuestos();
    //
    insertarMiembro("Sarapiqui",206710961,"Keilor Moreira Alvarado","Fiscal","Universitaria","Ofimatica");
    insertarMiembro("Sarapiqui",111111111,"Tony Corrales","Visepresidente","Universitaria","SAP");
    //impInfoPersoXcanton();

}


void menuAdministracion(){
    int opcion = 0;
        /* Tabla de colores.
        0 = Negro
        1 = Azul
        2 = Verde
        3 = Aguamarina
        4 = Rojo
        5 = Purpura
        6 = Amarillo
        7 = Blanco
        8 = Gris
        9 = Azul claro
        A = Verde claro
        B = Aguamarina claro
        C = Rojo claro
        D = Purpura claro
        E = Amarillo claro
        F = Blanco brillante
        */
        system ("color 1F" ); // primer digito cambia pantalla, segundo cambia letra.
    while(true){
        system("cls");
        cout<<"********************************\n";
        cout<<"****                        ****\n";
        cout<<"**** Menu de Administración ****\n";
        cout<<"****                        ****\n";
        cout<<"********************************\n";

        cout<<"\n [1] Insertar Cantón.";
        //cout<<"\n [2] Eliminar Cantón.";
        cout<<"\n [3] Imprimir Cantones.\n";

        cout<<"\n [4] Insertar Puesto.";
        //cout<<"\n [5] Eliminar Puesto.";
        cout<<"\n [6] Imprimir Puestos.\n";

        cout<<"\n [7] Insertar Capacitación.";
        //cout<<"\n [8] Eliminar Capacitación.";
        cout<<"\n [9] Imprimir Capacitaciones.\n";

        cout<<"\n[10] Insertar Miembro a Comité.";
        cout<<"\n[11] Eliminar Miembro a Comité.";
        cout<<"\n[12] Imprimir Miembros del Comité.\n";

        cout<<"\n[13] Insertar Programa.";
        //cout<<"\n[14] Eliminar Programa.";
        cout<<"\n[15] Imprimir Programas.\n";

        cout<<"\n[16] Insertar Formación Académica.";
        //cout<<"\n[17] Eliminar Formación Académica.";
        cout<<"\n[18] Imprimir Formación Académica.\n";

        cout<<"\n[19] Insertar Convenio.";
        //cout<<"\n[20] Eliminar Convenio.";
        cout<<"\n[21] Imprimir Convenios.\n";

        cout<<"\n[22] Insertar Infraestructura.";
        cout<<"\n[23] Eliminar Infraestructura.";
        cout<<"\n[24] Imprimir Infraestructuras.\n";

        cout<<"\n[-1] Atras.\n________________________________\n\n>>> ";

        cin>>opcion;

        if(opcion == 1){
            datosCantones();
        }
        else if(opcion == 2){
            // eliminar cantones
        }
        else if(opcion == 3){
                // imprimir Catones
         }
        else if(opcion == 4){
        	datosPuestos();
        }
        else if(opcion == 5){
        	//eliminar un puesto
        }
        else if(opcion == 6){
        	//imprimirPuestos();
		}
		else if(opcion ==7){
            datosCapacitacion();
		}
		else if(opcion ==8){
			// eliminar capacitacion
	    }
		else if(opcion == 9){
            //imprimirCapacitaciones();

        }
        else if(opcion == 10){
        	//
		}
		else if(opcion == 11){
            //eliminar miembro
		}
		else if(opcion == 12){
            //imprimir("miembros");
		}
		else if(opcion == 13){
            //datosProgramas();
		}
		else if(opcion == 14){
            // eliminar programa
		}
		else if(opcion == 15){
            //imprimir("programas");
		}
		else if(opcion == 16){
            datosFormacion();
		}
		else if(opcion == 17){
            // eliminar formacion
		}
		else if(opcion == 18){
            //imprimir("formaciones");
		}
		else if(opcion == 19){
            //datosConvenios();
		}
		else if(opcion == 20){
            //eliminar convenio
		}
		else if(opcion == 21){
            //imprimir("convenios");
		}
		else if(opcion == 22){
            //datosInfraestructura();
		}
		else if(opcion == 23){
            //eliminar infraestructura
		}
		else if(opcion == 24){
            //imprimir("infraestructuras");
		}
		else if(opcion == -1){
            system("cls");
            return ;
		}
    }
}

void menuConsultas(){

}

void menuReportes(){

}

void menu(){//funcion del menu aqui se maneja lo que el usuario desea realizar
    int opcion = 0;
    while(true){
        cout<<"********************************\n";
        cout<<"****                        ****\n";
        cout<<"****          MENU          ****\n";
        cout<<"****                        ****\n";
        cout<<"********************************\n";
        cout<<"\n[1]  Menu de Administración.";
        cout<<"\n[2]  Menu de Consultas.";
        cout<<"\n[3]  Menu de Reportes.\n";
        cout<<"\n[-1] Salir del Programa.\n________________________________\n\n>>> ";
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
    setlocale(LC_CTYPE, "Spanish"); // para que se reconozcan las tildes.
	cargarDatos();
    //menu();
	return 0;
}
