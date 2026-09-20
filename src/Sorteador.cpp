#include "../include/Sorteador.h"

#include <iostream>

Sorteador::Sorteador() : gerador(std::random_device{}())
{
}


void Sorteador::definirSemente(unsigned int semente)
{
    gerador.seed(semente);
}


// Rola uma quantidade de dados de 6 lados
int Sorteador::rolarDados(int quantidade)
{
    std::uniform_int_distribution<int> dado(1, 6);

    int soma = 0;

    for (int i = 0; i < quantidade; i++)
        soma += dado(gerador);

    return soma;
}


// Sorteia um número inteiro entre minimo e maximo (inclusive)
int Sorteador::rolarNumero(int minimo, int maximo)
{
    std::uniform_int_distribution<int> distribuicao(minimo, maximo);

    return distribuicao(gerador);
}


// Teste de sorte: sorteia 2d6 e compara com a SORTE atual do jogador.
// Sucesso quando o resultado e menor ou igual a SORTE.
// Cada vez que a sorte e usada, a SORTE atual diminui em 1.
bool Sorteador::testarSorte(Jogador& jogador)
{
    int rolagem = rolarDados(2);

    int sorteAtual = jogador.getSorte();

    bool sucesso =
        rolagem <= sorteAtual;

    std::cout << "Teste de sorte: "
              << rolagem
              << " contra SORTE "
              << sorteAtual
              << " -> "
              << (sucesso ? "SUCESSO" : "FALHA")
              << "\n";


    if (sorteAtual > 0)
        jogador.setSorte(sorteAtual - 1);

    std::cout << "SORTE atual: "
              << jogador.getSorte()
              << "\n";

    return sucesso;
}
