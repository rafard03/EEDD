//
// Created by Rafa on 20/09/2022.
//

#ifndef IMAGENES_IMAGEN_H
#define IMAGENES_IMAGEN_H
#include <iostream>
#include <stdexcept>
#include "fecha.h"
#include <string>
#include "Etiqueta.h"
#include <deque>
#include <vector>


class Imagen {
private:
    std::string id = "a";
    std::string nombre = "c";
    int tam = 0;
    Fecha fecha;
    std::deque<Etiqueta*> etiquetada;

public:
    Imagen();
    Imagen(const std::string& _id, const std::string& _nombre, int _tam, const Fecha& _fecha);
    Imagen(const Imagen &orig);
    virtual ~Imagen();
    Imagen(const std::string &id);


    std::string getId();
    std::string getNombre();
    int getTam();
    Fecha getFecha() ;
    vector<string> getEtiquetas();
    void anadirEtiqueta(Etiqueta* etiqueta);

    Imagen& setId(const std::string & _id);
    Imagen& setNombre(const std::string & _nombre);
    Imagen& setTam(int _tam);
    Imagen& setFecha(const Fecha & _fecha);

    bool operator< (const Imagen& origen);
    bool operator> (const Imagen& origen);
    Imagen& operator= ( const Imagen& origen);
    bool operator== (const Imagen& orig);
    int toInt(const std::string & cadena);
    void mostrar();
};


#endif //IMAGENES_IMAGEN_H
