#ifndef LISTA_H
#define LISTA_H
#include <string>

using namespace std;

struct Datos
{
    int idRep;
    string fecha;
    string descripcion;
    int coste;
};

class NodoL {
 private:
        Datos reparacion;
        NodoL *siguiente;
        friend class Lista;
    public:
        NodoL(Datos rep, NodoL *sig = NULL);
        void updateId(int idRep);
        int getId();
        string getFecha(int idRep);
        string getDescripcion(int idRep);
        int getCoste(int idRep);
};
typedef NodoL *pNodoL;


class Lista
{
    private:
        pNodoL cabeza, finall;
        pNodoL actual;
    public:
        Lista(){cabeza = actual = NULL;}
        ~Lista();
        void insertarNodo(Datos reparacion);
        Datos borrarNodo(int idRep);
        bool listaVacia();
        void mostrarLista();
        void esSiguiente();
        void esPrimero();
        void esUltimo();
        void esFinal();
        bool esActual();
        int getLastId();
};

Datos rellenarReparacion(int idRep);


#endif // LISTA_H
