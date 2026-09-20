#include "../include/DadosJogo.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Arquivos utilizados pelo jogo
static const std::string ARQUIVO_ITENS = "../txt/item.txt";
static const std::string ARQUIVO_MONSTROS = "../txt/monstro.txt";
static const std::string ARQUIVO_MAGIAS = "../txt/magia.txt";
static const std::string ARQUIVO_EVENTOS = "../txt/evento.txt";
static const std::string ARQUIVO_INICIAL = "../txt/inicial.txt";


// Converte "3,5,7" em {3, 5, 7}. Texto vazio gera lista vazia.
static std::vector<int> lerListaIds(const std::string& texto)
{
    std::vector<int> ids;

    std::stringstream ss(texto);
    std::string parte;

    while (std::getline(ss, parte, ','))
    {
        if (parte.empty())
            continue;

        ids.push_back(std::stoi(parte));
    }

    return ids;
}


// ================================================================
// CARREGAR TODOS OS DADOS
// ================================================================

bool DadosJogo::carregar()
{
    cenas.clear();
    itens.clear();
    monstros.clear();
    magias.clear();
    eventos.clear();
    itensIniciais.clear();

    carregarCenas();

    carregarItens();
    carregarMonstros();   // depois dos itens (valida o saque)
    carregarMagias();
    carregarEventos();    // depois dos monstros
    carregarItensIniciais();   // depois dos itens

    return !cenas.empty();
}


// ================================================================
// BUSCAS E CONSULTAS
// ================================================================

// Procura uma cena pelo número
Cena* DadosJogo::encontrarCena(int numero)
{
    for (Cena& cena : cenas)
    {
        if (cena.getNumero() == numero)
            return &cena;
    }

    return nullptr;
}


// Procura um item pelo ID
const Item* DadosJogo::encontrarItem(int id) const
{
    for (const Item& item : itens)
    {
        if (item.getId() == id)
            return &item;
    }

    return nullptr;
}


// Procura um monstro pelo ID
const Monstro* DadosJogo::encontrarMonstro(int id) const
{
    for (const Monstro& monstro : monstros)
    {
        if (monstro.getId() == id)
            return &monstro;
    }

    return nullptr;
}


const std::vector<Magia>& DadosJogo::getMagias() const
{
    return magias;
}


const std::vector<Evento>& DadosJogo::getEventos() const
{
    return eventos;
}


const std::vector<int>& DadosJogo::getItensIniciais() const
{
    return itensIniciais;
}


bool DadosJogo::temMagia() const
{
    return !magias.empty();
}


const Magia* DadosJogo::encontrarMagiaDoItem(int idItem) const
{
    if (idItem <= 0)
        return nullptr;

    for (const Magia& magia : magias)
    {
        if (magia.idItem == idItem)
            return &magia;
    }

    return nullptr;
}


// ================================================================
// CARREGAMENTO DAS CENAS
// ================================================================
//
// Cada cena fica em ../txt/<numero>.txt:
//   #1                    -> numero da cena
//   #2: Texto da decisao  -> decisao que leva a cena 2
//   qualquer outra linha  -> texto da cena

void DadosJogo::carregarCenas()
{
    int numeroArquivo = 1;

    while (true)
    {
        std::string nomeArquivo = "../txt/" + std::to_string(numeroArquivo) + ".txt";

        std::ifstream arquivo(nomeArquivo);

        if (!arquivo.is_open())
        {
            break;
        }

        std::string linha;
        std::string textoCena;
        int numeroCena = numeroArquivo;

        std::vector<Decisao> decisoes;

        while (std::getline(arquivo, linha))
        {
            // Ignora linhas vazias
            if (linha.empty())
            {
                continue;
            }

            // -----------------------------------
            // LINHA DA CENA
            // Exemplo:
            // #1
            // -----------------------------------
            if (linha[0] == '#' && linha.find(':') == std::string::npos)
            {
                try
                {
                    numeroCena = std::stoi(linha.substr(1));
                }
                catch (...)
                {
                    std::cout << "Erro no numero da cena: "
                              << linha << std::endl;
                }

                continue;
            }

            // -----------------------------------
            // DECISAO
            // Exemplo:
            // #2: Caminhar pela floresta
            // -----------------------------------
            if (linha[0] == '#' && linha.find(':') != std::string::npos)
            {
                size_t posDoisPontos = linha.find(':');

                try
                {
                    // Pega o numero depois do #
                    int proximaCena =
                        std::stoi(linha.substr(1, posDoisPontos - 1));

                    // Pega o texto depois dos :
                    std::string textoDecisao =
                        linha.substr(posDoisPontos + 1);

                    // Remove espacos do inicio
                    while (!textoDecisao.empty() &&
                           textoDecisao[0] == ' ')
                    {
                        textoDecisao.erase(0, 1);
                    }

                    Decisao decisao(
                        proximaCena,
                        textoDecisao,
                        proximaCena
                    );

                    decisoes.push_back(decisao);
                }
                catch (...)
                {
                    std::cout << "Erro ao ler decisao: "
                              << linha << std::endl;
                }

                continue;
            }

            // -----------------------------------
            // TEXTO DA CENA
            // -----------------------------------
            if (!textoCena.empty())
            {
                textoCena += "\n";
            }

            textoCena += linha;
        }

        arquivo.close();

        // -----------------------------------
        // CRIA A CENA
        // -----------------------------------
        Cena novaCena(numeroCena, textoCena);

        // Adiciona todas as decisoes
        for (const Decisao& decisao : decisoes)
        {
            novaCena.adicionarDecisao(decisao);
        }

        cenas.push_back(novaCena);

        numeroArquivo++;
    }
}


// ================================================================
// CARREGAMENTO DOS ITENS
// ================================================================

