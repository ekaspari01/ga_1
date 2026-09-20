#include "../include/Monstro.h"

Monstro::Monstro()
    : Personagem(),
      id(0)
{
}


Monstro::Monstro(int id, std::string nome, int habilidade, int energia)
    : Personagem(nome, habilidade, energia),
      id(id)
{
}


Monstro::~Monstro()
{
}


int Monstro::getId() const
{
    return id;
}
