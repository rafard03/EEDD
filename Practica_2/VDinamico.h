//
// Created by Rafa on 03/10/2022.
//

#ifndef PRACTICA1_2_VDINAMICO_H
#define PRACTICA1_2_VDINAMICO_H
#include <climits>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Imagen.h"

template <typename T>
class VDinamico {
private:
    int logical_tam = 0;
    int physical_tam = 0;
    T* vector;
public:
    VDinamico<T>();
    VDinamico<T>(int _logical_tam);
    VDinamico<T>(const VDinamico& orig);
    VDinamico<T>(const VDinamico<T>& origen, unsigned int posicionInicial, unsigned int numElementos);
    ~VDinamico();

    VDinamico& operator = (const VDinamico& orig);
    Imagen& operator[] (unsigned pos);
    void inserta(const T& dato, unsigned int pos = UINT_MAX);
    void borrar(unsigned int pos = UINT_MAX);
    void ordena();
    void ordenarRev();
    //TODO, si se encuentra el objeto, se crea un objeto basico T que contenga el atributo del objeto de la busqueda sino devuelve -1
    int busquedaBin(T& dato);
    unsigned int tamlog();
    bool operator ==(const T& dato);
    void mostrarDato(unsigned int dato);

};

/**
 * @brief Constructor por defecto
 * @tparam T
 * @post Inicializa un vector dinamico de tamaño 1
 */
template <typename T>
VDinamico<T>::VDinamico(): physical_tam(1), logical_tam(0) {
    vector = new T[physical_tam];
}
/**
 * @brief Constructor parametrizado
 * @tparam T
 * @param _logical_tam [in] tamaño lógico del vector que se quiere inicializar
 * @post Crea un nuevo vector dinámico de tipo T con el tamaño lógico dado y un tamaño físico de la siguiente potencia de 2 del lógico
 */
template <typename T>
VDinamico<T>::VDinamico(int _logical_tam): logical_tam(_logical_tam) {
    physical_tam = pow(2, ceil(log(logical_tam)/log(2)));
    vector = new T[physical_tam];
    logical_tam = 0;
}

/**
 * @brief Constructor de copia
 * @tparam T
 * @param orig [in] vector dinámico
 * @post Crea un nuevo vector dinámico a partir de uno existente
 */
template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig): physical_tam(orig.physical_tam), logical_tam(orig.logical_tam) {
    vector = new T[orig.physical_tam];
    for(int i = 0; i < logical_tam; i++){
        vector[i] = orig.vector[i];
    }
}

/**
 * @brief Constructor de copia parcial
 * @tparam T
 * @param origen [in] Vector a partir del cuál se va a copiar
 * @param posicionInicial [in] posición de origen a partir de la cuál se va a empezar a copiar
 * @param numElementos [in] número de elementos que se van a copiar
 * @post Crea un nuevo vector dinámico a partir de una posición y con un numero de elementos del vector origen, con tamaño a la siguiente potencia de 2 del número de elementos
 * @throw invalid_argument si la posición inicial es mayor que el tamaño lógico del vector
 * @throw invalid_argument si la posición inical más el número de elementos supera el tamaño lógico del vector
 */
template <typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &origen, unsigned int posicionInicial, unsigned int numElementos){
    if(posicionInicial >= logical_tam)
        throw std::invalid_argument("VDinamico:Copia parcial: Posicion inicial no valida");
    if(posicionInicial + numElementos >= logical_tam)
        throw std::invalid_argument("VDinamico:Copia parcial: Numero de elementos no valido");

    logical_tam = origen.logical_tam;
    physical_tam = pow(2, ceil(log(logical_tam)/log(2)));
    vector = new T[physical_tam];

    for(int i = 0; i < logical_tam; i++){
        vector[i] = origen.vector[posicionInicial + i];
    }
}

/**
 * @brief Sobrecarga del operador de asignación
 * @tparam T
 * @param orig [in] Objeto que se va a asignar
 * @return
 */
template <typename T>
VDinamico<T> &VDinamico<T>::operator=(const VDinamico<T> &orig) {
    if(this != &orig){
        logical_tam = orig.logical_tam;
        if(physical_tam != orig.physical_tam) {
            delete[] vector;
            physical_tam = orig.physical_tam;
            vector = new T[physical_tam];
        }
        for(int i = 0; i < logical_tam; i++){
            vector[i] = orig.vector[i];
        }
    }
    return *this;
}

/**
 * @brief Ordena el vector
 * @tparam T
 * @post Ordena el vector de menor a mayor
 */
template <typename T>
void VDinamico<T>::ordena() {
    sort(vector, vector + logical_tam);
}

/**
 * @brief Ordena el vector al revés
 * @tparam T
 * @post Ordena el vector de mayor a menor
 */