void DadosJogo::carregarItens()
{
    std::ifstream arquivo(ARQUIVO_ITENS);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir " << ARQUIVO_ITENS << "!\n";
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string id;
        std::string nome;
        std::string tipo;
        std::string valor;
        std::string descricao;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, tipo, '|');
        std::getline(ss, valor, '|');
        std::getline(ss, descricao);

        try
        {
            itens.push_back(
                Item(
                    std::stoi(id),
                    nome,
                    Item::tipoDeTexto(tipo),
                    std::stoi(valor),
                    descricao
                )
            );
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em item.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DOS MONSTROS
// ================================================================
//
// Formato de cada linha de monstro.txt:
//
//   id|nome|habilidade|energia|provisoes|itens|tesouros
//
// Os tres ultimos campos sao opcionais e sao listas de IDs de
// item.txt separadas por virgula. Exemplo:
//
//   1|Orc|7|8|3|5,6|9

void DadosJogo::carregarMonstros()
{
    std::ifstream arquivo(ARQUIVO_MONSTROS);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir " << ARQUIVO_MONSTROS << "!\n";
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string id;
        std::string nome;
        std::string habilidade;
        std::string energia;
        std::string provisoes;
        std::string itensSaque;
        std::string tesouros;

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, habilidade, '|');
        std::getline(ss, energia, '|');
        std::getline(ss, provisoes, '|');
        std::getline(ss, itensSaque, '|');
        std::getline(ss, tesouros);

        try
        {
            // Mantem apenas IDs que realmente existem em item.txt
            auto filtrar = [this, &nome](const std::vector<int>& ids) -> std::vector<int>
            {
                std::vector<int> validos;

                for (int idItem : ids)
                {
                    if (encontrarItem(idItem) == nullptr)
                    {
                        std::cout << "Aviso: item " << idItem
                                  << " do saque de " << nome
                                  << " nao existe.\n";
                    }
                    else
                    {
                        validos.push_back(idItem);
                    }
                }

                return validos;
            };


            Monstro monstro(
                std::stoi(id),
                nome,
                std::stoi(habilidade),
                std::stoi(energia)
            );

            monstro.definirSaque(
                filtrar(lerListaIds(provisoes)),
                filtrar(lerListaIds(itensSaque)),
                filtrar(lerListaIds(tesouros))
            );

            monstros.push_back(monstro);
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em monstro.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DAS MAGIAS
// ================================================================
//
// Formato de cada linha de magia.txt:
//
//   nome|custo_de_energia|dano|id_do_item
//
// O ultimo campo e opcional: e o ID (de item.txt) do item que guarda a
// magia, para os personagens que nao sao arcanos.
//
// Se o arquivo nao existir, a historia e considerada SEM magia.

void DadosJogo::carregarMagias()
{
    std::ifstream arquivo(ARQUIVO_MAGIAS);

    if (!arquivo.is_open())
        return;

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string nome;
        std::string custo;
        std::string dano;
        std::string idItem;

        std::getline(ss, nome, '|');
        std::getline(ss, custo, '|');
        std::getline(ss, dano, '|');
        std::getline(ss, idItem);

        try
        {
            Magia magia;

            magia.nome = nome;
            magia.custo = std::stoi(custo);
            magia.dano = std::stoi(dano);
            magia.idItem = idItem.empty() ? 0 : std::stoi(idItem);

            if (magia.idItem > 0 &&
                encontrarItem(magia.idItem) == nullptr)
            {
                std::cout << "Aviso: item da magia " << nome
                          << " nao existe.\n";

                magia.idItem = 0;
            }

            magias.push_back(magia);
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em magia.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DOS EVENTOS
// ================================================================

void DadosJogo::carregarEventos()
{
    std::ifstream arquivo(ARQUIVO_EVENTOS);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir " << ARQUIVO_EVENTOS << "!\n";
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string cena;
        std::string tipo;
        std::string p1;
        std::string p2;

        std::getline(ss, cena, '|');
        std::getline(ss, tipo, '|');
        std::getline(ss, p1, '|');
        std::getline(ss, p2);

        try
        {
            Evento evento;

            evento.cena = std::stoi(cena);
            evento.tipo = tipo;
            evento.p1 = std::stoi(p1);
            evento.p2 = p2.empty() ? 0 : std::stoi(p2);

            if (evento.tipo == "ITEM")
            {
                if (encontrarItem(evento.p1) == nullptr)
                {
                    std::cout << "Aviso: item do evento nao existe.\n";
                    continue;
                }
            }
            else if (evento.tipo == "COMBATE")
            {
                if (encontrarMonstro(evento.p1) == nullptr)
                {
                    std::cout << "Aviso: monstro do evento nao existe.\n";
                    continue;
                }
            }
            else if (evento.tipo != "ENERGIA" &&
                     evento.tipo != "TESTESORTE")
            {
                std::cout << "Aviso: tipo de evento invalido.\n";
                continue;
            }

            eventos.push_back(evento);
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em evento.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DOS ITENS INICIAIS
// ================================================================
//
// inicial.txt (opcional): itens com que o personagem comeca o jogo.
// Um ou mais IDs de item.txt por linha, separados por virgula:
//
//   2
//   1,1
//
// Se o arquivo nao existir, o personagem comeca sem itens.

void DadosJogo::carregarItensIniciais()
{
    std::ifstream arquivo(ARQUIVO_INICIAL);

    if (!arquivo.is_open())
        return;

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        try
        {
            for (int idItem : lerListaIds(linha))
            {
                if (encontrarItem(idItem) == nullptr)
                {
                    std::cout << "Aviso: item inicial " << idItem
                              << " nao existe.\n";
                }
                else
                {
                    itensIniciais.push_back(idItem);
                }
            }
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em inicial.txt.\n";
        }
    }
}
