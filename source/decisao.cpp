#include "../include/Decisao.h"

Decisao::Decisao()
{
    numero = 0;
    texto = "";
    proximaCena = 0;
}

Decisao::Decisao(int numero, std::string texto, int proximaCena)
{
    this->numero = numero;
    this->texto = texto;
    this->proximaCena = proximaCena;
}

Decisao::~Decisao()
{
}

void Decisao::setNumero(int numero)
{
    this->numero = numero;
}

void Decisao::setTexto(std::string texto)
{
    this->texto = texto;
}

void Decisao::setProximaCena(int proximaCena)
{
    this->proximaCena = proximaCena;
}

int Decisao::getNumero() const
{
    return numero;
}

std::string Decisao::getTexto() const
{
    return texto;
}

int Decisao::getProximaCena() const
{
    return proximaCena;
}