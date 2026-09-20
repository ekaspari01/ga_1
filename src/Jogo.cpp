#include "../include/Jogo.h"

#include <iostream>
#include <string>
#include "../include/CriacaoPersonagem.h"
#include "../include/GerenciadorSave.h"
#include "../include/MenuInventario.h"
#include "../include/TelaInventario.h"


// ================================================================
// CONSTRUTOR E FUNÇÕES BÁSICAS
// ================================================================

Jogo::Jogo()
    : combate(estado.jogador, sorteador, dadosJogo),
      executorEventos(estado, dadosJogo, sorteador, combate)
{
}

Jogo::~Jogo()
{
}

void Jogo::definirSemente(unsigned int semente)
{
    sorteador.definirSemente(semente);
}


// ================================================================
// NOVO JOGO / SAVE
// ================================================================

bool Jogo::iniciarNovoJogo()
{
    estado.reiniciar();

    if (!dadosJogo.carregar())
    {
        std::cout << "Nao foi possivel carregar as cenas!\n";
        return false;
    }

    // Tela do inventario: define os atributos...
    estado.arcano =
        CriacaoPersonagem::criar(estado.jogador, dadosJogo.temMagia());

    darItensIniciais();

    // ...e mostra o que o personagem leva antes de comecar a historia
    TelaInventario::mostrar(estado.jogador, dadosJogo, estado.arcano);
    TelaInventario::aguardarEnter("Pressione ENTER para iniciar a aventura...");

    estado.cenaAtual = 1;

    std::cout << "\nNovo jogo iniciado!\n";

    return true;
}


void Jogo::darItensIniciais()
{
    for (int idItem : dadosJogo.getItensIniciais())
    {
        const Item* item = dadosJogo.encontrarItem(idItem);

        if (item != nullptr)
            estado.jogador.getInventario().adicionar(*item);
    }
}


void Jogo::salvarJogo()
{
    GerenciadorSave::salvar(estado);
}


bool Jogo::carregarJogo()
{
    if (!GerenciadorSave::existe())
    {
        std::cout << "Nenhum save encontrado!\n";
        return false;
    }

    if (!dadosJogo.carregar())
    {
        std::cout << "Nao foi possivel carregar os dados!\n";
        return false;
    }

    if (!GerenciadorSave::carregar(estado, dadosJogo))
        return false;

    // Mostra o inventario e segue para a cena onde o jogador salvou
    TelaInventario::mostrar(estado.jogador, dadosJogo, estado.arcano);
    TelaInventario::aguardarEnter("Pressione ENTER para continuar a aventura...");

    return true;
}


// ================================================================
// ESCOLHA DA DECISÃO
// ================================================================

bool Jogo::escolherDecisao(Cena* cena, int& proximaCena)
{
    while (true)
    {
        std::cout << "\nEscolha "
                  << "(I = inventario, "
                  << "P = personagem, "
                  << "S = salvar, "
                  << "Q = sair): ";


        std::string entrada;

        std::cin >> entrada;


        // Sair
        if (entrada == "Q" ||
            entrada == "q")
        {
            return false;
        }


        // Inventário
        if (entrada == "I" ||
            entrada == "i")
        {
            MenuInventario::abrir(estado.jogador, dadosJogo);

            cena->mostrarDecisoes();

            continue;
        }


        // Status do personagem
        if (entrada == "P" ||
            entrada == "p")
        {
            estado.jogador.mostrarStatus();

            if (estado.arcano)
                std::cout << "Personagem ARCANO (lanca magias em combate).\n";

            cena->mostrarDecisoes();

            continue;
        }


        // Salvar
        if (entrada == "S" ||
            entrada == "s")
        {
            salvarJogo();

            cena->mostrarDecisoes();

            continue;
        }


        // Tenta transformar a entrada em número
        try
        {
            int numero =
                std::stoi(entrada);


            for (const Decisao& decisao :
                 cena->getDecisoes())
            {
                if (decisao.getNumero() == numero)
                {
                    proximaCena =
                        decisao.getProximaCena();

                    return true;
                }
            }


            std::cout << "Decisao invalida!\n";
        }
        catch (...)
        {
            std::cout << "Digite o numero da opcao "
                      << "ou I, P, S ou Q!\n";
        }
    }
}


// ================================================================
// LOOP PRINCIPAL DO JOGO
// ================================================================

void Jogo::executar()
{
    while (true)
    {
        // Verifica se o jogador morreu
        if (!estado.jogador.estaVivo())
        {
            std::cout << "\nVoce morreu... FIM DE JOGO.\n";
            break;
        }


        // Procura a cena atual
        Cena* cena =
            dadosJogo.encontrarCena(estado.cenaAtual);


        if (cena == nullptr)
        {
            std::cout << "Cena nao encontrada!\n";
            break;
        }


        // Verifica se é a primeira vez na cena
        bool primeiraVisita =
            !estado.jaVisitou(estado.cenaAtual);

        estado.registrarCenaVisitada(estado.cenaAtual);


        // Mostra o texto da cena
        cena->mostrar();

        // As cenas 14 e 17 sao finais da historia.
        // Nao devemos permitir que a opcao "#17: Encerrar aventura"
        // carregue novamente a cena 17.
        if (estado.cenaAtual == 14 || estado.cenaAtual == 17)
        {
            std::cout << "\n=================================\n";
            std::cout << "FIM DA AVENTURA\n";
            std::cout << "=================================\n";
            break;
        }


        // Executa eventos
        int proximaCena =
            executorEventos.executar(primeiraVisita);


        if (!estado.jogador.estaVivo())
            continue;


        // Evento pode mandar diretamente para outra cena
        if (proximaCena != -1)
        {
            estado.cenaAtual = proximaCena;
            continue;
        }


        // Mostra as opções
        cena->mostrarDecisoes();


        // Se não existem decisões, terminou a história
        if (cena->getDecisoes().empty())
        {
            std::cout << "\nFim da historia!\n";
            break;
        }


        // Vai para a próxima cena (ou sai do jogo)
        if (!escolherDecisao(cena, proximaCena))
            return;

        estado.cenaAtual = proximaCena;
    }
}
