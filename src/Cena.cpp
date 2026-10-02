// =====================================================================
// Cena.cpp
//
// [ARQUIVO] A cena lê o próprio arquivo de texto (veja o formato no Cena.h).
// =====================================================================

#include "../include/Cena.h"

#include <cstdlib>    // atoi
#include <fstream>    // ifstream: ler arquivos
#include <iostream>

// Tira os espaços do começo e do fim de um texto.
static std::string cortar(const std::string& texto)
{
    size_t inicio = texto.find_first_not_of(" \t");

    if (inicio == std::string::npos)
        return "";

    size_t fim = texto.find_last_not_of(" \t");

    return texto.substr(inicio, fim - inicio + 1);
}


Cena::Cena()
    : numero(0),
      tesouro(0),
      provisoes(0),
      energia(0),
      cenaSorte(0),
      cenaAzar(0),
      ehMonstro(false),
      cenaVitoria(0),
      cenaDerrota(0),
      visitada(false),
      vencida(false)
{
}


bool Cena::carregar(int numeroDaCena)
{
    numero = numeroDaCena;

    // Monta o nome do arquivo: "../txt/" + "1" + ".txt"
    std::string nomeArquivo = "../txt/" + std::to_string(numero) + ".txt";

    std::ifstream arquivo(nomeArquivo.c_str());

    if (!arquivo.is_open())
        return false;

    // Dados do monstro (usados só se a primeira linha for "m")
    std::string nomeMonstro = "Monstro";
    int habilidadeMonstro = 0;
    int energiaMonstro = 1;
    bool monstroPodeFugir = true;

    std::string linha;
    bool primeiraLinha = true;

    while (std::getline(arquivo, linha))
    {
        // Arquivos feitos no Windows terminam a linha com '\r': tira
        if (!linha.empty() && linha[linha.size() - 1] == '\r')
            linha.erase(linha.size() - 1);

        if (linha.empty())
            continue;

        // Primeira linha "m": a cena é um monstro
        if (primeiraLinha)
        {
            primeiraLinha = false;

            if (linha == "m")
            {
                ehMonstro = true;
                continue;
            }
        }

        // Linha que começa com '#': número da cena ("#1") ou decisão ("#2: texto")
        if (linha[0] == '#')
        {
            size_t doisPontos = linha.find(':');

            if (doisPontos != std::string::npos)
            {
                int destino = atoi(linha.substr(1, doisPontos - 1).c_str());
                std::string textoDecisao = cortar(linha.substr(doisPontos + 1));

                decisoes.push_back(Decisao(textoDecisao, destino));
            }

            continue;
        }

        // Linha que começa com número: "12;13" = cena se vencer ; se perder
        if (linha[0] >= '0' && linha[0] <= '9')
        {
            size_t pontoVirgula = linha.find(';');

            cenaVitoria = atoi(linha.c_str());

            if (pontoVirgula != std::string::npos)
                cenaDerrota = atoi(linha.substr(pontoVirgula + 1).c_str());

            continue;
        }

        // Linha "X: valor": informação extra da cena
        if (linha.size() >= 2 && linha[1] == ':')
        {
            std::string valor = cortar(linha.substr(2));
            bool linhaReconhecida = true;

            switch (linha[0])
            {
                case 'I':
                {
                    Item novoItem;

                    if (novoItem.lerDeTexto(valor))
                        itens.push_back(novoItem);
                    else
                        std::cout << "Aviso: item invalido em " << nomeArquivo << "\n";
                    break;
                }

                case 'T': tesouro = atoi(valor.c_str()); break;
                case 'P': provisoes = atoi(valor.c_str()); break;
                case 'V': energia = atoi(valor.c_str()); break;

                case 'L':
                    cenaSorte = atoi(valor.c_str());
                    if (valor.find(';') != std::string::npos)
                        cenaAzar = atoi(valor.substr(valor.find(';') + 1).c_str());
                    break;

                case 'N': nomeMonstro = valor; break;
                case 'M': monstroPodeFugir = (valor == "S" || valor == "s"); break;
                case 'H': habilidadeMonstro = atoi(valor.c_str()); break;
                case 'E': energiaMonstro = atoi(valor.c_str()); break;

                case 'S':
                    break;   // sorte do monstro: lida, mas o jogo não usa

                default:
                    linhaReconhecida = false;
                    break;
            }

            if (linhaReconhecida)
                continue;
        }

        // Qualquer outra linha faz parte do texto da cena
        if (!texto.empty())
            texto += "\n";

        texto += linha;
    }

    // Monta o monstro. Em cena de monstro, T/P/I são o que ELE solta,
    // então saem da lista de recompensas da cena.
    if (ehMonstro)
    {
        monstro = Monstro(nomeMonstro, habilidadeMonstro, energiaMonstro,
                          monstroPodeFugir);

        monstro.definirSaque(tesouro, provisoes);

        if (!itens.empty())
            monstro.definirItem(itens[0]);

        tesouro = 0;
        provisoes = 0;
        itens.clear();
    }

    return true;
}


// O número da cena NÃO é mostrado ao jogador (enunciado).
void Cena::mostrar() const
{
    std::cout << "\n" << texto << "\n";
}


// Mostra as opções numeradas 1, 2, 3... (o número vem da posição).
void Cena::mostrarDecisoes() const
{
    std::cout << "\n";

    for (int i = 0; i < (int)decisoes.size(); i++)
        std::cout << i + 1 << " - " << decisoes[i].getTexto() << "\n";
}


void Cena::aplicarRecompensas(Jogador& jogador) const
{
    for (int i = 0; i < (int)itens.size(); i++)
    {
        if (jogador.adicionarItem(itens[i]))
            std::cout << "\nVoce pegou: " << itens[i].getNome() << "\n";
        else
            std::cout << "\nInventario cheio! Voce deixou: " << itens[i].getNome() << "\n";
    }

    if (provisoes > 0)
    {
        jogador.ganharProvisoes(provisoes);
        std::cout << "\nVoce ganhou " << provisoes << " provisao(oes).\n";
    }

    if (tesouro > 0)
    {
        jogador.ganharOuro(tesouro);
        std::cout << "\nVoce ganhou " << tesouro << " moedas de ouro.\n";
    }

    if (energia > 0)
    {
        jogador.curar(energia);
        std::cout << "\nVoce recuperou " << energia << " de energia.\n";
    }
    else if (energia < 0)
    {
        jogador.receberDano(-energia);
        std::cout << "\nVoce perdeu " << -energia << " de energia.\n";
    }

    if (energia != 0)
        std::cout << "ENERGIA: " << jogador.getEnergia()
                  << "/" << jogador.getEnergiaMaxima() << "\n";
}
