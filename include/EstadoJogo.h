#ifndef ESTADOJOGO_H
#define ESTADOJOGO_H

#include <algorithm>
#include <vector>
#include "Jogador.h"

// Tudo que muda durante uma partida (e que vai para o save).
struct EstadoJogo
{
    Jogador jogador;
    bool arcano = false;   // so arcanos lancam magias (os demais usam itens)
    int cenaAtual = 0;
    std::vector<int> cenasVisitadas;
    std::vector<int> combatesVencidos;   // cena de cada combate ja vencido


    void reiniciar()
    {
        jogador = Jogador();
        arcano = false;
        cenaAtual = 0;
        cenasVisitadas.clear();
        combatesVencidos.clear();
    }


    // Registra uma cena no histórico de cenas visitadas
    void registrarCenaVisitada(int numero)
    {
        if (!cenasVisitadas.empty() && cenasVisitadas.back() == numero)
            return;

        cenasVisitadas.push_back(numero);
    }


    bool jaVisitou(int numero) const
    {
        return std::find(cenasVisitadas.begin(),
                         cenasVisitadas.end(),
                         numero) != cenasVisitadas.end();
    }


    // Última cena visitada diferente da atual (usada na fuga).
    // Retorna -1 se não existir.
    int cenaAnterior() const
    {
        for (size_t i = cenasVisitadas.size(); i-- > 0;)
        {
            if (cenasVisitadas[i] != cenaAtual)
                return cenasVisitadas[i];
        }

        return -1;
    }


    bool venceuCombate(int cena) const
    {
        return std::find(combatesVencidos.begin(),
                         combatesVencidos.end(),
                         cena) != combatesVencidos.end();
    }


    void registrarCombateVencido(int cena)
    {
        combatesVencidos.push_back(cena);
    }
};

#endif
