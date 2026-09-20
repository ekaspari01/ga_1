#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <cstddef>
#include <vector>
#include "Item.h"

class Inventario
{
private:
    std::vector<Item> itens;

public:
    // Quantidade maxima de itens que o jogador carrega
    static size_t getCapacidade();

    const std::vector<Item>& getItens() const;

    size_t tamanho() const;
    bool estaVazio() const;

    // Retorna false se o inventario estiver cheio
    bool adicionar(const Item& item);

    // Remove o item da posicao (0 = primeiro). Posicao invalida e ignorada.
    void removerPorPosicao(size_t posicao);

    // Mostra os itens numerados a partir de 1
    void listar() const;

    // Maior bonus de ARMA no inventario (armas nao se acumulam)
    int bonusArma() const;
};

#endif
