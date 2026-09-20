#ifndef CRIACAOPERSONAGEM_H
#define CRIACAOPERSONAGEM_H

#include "Jogador.h"

// Criacao do personagem: nome, distribuicao de pontos e (se a historia
// tiver magia) escolha entre personagem arcano ou comum.
//
// Pontos: o jogador tem Jogador::PONTOS_DISTRIBUIR pontos para dividir entre
// HABILIDADE, ENERGIA e SORTE. Cada atributo comeca no minimo
// (Jogador::HAB_MIN, ENE_MIN, SOR_MIN) e nao pode passar do maximo.
class CriacaoPersonagem
{
public:
    // Retorna true se o personagem for arcano
    // (so pergunta quando a historia possui magia).
    static bool criar(Jogador& jogador, bool historiaTemMagia);
};

#endif
