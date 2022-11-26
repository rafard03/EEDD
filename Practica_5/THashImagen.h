//
// Created by Rafa on 24/11/2022.
//

#ifndef PRACTICA_5_THASHIMAGEN_H
#define PRACTICA_5_THASHIMAGEN_H
#include "Imagen.h"
#include "vector"

class THashImagen {
private:
    enum Estado {libre,disponible,ocupado};
    class Entrada{
    public:
        unsigned long clave;
        Imagen img;
        Estado marca;
        Entrada():img(Imagen()), clave(0), marca(libre){}
        ~Entrada(){};
    };
    vector<Entrada> tabla;
    int tamImagenes;

    bool primo(unsigned int n);
    int siguientePrimo(int n);
    unsigned long djb2(const std::string &str);
public:
    unsigned long hash(unsigned long clave, int i);
    THashImagen(int maxElementos, float lambda=0.7);
    THashImagen(THashImagen &ta);
    THashImagen& operator=(THashImagen& ta);
    ~THashImagen();
    bool insertar(unsigned long clave, Imagen& imagen);
    Imagen* buscar(unsigned long clave);
    bool borrar(unsigned long clave);
    unsigned int numImages();

};


#endif //PRACTICA_5_THASHIMAGEN_H
