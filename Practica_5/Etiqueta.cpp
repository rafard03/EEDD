//
// Created by Rafa on 20/10/2022.
//

#include "Etiqueta.h"
Etiqueta::Etiqueta() {}

Etiqueta::Etiqueta(const std::string &_nombre): nombre(_nombre) {}

Etiqueta::Etiqueta(const Etiqueta &orig): nombre(orig.nombre) {}

std::string Etiqueta::getNombre() {return nombre;}

void Etiqueta::setNombre(const std::string &_nombre) {nombre = _nombre;}

Etiqueta::~Etiqueta() {}

bool Etiqueta::operator==(Etiqueta &orig) {return this->getNombre() == orig.getNombre();}