#include "../include/Jogo.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Arquivos utilizados pelo jogo
static const std::string ARQUIVO_CENAS = "../txt/cena.txt";
static const std::string ARQUIVO_DECISOES = "../txt/decisao.txt";
static const std::string ARQUIVO_ITENS = "../txt/item.txt";
static const std::string ARQUIVO_MONSTROS = "../txt/monstro.txt";
static const std::string ARQUIVO_EVENTOS = "../txt/evento.txt";
static const std::string ARQUIVO_SAVE = "../txt/save.txt";


// ================================================================
// CONSTRUTOR E FUNÇÕES BÁSICAS
// ================================================================

Jogo::Jogo() : gerador(std::random_device{}())
{
    cenaAtual = 0;
}

Jogo::~Jogo()
{
}

void Jogo::definirSemente(unsigned int semente)
{
    gerador.seed(semente);
}


// Registra uma cena no histórico de cenas visitadas
void Jogo::registrarCenaVisitada(int numero)
{
    if (!cenasVisitadas.empty() && cenasVisitadas.back() == numero)
        return;

    cenasVisitadas.push_back(numero);
}


// Verifica se determinada cena já foi visitada
bool Jogo::jaVisitou(int numero) const
{
    return std::find(
        cenasVisitadas.begin(),
        cenasVisitadas.end(),
        numero
    ) != cenasVisitadas.end();
}


// Procura uma cena pelo número
Cena* Jogo::encontrarCena(int numero)
{
    for (Cena& cena : cenas)
    {
        if (cena.getNumero() == numero)
            return &cena;
    }

    return nullptr;
}


// Procura um item pelo ID
const Item* Jogo::encontrarItem(int id) const
{
    for (const Item& item : itens)
    {
        if (item.getId() == id)
            return &item;
    }

    return nullptr;
}


// Procura um monstro pelo ID
const Monstro* Jogo::encontrarMonstro(int id) const
{
    for (const Monstro& monstro : monstros)
    {
        if (monstro.getId() == id)
            return &monstro;
    }

    return nullptr;
}


// ================================================================
// DADOS ALEATÓRIOS
// ================================================================

// Rola uma quantidade de dados de 6 lados
int Jogo::rolarDados(int quantidade)
{
    std::uniform_int_distribution<int> dado(1, 6);

    int soma = 0;

    for (int i = 0; i < quantidade; i++)
        soma += dado(gerador);

    return soma;
}


// ================================================================
// CARREGAMENTO DAS CENAS
// ================================================================

