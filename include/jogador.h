#ifndef JOGADOR_H
#define JOGADOR_H

#include "Personagem.h"
#include "Inventario.h"

class Jogador : public Personagem
{
private:
    Inventario inventario;
    int energiaMaxima;   // a energia nunca passa do valor inicial
    int sorteMaxima;     // a sorte nunca passa do valor inicial

public:
    // Regras da distribuicao de pontos
    static constexpr int PONTOS_DISTRIBUIR = 12;
    static constexpr int HAB_MIN = 6;
    static constexpr int HAB_MAX = 12;
    static constexpr int ENE_MIN = 12;
    static constexpr int ENE_MAX = 24;
    static constexpr int SOR_MIN = 6;
    static constexpr int SOR_MAX = 12;

    Jogador();
    ~Jogador();

    // Define os atributos finais. Retorna false (sem alterar nada) se violar:
    //  - limites minimo/maximo de cada atributo
    //  - total de pontos gastos acima do minimo != PONTOS_DISTRIBUIR
    bool definirAtributos(int habilidade, int energia, int sorte);

    int getEnergiaMaxima() const;
    int getSorteMaxima() const;
    void setEnergiaMaxima(int valor);
    void setSorteMaxima(int valor);

    void curar(int valor);   // recupera energia ate o maximo
    void gastarSorte();      // cada teste de sorte tira 1 ponto

    Inventario& getInventario();
    const Inventario& getInventario() const;

    void mostrarStatus() const;
};

#endif