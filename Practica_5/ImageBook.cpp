//
// Created by Rafa on 20/10/2022.
//

/**
 * @brief carga las imagenes en imagen book
 *
 */
#include "ImageBook.h"

ImageBook::ImageBook(std::string &fichEtiquetas, std::string &fichUsuarios, std::string &fichImagenes):images(10000), labels(), users(){
    //Leer etiquetas
    std::ifstream is;
    std::string fila;
    std::stringstream lectura;

    is.open("../"+fichEtiquetas);
    if(is.good()){
        while(getline(is, fila)){
            if(fila != ""){
                Etiqueta etiq(fila);
                labels.push_back(etiq);
                fila = "";
            }
        }
        is.close();
    }else{
        throw std::runtime_error("Fallo al abrir el archivo etiquetas.txt");
    }

    is.open("../"+fichUsuarios);
    if(is.good()){
        while(getline(is,fila)){
            if(fila != ""){
                Usuario us(fila,this);
                users[fila]=us;
                fila = "";
            }
        }
        is.close();
    }else{
        throw std::runtime_error("Fallo al abrir el archivo usuarios.txt");
    }



    //Leer datos imágenes
    std::stringstream columnas;
    std::string id = "";
    std::string email = "";
    std::string nombre = "";
    int tam = 0;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    std::string etiq = "";

    is.open("../"+fichImagenes);
    if(is.good()){
        int contador=0;
        while(getline(is,fila)){
            if(fila != ""){
                columnas.str(fila);
                getline(columnas, id, ';');
                getline(columnas, email, ';');
                getline(columnas, nombre, ';');
                columnas >> tam;
                columnas.ignore();
                columnas >> dia;
                columnas.ignore();
                columnas >> mes;
                columnas.ignore();
                columnas >> anno;
                columnas.ignore();

                getline(columnas, etiq);
                fila = "";
                columnas.clear();

                Imagen img(id, nombre, tam, Fecha(dia, mes, anno));
                lectura.clear();//limpar para no guardar las etiquetas de la img anterior
                lectura << etiq;
                std::string nombre;
                while(!lectura.eof()){
                    getline(lectura,nombre,',');

                    std::list<Etiqueta>::iterator iterador=labels.begin();

                    while(iterador != labels.end()){
                        if(iterador->getNombre() == nombre)
                            img.anadirEtiqueta(&(*iterador));
                        iterador++;
                    }
                }
                images[contador]=img;

                Usuario us(email, this);
                map<string,Usuario>::iterator iterador(users.find(us.getEmail()));
                if(iterador != users.end())
                    iterador->second.insertarImagen(&(images[contador]));
            }
            contador++;
        }
        is.close();
    }else {
        throw std::runtime_error("Fallo al abrir el archivo imagenes_v1.csv");
    }

}

/**
 * @brief destructor de imagebook
 */
ImageBook::~ImageBook() {

}

/**
 * @brief buscar imagen etiqueta
 * @param etiqueta
 * @return lista
 */
vector<Imagen> ImageBook::buscarImagEtiq(const std::string &etiqueta) {
    if(etiqueta == "")
        throw std::invalid_argument("ImageBook::buscarImagEtiq: Etiqueta invalida");
    vector<Imagen> lista;
    Etiqueta etiq(etiqueta);
    for(int i = 0; i < images.size(); i++){
        for(int j = 0; j < images[i].getEtiquetas().size(); j++) {
            vector<string> etiquetas(images[i].getEtiquetas());
            if (etiquetas[j] == etiqueta) {
                lista.push_back(images[i]);
                break;
            }
        }
    }
    return lista;
}

/**
 * @brief tamaño imagebook
 * @return  tam
 * @post devuelve el tamaño
 */
int ImageBook::tamImagenes() {
    return images.size();
}

/**
 * @brief tamaño de etiquetas
 * @return cantidad de etiquetas
 * @post devuelve cantidad de etiquetas
 */
int ImageBook::tamEtiquetas() {
    return labels.size();
}

/**
 * @brief getlabel
 * @return label
 * @post devuelve la lista de etiquetas
 */
list<Etiqueta> ImageBook::getLabels() {
    return labels;
}

/**
 * @brief etiqueta mas repetida
 * @return string etiqueta mas repetida
 * @post devuelve la etiqueta mas repetida en imagebook
 */
string ImageBook::etiquetaMasRepetida() {
    string palabra_max = labels.begin()->getNombre();
    int contador = 0;
    int aux = 0;
    list<Etiqueta>::iterator i = labels.begin();
    int contadorMax = buscarImagEtiq(palabra_max).size();
    while(i != labels.end()) {
        contador = buscarImagEtiq(i->getNombre()).size();
        if(contador > contadorMax){
            palabra_max = i->getNombre();
            contadorMax = contador;
        }
        i++;
    }

    return palabra_max;
}

