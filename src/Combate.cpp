#include "../include/Combate.h"

#include <iostream>
#include <string>
#include "../include/MenuInventario.h"

// Regras do combate
static const int DANO_COMBATE = 2;   // energia que o vencedor da rodada tira do oponente
static const int DANO_FUGA = 2;      // energia perdida ao tentar fugir

// Efeito do teste de sorte no dano
static const int DANO_ACERTO_COM_SORTE = 4;   // voce acerta + sucesso: dano maior
static const int DANO_ACERTO_COM_AZAR = 1;    // voce acerta + falha: dano menor
static const int DANO_RECEBIDO_COM_SORTE = 1; // monstro acerta + sucesso: dano reduzido
static const int DANO_RECEBIDO_COM_AZAR = 3;  // monstro acerta + falha: dano maior


Combate::Combate(Jogador& jogador,
                 Sorteador& sorteador,
                 const DadosJogo& dadosJogo)
    : jogador(jogador),
      sorteador(sorteador),
      dadosJogo(dadosJogo)
{
}


// ================================================================
// RODADA
// ================================================================
//
// Sorteia as FAs e aplica o resultado de uma rodada.
// jogadorAtaca = false significa que o jogador gastou o turno com outra
// acao (item/magia): se ele vencer a rodada, nada acontece.

void Combate::resolverRodada(Monstro& monstro, bool jogadorAtaca)
{
    int bonusArma =
        jogador.getInventario().bonusArma();

    int forcaJogador =
        jogador.getHabilidade()
        + bonusArma
        + sorteador.rolarNumero(1, 10);

    int forcaMonstro =
        monstro.getHabilidade()
        + sorteador.rolarNumero(1, 10);


    std::cout << "\nSua FA: "
              << forcaJogador
              << " | FA de "
              << monstro.getNome()
              << ": "
              << forcaMonstro
              << "\n";


    // Jogador venceu a rodada
    if (forcaJogador > forcaMonstro)
    {
        if (!jogadorAtaca)
        {
            std::cout << "Voce desvia do golpe de "
                      << monstro.getNome()
                      << "!\n";
        }
        else
        {
            int dano = DANO_COMBATE;

            std::cout << "Voce acertou!\n";

            if (jogador.getSorte() > 0)
            {
                char resposta;

                std::cout << "Testar a sorte para causar mais dano? (SORTE "
                          << jogador.getSorte()
                          << ") (s/n): ";
                std::cin >> resposta;

                if (resposta == 's' ||
                    resposta == 'S')
                {
                    if (sorteador.testarSorte(jogador))
                        dano = DANO_ACERTO_COM_SORTE;
                    else
                        dano = DANO_ACERTO_COM_AZAR;
                }
            }

            monstro.receberDano(dano);

            std::cout << "Dano causado: "
                      << dano << "\n";
        }
    }


    // Monstro venceu a rodada
    else if (forcaMonstro > forcaJogador)
    {
        int dano = DANO_COMBATE;

        std::cout << monstro.getNome()
                  << " acertou voce!\n";


        if (jogador.getSorte() > 0)
        {
            char resposta;

            std::cout << "Testar a sorte para reduzir o dano? (SORTE "
                      << jogador.getSorte()
                      << ") (s/n): ";
            std::cin >> resposta;

            if (resposta == 's' ||
                resposta == 'S')
            {
                if (sorteador.testarSorte(jogador))
                    dano = DANO_RECEBIDO_COM_SORTE;
                else
                    dano = DANO_RECEBIDO_COM_AZAR;
            }
        }


        jogador.receberDano(dano);

        std::cout << "Dano recebido: "
                  << dano << "\n";
    }


    // Empate
    else
    {
        std::cout << "Empate! Ninguem acertou.\n";
    }


    std::cout << "ENERGIA -> "
              << jogador.getNome()
              << ": "
              << jogador.getEnergia()
              << "/"
              << jogador.getEnergiaMaxima()
              << " | "
              << monstro.getNome()
              << ": "
              << monstro.getEnergia()
              << "\n";
}


// ================================================================
// MAGIA
// ================================================================

// Menu de magias. Retorna true se uma magia foi lancada.
bool Combate::menuMagia(Monstro& monstro)
{
    const std::vector<Magia>& magias =
        dadosJogo.getMagias();


    std::cout << "\n--- MAGIAS ---\n";

    for (size_t i = 0; i < magias.size(); i++)
    {
        std::cout << i + 1 << " - "
                  << magias[i].nome
                  << " (custo: " << magias[i].custo
                  << " de energia | dano: " << magias[i].dano
                  << ")\n";
    }

    std::cout << "Escolha a magia (0 = voltar): ";

    int escolha;

    if (!(std::cin >> escolha))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        std::cout << "Magia invalida!\n";
        return false;
    }


    if (escolha == 0)
        return false;


    if (escolha < 1 ||
        escolha > static_cast<int>(magias.size()))
    {
        std::cout << "Magia invalida!\n";
        return false;
    }


    const Magia& magia =
        magias[static_cast<size_t>(escolha - 1)];


    // A magia nao pode matar o proprio jogador
    if (jogador.getEnergia() <= magia.custo)
    {
        std::cout << "Energia insuficiente para lancar "
                  << magia.nome << "!\n";

        return false;
    }


    jogador.receberDano(magia.custo);
    monstro.receberDano(magia.dano);

    std::cout << "\nVoce lancou " << magia.nome
              << "! " << monstro.getNome()
              << " perdeu " << magia.dano
              << " de energia (voce gastou "
              << magia.custo << ").\n";

    return true;
}


