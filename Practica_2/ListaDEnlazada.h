//
// Created by Rafa on 18/10/2022.
//

#ifndef PRACTICA_2_LISTADENLAZADA_H
#define PRACTICA_2_LISTADENLAZADA_H
#include <stdexcept>

template <typename T>
class ListaDEnlazada {
private:
    template <class Y>
            class Nodo {
            public:
                Y dato;
                Nodo *siguiente;
                Nodo *anterior;

                Nodo(Y &_dato, Nodo *_siguiente, Nodo *_anterior): dato(_dato), siguiente(_siguiente), anterior(_anterior){}
                ~Nodo() {}
            };
    Nodo<T>* cabecera;
    Nodo<T>* cola;
    int size;

public:
    class Iterador {
        private:
            Nodo<T>* nodo;
        public:
            Iterador(Nodo<T>* _nodo): nodo(_nodo){}
            ~Iterador() {}
            bool end() {return(nodo == nullptr);}
            void next() {nodo = nodo->siguiente;}
            void previous() {nodo = nodo->anterior;}
            T& dato() {return nodo->dato;}
    };

    ListaDEnlazada<T>();
    ListaDEnlazada<T>(const ListaDEnlazada& orig);
    ~ListaDEnlazada<T>();
    ListaDEnlazada<T>& operator=(const ListaDEnlazada& orig);
    bool operator==(const ListaDEnlazada& orig);

    T& inicio();
    T& fin();

    void insertaInicio(const T& dato);
    void insertaFin( T& dato);
    void inserta(const Iterador &i, const T& dato);

    void borraInicio();
    void borraFinal();
    void borra(const Iterador &i);

    int tam();

    ListaDEnlazada concatena(ListaDEnlazada<T> &l);
    ListaDEnlazada operator+(ListaDEnlazada<T> &l);

    Iterador iterador();
    Iterador busca(T& dato);

    ListaDEnlazada operator*(ListaDEnlazada<T> *l);
};


template <typename T>
ListaDEnlazada<T>::ListaDEnlazada(): cabecera(nullptr), cola(nullptr), size(0) {}

template <typename T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada& orig):size(0){
    Nodo<T>* nodo = orig.cabecera;
    cabecera = nullptr;
    cola = nullptr;
    while(nodo != nullptr){
        insertaFin(nodo->dato);
        nodo = nodo->siguiente;
    }
}

template <typename T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    if(cabecera != nullptr){
        Nodo<T>* nodo = cabecera;
        while(nodo->siguiente != nullptr){
            cabecera = cabecera->siguiente;
            delete nodo;
            nodo = cabecera;
        }
        cola = nullptr;
        cabecera = nullptr;
        size = 0;
    }
}

template <typename T>
ListaDEnlazada<T> &ListaDEnlazada<T>::operator=(const ListaDEnlazada<T> &orig) {
    if(this != &orig) {
        Nodo<T> *nodo = cabecera;
        while (cabecera != nullptr) {
            cabecera = cabecera->siguiente;
            delete nodo;
            nodo = cabecera;
        }

        size = orig.size;
        cabecera = nullptr;
        cola = nullptr;

        //Si la lista está vacía asignamos el primer elemento
        if (cabecera == nullptr) {
            nodo = new Nodo<T>(orig.cabecera->dato, nullptr, nullptr);
            cabecera = nodo;
            cola = nodo;
        }
        Iterador i = orig.cabecera;
        while (!i.end()) {
            nodo = new Nodo<T>(i.dato(), cola, nullptr);
            cola->siguiente = nodo;
            cola = nodo;
            i.next();
        }
    }
    return *this;
}

template <typename T>
T &ListaDEnlazada<T>::inicio() {
    return cabecera->dato;
}

template <typename T>
T &ListaDEnlazada<T>::fin() {
    return cola->dato;
}

template <typename T>
void ListaDEnlazada<T>::insertaInicio(const T &dato){
    Nodo<T>* nuevo;
    if(cola == cabecera ==nullptr){
        nuevo = new Nodo<T>(dato, nullptr, nullptr);
        cola = cabecera = nuevo;
    }else{
        nuevo = new Nodo<T>(dato, nullptr,cabecera);
        cabecera = nuevo;
        nuevo->siguiente->anterior = nuevo;
    }
    size++;
}

