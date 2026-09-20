#ifndef COMBATE_H
#define COMBATE_H

#include "DadosJogo.h"
#include "Jogador.h"
#include "Monstro.h"
#include "Sorteador.h"

enum class ResultadoCombate
{
    VITORIA,
    DERROTA,
    FUGA
};


// Tela de combate.
//
// Regras:
//   FA do monstro = HABILIDADE + numero de 1 a 10
//   FA do jogador = HABILIDADE (+ bonus de arma) + numero de 1 a 10
//   Maior FA vence a rodada e tira 2 de ENERGIA do oponente.
//   Empate: ninguem acertou.
//
// Acoes: 1 Atacar | 2 Usar item | 3 Usar magia (so arcanos) | 4 Fugir
//
// Sorte: depois de um golpe (dado ou recebido) o jogador pode testar a
// sorte para aumentar o dano causado ou reduzir o dano recebido.
// Cada teste diminui a SORTE atual em 1.
class Combate
{
private:
    Jogador& jogador;
    Sorteador& sorteador;
    const DadosJogo& dadosJogo;

    void resolverRodada(Monstro& monstro, bool jogadorAtaca);
    bool menuMagia(Monstro& monstro);
    void receberSaque(const Monstro& monstro);

public:
    Combate(Jogador& jogador,
            Sorteador& sorteador,
            const DadosJogo& dadosJogo);

    // podeFugir = existe uma cena anterior para onde voltar
    // arcano    = o personagem pode lancar magias (os demais usam itens magicos)
    ResultadoCombate executar(Monstro monstro, bool podeFugir, bool arcano);
};

#endif