template <typename T>
void VDinamico<T>::ordenarRev() {
    T *aux;
    aux = new T[physical_tam];
    std::sort(vector, vector + logical_tam);
    for(int i = 0; i < logical_tam; i++){
        aux[i] = vector[logical_tam -(i + 1)];
    }
    for(int i = 0; i < logical_tam; i++){
        vector[i] = aux[i];
    }
    delete []aux;
}

/**
 * @brief Operador []
 * @tparam T
 * @param pos [in] posición del vector a la que se va a acceder
 * @return posición del vector
 * @post Sobrecarga el operador [] para poder acceder a las posiciones del vector
 */
template <typename T>
Imagen& VDinamico<T>::operator[] (unsigned int pos) {
    return vector[pos];
}

/**
 * @brief Inserta un dato en el vector
 * @tparam T
 * @param dato [in] Dato a insertar
 * @param pos [in] Posición en la que se va a insertar
 * @post Inserta un dato en una posición del vector, si la posición es UINT_MAX inserta al final
 */
template<class T>
void VDinamico<T>::inserta(const T &dato, unsigned int pos) {
    if ( pos >= physical_tam && pos != UINT_MAX){
        throw std::invalid_argument("VDinamico::borrar:posicion inválida");
    }

    if (logical_tam == physical_tam){
        physical_tam = physical_tam * 2;

        T aux[physical_tam];
        for(int i = 0; i < logical_tam; i++){
            aux[i] = vector[i];
        }
        delete[] vector;
        vector = new T[physical_tam];

        for (int i = 0; i < logical_tam ; i++){
            vector[i] = aux[i];
        }
    }

    if(pos == UINT_MAX){
        vector[logical_tam] = dato;

    }else{

        for(int i = physical_tam ; i >= pos ; i --){
            vector[i] = vector[ ( i - 1)];

        }
        vector[pos] = dato;
    }

    logical_tam++;
}

/**
 * @brief Borra un elemento de un vector
 * @tparam T
 * @param pos [in] Posición que se va a borrar
 * @post Borra un elemento del vector, si la posición es UINT_MAX borra el último
 */
template <typename T>
void VDinamico<T>::borrar(unsigned int pos) {
    if(pos >= logical_tam)
        throw std::invalid_argument("VDinamico::borrar:posicion inválida");
    if(pos == UINT_MAX){
        logical_tam--;
    }
    for(int i = ( pos + 1 ); i < logical_tam; i++){
        vector[i-1] = vector[i];
    }

    logical_tam--;

    if (logical_tam == (physical_tam /3)){
        T aux[physical_tam/2];
        for(int i = 0; i < logical_tam; i++){
            aux[i] = vector[logical_tam -(i + 1)];
        }
        delete[] vector;
        vector = new T[physical_tam];
        for(int i = 0; i < logical_tam; i++){
            vector[i] = aux[i];
        }
    }
}

/**
 * @brief Busca un dato en el vector
 * @tparam T
 * @param dato [in] dato que se va a buscar
 * @return -1 si no se encuentra
 * @return posición del vector en la que está el dato
 * @post Busca un dato en un vector mediante el algoritmo de búsqueda binaria
 */
template <typename T>
int VDinamico<T>::busquedaBin(T& dato){

    int inf, sup, mitad;
    int encontrado = -1;
    inf = 0;
    sup = logical_tam;
while (inf <= sup){

    mitad = ( inf +sup )/2;
    if ( vector[mitad] == dato){
        return mitad;
    }
    if ( vector[mitad] > dato ){
        sup = mitad-1;
        mitad = (inf + sup) / 2;
    }else{

        inf = mitad+1;
        mitad = (inf + sup) / 2 ;
    }
    }
    return encontrado;
}

/**
 * @brief Devuelve el tamaño lógico del vector
 * @tparam T
 * @return tamaño lógico
 */
template <typename T>
unsigned int VDinamico<T>::tamlog() {
    return logical_tam;
}

/**
 * @brief Operador ==
 * @tparam T
 * @param dato [in] vector dinámico con el que se va a comparar
 * @return true si son iguales, false si son diferentes
 * @post Compara dos vectores dinámicos y sus elementos para ver si son iguales
 */
template <typename T>
bool VDinamico<T>::operator==(const T& dato) {
    bool salida = false;
    if (physical_tam == dato.physical_tam && logical_tam == dato.logical_tam) {
        salida = true;
        for (int i = 0; i < logical_tam; i++){
            if(vector[i] != dato.vector[i]) {
                salida = false;
                break;
            }
        }


    }
    return salida;
}

/**
 * @brief Destructor del vector dinámico
 * @tparam T
 */
template <typename T>
VDinamico<T>::~VDinamico() {
    if(vector)
        delete[] vector;
}

/**
 * @brief Muestra un dato por pantalla
 * @tparam T tipo de dato
 * @param dato [in] dato que se va a mostrar
 * @pre La clase T debe tener un método mostrar()
 */
template <typename T>
void VDinamico<T>::mostrarDato(unsigned int pos) {
    vector[pos].mostrar();
}

#endif //PRACTICA1_2_VDINAMICO_H


