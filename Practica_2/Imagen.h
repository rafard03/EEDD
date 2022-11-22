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

class Imagen {
private:
    std::string id = "a";
    std::string email = "b";
    std::string nombre = "c";
    int tam = 0;
    Fecha fecha;
    Etiqueta* etiquetada;

public:
    Imagen();
    Imagen(const std::string& _id, const std::string& _email, const std::string& _nombre, int _tam, const Fecha& _fecha, Etiqueta* _etiquetada);
    virtual ~Imagen();
    Imagen(const std::string &id);
    Imagen(Etiqueta *et);

    std::string getId();
    std::string getEmail();
    std::string getNombre();
    int getTam();
    Fecha getFecha();
    Etiqueta* getEtiqueta();

    Imagen& setId(const std::string & _id);
    Imagen& setEmail(const std::string & _email);
    Imagen& setNombre(const std::string & _nombre);
    Imagen& setTam(int _tam);
    Imagen& setFecha(const Fecha & _fecha);
    Imagen& setEtiquetada(Etiqueta* _etiquetas);

    bool operator< (const Imagen& origen);
    bool operator> (const Imagen& origen);
    Imagen& operator= (const Imagen& origen);
    bool operator== (const Imagen& orig);
    int toInt(const std::string & cadena);
    void mostrar();
};


#endif //IMAGENES_IMAGEN_H
