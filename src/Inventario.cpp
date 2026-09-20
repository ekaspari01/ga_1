#include "../include/Inventario.h"

#include <iostream>

static const size_t CAPACIDADE = 10;


size_t Inventario::getCapacidade()
{
    return CAPACIDADE;
}


const std::vector<Item>& Inventario::getItens() const
{
    return itens;
}


size_t Inventario::tamanho() const
{
    return itens.size();
}


bool Inventario::estaVazio() const
{
    return itens.empty();
}


bool Inventario::adicionar(const Item& item)
{
    if (itens.size() >= CAPACIDADE)
        return false;

    itens.push_back(item);

    return true;
}


void Inventario::removerPorPosicao(size_t posicao)
{
    if (posicao >= itens.size())
        return;

    itens.erase(itens.begin() + static_cast<std::ptrdiff_t>(posicao));
}


void Inventario::listar() const
{
    for (size_t i = 0; i < itens.size(); i++)
    {
        const Item& item = itens[i];

        std::cout << i + 1 << ") "
                  << item.getNome()
                  << " [" << Item::textoDoTipo(item.getTipo());

        if (item.getTipo() == TipoItem::CURA ||
            item.getTipo() == TipoItem::ARMA)
        {
            std::cout << " +" << item.getValor();
        }

        std::cout << "]";

        if (!item.getDescricao().empty())
            std::cout << " - " << item.getDescricao();

        std::cout << "\n";
    }
}


int Inventario::bonusArma() const
{
    int melhor = 0;

    for (const Item& item : itens)
    {
        if (item.getTipo() == TipoItem::ARMA &&
            item.getValor() > melhor)
        {
            melhor = item.getValor();
        }
    }

    return melhor;
}
