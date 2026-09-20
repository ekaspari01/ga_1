#include "../include/Decisao.h"

Decisao::Decisao(int numero, const std::string& texto, int proximaCena)
    : numero(numero),
      texto(texto),
      proximaCena(proximaCena)
{
}


int Decisao::getNumero() const
{
    return numero;
}


const std::string& Decisao::getTexto() const
{
    return texto;
}


int Decisao::getProximaCena() const
{
    return proximaCena;
}
