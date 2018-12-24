#ifndef ARBOL_H
#define ARBOL_H
#include <Lista.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
using namespace std;

struct Ficha{     // estructura que almacena los atributos de la persona.
  int num_histo;
  string nomyape;
  int dni;
  Lista reparaciones;
};


class NodoA
{
    private:
        Ficha ficha;
        NodoA *izquierda;
        NodoA *derecha;
        friend class Arbol;

    public:
        NodoA (Ficha f, NodoA *izq=NULL, NodoA * der=NULL)
        {
            ficha = f;
            izquierda = izq;
            derecha = der;
        }
};
typedef NodoA *pNodoA;


class Arbol
{
    private:
        pNodoA actual = NULL;
        void auxContador(pNodoA nodo);
        void auxAltura(pNodoA nodo, int a);

        // Constantes y variables globales
        int cont, mayor;
        int contador, altura;
        string nombres [3] = { "Ivan Java", "Alvaro Pyzzon", "Sergio C++"};

    public:
        pNodoA raiz;
        Arbol() : raiz(NULL), actual(NULL) {}
        ~Arbol() { podar(raiz); }
        bool buscarNodo (int dni);
        void insertarNodo (Ficha f);
        void borrarNodo (int dni);
        bool Vacio(NodoA *r) { return r==NULL; }
        bool esHoja(pNodoA nodoA) { return !nodoA->derecha && !nodoA->izquierda; }
        int numeroNodos();
        int getAlturaArbol();
        void esRaiz() { actual = raiz; }
        void podar(pNodoA &nodoA);

        void inOrden(NodoA *nodoA);
        void preOrden(NodoA *nodoA);
        void postOrden(NodoA *nodoA);

        void rellenarInOrden();
        void rellenarInOrdenAux(NodoA *nodoA);

        int insertarReparacion(int dni, Datos rep);
        void mostrarReparaciones(int dni);
        int mostrarFicha(int dni);
        int getLastIdReparaciones(int dni);

        int getLastIdFicha();
        void getLastIdFichaAux(NodoA *nodoA);

        void mostrarTodasFichas(int opcion);
        void mostrarTodasFichasPostOrden(NodoA *nodoA);
        void mostrarTodasFichasInOrden(NodoA *nodoA);
        void mostrarTodasFichasPreOrden(NodoA *nodoA);
};

//Ficha rellenarFicha(int i, Lista lista);
void crear_ficha(int id, Arbol &arb);
void nueva_reparacion(Arbol &arb);
void buscar_ficha(Arbol &arb);
void borrar_ficha(Arbol &arb);
void crear_aleatorio(Arbol &arb);
void mostrar_fichas(Arbol &arb);

#endif // ARBOL_H
