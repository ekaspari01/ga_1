/*
g++ cena.cpp decisao.cpp inventario.cpp item.cpp jogador.cpp jogo.cpp main.cpp monstro.cpp personagem.cpp -o programa.exe
./programa.exe
*/
#include "../include/Jogo.h"
#include <iostream>
#include <string>

int main()
{
    Jogo jogo;

    while (true)
    {
        std::cout << std::endl;
        std::cout << "=== AVENTURA ===" << std::endl;
        std::cout << "1 - Novo jogo" << std::endl;
        std::cout << "2 - Carregar jogo" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "Opcao: ";

        std::string opcao;

        if (!std::getline(std::cin >> std::ws, opcao))
        {
            break;
        }

        if (opcao == "1")
        {
            if (jogo.iniciarNovoJogo())
            {
                jogo.executar();
            }
        }
        else if (opcao == "2")
        {
            if (jogo.carregarJogo())
            {
                jogo.executar();
            }
        }
        else if (opcao == "0")
        {
            break;
        }
        else
        {
            std::cout << "Opcao invalida!" << std::endl;
        }
    }

    std::cout << "Ate a proxima!" << std::endl;
    return 0;
}