void Jogo::carregarCenasArquivo()
{
    std::ifstream arquivo(ARQUIVO_CENAS);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir " << ARQUIVO_CENAS << "!\n";
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string numero;
        std::string texto;

        std::getline(ss, numero, '|');
        std::getline(ss, texto);

        try
        {
            cenas.push_back(
                Cena(std::stoi(numero), texto)
            );
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em cena.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DAS DECISÕES
// ================================================================

void Jogo::carregarDecisoesArquivo()
{
    std::ifstream arquivo(ARQUIVO_DECISOES);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir " << ARQUIVO_DECISOES << "!\n";
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.empty() || linha[0] == '#')
            continue;

        std::stringstream ss(linha);

        std::string cenaTexto;
        std::string numeroTexto;
        std::string texto;
        std::string proximaCenaTexto;

        std::getline(ss, cenaTexto, '|');
        std::getline(ss, numeroTexto, '|');
        std::getline(ss, texto, '|');
        std::getline(ss, proximaCenaTexto);

        try
        {
            int numeroCena = std::stoi(cenaTexto);
            int numeroDecisao = std::stoi(numeroTexto);
            int proximaCena = std::stoi(proximaCenaTexto);

            Cena* cena = encontrarCena(numeroCena);

            if (cena == nullptr)
            {
                std::cout << "Aviso: cena da decisao nao existe.\n";
                continue;
            }

            cena->adicionarDecisao(
                Decisao(
                    numeroDecisao,
                    texto,
                    proximaCena
                )
            );
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em decisao.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DOS ITENS
// ================================================================

void Jogo::carregarItensArquivo()
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

void Jogo::carregarMonstrosArquivo()
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

        std::getline(ss, id, '|');
        std::getline(ss, nome, '|');
        std::getline(ss, habilidade, '|');
        std::getline(ss, energia);

        try
        {
            monstros.push_back(
                Monstro(
                    std::stoi(id),
                    nome,
                    std::stoi(habilidade),
                    std::stoi(energia)
                )
            );
        }
        catch (...)
        {
            std::cout << "Aviso: linha invalida em monstro.txt.\n";
        }
    }
}


// ================================================================
// CARREGAMENTO DOS EVENTOS
// ================================================================

void Jogo::carregarEventosArquivo()
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
// CARREGAR TODOS OS DADOS
// ================================================================

bool Jogo::carregarDadosDoJogo()
{
    cenas.clear();
    itens.clear();
    monstros.clear();
    eventos.clear();

    carregarCenasArquivo();
    carregarDecisoesArquivo();
    carregarItensArquivo();
    carregarMonstrosArquivo();
    carregarEventosArquivo();

    return !cenas.empty();
}


// ================================================================
// DISTRIBUIÇÃO DOS ATRIBUTOS
// ================================================================

void Jogo::distribuirPontos()
{
    std::cout << "\n=== DISTRIBUICAO DE PONTOS ===\n";

    std::cout << "HABILIDADE: "
              << Jogador::HAB_MIN
              << " ate "
              << Jogador::HAB_MAX << "\n";

    std::cout << "ENERGIA: "
              << Jogador::ENE_MIN
              << " ate "
              << Jogador::ENE_MAX << "\n";

    std::cout << "SORTE: "
              << Jogador::SOR_MIN
              << " ate "
              << Jogador::SOR_MAX << "\n";

    int pontos = Jogador::PONTOS_DISTRIBUIR;

    int habilidade;

    do
    {
        std::cout << "\nPontos em HABILIDADE (0 a "
                  << pontos << "): ";

        std::cin >> habilidade;

        if (habilidade < 0 || habilidade > pontos)
            std::cout << "Valor invalido!\n";

    } while (habilidade < 0 || habilidade > pontos);


    pontos -= habilidade;


    int energia;

    int energiaMaxima =
        Jogador::ENE_MAX - Jogador::ENE_MIN;

    if (pontos > energiaMaxima)
        energiaMaxima = pontos;

    do
    {
        std::cout << "Pontos em ENERGIA (0 a "
                  << pontos << "): ";

        std::cin >> energia;

        if (energia < 0 || energia > pontos)
            std::cout << "Valor invalido!\n";

    } while (energia < 0 || energia > pontos);


    pontos -= energia;


    // Tudo que restou vai para SORTE
    int sorte = pontos;

    jogador.definirAtributos(
        Jogador::HAB_MIN + habilidade,
        Jogador::ENE_MIN + energia,
        Jogador::SOR_MIN + sorte
    );

    jogador.mostrarStatus();
}


// ================================================================
// NOVO JOGO
// ================================================================

bool Jogo::iniciarNovoJogo()
{
    jogador = Jogador();

    cenasVisitadas.clear();
    cenaAtual = 0;

    if (!carregarDadosDoJogo())
    {
        std::cout << "Nao foi possivel carregar as cenas!\n";
        return false;
    }

    std::string nome;

    std::cout << "Digite o nome do jogador: ";

    std::cin.ignore();
    std::getline(std::cin, nome);

    jogador.setNome(nome);

    distribuirPontos();

    cenaAtual = 1;

    std::cout << "\nNovo jogo iniciado!\n";

    return true;
}


// ================================================================
// SALVAR JOGO
// ================================================================

void Jogo::salvarJogo()
{
    std::ofstream arquivo(ARQUIVO_SAVE);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao criar save!\n";
        return;
    }


    // Nome
    arquivo << jogador.getNome() << "\n";


    // Cena atual
    arquivo << cenaAtual << "\n";


    // Cenas visitadas
    for (size_t i = 0; i < cenasVisitadas.size(); i++)
    {
        arquivo << cenasVisitadas[i];

        if (i + 1 < cenasVisitadas.size())
            arquivo << "|";
    }

    arquivo << "\n";


    // Atributos
    arquivo << jogador.getHabilidade() << "|"
            << jogador.getEnergia() << "|"
            << jogador.getEnergiaMaxima() << "|"
            << jogador.getSorte() << "|"
            << jogador.getSorteMaxima()
            << "\n";


    // Inventário
    const std::vector<Item>& inventario =
        jogador.getInventario().getItens();

    for (size_t i = 0; i < inventario.size(); i++)
    {
        arquivo << inventario[i].getId();

        if (i + 1 < inventario.size())
            arquivo << "|";
    }

    arquivo << "\n";

    std::cout << "Jogo salvo!\n";
}


