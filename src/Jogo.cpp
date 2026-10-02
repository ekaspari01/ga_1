// =====================================================================
// Jogo.cpp
//
// Fluxo do jogo: criação do personagem, tela padrão (cenas), tela de
// inventário, tela de batalha e salvar/carregar.
//
// [PONTEIRO]      Cena* (cena atual) e Personagem* (combate).
// [POLIMORFISMO]  No combate, Jogador e Monstro são tratados como
//                 Personagem*: a mesma chamada roda a versão de cada um.
// [ARQUIVO]       Cenas e save são arquivos de texto lidos com vector.
// =====================================================================

#include "../include/Jogo.h"

#include <cstdlib>    // atoi, exit
#include <fstream>    // ifstream / ofstream
#include <iostream>
#include <sstream>

static const std::string ARQUIVO_SAVE = "../txt/save.txt";

// Regras da criação do personagem (12 pontos para distribuir)
static const int PONTOS_DISTRIBUIR = 12;
static const int HAB_MIN = 6;
static const int HAB_MAX = 12;
static const int ENE_MIN = 12;
static const int ENE_MAX = 24;
static const int SOR_MIN = 6;
static const int SOR_MAX = 12;

// Regras do combate
static const int DANO_COMBATE = 2;   // energia que o vencedor da rodada tira
static const int DANO_FUGA = 2;      // energia perdida ao fugir


// ---------------------------------------------------------------------
// LEITURA DO TECLADO
// Sempre lemos a linha inteira com getline: assim sobra nada no buffer.
// ---------------------------------------------------------------------
std::string lerLinha()
{
    std::string linha;

    // Se a entrada acabar (Ctrl+D / Ctrl+Z), encerra o programa
    if (!std::getline(std::cin, linha))
    {
        std::cout << "\nEntrada encerrada.\n";
        exit(0);
    }

    return linha;
}


// Lê um número. Devolve -1 se estiver vazio ou tiver algo que não é dígito.
int lerNumero()
{
    std::string linha = lerLinha();

    if (linha.empty() || linha.size() > 6)
        return -1;

    for (int i = 0; i < (int)linha.size(); i++)
    {
        if (linha[i] < '0' || linha[i] > '9')
            return -1;
    }

    return atoi(linha.c_str());
}


// Pergunta s/n.
static bool lerSim()
{
    std::string linha = lerLinha();

    return !linha.empty() && (linha[0] == 's' || linha[0] == 'S');
}


// Pede um número entre minimo e maximo, repetindo até o jogador acertar.
static int lerEntre(const std::string& texto, int minimo, int maximo)
{
    while (true)
    {
        std::cout << texto << " (" << minimo << " a " << maximo << "): ";

        int valor = lerNumero();

        if (valor >= minimo && valor <= maximo)
            return valor;

        std::cout << "Valor invalido!\n";
    }
}


Jogo::Jogo()
    : cenaAtual(0), cenaAnterior(0)
{
}


// ---------------------------------------------------------------------
// CENAS  [ARQUIVO]
// Lê 1.txt, 2.txt, 3.txt... até um arquivo não existir.
// ---------------------------------------------------------------------
bool Jogo::carregarCenas()
{
    cenas.clear();

    int numero = 1;

    while (true)
    {
        Cena nova;

        if (!nova.carregar(numero))
            break;

        cenas.push_back(nova);
        numero++;
    }

    return !cenas.empty();
}


// [PONTEIRO] Devolve o ENDEREÇO da cena (&cenas[i]) ou nullptr se não achou.
Cena* Jogo::buscarCena(int numero)
{
    for (int i = 0; i < (int)cenas.size(); i++)
    {
        if (cenas[i].getNumero() == numero)
            return &cenas[i];
    }

    return nullptr;
}


