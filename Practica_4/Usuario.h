//
// Created by Rafa on 08/11/2022.
//

#ifndef PRACTICA_2_USUARIO_H
#define PRACTICA_2_USUARIO_H
#include <iostream>
#include "Imagen.h"
#include <map>
#include <vector>
#include "ImageBook.h"

class ImageBook;

class Usuario {
private:
    std::string email;
    map<string,Imagen*> userImages;
    ImageBook* linkIB;
public:
    Usuario();
    Usuario(const std::string &_email, ImageBook* _linkIB);
    Usuario(const Usuario &orig);
    ~Usuario();

    std::string getEmail() {return email;}
    int getNumImages() {return userImages.size();}
    void insertarImagen(Imagen *img);
    void anadirEtiquetaImagen(std::string &id, std::string nombreEti);


    bool operator<(const Usuario& orig);
    bool operator>(const Usuario& orig) {return !operator<(orig);}
    bool operator==(Usuario& orig);

    Imagen* buscarImagen(const std::string &id);
    vector<Imagen*> buscarEtiqueta(const std::string &orig);
    vector<Usuario*> buscarUsuariosEtiq(const std::string &nombreEti);
    Imagen* getImagenMasAntigua();
    Imagen* getImagenMasReciente();
    vector<Imagen*> getImagenFecha(Fecha fecha);

    bool esMasActivo();
    void mostrar();

};


#endif //PRACTICA_2_USUARIO_H
