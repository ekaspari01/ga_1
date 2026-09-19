#include "../include/Personagem.h"

Personagem::Personagem()
{
    nome = "";
    habilidade = 0;
    energia = 0;
    sorte = 0;
}

Personagem::Personagem(std::string nome, int habilidade, int energia, int sorte)
{
    this->nome = nome;
    this->habilidade = habilidade;
    this->energia = energia;
    this->sorte = sorte;
}

Personagem::~Personagem()
{
}

void Personagem::setNome(std::string nome) { this->nome = nome; }
void Personagem::setHabilidade(int habilidade) { this->habilidade = habilidade; }
void Personagem::setEnergia(int energia) { this->energia = energia; }
void Personagem::setSorte(int sorte) { this->sorte = sorte; }

std::string Personagem::getNome() const { return nome; }
int Personagem::getHabilidade() const { return habilidade; }
int Personagem::getEnergia() const { return energia; }
int Personagem::getSorte() const { return sorte; }

bool Personagem::estaVivo() const
{
    return energia > 0;
}

void Personagem::receberDano(int dano)
{
    if (dano < 0)
    {
        dano = 0;
    }

    energia -= dano;

    if (energia < 0)
    {
        energia = 0;
    }
}