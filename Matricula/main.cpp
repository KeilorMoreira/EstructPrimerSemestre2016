#include <iostream>
#include <stdlib.h>
#include <cstring>


using namespace std;
////Estructura Curso
struct Curso{
    string nombre;
    int creditos;
    string sigla;
    struct Curso *sig;
}*primeroC;//variable global para almacenar el primero de la lista Circular Curso
////Estructura Matricula
struct Matricula{
    struct Curso *enlace;//enlace hacia el curso a matricular
    struct Matricula *sig;
    Matricula(){
    	enlace = NULL;
    	sig = NULL;
	}
};

////Estructura Estudiante
struct Estudiante{
    int carne;
    string nombre;
    int edad;
    string direccion;
    string carrera;
    struct Estudiante *sig, *ant;//lista doble
    struct Matricula *matri;
}*primeroE;// variable global para almacenar el primero de la lista ordenada doblemente enlazada de Estudiantes

////////////////////////////METODOS//////////////////////////////////

//Funcion que busca un estudiante por numero de carne,
//retorna el nodo buscado.
//sino lo encuentra retorna NULL

struct Estudiante *buscarE(int carne){

struct Estudiante *tempE =primeroE;
if(tempE==NULL)
      return NULL;
      do {
          if(tempE->carne==carne)
              return tempE;
          tempE = tempE->sig;
      } while( tempE!=NULL);

return NULL;
}

//Funcion que busca un curso por su sigla,
//retorna el nodo buscado.
//sino lo encuentra retorna NULL
struct Curso * buscarC(string sigla)
{
struct Curso *tempC =primeroC;
if(tempC==NULL)
      return NULL;
do {
    if(tempC->sigla==sigla)
        return tempC;
    tempC = tempC->sig;
    }
while( tempC!=primeroC);
return NULL;
}

//Inserción al inicio de una lista circular
//Retorna la lista modificada con la nueva insercción

struct Curso * insertarCurso(struct Curso *lista, string sigla, string nombre, int cred){
      struct Curso * nn= new Curso(); //se crea el nuevo nodo
      nn->sigla = sigla; //se le asignan la informacion con los parametros recibidos
      nn->nombre= nombre;
      nn->creditos = cred;

            if(lista ==NULL)
                nn->sig=nn;

            else  //if(lista !=NULL)
            {
                struct Curso *temp =lista;
                do {
                      temp = temp->sig;
                    } while( temp->sig!=lista);

                temp->sig = nn;
                nn->sig=lista;
            }
            lista =nn;// se modifica el primero de la lista para que apunte al nodo más reciente
            return lista;
}


//Inserción ordenada de una lista doble
//Modifica la lista global de estudiantes

void insertarOrdenado(int num, string nombre, int edad, string direccion, string carrera){
    struct Estudiante* nn= new Estudiante();//se crea el nuevo nodo
    nn->carne= num;//se le asignan la informacion con los parametros recibidos
    nn->nombre= nombre;
    nn->edad= edad;
    nn->direccion= direccion;
    nn->carrera= carrera;
    nn->sig= NULL;
    nn->ant= NULL;


    if(primeroE==NULL)//si la lista esta vacia
        primeroE=nn;
    else {
        struct Estudiante * actual=primeroE;
        struct Estudiante * ant=NULL;
        while((actual !=NULL)&&(num >actual->carne)){
                    ant=actual;
                    actual =actual->sig;
          }
        if(actual ==NULL)//se inserta al final de la lista
        {
            ant->sig=nn;
            nn->ant=ant;
        }
        else if(ant==NULL)//se inserta al inicio de la lista
        {
            nn->sig=primeroE;
            primeroE->ant=nn;
            primeroE=nn;
        }
        else{//insertar en medio
            ant->sig=nn;
            actual->ant=nn;
            nn->sig=actual;
            nn->ant=ant;
        }

    }
}

//Inserción al inicio de la sublista matricula
//Se busca el estudiante y el curso respectivo
//se hacen los enlaces correspondientes para registrar una matricula

void insertarMatricula(int carne, string sigla){

    struct Estudiante *tempE= buscarE(carne);//ya visto en clase
    struct Curso *tempC =buscarC(sigla);//ya visto en clase

    if((tempE!=NULL)&&(tempC!=NULL))
    {
        struct Matricula *nn= new Matricula();
        nn->enlace=tempC;//se enlaza con el curso a matricular
        nn->sig= tempE->matri;//se enlaza con la sublista ya existente del estudiante
        tempE->matri=nn;// el nn pasa a ser el primer nodo de la sublista matricula
    }
}


//Imprime el informe de matricula de un estudiante X
void matriculaEstX(int carne)
{
struct Estudiante *tempE=buscarE(carne);//busca el estudiante respectivo
      if(tempE!=NULL){
                      //se imprime la informacion del estudiante respectivo
          cout<< "\n          Estudiante:    "<<tempE->nombre << "\n\n\n Su matricula es: \n\n";
          struct Matricula *tempM = tempE->matri;
          while(tempM!=NULL)//se recorre la sublista de matricula del estudiante buscado
            {
                cout<<tempM->enlace->sigla <<"  " <<tempM->enlace->nombre <<"\n";
                tempM=tempM->sig;
            }
          cout<<"-------------------Ultima linea-------------------\n\n";
        }
}

////////////////////////////////MAIN///////////////////////////////////


int main()
{
    ///////////////////Inserción de Estudiantes////////////////////////////
    insertarOrdenado(20101010, "Ana", 20, "Santa Clara","CA");
    insertarOrdenado(20101011, "Beto", 21, "Santa Rita","CA");
    insertarOrdenado(20101012, "Carlos", 20, "Cuidad Quesada","CA");
    insertarOrdenado(20121013, "Daniel", 19, "San Carlos","CA");
    insertarOrdenado(20091014, "Laura", 18, "Fortuna","CA");
    insertarOrdenado(20081015, "Maria", 22, "Venecia","CA");

    ///////////////////Inserción de Cursos ////////////////////////////
    primeroC= insertar(primeroC, "IC2001","OCLE",4);
    primeroC= insertar(primeroC, "IC2101","Datos",4);
    primeroC= insertar(primeroC, "IC2011","POO",3);
    primeroC= insertar(primeroC, "IC1801","Taller",3);
    primeroC= insertar(primeroC, "IC1802","Intro",3);

    ///////////////////Inserción de Matriculas ////////////////////////////
    insertarMatricula(20101011, "IC2001");
    insertarMatricula(20091014, "IC2001");
    insertarMatricula(20101011, "IC1801");
    insertarMatricula(20101011, "IC1802");

    ///////////////////Imprimir informes de matricula////////////////////////
    matriculaEstX(20101011);
    matriculaEstX(20091014);

    system("PAUSE");
    return EXIT_SUCCESS;
}