// ================================================================
// CARREGAR JOGO
// ================================================================

bool Jogo::carregarJogo()
{
    std::ifstream arquivo(ARQUIVO_SAVE);

    if (!arquivo.is_open())
    {
        std::cout << "Nenhum save encontrado!\n";
        return false;
    }


    if (!carregarDadosDoJogo())
    {
        std::cout << "Nao foi possivel carregar os dados!\n";
        return false;
    }


    std::string nome;
    std::string linhaCena;
    std::string linhaHistorico;
    std::string linhaAtributos;
    std::string linhaItens;

    std::getline(arquivo, nome);
    std::getline(arquivo, linhaCena);
    std::getline(arquivo, linhaHistorico);
    std::getline(arquivo, linhaAtributos);
    std::getline(arquivo, linhaItens);


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


        // Histórico
        std::vector<int> historico;

        ss.clear();
        ss.str(linhaHistorico);

        std::string numero;

        while (std::getline(ss, numero, '|'))
        {
            if (!numero.empty())
                historico.push_back(std::stoi(numero));
        }


        // Inventário
        ss.clear();
        ss.str(linhaItens);

        std::string id;

        while (std::getline(ss, id, '|'))
        {
            if (id.empty())
                continue;

            const Item* item =
                encontrarItem(std::stoi(id));

            if (item == nullptr)
                throw std::runtime_error("Item inexistente");

            novo.getInventario().adicionar(*item);
        }


        // Só substitui o jogador depois de carregar tudo
        jogador = novo;
        cenaAtual = cena;
        cenasVisitadas = historico;
    }
    catch (...)
    {
        std::cout << "Save corrompido!\n";
        return false;
    }


    std::cout << "Jogo carregado!\n";

    return true;
}


// ================================================================
// TESTE DE SORTE
// ================================================================

bool Jogo::testarSorte()
{
    int rolagem = rolarDados(2);

    bool sucesso =
        rolagem <= jogador.getSorte();

    std::cout << "Teste de sorte: "
              << rolagem
              << " contra SORTE "
              << jogador.getSorte()
              << "\n";


    jogador.gastarSorte();

    return sucesso;
}


// ================================================================
// COMBATE
// ================================================================

