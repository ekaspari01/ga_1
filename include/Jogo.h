#ifndef JOGO_H
#define JOGO_H

#include <string>
#include <vector>
#include "Cena.h"
#include "Jogador.h"
#include "Monstro.h"

// Como um combate terminou
enum Resultado
{
    VITORIA,
    DERROTA,
    FUGA
};

// Controla o fluxo do jogo: criação do personagem, tela padrão (cenas),
// tela de inventário, tela de batalha e salvar/carregar.
class Jogo
{
private:
    std::vector<Cena> cenas;   // todas as cenas, lidas dos arquivos
    Jogador jogador;
    int cenaAtual;
    int cenaAnterior;          // 0 = ainda não há (usada na fuga)

    bool carregarCenas();
    Cena* buscarCena(int numero);   // [PONTEIRO] nullptr se não existir

    void criarPersonagem();
    void telaInventario();
    bool trocarEquipamento();

    void rodada(Monstro& inimigo, bool jogadorAtaca);
    Resultado combate(Monstro& inimigo, bool podeFugir);

    int escolherDecisao(Cena* cena);   // -1 = o jogador quis sair
    void salvarJogo();

public:
    Jogo();

    bool novoJogo();
    bool carregarJogo();
    void jogar();
};

// Funções de leitura do teclado (usadas também pelo main)
std::string lerLinha();
int lerNumero();    // -1 se o jogador não digitou um número

#endif
