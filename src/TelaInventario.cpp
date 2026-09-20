#include "../include/TelaInventario.h"

#include <iostream>
#include <vector>


// "  - Espada (+1) - Bonus de ataque"
static void mostrarItem(const Item& item)
{
    std::cout << "  - " << item.getNome();

    if (item.getTipo() == TipoItem::ARMA ||
        item.getTipo() == TipoItem::CURA)
    {
        std::cout << " (+" << item.getValor() << ")";
    }

    if (!item.getDescricao().empty())
        std::cout << " - " << item.getDescricao();

    std::cout << "\n";
}


static void mostrarSecao(const std::string& titulo,
                         const std::vector<const Item*>& itens)
{
    std::cout << "\n" << titulo << "\n";

    if (itens.empty())
    {
        std::cout << "  Nenhum.\n";
        return;
    }

    for (const Item* item : itens)
        mostrarItem(*item);
}


void TelaInventario::mostrar(const Jogador& jogador,
                             const DadosJogo& dadosJogo,
                             bool arcano)
{
    const std::vector<Item>& itens =
        jogador.getInventario().getItens();


    // Arma equipada: a de maior bonus (mesma regra usada no combate)
    const Item* equipada = nullptr;

    for (const Item& item : itens)
    {
        if (item.getTipo() == TipoItem::ARMA &&
            (equipada == nullptr || item.getValor() > equipada->getValor()))
        {
            equipada = &item;
        }
    }


    // Separa o resto do inventario
    std::vector<const Item*> extras;
    std::vector<const Item*> tesouros;
    std::vector<const Item*> itensMagicos;

    for (const Item& item : itens)
    {
        if (&item == equipada)
            continue;

        if (item.getTipo() == TipoItem::MAGIA ||
            dadosJogo.encontrarMagiaDoItem(item.getId()) != nullptr)
        {
            itensMagicos.push_back(&item);
        }
        else if (item.getTipo() == TipoItem::TESOURO)
        {
            tesouros.push_back(&item);
        }
        else
        {
            // armas reservas, provisoes e outros
            extras.push_back(&item);
        }
    }


    std::cout << "\n=================================\n";
    std::cout << "INVENTARIO\n";
    std::cout << "=================================\n";

    jogador.mostrarStatus();

    if (arcano)
        std::cout << "Personagem ARCANO\n";


    // ---- Equipado ----
    std::cout << "\nEQUIPADO\n";

    if (equipada == nullptr)
        std::cout << "  Nada (combate desarmado).\n";
    else
        mostrarItem(*equipada);


    // ---- Extras e tesouros ----
    mostrarSecao("EQUIPAMENTOS EXTRAS (armas reservas e provisoes)", extras);
    mostrarSecao("TESOUROS", tesouros);


    // ---- Magias ----
    std::cout << "\nMAGIAS\n";

    bool temAlgumaMagia = false;

    if (arcano)
    {
        for (const Magia& magia : dadosJogo.getMagias())
        {
            std::cout << "  - " << magia.nome
                      << " (custo: " << magia.custo
                      << " de energia | dano: " << magia.dano
                      << ")\n";

            temAlgumaMagia = true;
        }
    }

    for (const Item* item : itensMagicos)
    {
        const Magia* magia =
            dadosJogo.encontrarMagiaDoItem(item->getId());

        std::cout << "  - " << item->getNome();

        if (magia != nullptr)
        {
            std::cout << " -> " << magia->nome
                      << " (dano: " << magia->dano
                      << ", uso unico)";
        }

        std::cout << "\n";

        temAlgumaMagia = true;
    }

    if (!temAlgumaMagia)
        std::cout << "  Nenhuma.\n";


    std::cout << "\nItens: "
              << jogador.getInventario().tamanho()
              << "/"
              << Inventario::getCapacidade()
              << "\n";
}


void TelaInventario::aguardarEnter(const std::string& mensagem)
{
    std::cout << "\n" << mensagem;

    // Descarta o resto da linha da leitura anterior (feita com >>)
    // e espera o ENTER do jogador
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    std::string resto;
    std::getline(std::cin, resto);
}