// ---------------------------------------------------------------------
// CRIAÇÃO DO PERSONAGEM
// 12 pontos para dividir. Cada atributo começa no mínimo e recebe extras:
//   HABILIDADE 6 a 12 (até 6 extras)
//   ENERGIA   12 a 24 (até 12 extras)
//   SORTE      6 a 12 (até 6 extras)
// O jogador escolhe HABILIDADE e ENERGIA; o que sobrar vai para SORTE.
// ---------------------------------------------------------------------
void Jogo::criarPersonagem()
{
    int maxHab = HAB_MAX - HAB_MIN;
    int maxEne = ENE_MAX - ENE_MIN;
    int maxSor = SOR_MAX - SOR_MIN;

    std::cout << "\n=== INVENTARIO: DEFINICAO DOS ATRIBUTOS ===\n";
    std::cout << "Digite o nome do jogador: ";

    std::string nome = lerLinha();

    if (nome.empty())
        nome = "Aventureiro";

    std::cout << "\nVoce tem " << PONTOS_DISTRIBUIR << " pontos para distribuir.\n";
    std::cout << "HABILIDADE: " << HAB_MIN << " ate " << HAB_MAX << "\n";
    std::cout << "ENERGIA: " << ENE_MIN << " ate " << ENE_MAX << "\n";
    std::cout << "SORTE: " << SOR_MIN << " ate " << SOR_MAX << "\n\n";

    // HABILIDADE: o que sobrar precisa caber em ENERGIA + SORTE
    int minimo = PONTOS_DISTRIBUIR - maxEne - maxSor;
    if (minimo < 0)
        minimo = 0;

    int maximo = (maxHab < PONTOS_DISTRIBUIR) ? maxHab : PONTOS_DISTRIBUIR;
    int extraHab = lerEntre("Pontos em HABILIDADE", minimo, maximo);

    int restante = PONTOS_DISTRIBUIR - extraHab;

    // ENERGIA: o que sobrar vai para SORTE e precisa caber no limite dela
    minimo = restante - maxSor;
    if (minimo < 0)
        minimo = 0;

    maximo = (maxEne < restante) ? maxEne : restante;
    int extraEne = lerEntre("Pontos em ENERGIA", minimo, maximo);

    int extraSor = restante - extraEne;
    std::cout << "Pontos em SORTE (o que sobrou): " << extraSor << "\n";

    jogador.definirAtributos(nome, HAB_MIN + extraHab, ENE_MIN + extraEne,
                             SOR_MIN + extraSor);
}


// ---------------------------------------------------------------------
// NOVO JOGO
// ---------------------------------------------------------------------
bool Jogo::novoJogo()
{
    if (!carregarCenas())
    {
        std::cout << "Nao foi possivel carregar as cenas!\n";
        return false;
    }

    jogador = Jogador();   // jogador novo, sem nada do jogo anterior

    criarPersonagem();

    // Equipamento inicial: uma espada curta e uma provisão
    jogador.adicionarItem(Item("Espada Curta", 'w', true, 1, 0));
    jogador.ganharProvisoes(1);

    // Tela de inventário antes de começar a história
    jogador.mostrarInventario();
    std::cout << "\nPressione ENTER para iniciar a aventura...";
    lerLinha();

    cenaAtual = 1;
    cenaAnterior = 0;

    return true;
}


// ---------------------------------------------------------------------
// SALVAR  [ARQUIVO]
// Formato (uma informação por linha):
//   nome
//   hab ene eneMax sorte sorteMax ouro provisoes arma armadura
//   cenaAtual cenaAnterior
//   quantidade de itens
//   um item por linha (nome;tipo;combate;FA;dano)
//   cenas visitadas  (números separados por espaço)
//   cenas com monstro vencido
// ---------------------------------------------------------------------
void Jogo::salvarJogo()
{
    std::ofstream arquivo(ARQUIVO_SAVE.c_str());

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao criar o save!\n";
        return;
    }

    arquivo << jogador.getNome() << "\n";

    arquivo << jogador.getHabilidade() << " "
            << jogador.getEnergia() << " "
            << jogador.getEnergiaMaxima() << " "
            << jogador.getSorte() << " "
            << jogador.getSorteMaxima() << " "
            << jogador.getOuro() << " "
            << jogador.getProvisoes() << " "
            << jogador.getArmaEquipada() << " "
            << jogador.getArmaduraEquipada() << "\n";

    arquivo << cenaAtual << " " << cenaAnterior << "\n";

    arquivo << jogador.getTotalItens() << "\n";

    for (int i = 0; i < jogador.getTotalItens(); i++)
        arquivo << jogador.getItem(i).paraTexto() << "\n";

    for (int i = 0; i < (int)cenas.size(); i++)
    {
        if (cenas[i].foiVisitada())
            arquivo << cenas[i].getNumero() << " ";
    }
    arquivo << "\n";

    for (int i = 0; i < (int)cenas.size(); i++)
    {
        if (cenas[i].foiVencida())
            arquivo << cenas[i].getNumero() << " ";
    }
    arquivo << "\n";

    std::cout << "[Jogo salvo]\n";
}


