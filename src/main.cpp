// =====================================================================
// main.cpp  -  TELA DE ABERTURA
//   1 - Novo jogo       define os atributos, mostra o inventário e
//                       começa a história
//   2 - Carregar jogo   continua de onde o jogador parou
//   3 - Creditos        nomes dos programadores
//   0 - Sair
// =====================================================================

#include <cstdlib>    // srand
#include <ctime>      // time
#include <iostream>

#include "../include/Jogo.h"

static void mostrarTelaInicial()
{
    std::cout << "\n=================================\n";
    std::cout << "        JOGO DE AVENTURA\n";
    std::cout << "=================================\n";
    std::cout << "1 - Novo jogo\n";
    std::cout << "2 - Carregar jogo\n";
    std::cout << "3 - Creditos\n";
    std::cout << "0 - Sair\n";
    std::cout << "Escolha: ";
}


static void mostrarCreditos()
{
    std::cout << "\n=================================\n";
    std::cout << "CREDITOS\n";
    std::cout << "=================================\n";
    std::cout << "Programadores:\n";
    std::cout << "  - Elisandro Kaspari\n";
    
}


int main()
{
    // A semente é a hora atual: a cada partida os sorteios mudam
    srand((unsigned int)time(NULL));

    Jogo jogo;

    while (true)
    {
        mostrarTelaInicial();

        switch (lerNumero())
        {
            case 1:
                if (jogo.novoJogo())
                    jogo.jogar();
                break;

            case 2:
                if (jogo.carregarJogo())
                    jogo.jogar();
                break;

            case 3:
                mostrarCreditos();
                break;

            case 0:
                std::cout << "\nAte a proxima aventura!\n";
                return 0;

            default:
                std::cout << "\nOpcao invalida!\n";
                break;
        }
    }

    return 0;
}
