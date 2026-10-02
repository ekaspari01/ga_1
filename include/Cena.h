#ifndef CENA_H
#define CENA_H

#include <string>
#include <vector>
#include "Decisao.h"
#include "Item.h"
#include "Jogador.h"
#include "Monstro.h"

// Uma cena da história. Cada cena é lida de um arquivo (1.txt, 2.txt...).
//
// Formato do arquivo (veja o enunciado):
//   #1                    número da cena (opcional, vale o nome do arquivo)
//   texto...              qualquer linha comum é texto da cena
//   #2: texto da opção    decisão: leva para a cena 2
//   I: nome;tipo;combate;FA;dano   item que o jogador ganha
//
// Linhas extras (todas opcionais):
//   T: 50        ganha 50 moedas de ouro
//   P: 1         ganha 1 provisão
//   V: -3        variação de energia (negativo machuca, positivo cura)
//   L: 7;8       teste de sorte: sucesso vai para a 7, falha para a 8
//
// Cena de monstro: a primeira linha é "m" e depois vêm
//   N: nome   M: S ou N (pode fugir?)   H: habilidade   E: energia
//   T / P / I: o que o monstro solta
//   12;13     cena se vencer ; cena se perder (0 = fim de jogo)
class Cena
{
private:
    int numero;
    std::string texto;
    std::vector<Decisao> decisoes;   // a cena TEM várias decisões

    // O que o jogador recebe ao entrar na cena (só na primeira vez)
    std::vector<Item> itens;
    int tesouro;
    int provisoes;
    int energia;

    // Teste de sorte (0 = a cena não tem)
    int cenaSorte;
    int cenaAzar;

    // Monstro (só vale se ehMonstro for true)
    bool ehMonstro;
    Monstro monstro;
    int cenaVitoria;
    int cenaDerrota;

    // Andamento (vai para o arquivo de save)
    bool visitada;
    bool vencida;

public:
    Cena();

    // Lê o arquivo "../txt/<numero>.txt". Retorna false se ele não existe.
    bool carregar(int numeroDaCena);

    int getNumero() const { return numero; }
    bool eMonstro() const { return ehMonstro; }
    Monstro getMonstro() const { return monstro; }
    int getCenaVitoria() const { return cenaVitoria; }
    int getCenaDerrota() const { return cenaDerrota; }
    bool temTesteSorte() const { return cenaSorte != 0; }
    int getCenaSorte() const { return cenaSorte; }
    int getCenaAzar() const { return cenaAzar; }

    bool foiVisitada() const { return visitada; }
    void setVisitada() { visitada = true; }
    bool foiVencida() const { return vencida; }
    void setVencida() { vencida = true; }

    int getTotalDecisoes() const { return (int)decisoes.size(); }
    int getProximaCena(int posicao) const { return decisoes[posicao].getProximaCena(); }

    void mostrar() const;           // texto da cena
    void mostrarDecisoes() const;   // opções numeradas 1, 2, 3...

    // Entrega ao jogador itens, ouro, provisões e variação de energia.
    void aplicarRecompensas(Jogador& jogador) const;
};

#endif
