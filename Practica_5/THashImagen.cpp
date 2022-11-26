//
// Created by Rafa on 24/11/2022.
//

#include "THashImagen.h"

THashImagen::THashImagen(int maxElementos, float lambda):tamImagenes(0), tabla(siguientePrimo(maxElementos),Entrada()) {

}

THashImagen &THashImagen::operator=(THashImagen &ta) {
    if(this != &ta){
        tabla=ta.tabla;
        tamImagenes=ta.tamImagenes;

    }
    return *this;
}

unsigned long THashImagen::djb2(const std::string &str) {
    unsigned long hash = 5381;
    unsigned int size = str.length();
    unsigned int i = 0;
    for (i = 0; i < size; i++) {
        hash = ((hash << 5) + hash) + (str[i]);
    }
    return hash;
}
/**
 * @brief Devuelve el numero de imagenes insertadas en la tabla hash
 * @return numero de imagenes insertadas
 */
unsigned int THashImagen::numImages() {
    return tamImagenes;
}


Imagen *THashImagen::buscar(unsigned long clave) {
    int i=0;
    unsigned long pos=hash(clave,i);
    while(tabla[pos].clave != clave){
        pos=hash(clave,i++);
    }
}

/**
 * @brief Comprueba si un numero es primo
 * @param n [in] numero a comparar
 * @return true si es numero primo o false si no lo es
 */
bool THashImagen::primo(unsigned int n) {
    if (n == 0 || n == 1) {
        return false;
    }

    for (int i = 2; i <= n/2; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Devuelve el siguiente numero primo a uno dado
 * @param n [in] numero a partir del cual se busca el siguiente primo
 * @return siguiente numero primo a uno dado
 */
int THashImagen::siguientePrimo(int n) {
    if(n < 2 )
        return 2;
    bool esPrimo=false;
    while(esPrimo==false){
        n++;
        if(primo(n))
            esPrimo=true;
    }
    return n;
}