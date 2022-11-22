#include "Usuario.h"
#include "fecha.h"
#include "ImageBook.h"
#include "Imagen.h"
#include "Etiqueta.h"

#include <iostream>

int main(){
    string fichEtiquetas="etiquetas.txt";
    std::string fichUsuarios="usuarios.txt";
    std::string fichImagenes="imagenes_v1.csv";
    ImageBook imageBook(fichEtiquetas, fichUsuarios, fichImagenes);

    int opt;
    do{
        std::cout << "MENU PRACTICA 4 ( STL ) :" << std::endl;
        std::cout << "1 -  noelia30@hotmail.com incluirá playa en sus imagen " <<std::endl;
        std::cout << "2 - El usuario kenny modificará su útilma imagen " << std::endl;
        std::cout << "3 - Usuarios que comparten la etiqueta arroz " << std::endl;
        std::cout << "4 - Buscar los usuarios que publicaron imagenes el 7/9/2021 y mostrar quien ha publicado más " << std::endl;
        std::cout << "5 - Comprobar si chesley.gerlach es el usuario mas activo " << std::endl;
        std::cout << "6 - Crear el vector de usuarios premiums y mostrarlo " << std::endl;
        std::cout << "0 - Cerrar" << std::endl;
        std::cin >> opt;

        switch (opt) {

            case 1: {
                //Apartado noelia
                Usuario* noelia=imageBook.buscarUsuario("noelia30@hotmail.com");
                Etiqueta etiquetaNoelia("playa");
                if(noelia != nullptr) {
                    if (noelia->buscarImagen("625722993")) {
                        try {
                            noelia->buscarImagen("625722993")->mostrar();
                            noelia->buscarImagen("625722993")->anadirEtiqueta(&etiquetaNoelia);
                            noelia->buscarImagen("625722993")->mostrar();
                        }catch(const std::invalid_argument &ia){
                            std::cerr << ia.what();
                        }
                    } else {
                        std::cout << "El usuario con email: noelia30@hotmail.com no ha subido ninguna imagen con el ID 625722993"
                                  << std::endl;
                    }
                }
                else{
                    std::cout << "No existe el usuario noelia30@hotmail.com" << std::endl;
                }
                break;
            }

            case 2: {

                //Apartado kenny
                Usuario* kenny=imageBook.buscarUsuario("kenny_ohara73@yahoo.com");
                if(kenny != nullptr){
                    Etiqueta etiquetaKenny("viernes");
                    try {
                        if (kenny->getImagenMasReciente()) {
                            kenny->getImagenMasReciente()->anadirEtiqueta(&etiquetaKenny);
                            kenny->getImagenMasReciente()->mostrar();
                        } else {
                            std::cout << "El usuario con email: kenny_ohara73@yahoo.com no ha subido ninguna foto" << std::endl;
                        }
                    }catch (const std::invalid_argument &ia){
                        std::cerr << ia.what();
                    }
                }else{
                    std::cout << "No existe el usuario kenny_ohara73@yahoo.com" << std::endl;
                }

                break;
            }

            case 3:{
                Usuario* us = imageBook.buscarUsuario("elton.botsford@yahoo.com");
                if(us) {
                    vector<Usuario *> conarroz;
                    try {
                        conarroz = us->buscarUsuariosEtiq("arroz");
                    } catch (const std::invalid_argument &no) {
                        std::cerr << no.what();
                    }
                    std::cout << "Hay " << conarroz.size() << " usuarios con la etiqueta 'arroz'" << endl;
                    std::cout << "Lista de ellos: " << endl;
                    for (int i = 0; i < conarroz.size(); i++) {
                        std::cout << conarroz[i]->getEmail() << std::endl;
                    }
                }
                break;
            }

            case 4: {
                Fecha fecha(7,9,2021);
                try {
                    vector<Usuario *> usuariosFecha = imageBook.buscarUsuarioFechaImagen(fecha);
                    Usuario *masFotos = *usuariosFecha.begin();
                    if (!(usuariosFecha.empty())) {
                        std::cout << "En la fecha " << fecha << " publicaron imagenes:" << std::endl;
                        for (int i = 0; i < usuariosFecha.size(); i++) {
                            std::cout << usuariosFecha[i]->getEmail() << std::endl;
                            if (usuariosFecha[i]->getImagenFecha(fecha).size() > masFotos->getImagenFecha(fecha).size())
                                masFotos = usuariosFecha[i];
                        }
                        std::cout << "===============================================" << std::endl;
                        std::cout << "El usuario que mas imagenes publico ese dia es " << masFotos->getEmail()
                                  << std::endl;
                    } else {
                        std:
                        cout << "En la fecha " << fecha << " no se publico ninguna imagen" << std::endl;
                    }
                }catch(const std::runtime_error &re){
                    std::cerr<<re.what();
                }
                break;
            }

            case 5:{
                if (imageBook.buscarUsuario("chesley.gerlach@hotmail.com")->esMasActivo() ){
                    std::cout << "chesley.gerlach@hotmail.com es el mas activo de la red social" << std::endl;
                }else{
                    std::cout << "chesley.gerlach@hotmail.com NO es el mas activo de la red social" << std::endl;
                }
                break;
            }

            case 6:{
            try {
                vector<Usuario * > VIPS = imageBook.buscaUsuariosPremium();

                if(VIPS.size() == 1){
                    std::cout<< "El usuario mas antiguo es " << VIPS[0]->getEmail() << std::endl;
                }else{
                    std::cout << "Los usuarios mas antiguos son: " << std::endl;
                    for (int i = 0 ; i != VIPS.size() ;i++){
                        std::cout << VIPS[i]->getEmail() << std::endl;
                    }
                }

            } catch ( const std::runtime_error &vacio){
                std::cerr << vacio.what();
            } catch (const std::invalid_argument &ia){
                std::cerr <<ia.what();
            }
            break;
            }
        }
    }while(opt != 0 );

    return 0;
}