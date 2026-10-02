#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <vector>
#include "Item.h"
#include "Personagem.h"

// Quantidade máxima de itens no inventário.
const int MAX_ITENS = 10;

// =====================================================================
// Jogador
//
// [HERANCA]      "public Personagem": o Jogador é um Personagem. Herda nome,
//                habilidade e energia e acrescenta SORTE, ouro, provisões
//                e o inventário (um vector de Item).
// [POLIMORFISMO] Reescreve (override) mostrarStatus e forcaDeAtaque.
// =====================================================================
class Jogador : public Personagem
{
private:
    int sorte;
    int sorteMaxima;
    int ouro;                  // tesouro: moedas de ouro
    int provisoes;             // cada provisão recupera 4 de energia
    std::vector<Item> itens;   // inventário
    int armaEquipada;          // posição no vector (-1 = nenhuma)
    int armaduraEquipada;      // posição no vector (-1 = nenhuma)

public:
    Jogador();

    // Define os atributos no início do jogo (energia e sorte começam cheias).
    void definirAtributos(const std::string& nome, int habilidade,
                          int energia, int sorte);

    // Restaura tudo de uma vez (usado ao carregar o jogo salvo).
    void restaurar(const std::string& nome, int habilidade, int energia,
                   int energiaMaxima, int sorte, int sorteMaxima, int ouro,
                   int provisoes, int arma, int armadura);

    void mostrarStatus() const override;
    int forcaDeAtaque(int dado) const override;

    int getSorte() const { return sorte; }
    int getSorteMaxima() const { return sorteMaxima; }
    int getOuro() const { return ouro; }
    int getProvisoes() const { return provisoes; }
    int getTotalItens() const { return (int)itens.size(); }
    Item getItem(int posicao) const { return itens[posicao]; }
    int getArmaEquipada() const { return armaEquipada; }
    int getArmaduraEquipada() const { return armaduraEquipada; }

    // Bônus do que está equipado (0 se não houver nada equipado).
    int getFaArma() const;
    int getDanoArma() const;
    int getFaArmadura() const;
    int getDanoArmadura() const;

    // Teste de sorte: 2 dados <= SORTE atual = sucesso. Gasta 1 de SORTE.
    bool testarSorte();

    bool adicionarItem(const Item& item);   // false se o inventário estiver cheio
    void ganharOuro(int quantidade);
    void ganharProvisoes(int quantidade);
    bool usarProvisao();                    // true se usou de verdade
    bool equipar(int posicao);              // true se equipou

    void listarItens() const;               // lista numerada a partir de 1
    void mostrarInventario() const;         // tela de inventário completa
};

#endif