bool Jogo::combater(Monstro monstro)
{
    std::cout << "\n=================================\n";
    std::cout << "COMBATE: "
              << jogador.getNome()
              << " x "
              << monstro.getNome()
              << "\n";

    std::cout << "HABILIDADE: "
              << monstro.getHabilidade()
              << " | ENERGIA: "
              << monstro.getEnergia()
              << "\n";

    std::cout << "=================================\n";


    int bonusArma =
        jogador.getInventario().bonusArma();


    while (jogador.estaVivo() &&
           monstro.estaVivo())
    {
        int forcaJogador =
            jogador.getHabilidade()
            + bonusArma
            + rolarDados(2);

        int forcaMonstro =
            monstro.getHabilidade()
            + rolarDados(2);


        std::cout << "\nSua forca: "
                  << forcaJogador
                  << " | Forca do monstro: "
                  << forcaMonstro
                  << "\n";


        // Jogador venceu
        if (forcaJogador > forcaMonstro)
        {
            int dano = 2;

            std::cout << "Voce acertou!\n";

            if (jogador.getSorte() > 0)
            {
                char resposta;

                std::cout << "Testar a sorte para causar mais dano? (s/n): ";
                std::cin >> resposta;

                if (resposta == 's' ||
                    resposta == 'S')
                {
                    if (testarSorte())
                        dano = 4;
                    else
                        dano = 1;
                }
            }

            monstro.receberDano(dano);

            std::cout << "Dano causado: "
                      << dano << "\n";
        }


        // Monstro venceu
        else if (forcaMonstro > forcaJogador)
        {
            int dano = 2;

            std::cout << monstro.getNome()
                      << " acertou voce!\n";


            if (jogador.getSorte() > 0)
            {
                char resposta;

                std::cout << "Testar a sorte para reduzir o dano? (s/n): ";
                std::cin >> resposta;

                if (resposta == 's' ||
                    resposta == 'S')
                {
                    if (testarSorte())
                        dano = 1;
                    else
                        dano = 3;
                }
            }


            jogador.receberDano(dano);

            std::cout << "Dano recebido: "
                      << dano << "\n";
        }


        // Empate
        else
        {
            std::cout << "Empate! Ninguem sofreu dano.\n";
        }


        std::cout << "ENERGIA -> "
                  << jogador.getNome()
                  << ": "
                  << jogador.getEnergia()
                  << " | "
                  << monstro.getNome()
                  << ": "
                  << monstro.getEnergia()
                  << "\n";
    }


    if (jogador.estaVivo())
    {
        std::cout << "\nVoce derrotou "
                  << monstro.getNome()
                  << "!\n";
    }


    return jogador.estaVivo();
}


// ================================================================
// INVENTÁRIO
// ================================================================

void Jogo::menuInventario()
{
    Inventario& inventario =
        jogador.getInventario();


    std::cout << "\n--- INVENTARIO ("
              << inventario.tamanho()
              << "/"
              << Inventario::getCapacidade()
              << ") ---\n";


    if (inventario.estaVazio())
    {
        std::cout << "Vazio.\n";
        return;
    }


    inventario.listar();


    std::cout << "Digite o numero do item para usar "
              << "(0 = voltar): ";


    int escolha;

    std::cin >> escolha;


    if (escolha == 0)
        return;


    if (escolha < 1 ||
        escolha > static_cast<int>(inventario.tamanho()))
    {
        std::cout << "Item invalido!\n";
        return;
    }


    size_t posicao =
        static_cast<size_t>(escolha - 1);


    Item item =
        inventario.getItens()[posicao];


    switch (item.getTipo())
    {
        case TipoItem::CURA:

            if (jogador.getEnergia() >=
                jogador.getEnergiaMaxima())
            {
                std::cout << "Sua energia ja esta no maximo!\n";
            }
            else
            {
                jogador.curar(item.getValor());

                inventario.removerPorPosicao(posicao);

                std::cout << "Voce usou "
                          << item.getNome()
                          << ". Energia: "
                          << jogador.getEnergia()
                          << "/"
                          << jogador.getEnergiaMaxima()
                          << "\n";
            }

            break;


        case TipoItem::ARMA:

            std::cout << item.getNome()
                      << " e usada automaticamente nos combates.\n";

            break;


        default:

            std::cout << "Este item nao pode ser usado diretamente.\n";

            break;
    }
}


// ================================================================
// EVENTOS
// ================================================================

