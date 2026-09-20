#ifndef JOGO_H
#define JOGO_H

#include "Cena.h"
#include "Combate.h"
#include "DadosJogo.h"
#include "EstadoJogo.h"
#include "ExecutorEventos.h"
#include "Sorteador.h"

// Controla o fluxo do jogo. O trabalho pesado fica nas classes auxiliares:
//   DadosJogo          carrega cenas, itens, monstros, magias e eventos
//   EstadoJogo         jogador, cena atual e historico da partida
//   Sorteador          dados e teste de sorte
//   Combate            tela de combate
//   ExecutorEventos    eventos das cenas
//   GerenciadorSave    salvar e carregar
//   CriacaoPersonagem  nome e distribuicao de pontos
//   MenuInventario     usar itens
//   TelaInventario     tela que mostra equipamentos, tesouros e magias
class Jogo
{
private:
    // A ordem importa: os membros de baixo usam os de cima
    EstadoJogo estado;
    DadosJogo dadosJogo;
    Sorteador sorteador;
    Combate combate;
    ExecutorEventos executorEventos;

    // Coloca no inventario os itens de inicial.txt
    void darItensIniciais();

    // Menu de escolha da cena. Retorna false se o jogador quis sair.
    bool escolherDecisao(Cena* cena, int& proximaCena);

public:
    Jogo();
    ~Jogo();

    // O Jogo guarda referencias internas, entao nao pode ser copiado
    Jogo(const Jogo&) = delete;
    Jogo& operator=(const Jogo&) = delete;

    bool iniciarNovoJogo();
    bool carregarJogo();
    void salvarJogo();
    void executar();

    void definirSemente(unsigned int semente);   // util para testes
};

#endif