// ---------------------------------------------------------------------
// CARREGAR  [ARQUIVO]
// O jogador novo é montado à parte e só substitui o atual se o save
// inteiro estiver correto.
// ---------------------------------------------------------------------
bool Jogo::carregarJogo()
{
    std::ifstream arquivo(ARQUIVO_SAVE.c_str());

    if (!arquivo.is_open())
    {
        std::cout << "Nenhum save encontrado!\n";
        return false;
    }

    if (!carregarCenas())
    {
        std::cout << "Nao foi possivel carregar as cenas!\n";
        return false;
    }

    std::string nome, linhaAtributos, linhaCenas, linhaTotal;

    std::getline(arquivo, nome);
    std::getline(arquivo, linhaAtributos);
    std::getline(arquivo, linhaCenas);
    std::getline(arquivo, linhaTotal);

    // Atributos: "hab ene eneMax sorte sorteMax ouro provisoes arma armadura"
    int hab, ene, eneMax, sorte, sorteMax, ouro, provisoes, arma, armadura;
    std::stringstream atributos(linhaAtributos);
    atributos >> hab >> ene >> eneMax >> sorte >> sorteMax
              >> ouro >> provisoes >> arma >> armadura;

    // Cenas: "cenaAtual cenaAnterior"
    int atual, anterior;
    std::stringstream cenasSalvas(linhaCenas);
    cenasSalvas >> atual >> anterior;

    if (!arquivo || atributos.fail() || cenasSalvas.fail())
    {
        std::cout << "Save corrompido!\n";
        return false;
    }

    // Inventário: lê um item por linha
    Jogador novo;
    int total = atoi(linhaTotal.c_str());

    for (int i = 0; i < total; i++)
    {
        std::string linhaItem;
        Item item;

        std::getline(arquivo, linhaItem);

        if (!item.lerDeTexto(linhaItem))
        {
            std::cout << "Save corrompido!\n";
            return false;
        }

        novo.adicionarItem(item);
    }

    novo.restaurar(nome, hab, ene, eneMax, sorte, sorteMax,
                   ouro, provisoes, arma, armadura);

    // Cenas visitadas e monstros vencidos
    std::string linhaVisitadas, linhaVencidas;
    std::getline(arquivo, linhaVisitadas);
    std::getline(arquivo, linhaVencidas);

    if (buscarCena(atual) == nullptr)
    {
        std::cout << "Save corrompido!\n";
        return false;
    }

    // Tudo certo: agora sim substitui o estado do jogo
    jogador = novo;
    cenaAtual = atual;
    cenaAnterior = anterior;

    int numero;

    std::stringstream visitadas(linhaVisitadas);
    while (visitadas >> numero)
    {
        Cena* cena = buscarCena(numero);

        if (cena != nullptr)
            cena->setVisitada();
    }

    std::stringstream vencidas(linhaVencidas);
    while (vencidas >> numero)
    {
        Cena* cena = buscarCena(numero);

        if (cena != nullptr)
            cena->setVencida();
    }

    std::cout << "Jogo carregado!\n";

    jogador.mostrarInventario();
    std::cout << "\nPressione ENTER para continuar a aventura...";
    lerLinha();

    return true;
}


// ---------------------------------------------------------------------
// TELA DE INVENTÁRIO
// Mostra tudo e deixa o jogador comer uma provisão ou trocar o equipamento.
// ---------------------------------------------------------------------
void Jogo::telaInventario()
{
    bool voltar = false;

    while (!voltar)
    {
        jogador.mostrarInventario();

        std::cout << "\n1 - Comer uma provisao\n";
        std::cout << "2 - Equipar arma ou armadura\n";
        std::cout << "0 - Voltar\n";
        std::cout << "Escolha: ";

        switch (lerNumero())
        {
            case 1:
                jogador.usarProvisao();
                break;

            case 2:
                trocarEquipamento();
                break;

            case 0:
                voltar = true;
                break;

            default:
                std::cout << "Opcao invalida!\n";
                break;
        }
    }
}


// Lista os itens e equipa o escolhido. Retorna true se equipou.
bool Jogo::trocarEquipamento()
{
    if (jogador.getTotalItens() == 0)
    {
        std::cout << "Voce nao tem itens.\n";
        return false;
    }

    std::cout << "\n";
    jogador.listarItens();

    std::cout << "Numero do item para equipar (0 = voltar): ";

    int escolha = lerNumero();

    if (escolha <= 0)
        return false;

    // O jogador digita a partir de 1, mas o vector começa em 0
    return jogador.equipar(escolha - 1);
}


