#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>

using namespace std;

class Personagem
{

public:
    Personagem();
    ~Personagem();

    void criarPersonagem();

    void setNome(string nome);
    string getNome();

    void setHabilidade(int habilidade);
    int getHabilidade();

    void setEnergia(int energia);
    int getEnergia();

    void setSorte(int sorte);
    int getSorte();

    void perderEnergia(int valor);
    void recuperarEnergia(int valor);

    bool testarSorte();

    void mostrarStatus();

    bool estaVivo();

private:
    string nome;
    int habilidade;
    int energia;
    int sorte;
    int sorteInicial;

};
#endif