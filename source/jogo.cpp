#include "../include/Jogo.h"

#include <iostream>
#include <fstream>
#include <sstream>

Jogo::Jogo()
{
    cenaAtual = 0;
}

Jogo::~Jogo()
{
}
void Jogo::registrarCenaVisitada(int numero)
{
    cenasVisitadas.push_back(numero);
}

void Jogo::carregarCenasArquivo()
{
    std::ifstream arquivo("../txt/cena.txt");

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir cena.txt!" << std::endl;
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
        {
            continue;
        }

        std::stringstream ss(linha);

        std::string numeroTexto;
        std::string texto;

        std::getline(ss, numeroTexto, '|');
        std::getline(ss, texto);

        int numero = std::stoi(numeroTexto);

        Cena cena(numero, texto);

        cenas.push_back(cena);
    }

    arquivo.close();
}
void Jogo::carregarDecisoesArquivo()
{
    std::ifstream arquivo("../txt/decisao.txt");

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir decisao.txt!" << std::endl;
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty())
        {
            continue;
        }

        std::stringstream ss(linha);

        std::string cenaTexto;
        std::string decisaoTexto;
        std::string texto;
        std::string proximaCenaTexto;

        std::getline(ss, cenaTexto, '|');
        std::getline(ss, decisaoTexto, '|');
        std::getline(ss, texto, '|');
        std::getline(ss, proximaCenaTexto);

        int numeroCena = std::stoi(cenaTexto);
        int numeroDecisao = std::stoi(decisaoTexto);
        int proximaCena = std::stoi(proximaCenaTexto);

        Cena* cena = encontrarCena(numeroCena);

        if (cena != nullptr)
        {
            Decisao decisao(
                numeroDecisao,
                texto,
                proximaCena
            );

            cena->adicionarDecisao(decisao);
        }
    }

    arquivo.close();
}
Cena* Jogo::encontrarCena(int numero)
{
    for (Cena& cena : cenas)
    {
        if (cena.getNumero() == numero)
        {
            return &cena;
        }
    }

    return nullptr;
}

void Jogo::iniciarNovoJogo()
{
    cenas.clear();
    cenasVisitadas.clear();

    cenaAtual = 1;

    std::cout << "Digite o nome do jogador: ";

    std::string nome;
    std::getline(std::cin >> std::ws, nome);

    jogador.setNome(nome);

    carregarCenasArquivo();
    carregarDecisoesArquivo();

    std::cout << std::endl;
    std::cout << "Novo jogo iniciado!" << std::endl;
}

void Jogo::carregarJogo()
{
    std::ifstream arquivo("../txt/save.txt");

    if (!arquivo.is_open())
    {
        std::cout << "Nenhum save encontrado!" << std::endl;
        return;
    }

    cenas.clear();
    cenasVisitadas.clear();

    carregarCenasArquivo();
    carregarDecisoesArquivo();

    std::string linha;

    std::getline(arquivo, linha);
    jogador.setNome(linha);

    std::getline(arquivo, linha);
    cenaAtual = std::stoi(linha);

    std::getline(arquivo, linha);

    std::stringstream ss(linha);
    std::string numero;

    while (std::getline(ss, numero, '|'))
    {
        if (!numero.empty())
        {
            cenasVisitadas.push_back(std::stoi(numero));
        }
    }

    arquivo.close();

    std::cout << "Jogo carregado!" << std::endl;
}
void Jogo::salvarJogo()
{
    std::ofstream arquivo("../txt/save.txt");

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao criar save!" << std::endl;
        return;
    }

    arquivo << jogador.getNome() << std::endl;

    arquivo << cenaAtual << std::endl;

    for (int i = 0; i < cenasVisitadas.size(); i++)
    {
        arquivo << cenasVisitadas[i];

        if (i < cenasVisitadas.size() - 1)
        {
            arquivo << "|";
        }
    }

    arquivo << std::endl;

    arquivo.close();

    std::cout << "Jogo salvo!" << std::endl;
}
void Jogo::executar()
{
    while (true)
    {
        Cena* cena = encontrarCena(cenaAtual);

        if (cena == nullptr)
        {
            std::cout << "Cena nao encontrada!" << std::endl;
            break;
        }

        registrarCenaVisitada(cenaAtual);

        cena->mostrar();
        cena->mostrarDecisoes();

        // Se a cena nao possui decisoes, termina a historia
        if (cena->getDecisoes().empty())
        {
            std::cout << std::endl;
            std::cout << "Fim da historia!" << std::endl;
            break;
        }

        std::cout << std::endl;
        std::cout << "Escolha: ";

        int escolha;
        std::cin >> escolha;

        bool encontrada = false;

        for (const Decisao& decisao : cena->getDecisoes())
        {
            if (decisao.getNumero() == escolha)
            {
                cenaAtual = decisao.getProximaCena();
                encontrada = true;
                break;
            }
        }

        if (!encontrada)
        {
            std::cout << "Decisao invalida!" << std::endl;
        }
    }
}