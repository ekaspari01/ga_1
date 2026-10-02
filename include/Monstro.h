#ifndef MONSTRO_H
#define MONSTRO_H

#include <string>
#include "Item.h"
#include "Personagem.h"

class Jogador;   // declaração antecipada: só usamos Jogador& aqui

// =====================================================================
// Monstro
//
// [HERANCA]      Filho de Personagem: herda nome, habilidade e energia.
// [POLIMORFISMO] Implementa o método virtual puro forcaDeAtaque.
// =====================================================================
class Monstro : public Personagem
{
private:
    int tesouro;       // moedas de ouro que ele solta
    int provisoes;     // provisões que ele solta
    bool temItem;      // ele solta um item?
    Item item;
    bool podeFugir;    // false = o jogador tenta fugir e não consegue

public:
    Monstro();
    Monstro(const std::string& nome, int habilidade, int energia, bool podeFugir);

    void definirSaque(int tesouro, int provisoes);
    void definirItem(const Item& novoItem);

    bool getPodeFugir() const { return podeFugir; }

    // Passa o que o monstro carrega para o jogador (quando ele é derrotado).
    void entregarSaque(Jogador& jogador) const;

    int forcaDeAtaque(int dado) const override;
};

#endif
