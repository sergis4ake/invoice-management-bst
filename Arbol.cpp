#include "Arbol.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

void Arbol::podar(pNodoA &nodoA)
{
    if(nodoA) {
        podar(nodoA->izquierda); // Podar izquierdo
        podar(nodoA->derecha);   // Podar derecho
        delete nodoA;            // Eliminar nodo
        nodoA = NULL;
    }
}

bool Arbol::buscarNodo (int dni)
{
    actual = raiz;

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni) return true;
        else
            if(dni > actual->ficha.dni) actual = actual->derecha;
            else if(dni < actual->ficha.dni) actual = actual->izquierda;
    }
    return false;
}


void Arbol::insertarNodo (Ficha f)
{
    NodoA *padre = NULL;

    if (Vacio(raiz))
    {
        raiz = new NodoA(f);
    }else{
        actual = raiz;
        padre = actual;
        while(!Vacio(actual))
        {
            padre = actual;
            if(f.dni > actual->ficha.dni) actual = actual->derecha;
            else if(f.dni <= actual->ficha.dni) actual = actual->izquierda;
        }
        if(f.dni <= padre->ficha.dni) padre->izquierda = new NodoA(f);
        else if(f.dni > padre->ficha.dni) padre->derecha = new NodoA(f);
    }
}

void Arbol::borrarNodo (int dni)
{
    NodoA *padre = NULL;
    NodoA *nodo;
    Ficha aux;
    actual = raiz;

    // Borrar el nodo raíz en caso de ser el unico nodo del arbol y coincide con el DNI.
    if(esHoja(raiz) && raiz->ficha.dni == dni)
    {
        raiz = NULL;
        return;
    }

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni) {
            if(esHoja(actual)){
                if(padre->derecha == actual) padre->derecha = NULL;
                else if(padre->izquierda == actual) padre->izquierda = NULL;
                delete actual; // Borrar el nodo
                actual = NULL;
                return;
            }
            else
            {
                padre = actual;
                if(actual->derecha)
                {
                    nodo = actual->derecha;
                    while(nodo->izquierda) {
                        padre = nodo;
                        nodo = nodo->izquierda;
                    }
                }
                else
                {
                    nodo = actual->izquierda;
                    while(nodo->derecha) {
                        padre = nodo;
                        nodo = nodo->derecha;
                    }
                }
                aux = actual->ficha;
                actual->ficha = nodo->ficha;
                nodo->ficha = aux;
                actual = nodo;
            }
        }
        else
        {
            padre = actual;
            if(dni > actual->ficha.dni) actual = actual->derecha;
            else if(dni < actual->ficha.dni) actual = actual->izquierda;
        }
    }
}


void Arbol::preOrden (NodoA *nodoA)
{
    if (nodoA!= NULL)
    {
        cout << nodoA->ficha.dni <<" ";
        if(nodoA->izquierda) preOrden (nodoA->izquierda);
        if(nodoA->derecha)   preOrden (nodoA->derecha);
    }
}


void Arbol::postOrden (NodoA *nodoA)
{
    if (nodoA!= NULL)
    {
        if(nodoA->izquierda) postOrden (nodoA->izquierda);
        if(nodoA->derecha)   postOrden (nodoA->derecha);
        cout << nodoA->ficha.dni <<" ";
    }
}


void Arbol::inOrden(NodoA *nodoA)
{
    if (nodoA!= NULL)
    {
        if(nodoA->izquierda) inOrden(nodoA->izquierda);
        cout << nodoA -> ficha.dni <<" ";
        if(nodoA->derecha)   inOrden(nodoA->derecha);
    }
}

// Rellenar el arbol aleatoriamente y mostrarlo en inOrden.
void Arbol::rellenarInOrden()
{
    cont = 0;
    // Si el arbol esta vacío, cogemos el <num_histo> desde cero, sino seguiremos
    // la numeración a partir del ultimo <num_histo> del arbol.
    // (Al rellenar parcialmente la ficha e introducirla en el arbol, el ID o num_histo es -1)
    if (raiz->ficha.num_histo != -1){
        cont = getLastIdFicha();
    }
    // Funcion recursiva para rellenar el arbol.
    rellenarInOrdenAux(raiz);
}