/**
 * @brief Busca un usuario en el imageBook
 * @param email [in] identificador a partir del cual vamos a buscar el usuario
 * @return Usuario* si encuentra el usuario o nullptr si no lo encuentra
 */
Usuario* ImageBook::buscarUsuario(const std::string email) {
    Usuario* almacen_users;
    Usuario us(email, this);
    map<string, Usuario>::iterator iterador = users.find(us.getEmail());
    if (iterador != users.end())
    return &iterador->second;
    else return nullptr;
}

/**
 * @brief Comprueba los usuarios mas activos de la red
 * @return vector <Usuario*> que contiene los usuarios más activos de la red
 * @post Guarda en un vector los usuarios más activos de la red que son aquellos que han subido más fotos
 */
vector<Usuario*> ImageBook::getMasActivos() {
    int max = 0;
    vector<Usuario*> _usuarios;
    map<string, Usuario>::iterator iterador(users.begin());
    while(iterador != users.end()){
        _usuarios.push_back(&(iterador->second));
        iterador++;
    }
    vector<Usuario*> salida;
    for(int i = 0; i < _usuarios.size(); i++){
        if(_usuarios[i]->getNumImages() > max)
            max = _usuarios[i]->getNumImages();
    }
    for(int i = 0; i < _usuarios.size(); i++){
        if(_usuarios[i]->getNumImages() == max)
            salida.push_back(_usuarios[i]);
    }
    return salida;
}
/**
 * @brief Devuelve los usuarios que hayan publicado una foto con una etiqueta dada
 * @param etiqueta [in] etiqueta con la que deben haber publicado alguna foto
 * @return vector<Usuario*> con todos los usuarios que han publicado una foto con la etiqueta
 */
vector<Usuario*> ImageBook::buscarUsuarioEtiq(const std::string etiqueta) {
    std::cout << "Entra en buscarusuarioEtiq" << std::endl;
    vector<Usuario*> usuarios, salida;
    vector<Imagen*> imgs;
    map<string, Usuario>::iterator iterador = users.begin();
    while(iterador != users.end()) {
        imgs = iterador->second.buscarEtiqueta(etiqueta);
        if (imgs.size() > 0)
            salida.push_back(&iterador->second);
        iterador++;
    }
    return salida;
}

/**
 * @brief Busca una etiqueta en el imageBook
 * @param nombre [in] nombre de la etiqueta a buscar
 * @return Etiqueta* si encuentra la etiqueta o nullptr si no la encuentra o imageBook no tiene etiquetas asignadas
 */
Etiqueta *ImageBook::buscarEtiqueta(std::string &nombre) {
    if(labels.empty())
        return nullptr;
    list<Etiqueta>::iterator iterador(labels.begin());
    while(iterador != labels.end()){
        if(iterador->getNombre()==nombre)
            return &(*iterador);
        iterador++;
    }
    return nullptr;
}

vector<Usuario *> ImageBook::buscarUsuarioFechaImagen(Fecha fecha) {
    vector<Usuario*> salida;
    map<string, Usuario>::iterator iteradorUsuarios = users.begin();
    while(iteradorUsuarios != users.end()){
        if(!(iteradorUsuarios->second.getImagenFecha(fecha).empty())) {
            salida.push_back(&(iteradorUsuarios->second));
        }
        iteradorUsuarios++;
    }
    if(!(salida.empty()))
        return salida;
    throw std::runtime_error("ImageBook::buscarUsuarioFechaImagen: No hay imagenes con esta fecha");
}

/**
 * @brief busqueda de usuarios premium (mas antiguos)
 * @return  vector Usuario*
 * @post almacena en un vector de usuarios* los usuarios que publicaron las imagenes mas antiguas y lo devuelve
 */
vector<Usuario*> ImageBook::buscaUsuariosPremium(){
    vector<Usuario*> VIP;
    map<string, Usuario>::iterator moving = users.begin();
    moving++;
    VIP.push_back(&(moving->second));
    while(moving != users.end()){
        if (moving->second.getImagenMasAntigua()->getFecha() < VIP[0]->getImagenMasAntigua()->getFecha()){
            VIP.clear();
            VIP.push_back(&(moving->second));
        }

        moving++;
    }
if(!(VIP.empty()))
    return VIP;
throw std::runtime_error("ImageBook::buscaUsuariosPremium: no se pudo localizar a los usuarios premium");


}