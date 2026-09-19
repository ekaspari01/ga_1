#ifndef JOGO_H
#define JOGO_H

#include <random>
#include <string>
#include <vector>
#include "Cena.h"
#include "Jogador.h"
#include "Item.h"
#include "Monstro.h"

// Um evento acontece quando o jogador entra em uma cena (linha do evento.txt):
//   ITEM        p1 = id do item
//   ENERGIA     p1 = valor (positivo cura, negativo causa dano)
//   COMBATE     p1 = id do monstro, p2 = cena se vencer
//   TESTESORTE  p1 = cena se tiver sorte, p2 = cena se tiver azar
struct Evento
{
    int cena;
    std::string tipo;
    int p1;
    int p2;
};

class Jogo
{
private:
    std::vector<Cena> cenas;
    std::vector<int> cenasVisitadas;
    std::vector<Item> itens;        // catalogo de itens (item.txt)
    std::vector<Monstro> monstros;  // catalogo de monstros (monstro.txt)
    std::vector<Evento> eventos;    // eventos das cenas (evento.txt)

    int cenaAtual;
    Jogador jogador;
    std::mt19937 gerador;

    // arquivos
    void carregarCenasArquivo();
    void carregarDecisoesArquivo();
    void carregarItensArquivo();
    void carregarMonstrosArquivo();
    void carregarEventosArquivo();
    bool carregarDadosDoJogo();

    // busca
    Cena* encontrarCena(int numero);
    const Item* encontrarItem(int id) const;
    const Monstro* encontrarMonstro(int id) const;

    // historico
    void registrarCenaVisitada(int numero);
    bool jaVisitou(int numero) const;

    // regras
    int rolarDados(int quantidade);
    void distribuirPontos();
    bool testarSorte();
    bool combater(Monstro monstro);
    int executarEventos(bool primeiraVisita);
    void menuInventario();

public:
    Jogo();
    ~Jogo();

    bool iniciarNovoJogo();
    bool carregarJogo();
    void salvarJogo();
    void executar();

    void definirSemente(unsigned int semente);   // util para testes
};

#endif