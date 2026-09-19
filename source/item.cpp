#include "../include/Item.h"
#include <iostream>

using namespace std;

Item::Item()
{
    nome = "";
    tipo = 'c';
    combate = false;
    bonusFA = 0;
    dano = 0;
}
Item::~Item()
{

}
Item::Item(string nome, char tipo, bool combate, int bonusFA, int dano)
{
    this->nome = nome;
    this->tipo = tipo;
    this->combate = combate;
    this->bonusFA = bonusFA;
    this->dano = dano;
}

void Item::setNome(string nome)
{
    this->nome = nome;
}

string Item::getNome()
{
    return nome;
}

void Item::setTipo(char tipo)
{
    this->tipo = tipo;
}

char Item::getTipo()
{
    return tipo;
}

void Item::setCombate(bool combate)
{
    this->combate = combate;
}

bool Item::getCombate()
{
    return combate;
}

void Item::setBonusFA(int bonusFA)
{
    this->bonusFA = bonusFA;
}

int Item::getBonusFA()
{
    return bonusFA;
}

void Item::setDano(int dano)
{
    this->dano = dano;
}

int Item::getDano()
{
    return dano;
}

void Item::mostrar()
{
    cout << nome;

    if (tipo == 'w')
        cout << " [Arma]";

    else if (tipo == 'r')
        cout << " [Armadura]";

    else
        cout << " [Comum]";

    cout << endl;
}