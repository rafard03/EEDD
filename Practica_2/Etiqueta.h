//
// Created by Rafa on 20/10/2022.
//

#ifndef PRACTICA_2_ETIQUETA_H
#define PRACTICA_2_ETIQUETA_H
#include <iostream>

class Etiqueta {
private:
    std::string nombre = "";
public:
     Etiqueta();
     Etiqueta(const std::string &_nombre);
     Etiqueta(const Etiqueta& orig);
     ~Etiqueta();

     std::string getNombre();

     void setNombre(const std::string &_nombre);

     bool operator==(Etiqueta& orig);
};


#endif //PRACTICA_2_ETIQUETA_H
