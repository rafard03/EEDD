//
// Created by Rafa on 02/11/2022.
//

#ifndef PRACTICA_2_AVL_H
#define PRACTICA_2_AVL_H
#include "VDinamico.h"

template <typename T> class Avl {
private:

///////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename U>
        class Nodo {
        public:
            Nodo *left;
            Nodo *right;
            U data;
            char bal;
            Nodo(U &ele): left(nullptr), right(nullptr), bal(0), data(ele) {}
            Nodo(Nodo<U> &orig): bal(orig.bal), data(orig.data) {left = new Nodo<U>*(orig.left); right = new Nodo<U>*(orig.right);}
            ~Nodo() {}
        };

////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Nodo<T> *root;
    int numElementos = 0;
    int inserta(Nodo<T>* &c, T &_data);
    void rotRight(Nodo<T>* &p);
    void rotLeft(Nodo<T>* &p);

    void inorden(Nodo<T> *p, VDinamico<T*> &vdin);
    Nodo<T>* buscaClave (T& data, Nodo<T>* p);
    void copy(Nodo<T> * root, Nodo<T>* p);
    int altura(Nodo<T>* p);
    void destruir(Nodo<T> *p);


public:
    Avl() : root(nullptr), numElementos(0) {};
    bool inserta(T& _data);
    Avl<T>(const Avl<T>& orig);
    Avl& operator=(Avl<T>* orig);
    T* buscaRec(T& dato);
    T* buscaIt(T& dato);


    VDinamico<T*> recorreInorden();

    int getNumElementos(){return numElementos;}
    int altura();
    int altura2();
    ~Avl() ;

};

/**
 * @brief Inserta
 * @tparam T
 * @param c [in] puntero al nodo en el cual se va a insertar el dato
 * @param data [in] dato que se va a insertar
 * @post busca el lugar indicado para insertar el dato
 * @pre la clase del dato debe tener el operador >
 * @return
 */
template<typename T>
int Avl<T>::inserta(Nodo<T>* &c, T &data){
    Nodo<T> *p = c;
    int deltaH = 0;
    if (!p){
        p = new Nodo<T>(data);
        c = p;
        deltaH=1;
        numElementos++;
    }
    else if (data > p->data){
        if (inserta(p->right, data)){
            p->bal--;
            if (p->bal == -1) deltaH=1;
            else if (p->bal == -2) {
                if (p->right->bal == 1) rotRight(p->right);
                rotLeft(c);
            }
        }
    }
    else if (data < p->data){
        if (inserta(p->left, data)){
            p->bal++;
            if (p->bal == 1) deltaH = 1;
            else if (p->bal == 2){
                if (p->left->bal == -1) rotLeft(p->left);
                rotRight(c);
            }
        }
    }

    return deltaH;
}

/**
 * @brief rotar a la izquierda
 * @param p [in] puntero inicial
 */
template<typename T>
void Avl<T>::rotLeft(Nodo<T>* &p){
    Nodo<T> *q = p, *r;
    p = r = q->right;
    q->right = r->left;
    r->left = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if(q->bal > 0) r->bal += q->bal;

}

/**
 * @brief rotar a la derecha
 * @param p [in] puntero inicial
 */
template<typename T>
void Avl<T>::rotRight(Nodo<T>* &p){
    Nodo<T> *q = p, *l;
    p = l = q->left;
    q->left = l->right;
    l->right = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if(q->bal < 0) l->bal -= -q->bal;

}

/**
 * @brief inorden
 * @tparam T
 * @param p
 * @post recorre los nodos de manera inordern
 * @param nivel
 */
template <typename T>
void Avl<T>::inorden (Nodo<T> *p, VDinamico<T*> &vector){
    if (p){
        inorden (p->left, vector);
        vector.inserta(&(p->data));
        inorden (p->right, vector);
    }
}

/**
 * @brief buscaClave
 * @tparam T
 * @param data [in] dato del tipo T
 * @param p [in] puntero
 * @post busca el dato
 * @return
 */
template <typename T>
typename Avl<T>::template Nodo<T>* Avl<T>::buscaClave(T &data, Nodo<T> *p) {
    if(!p)
        return 0;
    else if(data < p->data)
        return buscaClave(data, p->left);
    else if(data > p->data)
        return buscaClave(data, p->right);
    else return p;
}



/**
 * @brief busqueda recursiva
 * @tparam T
 * @param dato [in] dato a buscar
 * @return nullptr si no se ha encontrado o el dato buscado
 */
