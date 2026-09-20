#include "../include/GerenciadorSave.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

static const std::string ARQUIVO_SAVE = "../txt/save.txt";


// Escreve uma lista de inteiros separados por | em uma linha
static void escreverLista(std::ofstream& arquivo, const std::vector<int>& lista)
{
    for (size_t i = 0; i < lista.size(); i++)
    {
        arquivo << lista[i];

        if (i + 1 < lista.size())
            arquivo << "|";
    }

    arquivo << "\n";
}


// Le uma linha "1|2|3" e devolve {1, 2, 3}
static std::vector<int> lerLista(const std::string& linha)
{
    std::vector<int> lista;

    std::stringstream ss(linha);
    std::string numero;

    while (std::getline(ss, numero, '|'))
    {
        if (!numero.empty())
            lista.push_back(std::stoi(numero));
    }

    return lista;
}


bool GerenciadorSave::existe()
{
    std::ifstream arquivo(ARQUIVO_SAVE);

    return arquivo.is_open();
}


// ================================================================
// SALVAR JOGO
// ================================================================

void GerenciadorSave::salvar(EstadoJogo& estado)
{
    std::ofstream arquivo(ARQUIVO_SAVE);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao criar save!\n";
        return;
    }

    Jogador& jogador = estado.jogador;


    // Nome
    arquivo << jogador.getNome() << "\n";


    // Cena atual
    arquivo << estado.cenaAtual << "\n";


    // Cenas visitadas
    escreverLista(arquivo, estado.cenasVisitadas);


    // Atributos
    arquivo << jogador.getHabilidade() << "|"
            << jogador.getEnergia() << "|"
            << jogador.getEnergiaMaxima() << "|"
            << jogador.getSorte() << "|"
            << jogador.getSorteMaxima()
            << "\n";


    // Inventário
    std::vector<int> idsInventario;

    for (const Item& item : jogador.getInventario().getItens())
        idsInventario.push_back(item.getId());

    escreverLista(arquivo, idsInventario);


    // Combates já vencidos
    escreverLista(arquivo, estado.combatesVencidos);


    // Personagem arcano
    arquivo << (estado.arcano ? 1 : 0) << "\n";

    std::cout << "Jogo salvo!\n";
}


// ================================================================
// CARREGAR JOGO
// ================================================================

bool GerenciadorSave::carregar(EstadoJogo& estado, const DadosJogo& dados)
{
    std::ifstream arquivo(ARQUIVO_SAVE);

    if (!arquivo.is_open())
    {
        std::cout << "Nenhum save encontrado!\n";
        return false;
    }


    std::string nome;
    std::string linhaCena;
    std::string linhaHistorico;
    std::string linhaAtributos;
    std::string linhaItens;
    std::string linhaCombates;   // saves antigos nao tem esta linha
    std::string linhaArcano;     // saves antigos nao tem esta linha

    std::getline(arquivo, nome);
    std::getline(arquivo, linhaCena);
    std::getline(arquivo, linhaHistorico);
    std::getline(arquivo, linhaAtributos);
    std::getline(arquivo, linhaItens);
    std::getline(arquivo, linhaCombates);
    std::getline(arquivo, linhaArcano);


    try
    {
        Jogador novo;

        novo.setNome(nome);


        // Cena atual
        int cena = std::stoi(linhaCena);


        // Atributos
        std::stringstream ss(linhaAtributos);

        std::string habilidade;
        std::string energia;
        std::string energiaMaxima;
        std::string sorte;
        std::string sorteMaxima;

        std::getline(ss, habilidade, '|');
        std::getline(ss, energia, '|');
        std::getline(ss, energiaMaxima, '|');
        std::getline(ss, sorte, '|');
        std::getline(ss, sorteMaxima);


        novo.setHabilidade(std::stoi(habilidade));
        novo.setEnergia(std::stoi(energia));
        novo.setEnergiaMaxima(std::stoi(energiaMaxima));
        novo.setSorte(std::stoi(sorte));
        novo.setSorteMaxima(std::stoi(sorteMaxima));


        // Histórico e combates vencidos
        std::vector<int> historico = lerLista(linhaHistorico);
        std::vector<int> vencidos = lerLista(linhaCombates);


        // Inventário
        for (int id : lerLista(linhaItens))
        {
            const Item* item = dados.encontrarItem(id);

            if (item == nullptr)
                throw std::runtime_error("Item inexistente");

            novo.getInventario().adicionar(*item);
        }


        // Só substitui o estado depois de carregar tudo
        estado.jogador = novo;
        estado.cenaAtual = cena;
        estado.cenasVisitadas = historico;
        estado.combatesVencidos = vencidos;
        estado.arcano = (linhaArcano == "1");
    }
    catch (...)
    {
        std::cout << "Save corrompido!\n";
        return false;
    }


    std::cout << "Jogo carregado!\n";

    return true;
}
