#include "../include/CriacaoPersonagem.h"

#include <algorithm>
#include <iostream>
#include <string>


// Le um inteiro entre minimo e maximo, repetindo ate o valor ser valido.
static int lerNumero(const std::string& texto, int minimo, int maximo)
{
    // Nao ha escolha possivel
    if (minimo >= maximo)
    {
        std::cout << texto << ": " << minimo << "\n";
        return minimo;
    }

    while (true)
    {
        std::cout << texto << " (" << minimo << " a " << maximo << "): ";

        int valor;

        if (std::cin >> valor && valor >= minimo && valor <= maximo)
            return valor;

        // Entrada encerrada: evita ficar preso no laco
        if (std::cin.eof())
            return minimo;

        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Valor invalido!\n";
    }
}


// ================================================================
// DISTRIBUIÇÃO DOS ATRIBUTOS
// ================================================================
//
// Exemplo com as regras do jogo (12 pontos):
//   HABILIDADE 6 a 12  -> ate 6 pontos
//   ENERGIA   12 a 24  -> ate 12 pontos
//   SORTE      6 a 12  -> ate 6 pontos
//
// O jogador escolhe HABILIDADE e ENERGIA; o que sobrar vai para SORTE.
// Os limites mostrados ja garantem que nenhum atributo passe do maximo
// e que todos os pontos sejam usados.

static void distribuirPontos(Jogador& jogador)
{
    const int total = Jogador::PONTOS_DISTRIBUIR;

    const int habMin = Jogador::HAB_MIN;
    const int eneMin = Jogador::ENE_MIN;
    const int sorMin = Jogador::SOR_MIN;

    // Quantos pontos cada atributo aceita acima do minimo
    const int maxHab = Jogador::HAB_MAX - habMin;
    const int maxEne = Jogador::ENE_MAX - eneMin;
    const int maxSor = Jogador::SOR_MAX - sorMin;


    std::cout << "\n=== INVENTARIO: DEFINICAO DOS ATRIBUTOS ===\n";

    std::cout << "Voce tem " << total << " pontos para distribuir.\n";

    std::cout << "HABILIDADE: " << habMin << " ate " << Jogador::HAB_MAX << "\n";
    std::cout << "ENERGIA: " << eneMin << " ate " << Jogador::ENE_MAX << "\n";
    std::cout << "SORTE: " << sorMin << " ate " << Jogador::SOR_MAX << "\n";


    // HABILIDADE: o que sobrar precisa caber em ENERGIA + SORTE
    int minimoHab = std::max(0, total - maxEne - maxSor);
    int maximoHab = std::min(maxHab, total);

    int habilidade = lerNumero("\nPontos em HABILIDADE", minimoHab, maximoHab);

    int restante = total - habilidade;


    // ENERGIA: o que sobrar vai para SORTE e precisa caber no limite dela
    int minimoEne = std::max(0, restante - maxSor);
    int maximoEne = std::min(maxEne, restante);

    int energia = lerNumero("Pontos em ENERGIA", minimoEne, maximoEne);

    restante -= energia;


    // Tudo que restou vai para SORTE
    int sorte = restante;

    std::cout << "Pontos em SORTE (o que sobrou): " << sorte << "\n";


    jogador.definirAtributos(
        habMin + habilidade,
        eneMin + energia,
        sorMin + sorte
    );
}


// ================================================================
// PERSONAGEM ARCANO
// ================================================================

static bool perguntarArcano()
{
    std::cout << "\nEsta historia possui magia.\n"
              << "Personagens ARCANOS lancam magias em combate.\n"
              << "Os demais so usam magias por meio de itens.\n";

    while (true)
    {
        std::string resposta;

        std::cout << "Seu personagem e arcano? (s/n): ";

        if (!(std::cin >> resposta))
            return false;

        if (resposta == "s" || resposta == "S")
            return true;

        if (resposta == "n" || resposta == "N")
            return false;

        std::cout << "Responda s ou n!\n";
    }
}


bool CriacaoPersonagem::criar(Jogador& jogador, bool historiaTemMagia)
{
    std::string nome;

    std::cout << "Digite o nome do jogador: ";

    // std::ws descarta o que sobrou da linha anterior (ex.: a opcao do menu)
    std::getline(std::cin >> std::ws, nome);

    jogador.setNome(nome);

    distribuirPontos(jogador);

    if (!historiaTemMagia)
        return false;

    return perguntarArcano();
}
