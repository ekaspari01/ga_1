// =====================================================================
// Jogador.cpp
//
// [HERANCA]      Jogador é filho de Personagem.
// [POLIMORFISMO] Reescreve mostrarStatus() e forcaDeAtaque().
// =====================================================================

#include "../include/Jogador.h"

#include <iostream>

// [HERANCA] O construtor do filho chama o do pai (Personagem()) antes.
Jogador::Jogador()
    : Personagem(),
      sorte(0),
      sorteMaxima(0),
      ouro(0),
      provisoes(0),
      armaEquipada(-1),
      armaduraEquipada(-1)
{
}


// habilidade, energia e energiaMaxima são "protected" no pai:
// o filho consegue usar diretamente.
void Jogador::definirAtributos(const std::string& novoNome, int novaHabilidade,
                               int novaEnergia, int novaSorte)
{
    nome = novoNome;
    habilidade = novaHabilidade;

    energiaMaxima = novaEnergia;
    energia = energiaMaxima;

    sorteMaxima = novaSorte;
    sorte = sorteMaxima;
}


void Jogador::restaurar(const std::string& novoNome, int novaHabilidade,
                        int novaEnergia, int novaEnergiaMaxima, int novaSorte,
                        int novaSorteMaxima, int novoOuro, int novasProvisoes,
                        int arma, int armadura)
{
    nome = novoNome;
    habilidade = novaHabilidade;
    energia = novaEnergia;
    energiaMaxima = novaEnergiaMaxima;
    sorte = novaSorte;
    sorteMaxima = novaSorteMaxima;
    ouro = novoOuro;
    provisoes = novasProvisoes;

    // Só aceita posições que existem no inventário
    armaEquipada = (arma >= 0 && arma < (int)itens.size()) ? arma : -1;
    armaduraEquipada = (armadura >= 0 && armadura < (int)itens.size()) ? armadura : -1;
}


// [POLIMORFISMO] Reaproveita a versão do pai e acrescenta a SORTE.
void Jogador::mostrarStatus() const
{
    Personagem::mostrarStatus();

    std::cout << "SORTE: " << sorte << "/" << sorteMaxima << "\n";
}


// [POLIMORFISMO] FA do jogador = habilidade + bônus da arma + dado.
// O Monstro tem a sua própria versão, sem arma.
int Jogador::forcaDeAtaque(int dado) const
{
    return habilidade + getFaArma() + dado;
}


int Jogador::getFaArma() const
{
    if (armaEquipada == -1)
        return 0;

    return itens[armaEquipada].getFa();
}


int Jogador::getDanoArma() const
{
    if (armaEquipada == -1)
        return 0;

    return itens[armaEquipada].getDano();
}


int Jogador::getFaArmadura() const
{
    if (armaduraEquipada == -1)
        return 0;

    return itens[armaduraEquipada].getFa();
}


int Jogador::getDanoArmadura() const
{
    if (armaduraEquipada == -1)
        return 0;

    return itens[armaduraEquipada].getDano();
}


// TESTE DE SORTE: 2 dados de 6 lados. Resultado <= SORTE atual = sucesso.
// Toda vez que a sorte é usada, ela diminui em 1.
bool Jogador::testarSorte()
{
    int rolagem = sortear(1, 6) + sortear(1, 6);
    bool sucesso = (rolagem <= sorte);

    std::cout << "Teste de sorte: " << rolagem << " contra SORTE " << sorte
              << " -> " << (sucesso ? "SUCESSO" : "FALHA") << "\n";

    if (sorte > 0)
        sorte--;

    std::cout << "SORTE atual: " << sorte << "\n";

    return sucesso;
}


// Guarda o item no vector. Arma ou armadura de combate é equipada
// sozinha se o jogador ainda não tem nada equipado (ou se a arma é melhor).
bool Jogador::adicionarItem(const Item& item)
{
    if ((int)itens.size() >= MAX_ITENS)
        return false;

    itens.push_back(item);

    int posicao = (int)itens.size() - 1;

    if (item.getCombate())
    {
        if (item.getTipo() == 'w' &&
            (armaEquipada == -1 || item.getFa() > itens[armaEquipada].getFa()))
        {
            armaEquipada = posicao;
        }

        if (item.getTipo() == 'r' && armaduraEquipada == -1)
            armaduraEquipada = posicao;
    }

    return true;
}


void Jogador::ganharOuro(int quantidade)
{
    ouro = ouro + quantidade;
}


void Jogador::ganharProvisoes(int quantidade)
{
    provisoes = provisoes + quantidade;
}


// Uma provisão recupera sempre 4 de energia (só fora de combate).
bool Jogador::usarProvisao()
{
    if (provisoes <= 0)
    {
        std::cout << "Voce nao tem provisoes!\n";
        return false;
    }

    if (energia >= energiaMaxima)
    {
        std::cout << "Sua energia ja esta no maximo!\n";
        return false;
    }

    curar(4);
    provisoes--;

    std::cout << "Voce comeu uma provisao. ENERGIA: " << energia
              << "/" << energiaMaxima << "\n";

    return true;
}


// Equipa o item da posição indicada (0 = primeiro).
bool Jogador::equipar(int posicao)
{
    if (posicao < 0 || posicao >= (int)itens.size())
    {
        std::cout << "Item invalido!\n";
        return false;
    }

    char tipo = itens[posicao].getTipo();

    if (!itens[posicao].getCombate() || (tipo != 'w' && tipo != 'r'))
    {
        std::cout << "Este item nao pode ser equipado.\n";
        return false;
    }

    if (tipo == 'w')
        armaEquipada = posicao;
    else
        armaduraEquipada = posicao;

    std::cout << "Voce equipou: " << itens[posicao].getNome() << "\n";

    return true;
}


// Lista os itens numerados a partir de 1.
void Jogador::listarItens() const
{
    for (int i = 0; i < (int)itens.size(); i++)
    {
        std::cout << "  " << i + 1 << ") ";
        itens[i].mostrar();

        if (i == armaEquipada || i == armaduraEquipada)
            std::cout << " <- equipado";

        std::cout << "\n";
    }
}


// TELA DE INVENTÁRIO: atributos, equipado, itens, tesouro e provisões.
void Jogador::mostrarInventario() const
{
    std::cout << "\n=================================\n";
    std::cout << "INVENTARIO\n";
    std::cout << "=================================\n";

    // [POLIMORFISMO] mostrarStatus é virtual: aqui roda a versão do Jogador
    mostrarStatus();

    std::cout << "\nEQUIPADO\n";

    std::cout << "  Arma: ";
    if (armaEquipada == -1)
        std::cout << "nenhuma (combate desarmado)";
    else
        itens[armaEquipada].mostrar();
    std::cout << "\n";

    std::cout << "  Armadura: ";
    if (armaduraEquipada == -1)
        std::cout << "nenhuma";
    else
        itens[armaduraEquipada].mostrar();
    std::cout << "\n";

    std::cout << "\nITENS (" << itens.size() << "/" << MAX_ITENS << ")\n";

    if (itens.empty())
        std::cout << "  Nenhum.\n";
    else
        listarItens();

    std::cout << "\nTESOURO: " << ouro << " moedas de ouro\n";
    std::cout << "PROVISOES: " << provisoes << " (cada uma recupera 4 de energia)\n";
}