//Funcion auxiliar para rellenar el arbol aleatoriamente y mostrarlo en inOrden.
void Arbol::rellenarInOrdenAux(NodoA *nodoA)
{
    int rnd, i;

    if (nodoA!= NULL)
    {
        rnd = rand()%3;
        nodoA->ficha.nomyape = nombres[rnd];
        nodoA->ficha.num_histo = cont ++;

        // Rellenamos las 3 reparaciones tipo struct y las insertamos en la lista.
        for(i=0;i<3;i++)
        {
            //reparacion = rellenarReparacion(i);
            //lista.insertarNodo(reparacion);

            // Insertamos cada reparacion struct rellenada directamente en la lista de la ficha del nodo del arbol.
            nodoA->ficha.reparaciones.insertarNodo(rellenarReparacion(i));
        }
        // Insertamos la lista en la ficha del nodo del arbol actual.
        //nodo->ficha.reparaciones = lista;

        // Recorremos los nodos del arbol en inOrden.
        if(nodoA->izquierda) rellenarInOrdenAux(nodoA->izquierda);
        // Mostramos la ficha del nodo actual y sus reparaciones.
        mostrarFicha(nodoA->ficha.dni);
        if(nodoA->derecha) rellenarInOrdenAux(nodoA->derecha);
    }
}

// Contar el número de nodos
int Arbol::numeroNodos()
{
    contador = 0;       // Variable global.
    auxContador(raiz);  // Función recurrente.
    return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void Arbol::auxContador(NodoA *nodoA)
{
    contador++;  // Otro nodo
    // Continuar recorrido
    if(nodoA->izquierda) auxContador(nodoA->izquierda);
    if(nodoA->derecha)   auxContador(nodoA->derecha);
}

// Función que inserta una reparación como elemento de la lista,
// que esta dentro de una ficha y a su vez en un nodo del arbol.
int Arbol::insertarReparacion(int dni, Datos rep)
{
    actual = raiz;

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni){
            actual->ficha.reparaciones.insertarNodo(rep);
            return 0;
        }
        else if(dni > actual->ficha.dni) actual = actual->derecha;
        else if(dni < actual->ficha.dni) actual = actual->izquierda;
    }
    return -1;
}

// Muestra las reparaciones de una ficha según su DNI.
void Arbol::mostrarReparaciones(int dni)
{
    actual = raiz;

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni){
            if(!actual->ficha.reparaciones.listaVacia())
                actual->ficha.reparaciones.mostrarLista();
            else
                cout << "[ERROR] - El cliente con DNI " << actual->ficha.dni << " no tiene historial de reparaciones." << endl;
            return;
        }
        else if(dni > actual->ficha.dni) actual = actual->derecha;
        else if(dni < actual->ficha.dni) actual = actual->izquierda;
    }
}

// Muestra el contenido de una ficha y sus reparaciones en función del DNI.
int Arbol::mostrarFicha(int dni)
{
    actual = raiz;

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni){
            cout<<"$ Nombre y Apellidos: "<<actual->ficha.nomyape<<"\n  DNI: "<<actual->ficha.dni<<"\n  Numero de historial: "<<actual->ficha.num_histo<<endl;
            if(actual->ficha.reparaciones.listaVacia())
                return -1;
            else
                actual->ficha.reparaciones.mostrarLista();
            return 0;
        }
        else if(dni > actual->ficha.dni) actual = actual->derecha;
        else if(dni < actual->ficha.dni) actual = actual->izquierda;
    }
    return -1;
}

// Funcion para conseguir el último ID de la ultima reparacion añadida de una ficha
// de un cliente según su DNI.
int Arbol::getLastIdReparaciones(int dni)
{
    int id = 0;
    actual = raiz;

    while(!Vacio(actual))
    {
        if(dni == actual->ficha.dni){
            if(!actual->ficha.reparaciones.listaVacia())
                id = actual->ficha.reparaciones.getLastId() + 1;
            return id;
        }
        else if(dni > actual->ficha.dni) actual = actual->derecha;
        else if(dni < actual->ficha.dni) actual = actual->izquierda;
    }

    return -1;
}

