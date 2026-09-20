#include "../include/Personagem.h"

Personagem::Personagem()
    : nome(""),
      habilidade(0),
      energia(0),
      energiaMaxima(0)
{
}


Personagem::Personagem(const std::string& nome, int habilidade, int energia)
    : nome(nome),
      habilidade(habilidade),
      energia(energia),
      energiaMaxima(energia)
{
}


Personagem::~Personagem()
{
}


const std::string& Personagem::getNome() const
{
    return nome;
}


void Personagem::setNome(const std::string& novoNome)
{
    nome = novoNome;
}


int Personagem::getHabilidade() const
{
    return habilidade;
}


void Personagem::setHabilidade(int valor)
{
    habilidade = valor < 0 ? 0 : valor;
}


int Personagem::getEnergia() const
{
    return energia;
}


int Personagem::getEnergiaMaxima() const
{
    return energiaMaxima;
}


// Os setters nao limitam pelo maximo para que o save possa restaurar
// os valores em qualquer ordem.
void Personagem::setEnergia(int valor)
{
    energia = valor < 0 ? 0 : valor;
}


void Personagem::setEnergiaMaxima(int valor)
{
    energiaMaxima = valor < 0 ? 0 : valor;
}


bool Personagem::estaVivo() const
{
    return energia > 0;
}


void Personagem::receberDano(int dano)
{
    if (dano <= 0)
        return;

    energia -= dano;

    if (energia < 0)
        energia = 0;
}


void Personagem::curar(int valor)
{
    if (valor <= 0)
        return;

    energia += valor;

    if (energia > energiaMaxima)
        energia = energiaMaxima;
}