// ---------------------------------------------------------------------
// TELA DE BATALHA
// FA (Força de Ataque) = HABILIDADE (+ bônus) + número de 1 a 10.
// Quem tiver a maior FA vence a rodada e tira 2 de ENERGIA do oponente.
// Empate: ninguém acertou.
// jogadorAtaca = false: o jogador gastou o turno (trocou de item ou tentou
// fugir), então só o monstro pode acertar.
// ---------------------------------------------------------------------
void Jogo::rodada(Monstro& inimigo, bool jogadorAtaca)
{
    // [POLIMORFISMO] Array de ponteiros do tipo da classe PAI.
    // Cada um calcula a FA do seu jeito (Jogador usa a arma, Monstro não).
    Personagem* lutadores[2] = { &jogador, &inimigo };
    int forca[2];

    for (int i = 0; i < 2; i++)
        forca[i] = lutadores[i]->forcaDeAtaque(sortear(1, 10));

    // A armadura do jogador altera a FA do oponente
    forca[1] = forca[1] + jogador.getFaArmadura();

    std::cout << "\nSua FA: " << forca[0] << " | FA de "
              << inimigo.getNome() << ": " << forca[1] << "\n";

    if (forca[0] > forca[1])
    {
        // ---- Jogador venceu a rodada ----
        if (!jogadorAtaca)
        {
            std::cout << "Voce desvia do golpe de " << inimigo.getNome() << "!\n";
        }
        else
        {
            int dano = DANO_COMBATE;

            std::cout << "Voce acertou!\n";

            if (jogador.getSorte() > 0)
            {
                std::cout << "Testar a sorte para causar mais dano? (SORTE "
                          << jogador.getSorte() << ") (s/n): ";

                if (lerSim())
                {
                    if (jogador.testarSorte())
                        dano = 4;    // sorte: dano maior
                    else
                        dano = 1;    // azar: dano menor
                }
            }

            // Bônus de dano da arma equipada
            dano = dano + jogador.getDanoArma();

            if (dano < 0)
                dano = 0;

            inimigo.receberDano(dano);

            std::cout << "Dano causado: " << dano << "\n";
        }
    }
    else if (forca[1] > forca[0])
    {
        // ---- Monstro venceu a rodada ----
        int dano = DANO_COMBATE;

        std::cout << inimigo.getNome() << " acertou voce!\n";

        if (jogador.getSorte() > 0)
        {
            std::cout << "Testar a sorte para reduzir o dano? (SORTE "
                      << jogador.getSorte() << ") (s/n): ";

            if (lerSim())
            {
                if (jogador.testarSorte())
                    dano = 1;    // sorte: dano menor
                else
                    dano = 3;    // azar: dano maior
            }
        }

        // A armadura equipada diminui o dano recebido
        dano = dano - jogador.getDanoArmadura();

        if (dano < 0)
            dano = 0;

        jogador.receberDano(dano);

        std::cout << "Dano recebido: " << dano << "\n";
    }
    else
    {
        // ---- Empate ----
        std::cout << "Empate! Ninguem acertou.\n";
    }

    std::cout << "ENERGIA -> " << jogador.getNome() << ": "
              << jogador.getEnergia() << "/" << jogador.getEnergiaMaxima()
              << " | " << inimigo.getNome() << ": " << inimigo.getEnergia() << "\n";
}


Resultado Jogo::combate(Monstro& inimigo, bool podeFugir)
{
    bool fugiu = false;

    // [POLIMORFISMO] mostrarStatus virtual: cada um mostra o seu
    Personagem* lutadores[2] = { &jogador, &inimigo };

    while (jogador.estaVivo() && inimigo.estaVivo() && !fugiu)
    {
        std::cout << "\n=================================\n";
        std::cout << "COMBATE: " << jogador.getNome() << " x " << inimigo.getNome() << "\n";
        std::cout << "=================================\n";

        for (int i = 0; i < 2; i++)
            lutadores[i]->mostrarStatus();

        std::cout << "---------------------------------\n";
        std::cout << "1 - Atacar\n";
        std::cout << "2 - Usar item (trocar arma ou armadura)\n";
        std::cout << "3 - Fugir (custa " << DANO_FUGA << " de energia)\n";
        std::cout << "Acao: ";

        switch (lerNumero())
        {
            case 1:
                rodada(inimigo, true);
                break;

            case 2:
                // Trocar de equipamento gasta o turno
                if (trocarEquipamento())
                    rodada(inimigo, false);
                break;

            case 3:
                if (!podeFugir)
                {
                    // Monstro que não deixa fugir
                    std::cout << "\nVoce tenta fugir, mas "
                              << inimigo.getNome() << " bloqueia o caminho!\n";
                    rodada(inimigo, false);
                }
                else
                {
                    std::cout << "\nVoce tenta fugir, mas " << inimigo.getNome()
                              << " te acerta pelas costas! (-" << DANO_FUGA << " ENERGIA)\n";

                    jogador.receberDano(DANO_FUGA);

                    if (jogador.estaVivo())
                    {
                        std::cout << "Voce escapou!\n";
                        fugiu = true;
                    }
                }
                break;

            default:
                std::cout << "Acao invalida!\n";
                break;
        }
    }

    if (!jogador.estaVivo())
        return DERROTA;

    if (fugiu)
        return FUGA;

    std::cout << "\nVoce derrotou " << inimigo.getNome() << "!\n";

    return VITORIA;
}


