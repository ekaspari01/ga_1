#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <cstddef>
#include <vector>
#include "Item.h"

class Inventario
{
private:
    std::vector<Item> itens;
    static constexpr std::size_t CAPACIDADE = 8;

public:
    Inventario();
    ~Inventario();

    bool adicionar(const Item& item);              // false se estiver cheio
    bool removerPorPosicao(std::size_t posicao);   // posicao comeca em 0
    bool temItem(int id) const;

    const std::vector<Item>& getItens() const;
    std::size_t tamanho() const;
    bool estaVazio() const;
    bool estaCheio() const;
    static std::size_t getCapacidade();

    int bonusArma() const;   // maior bonus entre as armas carregadas
    void listar() const;
};

#endif