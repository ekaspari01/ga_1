#include "../include/Cena.h"
#include <iostream>

Cena::Cena()
{
    numero = 0;
    texto = "";
}

Cena::Cena(int numero, std::string texto)
{
    this->numero = numero;
    this->texto = texto;
}

Cena::~Cena()
{
}

void Cena::setNumero(int numero)
{
    this->numero = numero;
}

void Cena::setTexto(std::string texto)
{
    this->texto = texto;
}

int Cena::getNumero() const
{
    return numero;
}

std::string Cena::getTexto() const
{
    return texto;
}

void Cena::adicionarDecisao(Decisao decisao)
{
    decisoes.push_back(decisao);
}

const std::vector<Decisao>& Cena::getDecisoes() const
{
    return decisoes;
}

void Cena::mostrar()
{
    std::cout << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "CENA " << numero << std::endl;
    std::cout << "=================================" << std::endl;

    std::cout << texto << std::endl;
}

void Cena::mostrarDecisoes()
{
    if (decisoes.empty())
    {
        std::cout << std::endl;
        std::cout << "Fim desta parte da historia." << std::endl;
        return;
    }

    std::cout << std::endl;

    for (const Decisao& decisao : decisoes)
    {
        std::cout << decisao.getNumero()
                  << " - "
                  << decisao.getTexto()
                  << std::endl;
    }
}