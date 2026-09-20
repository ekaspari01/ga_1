#ifndef SORTEADOR_H
#define SORTEADOR_H

#include <random>
#include "Jogador.h"

// Tudo que envolve sorteio: dados e teste de sorte.
class Sorteador
{
private:
    std::mt19937 gerador;

public:
    Sorteador();

    void definirSemente(unsigned int semente);   // util para testes

    int rolarDados(int quantidade);              // soma de dados de 6 lados
    int rolarNumero(int minimo, int maximo);     // inteiro entre minimo e maximo
    bool testarSorte(Jogador& jogador);          // 2d6 <= SORTE; gasta 1 ponto de SORTE
};

#endif