template <typename T>
void ListaDEnlazada<T>::insertaFin( T &dato) {
    Nodo<T>* nuevo;
    if(cabecera == cola && cola == nullptr){
        nuevo = new Nodo<T>(dato, nullptr, nullptr);
        cola = cabecera = nuevo;
    }else{
        nuevo = new Nodo<T>(dato, nullptr, cola);
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    size++;
}

template <typename T>
void ListaDEnlazada<T>::inserta(const ListaDEnlazada::Iterador &i, const T &dato) {
    if(i.nodo == nullptr)
        throw std::invalid_argument("ListaDEnlazada::inserta: Iterador incorrecto");
    if(cabecera == cola == nullptr)
        insertaInicio(dato);
    if(i.nodo == cabecera)
        insertaInicio(dato);
    if(i.nodo == cola)
        insertaFin(dato);
    if(cabecera == cola)
        insertaInicio(dato);
    Nodo<T>* nuevo;
    nuevo = new Nodo<T>(dato,i.previous(),i);
    i.nodo->anterior->siguiente = nuevo;
    i.nodo->anterior = nuevo;
    size++;
}

template <typename T>
void ListaDEnlazada<T>::borraInicio() {
    if(cabecera == cola == nullptr)
        throw std::invalid_argument("ListaDEnlazada::borraInicio: La lista esta vacia");
    if(cabecera == cola){
        delete cabecera;
        cabecera = cola = nullptr;
    }else{
        cabecera = cabecera->siguiente;
        delete cabecera->anterior;
        cabecera->anterior = nullptr;
    }
    size--;
}

template <typename T>
void ListaDEnlazada<T>::borraFinal() {
    if(cabecera == cola == nullptr)
        throw std::invalid_argument("ListaDEnlazada::borraFinal: La lista esta vacia");
    if(cabecera == cola){
        delete cola;
        cabecera = cola =nullptr;
    }else{
        cola = cola->anterior;
        delete cola->siguiente;
        cola->siguiente = nullptr;
    }
    size--;
}

template <typename T>
void ListaDEnlazada<T>::borra(const ListaDEnlazada::Iterador &i) {
    if(i.nodo == nullptr)
        throw std::invalid_argument("ListaDEnlazada::borraFinal: Iterador incorrecto");
    if(cabecera == cola == nullptr)
        throw std::invalid_argument("ListaDEnlazada::borraFinal: La lista esta vacia");
    if(i.nodo == cola)
        borraFinal();
    if(i.nodo == cabecera)
        borraInicio();
    if(cabecera == cola){
        delete cola;
        cabecera = cola =nullptr;
    }else{
        i.nodo->siguiente->anterior = i.nodo->anterior;
        i.nodo->anterior->siguiente = i.nodo->siguiente;
        delete i.nodo;
    }
    size--;
}

template <typename T>
int ListaDEnlazada<T>::tam() {
    return size;
}

template <typename T>
ListaDEnlazada<T> ListaDEnlazada<T>::concatena( ListaDEnlazada<T> &l) {
    if(l.cabecera == l.cola && l.cola == nullptr)
        return *this;
    if(cabecera == cola && cola == nullptr)
        return l;

    ListaDEnlazada<T>* salida;
    salida = new ListaDEnlazada<T>(*this);
    Iterador i = l.iterador();
    while(!i.end()){
        salida->insertaFin(i.dato());
        i.next();
    }
    return *salida;
}

template <typename T>
typename ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::iterador() {
    return Iterador(cabecera);
}

template <typename T>
typename ListaDEnlazada<T>::Iterador ListaDEnlazada<T>::busca(T &dato) {
    Iterador i = iterador();
    while(!i.end()){
        if(i.dato() == dato)
            return i;
        i.next();
    }
    return iterador();
}

template <typename T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator+( ListaDEnlazada<T> &l) {
    return this->concatena(l);
}

template <typename T>
bool ListaDEnlazada<T>::operator==(const ListaDEnlazada<T> &orig) {
    Iterador iterador = this->iterador();
    Iterador iterador2(orig.cabecera);
    for(int i = 0; i < iterador.end(); i++){
        if(!(iterador.dato() == iterador2.dato()))
            return false;
        iterador.next();
        iterador2.next();
    }
    return true;
}

template <typename T>
ListaDEnlazada<T> ListaDEnlazada<T>::operator*(ListaDEnlazada<T> *l) {
    return *l;
}
#endif //PRACTICA_2_LISTADENLAZADA_H
