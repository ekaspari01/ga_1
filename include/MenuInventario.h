#ifndef MENUINVENTARIO_H
#define MENUINVENTARIO_H

#include "DadosJogo.h"
#include "Jogador.h"
#include "Monstro.h"

// Menu para listar e usar os itens do inventario do jogador.
class MenuInventario
{
public:
    // alvo = monstro do combate atual (nullptr fora de combate).
    // Itens magicos so podem ser usados em combate.
    // Retorna true se algum item foi realmente usado (consumido).
    static bool abrir(Jogador& jogador,
                      const DadosJogo& dadosJogo,
                      Monstro* alvo = nullptr);
};

#endif
