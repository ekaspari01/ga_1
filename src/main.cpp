#include <iostream>
#include <string>
/*
cd src
g++ Cena.cpp Combate.cpp CriacaoPersonagem.cpp DadosJogo.cpp Decisao.cpp ExecutorEventos.cpp GerenciadorSave.cpp Inventario.cpp Item.cpp Jogador.cpp Jogo.cpp main.cpp MenuInventario.cpp Monstro.cpp Personagem.cpp Sorteador.cpp TelaInventario.cpp -o programa.exe
./programa.exe 
*/
#include "../include/Jogo.h"

// ================================================================
// TELA INICIAL
//
//   1 - Novo jogo     define os atributos, mostra o inventario e
//                     comeca a historia
//   2 - Carregar jogo le o save, mostra o inventario e continua
//                     de onde o jogador parou
//   0 - Sair
// ================================================================

static void mostrarTelaInicial()
{
    std::cout << "\n=================================\n";
    std::cout << "        JOGO DE AVENTURA\n";
    std::cout << "=================================\n";
    std::cout << "1 - Novo jogo\n";
    std::cout << "2 - Carregar jogo\n";
    std::cout << "0 - Sair\n";
    std::cout << "Escolha: ";
}


int main()
{
    Jogo jogo;

    while (true)
    {
        mostrarTelaInicial();

        std::string opcao;

        // Fim da entrada (Ctrl+D / Ctrl+Z)
        if (!(std::cin >> opcao))
            break;


        // ----------------------------------------------------
        // NOVO JOGO
        // ----------------------------------------------------
        if (opcao == "1")
        {
            if (jogo.iniciarNovoJogo())
                jogo.executar();
        }


        // ----------------------------------------------------
        // CARREGAR JOGO
        // ----------------------------------------------------
        else if (opcao == "2")
        {
            if (jogo.carregarJogo())
                jogo.executar();
        }


        // ----------------------------------------------------
        // SAIR
        // ----------------------------------------------------
        else if (opcao == "0")
        {
            std::cout << "\nAte a proxima aventura!\n";
            break;
        }


        else
        {
            std::cout << "\nOpcao invalida!\n";
        }
    }

    return 0;
}