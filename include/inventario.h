#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "Item.h"
#include <vector>
#include <string>

using namespace std;

class Inventario
{
public:
    Inventario();
    ~Inventario();

    void adicionarItem(Item item);

    bool possuiItem(string nome);

    void mostrar();

    void adicionarTesouro(int quantidade);
    int getTesouro();

    void adicionarProvisao(int quantidade);
    int getProvisoes();

    bool usarProvisao(int& energia);

    vector<Item>& getItens();

private:
    vector<Item> itens;

    int tesouro;
    int provisoes;

};

#endif