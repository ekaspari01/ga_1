/*
g++ cena.cpp decisao.cpp inventario.cpp item.cpp jogador.cpp jogo.cpp main.cpp monstro.cpp personagem.cpp -o programa.exe
./programa.exe
*/
#include "../include/Jogo.h"
#include <iostream>

using namespace std;

void telaAbertura()
{
    Jogo jogo;

    int opcao;

    do
    {
        cout << endl;
        cout << "=================================" << endl;
        cout << "          AVENTURA RPG           " << endl;
        cout << "=================================" << endl;
        cout << endl;

        cout << "1 - Novo jogo" << endl;
        cout << "2 - Carregar jogo" << endl;
        cout << "3 - Exibir creditos" << endl;
        cout << "4 - Encerrar aplicacao" << endl;

        cout << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao)
        {
            case 1:
                jogo.iniciarNovoJogo();
                jogo.executar();
                break;

            case 2:
                jogo.carregarJogo();
                jogo.executar();
                break;

            case 3:
                cout << endl;
                cout << "=================================" << endl;
                cout << "             CREDITOS            " << endl;
                cout << "=================================" << endl;
                cout << endl;
                cout << "Programadores:" << endl;
                cout << "Elisandro Kaspari" << endl;
                // cout << "Nome do segundo programador" << endl;
                cout << endl;
                break;

            case 4:
                cout << endl;
                cout << "Encerrando aplicacao..." << endl;
                break;

            default:
                cout << endl;
                cout << "Opcao invalida!" << endl;
                break;
        }

    } while (opcao != 4);
}

int main()
{
    telaAbertura();

    return 0;
}