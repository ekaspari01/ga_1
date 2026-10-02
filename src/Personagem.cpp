// =====================================================================
// Personagem.cpp  -  classe base de Jogador e Monstro  [HERANCA]
// =====================================================================

#include "../include/Personagem.h"

#include <cstdlib>    // rand
#include <iostream>

// Sorteia entre minimo e maximo. (O srand fica no main.)
int sortear(int minimo, int maximo)
{
    return minimo + rand() % (maximo - minimo + 1);
}


Personagem::Personagem()
    : nome(""), habilidade(0), energia(0), energiaMaxima(0)
{
}


// A energia inicial também é a energia máxima.
Personagem::Personagem(const std::string& nome, int habilidade, int energia)
    : nome(nome), habilidade(habilidade), energia(energia), energiaMaxima(energia)
{
}


Personagem::~Personagem()
{
}


std::string Personagem::getNome() const
{
    return nome;
}


int Personagem::getHabilidade() const
{
    return habilidade;
}


int Personagem::getEnergia() const
{
    return energia;
}


int Personagem::getEnergiaMaxima() const
{
    return energiaMaxima;
}


bool Personagem::estaVivo() const
{
    return energia > 0;
}


// Tira energia, sem deixar ficar negativa.
void Personagem::receberDano(int dano)
{
    if (dano <= 0)
        return;

    energia = energia - dano;

    if (energia < 0)
        energia = 0;
}


// Recupera energia, sem passar do máximo.
void Personagem::curar(int valor)
{
    if (valor <= 0)
        return;

    energia = energia + valor;

    if (energia > energiaMaxima)
        energia = energiaMaxima;
}


// [POLIMORFISMO] Versão padrão. O Jogador reescreve para mostrar a SORTE.
void Personagem::mostrarStatus() const
{
    std::cout << "\n--- " << nome << " ---\n";
    std::cout << "HABILIDADE: " << habilidade << "\n";
    std::cout << "ENERGIA: " << energia << "/" << energiaMaxima << "\n";
}
