#include <iostream>

using namespace std;

//estructura autor

struct autor{
    string libro;
    string nacionalidad;
    struct autor *sig;
    struct susLibros *primeroSusLibros;
}*primeroA;

//esgtructura libro
struct libro{
    string titulo;
    string anno;
    struct libro *sig;
    struct editorial *subEditorial; // Relacion con la editorial
    struct susAutores *primeroSusAutores;
}*primeroL;


// estructura editorial
struct editorial{
    string nombre;
    string pais;
    struct editorial *sig;
}*primeroE;

//estrutura para relacionar el autro con sus libros

struct susLibros{
    struct susLibros *sig;
    struct susLibros *enlaceL;
}; // Noo tiene primero

//estructura para relacionar el libro con sus autroes

struct susAutores{
    struct susAutores *sig;
    struct susAutores *enlaceA;
}; // Noo tiene primero

// Insertar

void insertarAutor(string lib, string nac){
    struct autor *nn = new autor();
    nn->libro = lib;
    nn->nacionalidad = nac;


    nn->sig= primeroA;
    primeroA = nn;

}

void insertarLibro(string tit, string an){
    struct libro *nn = new libro();
    nn->titulo = tit;
    nn->anno = an;


    nn->sig= primeroL;
    primeroL = nn;

}

void insertarEditorial(string nom, string p){
    struct editorial *nn = new editorial();
    nn->nombre = nom;
    nn->pais = p;


    nn->sig= primeroE;
    primeroE = nn;

}

// buscar

struct autor* buscarL(string lib){
    struct autor *temp = primeroA;
    while(temp!=NULL){
        if(temp->libro==lib)
            return temp;
        temp = temp->sig;
    }
    return NULL;
}

struct libro* buscarT(string tit){
    struct libro *temp = primeroL;
    while(temp!=NULL){
        if(temp->titulo==tit)
            return temp;
        temp = temp->sig;
    }
    return NULL;
}

struct editorial* buscarE(string nom){
    struct editorial *temp = primeroE;
    while(temp!=NULL){
        if(temp->nombre==nom)
            return temp;
        temp = temp->sig;
    }
    return NULL;
}

// por parametro t = titulo del libro
void insertarLibroAutor(string t, string a){
    struct libro *buscadoL = buscarL(t);
    struct autor *buscadoA = buscarA(a);

    if(buscadoL == NULL){
        cout<<"El libro no esta en la lista";
        return;

    }
    if(buscadoA == NULL){
        cout<<"Autor no en lista";
        return;
    }

    struct susAutores *nn = new susAutores();
    nn->enlaceA = buscadoA;

    nn->sig = buscadoL->primeroSusAutores;
    buscadoL->primeroSusAutores= nn;
}






void cargarDatos(){
    insertarAutor("Miguel Cervantes", "Espanol")
    insertarAutor("Navarro", "Colombiano")

    insertarLibro("Quijote", "2000")
    insertarLibro("Quijote", "2000")

    insertarEditorial("Espanna", "Espana")

    insertarLibroAutor("Quijote","Miguel Cervantes");


}



int main()
{
    primeroA = NULL;
    primeroE = NULL;
    primeroL = NULL;
}
