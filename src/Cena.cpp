#include "../include/Cena.h"

#include <iostream>

Cena::Cena(int numero, const std::string& texto)
    : numero(numero),
      texto(texto)
{
}


int Cena::getNumero() const
{
    return numero;
}


const std::string& Cena::getTexto() const
{
    return texto;
}


void Cena::adicionarDecisao(const Decisao& decisao)
{
    decisoes.push_back(decisao);
}


const std::vector<Decisao>& Cena::getDecisoes() const
{
    return decisoes;
}


void Cena::mostrar() const
{
    std::cout << "\n=== CENA " << numero << " ===\n";
    std::cout << texto << "\n";
}


void Cena::mostrarDecisoes() const
{
    std::cout << "\n";

    for (const Decisao& decisao : decisoes)
    {
        std::cout << decisao.getNumero()
                  << " - "
                  << decisao.getTexto()
                  << "\n";
    }
}
