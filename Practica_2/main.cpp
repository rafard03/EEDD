#include <iostream>
#include "ImageBook.h"

int main() {
    int opt = 0;
    try {
        ImageBook imageBook;
        ListaDEnlazada<Imagen> listaComida;
        ListaDEnlazada<Imagen> listaPlaya;
        ListaDEnlazada<Imagen> listaResultante;

    do {
        std::cout << "============MENU===============" << std::endl;
        std::cout << "1.Devolver y mostrar todas aquellas imagenes con la etiqueta 'playa' y 'comida' " << std::endl;
        std::cout << "2.Unir ambas listas resultantes en una lista con 'concatenar' comprobando con operator+  " << std::endl;
        std::cout << "3.Devolver cual es la etiqueta mas repetida usando el procedimiento anterior " << std::endl;
        std::cout << "4.Buscar el id 616564861 en la lista enlazada " << std::endl;  //leer pdf
        std::cout << "0. Salir " << std::endl;

        cin >> opt;

        switch (opt) {

            case 1 : {

                std::cout << "IMAGENES DE PLAYA" << std::endl;
                for (int i = 0; i < imageBook.tamImagenes(); i++) {
                    if (imageBook[i].getEtiqueta()->getNombre() == "playa") {
                        imageBook[i].mostrar();
                        listaPlaya.insertaFin(imageBook[i]);
                    }
                }
                std::cout << "IMAGENES DE COMIDA" << std::endl;
                for (int i = 0; i < imageBook.tamImagenes(); i++) {
                    if (imageBook[i].getEtiqueta()->getNombre() == "comida") {
                        imageBook[i].mostrar();
                        listaComida.insertaFin(imageBook[i]);
                    }
                }
                break;
            }
            case 2: {
                ListaDEnlazada<Imagen>* listaConcatena;
                listaConcatena = new ListaDEnlazada<Imagen>(listaComida.concatena(listaPlaya));
                listaResultante = listaPlaya + listaComida;
                if (listaResultante.tam() == listaConcatena->tam())
                    std::cout << "Las dos listas son iguales " << std::endl;
                else std::cout << "Listas distintas" << std::endl;;
                delete listaConcatena;
                break;
            }

            case 3: {
                int contador = 0;
                int contadorSalida = 0;
                int pos = 0;
                //Inicio de condiciones
                clock_t t_ini = clock();
                std::string masRepetida = imageBook.getLabels().inicio().getNombre();
                ListaDEnlazada<Etiqueta>::Iterador iteratorEtiquetas = imageBook.getLabels().iterador();
                ListaDEnlazada<Imagen>* lista1;
                while (!iteratorEtiquetas.end()) {
                    lista1 = new ListaDEnlazada<Imagen>(imageBook.buscarImagEtiq(iteratorEtiquetas.dato().getNombre()));
                    if(lista1->tam() > contadorSalida){
                        masRepetida = iteratorEtiquetas.dato().getNombre();
                        contadorSalida = lista1->tam();
                    }
                }
                delete lista1;
                std::cout << "La etiqueta mas repetida es " << masRepetida << " y se encuentra en " << contadorSalida
                          << " imagenes" << std::endl;
                std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
                break;
            }

            case 4 : {


                Imagen imagen("616564861");

                ListaDEnlazada<Imagen>::Iterador i = listaPlaya.busca(imagen);
                i.dato().mostrar();

                break;
            }


        }




    }while(opt != 0);


    }catch(const std::runtime_error &re){
        std::cerr << re.what();
    }catch(const std::out_of_range &our){
        std::cerr << our.what();
    }catch(std::bad_alloc &ba){
        std::cerr << ba.what();
    }
    return 0;
}
