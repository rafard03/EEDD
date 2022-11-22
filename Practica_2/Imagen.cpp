//
// Created by Rafa on 20/09/2022.
//

#include "Imagen.h"


/**
 * @brief Constructor por defecto
 */
Imagen::Imagen() {

};

/**
 * @brief Constructor parametrizado
 */
Imagen::Imagen(const std::string &_id, const std::string &_email, const std::string &_nombre, int _tam,
               const Fecha &_fecha, Etiqueta* _etiquetada):
               id(_id) , email(_email) , nombre(_nombre) , tam(_tam) , fecha(_fecha) , etiquetada(_etiquetada){

};

/**
 * @brief Construye una imagen con una etiqueta
 */
 Imagen::Imagen(Etiqueta *et){
     etiquetada = et;
 }

/**
 * @brief asigna un id a una imagen
 * @param _id [in] id que se va a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setId(const std::string & _id) {

    id = _id;

    //realizamos un return *this para poder hacer "sets encadenados"
    return *this;

}

/**
 * @brief asigna un email a una imagen
 * @param _email [in] email que se va a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setEmail(const std::string &_email) {

    email = _email;

    return *this;

}

/**
 * @breif asigna un nombre a una imagen
 * @param _nombre [in] nombre que se va a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setNombre(const std::string &_nombre) {

    nombre = _nombre;

    return *this;
}

/**
 * @brief asigna un tamaño a una imagen
 * @param _tam [in] tamaño que se va a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setTam(int _tam) {

    tam = _tam;

    return *this;

}

/**
 * @brief asigna una fecha a una imagen
 * @param _fecha [in] fecha que se va a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setFecha(const Fecha &_fecha) {

    fecha = _fecha;


    return *this;
}

/**
 * @brief asigna unas etiquetas a una imagen
 * @param _etiquetas [in] etiquetas que se van a asignar
 * @return dirección de memoria del objeto para poder encadenar los sets
 */
Imagen &Imagen::setEtiquetada(Etiqueta* _etiquetada) {

    etiquetada = _etiquetada;


    return *this;

}

/**
 * @brief Devuelve el id de una imagen
 * @return id de la imagen
 */
std::string Imagen::getId() {

    return id;

}

/**
 * @brief Devuelve el email de una imagen
 * @return email de la imagen
 */
std::string Imagen::getEmail() {

    return email;

}

/**
 * @brief Devuelve el nombre de una imagen
 * @return nombre de la imagen
 */
std::string Imagen::getNombre() {

    return nombre;

}

/**
 * @brief Devuelve el tamaño de una imagen
 * @return tamaño de la imagen
 */
int Imagen::getTam() {

    return tam;

}

/**
 * @brief Devuelve la fecha de una imagen
 * @return fecha de la imagen
 */
Fecha Imagen::getFecha(){

    return fecha;

}

/**
 * @brief Devuelve las etiquetas de una imagen
 * @return etiquetas de la imagen
 */
Etiqueta* Imagen::getEtiqueta() {
    return etiquetada;
}


/**
 * @brief Convierte una cadena a un entero
 * @param cadena [in] cadena que se quiere convertir
 * @return La conversión de cadena a entero
 */
int Imagen::toInt(const std::string &cadena) {
    int salida = std::stoi( cadena );
    return salida;
}

/**
 * @brief Operador menor que
 * @param origen [in] objeto con el que se va a comparar
 * @return true si el objeto es menor que origen o false si no
 */
bool Imagen::operator<(const Imagen &origen) {
    return(toInt(this->id) < toInt(origen.id));
}

/**
 * @brief Operador mayor que
 * @param origen [in] objeto con el que se va a comparar
 * @return true si el objeto es mayor que origen o false si no
 */
bool Imagen::operator>(const Imagen &origen){

    return (toInt(this->id) > toInt(origen.id));
}

/**
 * @brief Destructor de la clase
 */
Imagen::~Imagen() {}


Imagen &Imagen::operator=(const Imagen &origen) {
    if(this != &origen){
        id=origen.id;
        email=origen.email;
        nombre=origen.nombre;
        tam=origen.tam;
        fecha=origen.fecha;
        etiquetada=origen.etiquetada;
    }
    return *this;
}

/**
 * @brief Muestra los datos de una imagen por pantalla
 */
void Imagen::mostrar() {

    std::cout << " ID=" << getId()
              << " Email=" << getEmail() << " Fichero=" << getNombre() << " Tam=" << getTam()
              << " Fecha=" << getFecha().verDia() << "/" << getFecha().verMes() << "/" << getFecha().verAnio()
              << " Etiqueta=" << getEtiqueta()->getNombre() << std::endl;


}

/**
 * @brief Operador ==
 * @param orig [in] imagen a comparar
 * @return true si ambas imágenes son iguales y false si no
 * @post Compara si dos imágenes son iguales según su id
 */
bool Imagen::operator==(const Imagen &orig) {
    return (id == orig.id);
}

/**
 * @breif Constructor de imagen
 * @param id [in] id de la nueva imagen
 * @post Construye una nueva imagen con valores por defecto excepto el id
 */
Imagen::Imagen(const std::string &id) {
    Imagen();
    this->id = id;
}