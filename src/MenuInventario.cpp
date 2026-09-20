#include "../include/MenuInventario.h"

#include <iostream>
#include "../include/Item.h"

bool MenuInventario::abrir(Jogador& jogador,
                           const DadosJogo& dadosJogo,
                           Monstro* alvo)
{
    Inventario& inventario =
        jogador.getInventario();


    std::cout << "\n--- INVENTARIO ("
              << inventario.tamanho()
              << "/"
              << Inventario::getCapacidade()
              << ") ---\n";


    if (inventario.estaVazio())
    {
        std::cout << "Vazio.\n";
        return false;
    }


    inventario.listar();


    std::cout << "Digite o numero do item para usar "
              << "(0 = voltar): ";


    int escolha;

    std::cin >> escolha;


    if (escolha == 0)
        return false;


    if (escolha < 1 ||
        escolha > static_cast<int>(inventario.tamanho()))
    {
        std::cout << "Item invalido!\n";
        return false;
    }


    size_t posicao =
        static_cast<size_t>(escolha - 1);


    Item item =
        inventario.getItens()[posicao];


    // ------------------------------------------------------
    // ITEM MAGICO: qualquer personagem lanca a magia do item
    // (so em combate). O item e consumido.
    // ------------------------------------------------------
    const Magia* magia =
        dadosJogo.encontrarMagiaDoItem(item.getId());

    if (magia != nullptr)
    {
        if (alvo == nullptr)
        {
            std::cout << item.getNome()
                      << " so pode ser usado em combate.\n";

            return false;
        }

        inventario.removerPorPosicao(posicao);

        alvo->receberDano(magia->dano);

        std::cout << "\nVoce usou " << item.getNome()
                  << " e lancou " << magia->nome
                  << "! " << alvo->getNome()
                  << " perdeu " << magia->dano
                  << " de energia.\n";

        return true;
    }


    bool usouItem = false;


    switch (item.getTipo())
    {
        case TipoItem::CURA:

            if (jogador.getEnergia() >=
                jogador.getEnergiaMaxima())
            {
                std::cout << "Sua energia ja esta no maximo!\n";
            }
            else
            {
                jogador.curar(item.getValor());

                inventario.removerPorPosicao(posicao);

                usouItem = true;

                std::cout << "Voce usou "
                          << item.getNome()
                          << ". Energia: "
                          << jogador.getEnergia()
                          << "/"
                          << jogador.getEnergiaMaxima()
                          << "\n";
            }

            break;


        case TipoItem::ARMA:

            std::cout << item.getNome()
                      << " e usada automaticamente nos combates.\n";

            break;


        default:

            std::cout << "Este item nao pode ser usado diretamente.\n";

            break;
    }


    return usouItem;
}