template <typename T>
T* Avl<T>::buscaRec(T &dato) {
    Nodo<T> *r = buscaClave(dato, root);
    if(r)
        return &(r->data);
    else return nullptr;
}

/**
 * @brief operador =
 * @tparam T
 * @param orig [in] arbol a copiar
 * @post sobrecarga del operador igual para poder "copiar" un arbol
 * @return
 */
template <typename T>
Avl<T> &Avl<T>::operator=(Avl<T> *orig) {
    if(this != &orig){
        root = orig->root;
        Nodo<T>* p= orig->root;
        int nivel = 0;
        if (p){
            inorden (p->left, nivel + 1);
            inserta(p->data);
            inorden (p->right, nivel + 1);
        }

    }
    return *this;
}

/**
 * @brief copia de nodos
 * @tparam T [in] puntero a un nodo
 * @param root [in] puntero a nodo a copiar
 * @post en el private se mandan los punteros a dos nodos para copiar uno a otro
 * @param p
 */
template <typename T>
void Avl<T>::copy(Nodo<T> *root, Nodo<T> *p)
{
    if(p) {
        root->left = new Nodo<T>(p->left);
        root->right = new Nodo<T>(p->right);
        copy(root->left, p->left);
        copy(root->right, p->right);
    }


}


/**
 * @brief constructor por copia
 * @param orig [in] arbol origina
 * @post copia los elementos y disposición de un arbol a otro
 */
template <typename T>
Avl<T>::Avl(const Avl<T> &orig){
    root = new Nodo<T>(orig.root);
    copy(root, orig.root);
}


/**
 * brief altura
 * @post metodo que llama al private para poder activar la salida del arbol que se averigua de manera recursiva
 * @return
 */
template <typename T>
int Avl<T>::altura() {
    if(root){
        return altura(root);
    }
    return 0;
}

/**
 * @brief altura (private)
 * @param p [in] en el primer lugar se manda la raiz para empezar a desplazarse por el arbol de manera recursiva
 * @post el metodo se llama a si mismo (recursivo ) para poder hallar la altura mientras existan nodos
 * @return
 */
template <typename T>
int Avl<T>::altura(Nodo<T> *p) {
    if(p)
        return 1+max(altura(p->left), altura(p->right));
    return 0;
}


/**
 * @brief altura
 * @post el metodo averigua la altura utilizando la disposición que muestran los arboles avl 2^x
 * @return
 */
template <typename T>
int Avl<T>::altura2(){
    bool encontrado = false;
    int altura;
    int h;
    int cantidad;

    if( numElementos == 0 ){ //arbol esta vacio
        h = 0;
    }
    else if ( numElementos == 1){  //arbol tiene solo raiz (root)
        h = 1;
    }
    else{
        cantidad = numElementos - 1;
        h = 1;

        do {
          //al ser un arbol avl los nodos se posicionan de manera 2^x por lo que el programa intenta encontrar que x hace que el numero de nodos sea igual
            if( cantidad > ( pow( 2, (h-1)) and cantidad <= ( pow (2, h)) )){
                encontrado = true;
            }else{
                h++;
            }

        }while( encontrado == false);
         h++;
    }

    return h;

}

/**
 * brief busqueda iterativa
 * @param data [in] dato a buscar en el arbol
 * @post se pasa un dato el cual se va a buscar de manera iterativa comparando si es mayor o menor para saber en que dirección rotar
 * @return
 */
template <typename T>
T* Avl<T>::buscaIt(T &data) {
Nodo<T> *move = root ;


do{

    if (move->data == data) {
        return &(move->data);
    }
    if ( data < move->data){
        move = move->left;

    }else if(data > move-> data){
        move = move->right;

    }





}while (move);


return 0;
}

template <typename T>
VDinamico<T*> Avl<T>::recorreInorden() {
    VDinamico<T*> vector;
    inorden(root,vector);
    return vector;
}

template <typename T>
bool Avl<T>::inserta(T &_data) {

        return inserta(root,_data);
}

template <typename T>
Avl<T>::~Avl() {
    destruir(root);
    delete root;

}

template <typename T>
void Avl<T>::destruir(Nodo<T> *p) {
    do {
    if (p->left){
        destruir(p->left);
    }
    else if(p->right){
        destruir(p->right);
    }
    else{
        delete p;
    }


    }while(p);


}
#endif //PRACTICA_2_AVL_H


