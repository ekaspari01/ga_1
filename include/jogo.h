#ifndef JOGO_H
#define JOGO_H

#include <vector>
#include <string>

#include "Cena.h"
#include "Jogador.h"

class Jogo
{
private:
    std::vector<Cena> cenas;
    std::vector<int> cenasVisitadas;

    Jogador jogador;

    int cenaAtual;

    void carregarCenasArquivo();
    void carregarDecisoesArquivo();

    Cena* encontrarCena(int numero);
    void registrarCenaVisitada(int numero);

public:
    Jogo();
    ~Jogo();

    void iniciarNovoJogo();
    void carregarJogo();

    void executar();

    void salvarJogo();
};

#endif