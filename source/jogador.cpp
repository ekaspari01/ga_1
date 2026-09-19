#include "../include/Jogador.h"

Jogador::Jogador()
{
    nome = "";
}

Jogador::~Jogador()
{
}

void Jogador::setNome(std::string nome)
{
    this->nome = nome;
}

std::string Jogador::getNome() const
{
    return nome;
}