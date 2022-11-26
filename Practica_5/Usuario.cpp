//
// Created by Rafa on 08/11/2022.
//

#include "Usuario.h"
Usuario::Usuario() {}

Usuario::Usuario(const std::string &_email, ImageBook* _linkIB):email(_email), linkIB(_linkIB), userImages() {}

Usuario::Usuario(const Usuario &orig): email(orig.email), userImages(orig.userImages), linkIB(orig.linkIB) {}

Usuario::~Usuario() {}

/**
 * @brief Devuelve todas las imagenes de un usuario con una etiqueta
 * @param orig [in] nombre de la etiqueta a buscar
 * @return vector<Imagen*> vector de punteros a todas las imagenes del usuario que coinciden con orig
 */
vector<Imagen*> Usuario::buscarEtiqueta(const std::string &orig){
    vector<Imagen*> images;
    map<string,Imagen*>::iterator iterador = userImages.begin();
    for(int i = 0; i < userImages.size(); i++){
        std::vector<string> imagenes = iterador->second->getEtiquetas();
        for(int j = 0; j < imagenes.size(); j++){
            if(imagenes[j]==orig) {
                images.push_back(iterador->second);
                break;
            }
        }
        iterador++;
    }
    return images;
}

/**
 * @brief inserta una imagen en userImages
 * @param img [in] imagen a insertar
 */
void Usuario::insertarImagen(Imagen *img) {
    userImages[img->getId()]=img;
}

/**
 * @brief operador < de la clase usuario
 * @param orig [in] usuario a comparar
 * @return true si el email de orig es mayor que this->email
 * @post sobrecarga el operador < de la clase usuario para que compare según el email
 */
bool Usuario::operator<(const Usuario &orig) {
    return email < orig.email;
}

/**
 * @brief muestra un usuario
 * @post muestra el email, el numero de fotos subidas y los detalles de dichas fotos de un usuario
 */
void Usuario::mostrar() {
    std::cout << "Email: " << email << "Imagenes subidas: " << userImages.size() << std::endl;
    std::cout << "IMAGENES" << std::endl;
    map<string,Imagen*>::iterator iterador(userImages.begin());
    while(iterador != userImages.end()){
        iterador->second->mostrar();
        iterador++;
    }
}
/**
 * @brief operador == de la clase usuario
 * @param orig [in] usuario a comparar
 * @return true si el email de orig es igual al de orig
 * @post sobrecarga el operador == de la clase usuario para que compare segun el email
 */
bool Usuario::operator==(Usuario &orig) {
    return email==orig.email;
}

/**
 * @brief busca una imagen según un id
 * @param id [in] id de la imagen a buscar
 * @return Imagen* si encuentra la imagen o nullptr si no la encuentra
 */
Imagen *Usuario::buscarImagen(const std::string &id) {
    map<string,Imagen*>::iterator iterador=userImages.find(id);
    if(iterador != userImages.end()){
            return iterador->second;
    }
    return nullptr;
}

/**
 * @brief añade una nueva etiqueta a una imagen
 * @param id [in] id de la imagen
 * @param nombreEti [in] nombre de la etiqueta
 * @post añade una etiqueta a una imagen si la encuentra en userImages
 */
void Usuario::anadirEtiquetaImagen(std::string &id, std::string nombreEti) {
    map<string,Imagen*>::iterator iterador=userImages.find(id);
    if(iterador != userImages.end()){
            Etiqueta e(nombreEti);
            iterador->second->anadirEtiqueta(&e);
    }
}

/**
 * @brief Busca todos los usuarios que comparten una etiqueta
 * @param nombreEti [in] nombre de la etiqueta a buscar
 * @return vector<Usuario*> con todos los usuarios que tienen una imagen con esa etiqueta
 */
vector<Usuario *> Usuario::buscarUsuariosEtiq(const std::string &nombreEti) {
    vector<Usuario *> usuarios = linkIB->buscarUsuarioEtiq(nombreEti);
    if (!usuarios.empty()) {
        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i]->email == this->email) {
                return usuarios;
            }
        }
    }
    return usuarios;
}

/**
 * @brief Devuelve si un usuario pertenece a los usuarios mas activos de la red
 * @return true si pertenece a los mas activos y false si no
 */
bool Usuario::esMasActivo() {
    vector<Usuario*> masActivos(linkIB->getMasActivos());
    if(!masActivos.empty()) {
        for (int i = 0; i < masActivos.size(); i++) {
            if (masActivos[i] == this)
                return true;
        }
    }
    return false;
}

/**
 * @brief devuelve la imagen mas antigua de un usuario
 * @return Imagen* la imagen con la fecha mas pequeña de un usuario
 * @except invalid_argument si el usuario no ha publicado ninguna imagen
 */
Imagen *Usuario::getImagenMasAntigua() {
    if( userImages.empty())
        throw std::invalid_argument("Usuario::getImagenMasAntigua: El usuario no ha publicado ninguna imagen");
    map<string, Imagen*>::iterator iterador = userImages.begin();
    Fecha fecha = iterador->second->getFecha();
    map<string, Imagen*>::iterator iterador2 = userImages.begin();
    while(iterador != userImages.end()){
        if(iterador->second->getFecha() < fecha) {
            fecha = iterador->second->getFecha();
            iterador2=iterador;
        }
        iterador++;
    }
    return iterador2->second;
}

/**
 * @brief devuelve la imagen mas reciente de un usuario
 * @return Imagen* la imagen con la fecha mas grande de un usuario
 * @except invalid_argument si el usuario no ha publicado ninguna imagen
 */
Imagen *Usuario::getImagenMasReciente() {
    if( userImages.empty())
        throw std::invalid_argument("Usuario::getImagenMasReciente: El usuario no ha publicado ninguna imagen");
    map<string, Imagen*>::iterator iterador = userImages.begin();
    Fecha fecha = iterador->second->getFecha();
    map<string, Imagen*>::iterator iterador2 = userImages.begin();
    while(iterador != userImages.end()){
        if(fecha < (iterador->second->getFecha())) {
            fecha=iterador->second->getFecha();
            iterador2=iterador;
        }
        iterador++;
    }
    return iterador2->second;
}


/**
 * @brief busqueda imagenes
 * @param fecha
 * @return vector de imagenes
 * @post pasando una fecha almacena en un vector las imagenes de dicha fecha
 */
vector<Imagen *> Usuario::getImagenFecha(Fecha fecha) {
    vector<Imagen*> salida;
    map<string,Imagen*>::iterator iteradorImagenes = userImages.begin();
    while(iteradorImagenes != userImages.end()){
        if(iteradorImagenes->second->getFecha().mismoDia(fecha))
            salida.push_back(iteradorImagenes->second);
        iteradorImagenes++;
    }
    return salida;
}