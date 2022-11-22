//
// Created by Rafa on 20/10/2022.
//

#ifndef PRACTICA_2_IMAGEBOOK_H
#define PRACTICA_2_IMAGEBOOK_H
#include "Imagen.h"
#include "Etiqueta.h"
#include "Usuario.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

class Usuario;

class ImageBook {
private:
    vector<Imagen> images;
    list<Etiqueta> labels;
    map<string,Usuario> users;

public:
    ImageBook(std::string &fichEtiquetas, std::string &fichUsuarios, std::string &fichImagenes);
    ~ImageBook();
    vector<Imagen> buscarImagEtiq(const std::string &etiqueta);
    int tamImagenes();
    int tamEtiquetas();

    list<Etiqueta> getLabels();
    string etiquetaMasRepetida();
    vector<Usuario*> getMasActivos();
    Usuario* buscarUsuario(const std::string email);
    vector<Usuario*> buscarUsuarioEtiq(const std::string etiqueta);
    Etiqueta* buscarEtiqueta(std::string &nombre);
    vector <Usuario*> buscarUsuarioFechaImagen(Fecha fecha);
    vector<Usuario*> buscaUsuariosPremium();

};

#endif //PRACTICA_2_IMAGEBOOK_H
