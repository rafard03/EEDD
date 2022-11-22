//
// Created by Rafa on 20/10/2022.
//

#include "ImageBook.h"
ImageBook::ImageBook():images(10000), labels(){
    //Leer etiquetas
    std::ifstream is;
    std::string fila;

    is.open("../etiquetas.txt");
    clock_t t_ini = clock();
    if(is.good()){
        while(getline(is, fila)){
            if(fila != ""){
                Etiqueta etiq(fila);
                labels.insertaFin(etiq);
                fila = "";
            }
        }
        is.close();
    }else{
        throw std::runtime_error("Fallo al abrir el archivo etiquetas.txt");
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
    Etiqueta* etiqueta;

    is.open("../imagenes_v1.csv");
    if(is.good()){
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

                getline(columnas, etiq, ',');
                ListaDEnlazada<Etiqueta>::Iterador iterator = labels.iterador();
                for(int i = 0; i < labels.tam(); i++){
                    if(iterator.dato().getNombre() == etiq) {
                        etiqueta = &(iterator.dato());
                        break;
                    }
                    iterator.next();
                }

                fila = "";
                columnas.clear();

                Imagen img(id, email, nombre, tam, Fecha(dia, mes, anno), etiqueta);
                try{
                    images.inserta(img);
                }catch(const std::out_of_range &our){
                    throw our;
                }catch(const std::bad_alloc &ba){
                    throw ba;
                }
            }
        }
        is.close();
    }else {
        throw std::runtime_error("Fallo al abrir el archivo imagenes_v1.csv");
    }
    std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}

ImageBook::~ImageBook() {

}

ListaDEnlazada<Imagen> ImageBook::buscarImagEtiq(const std::string &etiqueta) {
    if(etiqueta == "")
        throw std::invalid_argument("ImageBook::buscarImagEtiq: Etiqueta invalida");
    ListaDEnlazada<Imagen> lista;
    Etiqueta etiq(etiqueta);
    for(int i = 0; i < images.tamlog(); i++){
        if(images[i].getEtiqueta()->getNombre() == etiqueta) {
            lista.insertaFin(images[i]);
        }
    }
    return lista;
}

int ImageBook::tamImagenes() {
    return images.tamlog();
}

Imagen &ImageBook::operator[](int pos) {
    return images[pos];
}

int ImageBook::tamEtiquetas() {
    return labels.tam();
}

ListaDEnlazada<Etiqueta> ImageBook::getLabels() {
    return labels;
}