// ---------------------------------------------------------------------
// ESCOLHA DA DECISÃO
// Lê o número da opção, ou I (inventário), P (personagem) ou Q (sair).
// Devolve o número da próxima cena, ou -1 se o jogador quis sair.
// ---------------------------------------------------------------------
int Jogo::escolherDecisao(Cena* cena)
{
    while (true)
    {
        std::cout << "\nEscolha (I = inventario, P = personagem, Q = sair): ";

        std::string entrada = lerLinha();

        // Comando de uma letra só
        if (entrada.size() == 1)
        {
            switch (entrada[0])
            {
                case 'Q':
                case 'q':
                    return -1;

                case 'I':
                case 'i':
                    telaInventario();
                    cena->mostrarDecisoes();
                    continue;

                case 'P':
                case 'p':
                    jogador.mostrarStatus();
                    cena->mostrarDecisoes();
                    continue;

                default:
                    break;
            }
        }

        // Não é comando: tenta como número da opção
        int numero = atoi(entrada.c_str());

        if (numero >= 1 && numero <= cena->getTotalDecisoes())
            return cena->getProximaCena(numero - 1);

        std::cout << "Decisao invalida!\n";
    }
}


// ---------------------------------------------------------------------
// TELA PADRÃO DO JOGO
// A cada cena: mostra o texto, entrega as recompensas (só na primeira
// visita), salva o jogo e resolve a cena (monstro, teste de sorte ou
// decisão do jogador).
// ---------------------------------------------------------------------
void Jogo::jogar()
{
    while (true)
    {
        // [PONTEIRO] procura a cena atual; nullptr = a cena não existe
        Cena* cena = buscarCena(cenaAtual);

        if (cena == nullptr)
        {
            std::cout << "Cena nao encontrada!\n";
            return;
        }

        cena->mostrar();

        // Itens, ouro, provisões e energia só valem na primeira vez
        if (!cena->foiVisitada())
        {
            cena->aplicarRecompensas(jogador);
            cena->setVisitada();
        }

        if (!jogador.estaVivo())
        {
            std::cout << "\nVoce morreu... FIM DE JOGO.\n";
            return;
        }

        // Salva sempre que uma cena nova é carregada
        salvarJogo();

        int proxima = 0;

        if (cena->eMonstro())
        {
            if (cena->foiVencida())
            {
                // Monstro já derrotado: não luta de novo
                proxima = cena->getCenaVitoria();
            }
            else
            {
                // Luta contra uma CÓPIA: se o jogador fugir, o monstro
                // do arquivo continua como era
                Monstro inimigo = cena->getMonstro();

                bool podeFugir = inimigo.getPodeFugir() && cenaAnterior != 0;

                Resultado resultado = combate(inimigo, podeFugir);

                if (resultado == DERROTA)
                {
                    if (cena->getCenaDerrota() == 0)
                    {
                        std::cout << "\nVoce morreu... FIM DE JOGO.\n";
                        return;
                    }

                    proxima = cena->getCenaDerrota();
                }
                else if (resultado == FUGA)
                {
                    proxima = cenaAnterior;   // volta; o monstro continua lá
                }
                else
                {
                    inimigo.entregarSaque(jogador);
                    cena->setVencida();
                    proxima = cena->getCenaVitoria();
                }
            }
        }
        else if (cena->temTesteSorte())
        {
            std::cout << "\nTeste de sorte!\n";

            if (jogador.testarSorte())
                proxima = cena->getCenaSorte();
            else
                proxima = cena->getCenaAzar();
        }
        else if (cena->getTotalDecisoes() == 0)
        {
            // Cena sem decisões: é um final da história
            std::cout << "\n=================================\n";
            std::cout << "FIM DA AVENTURA\n";
            std::cout << "=================================\n";
            return;
        }
        else
        {
            cena->mostrarDecisoes();

            proxima = escolherDecisao(cena);

            if (proxima == -1)
                return;   // o jogador saiu (o jogo já está salvo)
        }

        cenaAnterior = cenaAtual;
        cenaAtual = proxima;
    }
}