// ================================================================
// SAQUE
// ================================================================

// Transfere para o inventario as provisoes, itens e tesouros do monstro
void Combate::receberSaque(const Monstro& monstro)
{
    struct Grupo
    {
        const char* titulo;
        const std::vector<int>* ids;
    };

    const Grupo grupos[] =
    {
        { "Provisao", &monstro.getProvisoes() },
        { "Item",     &monstro.getItens()     },
        { "Tesouro",  &monstro.getTesouros()  }
    };


    bool encontrouAlgo = false;

    for (const Grupo& grupo : grupos)
    {
        for (int idItem : *grupo.ids)
        {
            const Item* item = dadosJogo.encontrarItem(idItem);

            if (item == nullptr)
                continue;

            encontrouAlgo = true;

            if (jogador.getInventario().adicionar(*item))
            {
                std::cout << grupo.titulo << " encontrado(a): "
                          << item->getNome() << "\n";
            }
            else
            {
                std::cout << "Inventario cheio! Voce deixou para tras: "
                          << item->getNome() << "\n";
            }
        }
    }


    if (!encontrouAlgo)
    {
        std::cout << monstro.getNome()
                  << " nao possuia nada de valor.\n";
    }
}


// ================================================================
// TELA DE COMBATE
// ================================================================

ResultadoCombate Combate::executar(Monstro monstro, bool podeFugir, bool arcano)
{
    // Somente personagens arcanos lancam magias diretamente.
    // Os demais usam magias por meio de itens (opcao 2).
    const bool podeLancarMagia = arcano && dadosJogo.temMagia();


    while (jogador.estaVivo() &&
           monstro.estaVivo())
    {
        // ------------------------------------------------------
        // TELA
        // ------------------------------------------------------

        int bonusArma =
            jogador.getInventario().bonusArma();

        std::cout << "\n=================================\n";
        std::cout << "COMBATE: "
                  << jogador.getNome()
                  << " x "
                  << monstro.getNome()
                  << "\n";
        std::cout << "=================================\n";

        std::cout << jogador.getNome()
                  << " -> HABILIDADE: "
                  << jogador.getHabilidade();

        if (bonusArma > 0)
            std::cout << " (+" << bonusArma << " arma)";

        std::cout << " | ENERGIA: "
                  << jogador.getEnergia()
                  << "/"
                  << jogador.getEnergiaMaxima()
                  << " | SORTE: "
                  << jogador.getSorte()
                  << "\n";

        std::cout << monstro.getNome()
                  << " -> HABILIDADE: "
                  << monstro.getHabilidade()
                  << " | ENERGIA: "
                  << monstro.getEnergia()
                  << "\n";

        std::cout << "---------------------------------\n";
        std::cout << "1 - Atacar\n";
        std::cout << "2 - Usar item\n";

        if (podeLancarMagia)
            std::cout << "3 - Usar magia\n";

        if (podeFugir)
            std::cout << "4 - Fugir (custa " << DANO_FUGA
                      << " de energia)\n";


        // ------------------------------------------------------
        // ESCOLHA DA ACAO
        // ------------------------------------------------------

        std::string entrada;

        std::cout << "Acao: ";
        std::cin >> entrada;

        int acao = 0;

        try
        {
            acao = std::stoi(entrada);
        }
        catch (...)
        {
            acao = 0;
        }


        switch (acao)
        {
            // ATACAR
            case 1:
            {
                resolverRodada(monstro, true);
                break;
            }


            // USAR ITEM
            case 2:
            {
                if (MenuInventario::abrir(jogador, dadosJogo, &monstro))
                {
                    // Item magico pode ter derrotado o monstro
                    if (monstro.estaVivo())
                        resolverRodada(monstro, false);
                }

                break;
            }


            // USAR MAGIA
            case 3:
            {
                if (!podeLancarMagia)
                {
                    std::cout << "Acao invalida!\n";
                    break;
                }

                if (menuMagia(monstro) && monstro.estaVivo())
                    resolverRodada(monstro, false);

                break;
            }


            // FUGIR
            case 4:
            {
                if (!podeFugir)
                {
                    std::cout << "Acao invalida!\n";
                    break;
                }

                std::cout << "\nVoce tenta fugir, mas "
                          << monstro.getNome()
                          << " te acerta pelas costas! (-"
                          << DANO_FUGA << " ENERGIA)\n";

                jogador.receberDano(DANO_FUGA);

                if (!jogador.estaVivo())
                    return ResultadoCombate::DERROTA;

                std::cout << "Voce escapou! ENERGIA: "
                          << jogador.getEnergia()
                          << "/"
                          << jogador.getEnergiaMaxima()
                          << "\n";

                return ResultadoCombate::FUGA;
            }


            default:
            {
                std::cout << "Acao invalida!\n";
                break;
            }
        }
    }


    // ----------------------------------------------------------
    // FIM DO COMBATE
    // ----------------------------------------------------------

    if (!jogador.estaVivo())
        return ResultadoCombate::DERROTA;


    std::cout << "\nVoce derrotou "
              << monstro.getNome()
              << "!\n";

    receberSaque(monstro);

    return ResultadoCombate::VITORIA;
}
