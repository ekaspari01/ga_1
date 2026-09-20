#include "../include/Jogador.h"

#include <iostream>

// Definicoes das constantes (necessarias se algum codigo pegar o endereco
// delas, por exemplo com std::min/std::max)
const int Jogador::HAB_MIN;
const int Jogador::HAB_MAX;
const int Jogador::ENE_MIN;
const int Jogador::ENE_MAX;
const int Jogador::SOR_MIN;
const int Jogador::SOR_MAX;
const int Jogador::PONTOS_DISTRIBUIR;


Jogador::Jogador()
    : Personagem(),
      sorte(0),
      sorteMaxima(0)
{
}


static int limitar(int valor, int minimo, int maximo)
{
    if (valor < minimo)
        return minimo;

    if (valor > maximo)
        return maximo;

    return valor;
}


void Jogador::definirAtributos(int novaHabilidade, int novaEnergia, int novaSorte)
{
    habilidade = limitar(novaHabilidade, HAB_MIN, HAB_MAX);

    energiaMaxima = limitar(novaEnergia, ENE_MIN, ENE_MAX);
    energia = energiaMaxima;

    sorteMaxima = limitar(novaSorte, SOR_MIN, SOR_MAX);
    sorte = sorteMaxima;
}


void Jogador::mostrarStatus() const
{
    std::cout << "\n--- " << nome << " ---\n";
    std::cout << "HABILIDADE: " << habilidade << "\n";
    std::cout << "ENERGIA: " << energia << "/" << energiaMaxima << "\n";
    std::cout << "SORTE: " << sorte << "/" << sorteMaxima << "\n";
}


int Jogador::getSorte() const
{
    return sorte;
}


int Jogador::getSorteMaxima() const
{
    return sorteMaxima;
}


// Como em Personagem, nao limita pelo maximo (o save restaura em qualquer ordem)
void Jogador::setSorte(int valor)
{
    sorte = valor < 0 ? 0 : valor;
}


void Jogador::setSorteMaxima(int valor)
{
    sorteMaxima = valor < 0 ? 0 : valor;
}


void Jogador::gastarSorte()
{
    if (sorte > 0)
        sorte--;
}


Inventario& Jogador::getInventario()
{
    return inventario;
}


const Inventario& Jogador::getInventario() const
{
    return inventario;
}
