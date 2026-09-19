#include "../include/Jogador.h"
#include <iostream>

Jogador::Jogador() : Personagem("", HAB_MIN, ENE_MIN, SOR_MIN)
{
    energiaMaxima = ENE_MIN;
    sorteMaxima = SOR_MIN;
}

Jogador::~Jogador()
{
}

bool Jogador::definirAtributos(int habilidade, int energia, int sorte)
{
    if (habilidade < HAB_MIN || habilidade > HAB_MAX)
    {
        return false;
    }

    if (energia < ENE_MIN || energia > ENE_MAX)
    {
        return false;
    }

    if (sorte < SOR_MIN || sorte > SOR_MAX)
    {
        return false;
    }

    int gastos = (habilidade - HAB_MIN) + (energia - ENE_MIN) + (sorte - SOR_MIN);

    if (gastos != PONTOS_DISTRIBUIR)
    {
        return false;
    }

    this->habilidade = habilidade;
    this->energia = energia;
    this->sorte = sorte;
    energiaMaxima = energia;
    sorteMaxima = sorte;

    return true;
}

int Jogador::getEnergiaMaxima() const { return energiaMaxima; }
int Jogador::getSorteMaxima() const { return sorteMaxima; }
void Jogador::setEnergiaMaxima(int valor) { energiaMaxima = valor; }
void Jogador::setSorteMaxima(int valor) { sorteMaxima = valor; }

void Jogador::curar(int valor)
{
    if (valor < 0)
    {
        return;
    }

    energia += valor;

    if (energia > energiaMaxima)
    {
        energia = energiaMaxima;
    }
}

void Jogador::gastarSorte()
{
    if (sorte > 0)
    {
        sorte--;
    }
}

Inventario& Jogador::getInventario()
{
    return inventario;
}

const Inventario& Jogador::getInventario() const
{
    return inventario;
}

void Jogador::mostrarStatus() const
{
    int bonus = inventario.bonusArma();

    std::cout << std::endl;
    std::cout << "----- " << nome << " -----" << std::endl;
    std::cout << "HABILIDADE: " << habilidade;

    if (bonus > 0)
    {
        std::cout << " (+" << bonus << " da arma)";
    }

    std::cout << std::endl;
    std::cout << "ENERGIA:    " << energia << "/" << energiaMaxima << std::endl;
    std::cout << "SORTE:      " << sorte << "/" << sorteMaxima << std::endl;
    std::cout << "INVENTARIO (" << inventario.tamanho() << "/"
              << Inventario::getCapacidade() << "):" << std::endl;

    if (inventario.estaVazio())
    {
        std::cout << "  vazio" << std::endl;
    }
    else
    {
        inventario.listar();
    }
}