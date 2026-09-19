#include "../include/inventario.h"

#include <iostream>

using namespace std;

Inventario::Inventario()
{
    tesouro = 0;
    provisoes = 0;
}
Inventario::~Inventario()
{
    
}
void Inventario::adicionarItem(Item item)
{
    itens.push_back(item);

    cout << endl;
    cout << "Item adquirido: " << item.getNome() << endl;
}

bool Inventario::possuiItem(string nome)
{
    for (Item& item : itens)
    {
        if (item.getNome() == nome)
            return true;
    }

    return false;
}

void Inventario::mostrar()
{
    cout << endl;
    cout << "================================" << endl;
    cout << "           INVENTARIO" << endl;
    cout << "================================" << endl;

    cout << endl;
    cout << "ITENS:" << endl;

    if (itens.empty())
    {
        cout << "Nenhum item." << endl;
    }
    else
    {
        for (int i = 0; i < (int)itens.size(); i++)
        {
            cout << i + 1 << " - ";
            itens[i].mostrar();
        }
    }

    cout << endl;
    cout << "Tesouro:   " << tesouro << " moedas" << endl;
    cout << "Provisoes: " << provisoes << endl;

    cout << "================================" << endl;
}

void Inventario::adicionarTesouro(int quantidade)
{
    tesouro += quantidade;
}

int Inventario::getTesouro()
{
    return tesouro;
}

void Inventario::adicionarProvisao(int quantidade)
{
    provisoes += quantidade;
}

int Inventario::getProvisoes()
{
    return provisoes;
}

bool Inventario::usarProvisao(int& energia)
{
    if (provisoes <= 0)
    {
        cout << "Voce nao possui provisoes." << endl;
        return false;
    }

    provisoes--;

    energia += 4;

    cout << "Voce utilizou uma provisao." << endl;
    cout << "Energia recuperada: +4" << endl;

    return true;
}

vector<Item>& Inventario::getItens()
{
    return itens;
}