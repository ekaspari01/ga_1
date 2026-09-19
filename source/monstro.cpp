#include "../include/Monstro.h"

Monstro::Monstro() : Personagem()
{
    id = 0;
}

// monstros nao testam a sorte, por isso a SORTE deles e 0
Monstro::Monstro(int id, std::string nome, int habilidade, int energia)
    : Personagem(nome, habilidade, energia, 0)
{
    this->id = id;
}

Monstro::~Monstro()
{
}

int Monstro::getId() const
{
    return id;
}