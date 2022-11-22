//
// Created by Rafa on 20/10/2022.
//

#ifndef PRACTICA_2_IMAGEBOOK_H
#define PRACTICA_2_IMAGEBOOK_H
#include "Imagen.h"
#include "Etiqueta.h"
#include "ListaDEnlazada.h"
#include "VDinamico.h"
#include <fstream>
#include <sstream>
#include <iostream>


class ImageBook {
private:
    VDinamico<Imagen> images;
    ListaDEnlazada<Etiqueta> labels;

public:
    ImageBook();
    ~ImageBook();
    ListaDEnlazada<Imagen> buscarImagEtiq(const std::string &etiqueta);
    int tamImagenes();
    int tamEtiquetas();
    Imagen& operator[](int pos);
    ListaDEnlazada<Etiqueta> getLabels();

};

#endif //PRACTICA_2_IMAGEBOOK_H
