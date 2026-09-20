#ifndef GERENCIADORSAVE_H
#define GERENCIADORSAVE_H

#include "DadosJogo.h"
#include "EstadoJogo.h"

// Grava e le o arquivo de save (../txt/save.txt).
//
// Formato (uma informacao por linha):
//   nome
//   cena atual
//   cenas visitadas          (separadas por |)
//   hab|ene|eneMax|sorte|sorteMax
//   ids do inventario        (separados por |)
//   cenas com combate vencido (separadas por |)
//   arcano (1 ou 0)
class GerenciadorSave
{
public:
    static bool existe();

    static void salvar(EstadoJogo& estado);

    // Os dados do jogo (itens) precisam estar carregados antes.
    // O estado so e alterado se o save inteiro for valido.
    static bool carregar(EstadoJogo& estado, const DadosJogo& dados);
};

#endif