int Jogo::executarEventos(bool primeiraVisita)
{
    for (const Evento& evento : eventos)
    {
        if (evento.cena != cenaAtual)
            continue;


        // --------------------------------------------------------
        // ITEM
        // --------------------------------------------------------

        if (evento.tipo == "ITEM")
        {
            if (!primeiraVisita)
                continue;


            const Item* item =
                encontrarItem(evento.p1);


            if (jogador.getInventario().adicionar(*item))
            {
                std::cout << "\nVoce pegou: "
                          << item->getNome()
                          << "\n";
            }
            else
            {
                std::cout << "\nInventario cheio!\n";
            }
        }


        // --------------------------------------------------------
        // ENERGIA
        // --------------------------------------------------------

        else if (evento.tipo == "ENERGIA")
        {
            if (!primeiraVisita)
                continue;


            if (evento.p1 >= 0)
            {
                jogador.curar(evento.p1);

                std::cout << "\nVoce recuperou "
                          << evento.p1
                          << " de energia.\n";
            }
            else
            {
                jogador.receberDano(-evento.p1);

                std::cout << "\nVoce perdeu "
                          << -evento.p1
                          << " de energia.\n";
            }


            std::cout << "ENERGIA: "
                      << jogador.getEnergia()
                      << "/"
                      << jogador.getEnergiaMaxima()
                      << "\n";


            if (!jogador.estaVivo())
                return -1;
        }


        // --------------------------------------------------------
        // COMBATE
        // --------------------------------------------------------

        else if (evento.tipo == "COMBATE")
        {
            if (!primeiraVisita)
                return evento.p2;


            const Monstro* monstro =
                encontrarMonstro(evento.p1);


            if (!combater(*monstro))
                return -1;


            return evento.p2;
        }


        // --------------------------------------------------------
        // TESTE DE SORTE
        // --------------------------------------------------------

        else if (evento.tipo == "TESTESORTE")
        {
            std::cout << "\nTeste de sorte!\n";

            if (testarSorte())
                return evento.p1;

            return evento.p2;
        }
    }


    return -1;
}


// ================================================================
// LOOP PRINCIPAL DO JOGO
// ================================================================

void Jogo::executar()
{
    while (true)
    {
        // Verifica se o jogador morreu
        if (!jogador.estaVivo())
        {
            std::cout << "\nVoce morreu... FIM DE JOGO.\n";
            break;
        }


        // Procura a cena atual
        Cena* cena =
            encontrarCena(cenaAtual);


        if (cena == nullptr)
        {
            std::cout << "Cena nao encontrada!\n";
            break;
        }


        // Verifica se é a primeira vez na cena
        bool primeiraVisita =
            !jaVisitou(cenaAtual);

        registrarCenaVisitada(cenaAtual);


        // Mostra o texto da cena
        cena->mostrar();


        // Executa eventos
        int proximaCena =
            executarEventos(primeiraVisita);


        if (!jogador.estaVivo())
            continue;


        // Evento pode mandar diretamente para outra cena
        if (proximaCena != -1)
        {
            cenaAtual = proximaCena;
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


        bool escolheu = false;
        int escolhida = 0;


        while (!escolheu)
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
                return;
            }


            // Inventário
            if (entrada == "I" ||
                entrada == "i")
            {
                menuInventario();

                cena->mostrarDecisoes();

                continue;
            }


            // Status do personagem
            if (entrada == "P" ||
                entrada == "p")
            {
                jogador.mostrarStatus();

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
                        escolhida =
                            decisao.getProximaCena();

                        escolheu = true;

                        break;
                    }
                }


                if (!escolheu)
                    std::cout << "Decisao invalida!\n";
            }
            catch (...)
            {
                std::cout << "Digite o numero da opcao "
                          << "ou I, P, S ou Q!\n";
            }
        }


        // Vai para a próxima cena
        cenaAtual = escolhida;
    }
}