/**------------------------------------------------
** CONSEGUIR EL ULTIMO NUM_HISTO DE TODO EL ARBOL **
---------------------------------------------------*/
// Función para conseguir el mayor <num_histo> del arbol, para seguir la numeración.
int Arbol::getLastIdFicha()
{
    mayor = 0;
    getLastIdFichaAux(raiz);
    return mayor;
}
// Función auxiliar que recorre el arbol y guarda el mayor.
void Arbol::getLastIdFichaAux(NodoA *nodoA)
{
    if (nodoA!= NULL)
    {
        if(mayor < nodoA->ficha.num_histo)
            mayor = nodoA->ficha.num_histo;

        // Recorremos los nodos del arbol en inOrden.
        if(nodoA->izquierda) getLastIdFichaAux(nodoA->izquierda);
        if(nodoA->derecha) getLastIdFichaAux(nodoA->derecha);
    }
}

/**---------------------------------------------------------
** MOSTRAR TODAS LAS FICHAS (inOrden, postOrden, preOrden) **
------------------------------------------------------------*/
void Arbol::mostrarTodasFichas(int opcion)
{
    cout << "--------------------------------------" << endl;
    switch(opcion)
    {
        case 1:
            cout << "------------| Pre Orden |-------------"<<endl;
            cout << "--------------------------------------\n" << endl;
            mostrarTodasFichasPreOrden(raiz);
            break;
        case 2:
            cout << "------------| In Orden |--------------"<<endl;
            cout << "--------------------------------------\n" << endl;
            mostrarTodasFichasInOrden(raiz);
            break;
        case 3:
            cout << "------------| Post Orden |------------"<<endl;
            cout << "--------------------------------------\n" << endl;
            mostrarTodasFichasPostOrden(raiz);
            break;
        default:
            cout << "[ERROR] - Debes elegir las opciones preOrden/inOrden/postOrden." << endl;
    }
}

void Arbol::mostrarTodasFichasPreOrden(NodoA *nodoA)
{
    if(nodoA!=NULL)
    {
        cout<<"$ Nombre y Apellidos: "<<nodoA->ficha.nomyape<<"\n  DNI: "<<nodoA->ficha.dni<<"\n  Numero de historial: "<<nodoA->ficha.num_histo<<endl;
        if(nodoA->ficha.reparaciones.listaVacia())
            cout << "   No existen reparaciones registradas para este cliente." << endl;
        else
            nodoA->ficha.reparaciones.mostrarLista();

        if(nodoA->izquierda) mostrarTodasFichasPreOrden(nodoA->izquierda);
        if(nodoA->derecha) mostrarTodasFichasPreOrden(nodoA->derecha);
    }
}

void Arbol::mostrarTodasFichasInOrden(NodoA *nodoA)
{
    if(nodoA!=NULL)
    {
        if(nodoA->izquierda) mostrarTodasFichasInOrden(nodoA->izquierda);

        cout<<"$ Nombre y Apellidos: "<<nodoA->ficha.nomyape<<"\n  DNI: "<<nodoA->ficha.dni<<"\n  Numero de historial: "<<nodoA->ficha.num_histo<<endl;
        if(nodoA->ficha.reparaciones.listaVacia())
            cout << "   No existen reparaciones registradas para este cliente." << endl;
        else
            nodoA->ficha.reparaciones.mostrarLista();

        if(nodoA->derecha) mostrarTodasFichasInOrden(nodoA->derecha);
    }
}


void Arbol::mostrarTodasFichasPostOrden(NodoA *nodoA)
{
    if(nodoA!=NULL)
    {
        if(nodoA->izquierda) mostrarTodasFichasPostOrden(nodoA->izquierda);
        if(nodoA->derecha) mostrarTodasFichasPostOrden(nodoA->derecha);

        cout<<"$ Nombre y Apellidos: "<<nodoA->ficha.nomyape<<"\n  DNI: "<<nodoA->ficha.dni<<"\n  Numero de historial: "<<nodoA->ficha.num_histo<<endl;
        if(nodoA->ficha.reparaciones.listaVacia())
            cout << "   No existen reparaciones registradas para este cliente." << endl;
        else
            nodoA->ficha.reparaciones.mostrarLista();
    }
}
