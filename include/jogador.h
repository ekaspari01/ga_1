#ifndef JOGADOR_H
#define JOGADOR_H

#include "Inventario.h"
#include "Personagem.h"

class Jogador : public Personagem
{
private:
    int sorte;
    int sorteMaxima;
    Inventario inventario;

public:
    // Limites dos atributos e pontos para distribuir na criacao
    static const int HAB_MIN = 6;
    static const int HAB_MAX = 12;
    static const int ENE_MIN = 12;
    static const int ENE_MAX = 24;
    static const int SOR_MIN = 6;
    static const int SOR_MAX = 12;
    static const int PONTOS_DISTRIBUIR = 12;

    Jogador();

    // Define os atributos iniciais (energia e sorte maximas = valor inicial)
    void definirAtributos(int novaHabilidade, int novaEnergia, int novaSorte);

    void mostrarStatus() const;

    // SORTE
    int getSorte() const;
    int getSorteMaxima() const;
    void setSorte(int valor);
    void setSorteMaxima(int valor);

    // Cada uso da sorte reduz a SORTE atual em 1
    void gastarSorte();

    Inventario& getInventario();
    const Inventario& getInventario() const;
};

#endif
