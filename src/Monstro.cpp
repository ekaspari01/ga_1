// =====================================================================
// Monstro.cpp
//
// [HERANCA]      Monstro é filho de Personagem.
// [POLIMORFISMO] Implementa forcaDeAtaque do jeito do monstro.
// =====================================================================

#include "../include/Monstro.h"

#include <iostream>
#include "../include/Jogador.h"

Monstro::Monstro()
    : Personagem(), tesouro(0), provisoes(0), temItem(false), podeFugir(true)
{
}


// [HERANCA] Chama o construtor do pai passando nome, habilidade e energia.
Monstro::Monstro(const std::string& nome, int habilidade, int energia, bool podeFugir)
    : Personagem(nome, habilidade, energia),
      tesouro(0),
      provisoes(0),
      temItem(false),
      podeFugir(podeFugir)
{
}


void Monstro::definirSaque(int novoTesouro, int novasProvisoes)
{
    tesouro = novoTesouro;
    provisoes = novasProvisoes;
}


void Monstro::definirItem(const Item& novoItem)
{
    item = novoItem;
    temItem = true;
}


// Quando o monstro morre, o que ele carregava vai para o inventário.
void Monstro::entregarSaque(Jogador& jogador) const
{
    if (tesouro == 0 && provisoes == 0 && !temItem)
    {
        std::cout << nome << " nao possuia nada de valor.\n";
        return;
    }

    if (tesouro > 0)
    {
        jogador.ganharOuro(tesouro);
        std::cout << "Voce encontrou " << tesouro << " moedas de ouro.\n";
    }

    if (provisoes > 0)
    {
        jogador.ganharProvisoes(provisoes);
        std::cout << "Voce encontrou " << provisoes << " provisao(oes).\n";
    }

    if (temItem)
    {
        if (jogador.adicionarItem(item))
            std::cout << "Voce encontrou: " << item.getNome() << "\n";
        else
            std::cout << "Inventario cheio! Voce deixou para tras: "
                      << item.getNome() << "\n";
    }
}


// [POLIMORFISMO] Versão do monstro: habilidade + dado (sem arma).
int Monstro::forcaDeAtaque(int dado) const
{
    return habilidade + dado;
}
