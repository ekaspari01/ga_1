#include "../include/Inventario.h"
#include <iostream>

Inventario::Inventario()
{
}

Inventario::~Inventario()
{
}

bool Inventario::adicionar(const Item& item)
{
    if (estaCheio())
    {
        return false;
    }

    itens.push_back(item);
    return true;
}

bool Inventario::removerPorPosicao(std::size_t posicao)
{
    if (posicao >= itens.size())
    {
        return false;
    }

    itens.erase(itens.begin() + static_cast<std::ptrdiff_t>(posicao));
    return true;
}

bool Inventario::temItem(int id) const
{
    for (const Item& item : itens)
    {
        if (item.getId() == id)
        {
            return true;
        }
    }

    return false;
}

const std::vector<Item>& Inventario::getItens() const
{
    return itens;
}

std::size_t Inventario::tamanho() const
{
    return itens.size();
}

bool Inventario::estaVazio() const
{
    return itens.empty();
}

bool Inventario::estaCheio() const
{
    return itens.size() >= CAPACIDADE;
}

std::size_t Inventario::getCapacidade()
{
    return CAPACIDADE;
}

int Inventario::bonusArma() const
{
    int melhor = 0;

    for (const Item& item : itens)
    {
        if (item.getTipo() == TipoItem::ARMA && item.getValor() > melhor)
        {
            melhor = item.getValor();
        }
    }

    return melhor;
}

void Inventario::listar() const
{
    for (std::size_t i = 0; i < itens.size(); i++)
    {
        const Item& item = itens[i];

        std::cout << "  " << (i + 1) << " - "
                  << item.getNome()
                  << " [" << item.getTipoTexto() << "] "
                  << "(" << item.descreverEfeito() << ") - "
                  << item.getDescricao()
                  << std::endl;
    }
}