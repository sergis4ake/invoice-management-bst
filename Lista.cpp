#include "Lista.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

Lista::~Lista()
{
    pNodoL aux;
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    actual = NULL;
}

void Lista::insertarNodo(Datos reparacion)
{
    pNodoL aux;
    if(listaVacia())
    {
        cabeza = new NodoL(reparacion);
        finall = cabeza;
    }
    else
    {
        aux = new NodoL(reparacion);
        finall->siguiente=aux;
        finall=aux;
    }
}

Datos Lista::borrarNodo(int idRep)   // Borrar nodo y guardar los datos del nodo que vamos a borrar en un struct auxiliar,
{                                    // que será lo que devuelva la función. //
    pNodoL anterior = NULL;
    actual = cabeza;
    Datos reparacionAux;
    pNodoL aux = NULL;

    while ((aux->siguiente!=NULL) && (actual->reparacion.idRep!=idRep)){
        anterior=actual;
        actual=actual->siguiente;
    }
    if(actual==cabeza) // Primer elemento
        cabeza = actual->siguiente;
    else{
        anterior->siguiente = actual->siguiente;
        if (actual==finall){
            finall=anterior;
        }
    }
    reparacionAux = actual->reparacion;  // Guardo los datos del nodo//
    actual->siguiente=NULL;
    delete actual;                  // Borrar el nodo //
    return reparacionAux;           // La funcion devuelve los datos del nodo borrado //
}

bool Lista::listaVacia()
{
    return cabeza == NULL;
}


Datos rellenarReparacion(int idRep)
{
    Datos reparacion = {0," "," ",0};
    int rnd = 0, rnd2;
    string fecha = "16/11/2012";

    rnd = rand()%3;
    rnd2 = rand()%3;

    string descripcion[3] = { "Cambio de aceite.", "Revision completa.", "Cambio de filtros."};
    int coste [3] = {60, 120, 80};

    reparacion = {idRep, fecha, descripcion[rnd], coste[rnd2]};
    return reparacion;
}

void Lista::mostrarLista()
{
    NodoL *aux;
    aux = cabeza;
    while(aux)
    {
        cout<<"\t- Reparacion "<<aux->reparacion.idRep<<"\n\t    Fecha: "<<aux->reparacion.fecha<<"\n\t    Descripcion: "<<aux->reparacion.descripcion<<"\n\t    Coste: "<<aux->reparacion.coste<< endl;
        aux = aux->siguiente;
    }
    cout<< endl;
}

int Lista::getLastId()
{
    NodoL *aux;
    aux = cabeza;
    int mayor = 0;
    while(aux)
    {
        if(mayor < aux->getId())
            mayor = aux->getId();

        aux = aux->siguiente;
    }
    return mayor;
}

void Lista::esSiguiente()
{
    if(actual) actual=actual->siguiente;
}

void Lista::esPrimero()
{
    actual=cabeza;
}


void Lista::esFinal()
{
    esPrimero();
    if(!listaVacia())
    while(actual->siguiente)
    esSiguiente();
}


bool Lista::esActual()
{
    return actual !=NULL;
}


/**** FUNCIONES DEL NODO *****/

NodoL::NodoL(Datos rep, NodoL *sig)
{
    reparacion = rep;
    siguiente = sig;
}

string NodoL::getFecha(int idRep)
{
    return reparacion.fecha;
}

string NodoL::getDescripcion(int idRep)
{
    return reparacion.descripcion;
}

int NodoL::getCoste(int idRep)
{
    return reparacion.coste;
}

void NodoL::updateId(int idRep)
{
    reparacion.idRep = idRep;
}

int NodoL::getId()
{
    return reparacion.idRep;
}
