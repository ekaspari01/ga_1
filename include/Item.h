#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    std::string nome;
    char tipo;
    bool combate;
    int bonusFA;
    int dano;

public:
    Item();
    ~Item();

    Item(std::string nome, char tipo, bool combate, int bonusFA, int dano);

    void setNome(std::string nome);
    std::string getNome();

    void setTipo(char tipo);
    char getTipo();

    void setCombate(bool combate);
    bool getCombate();

    void setBonusFA(int bonusFA);
    int getBonusFA();

    void setDano(int dano);
    int getDano();

    void mostrar();
};

#endif