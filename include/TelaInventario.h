#ifndef TELAINVENTARIO_H
#define TELAINVENTARIO_H

#include <string>
#include "DadosJogo.h"
#include "Jogador.h"

// Tela do inventario: mostra os atributos do personagem, o que ele tem
// equipado, os equipamentos extras, os tesouros e as magias.
class TelaInventario
{
public:
    static void mostrar(const Jogador& jogador,
                        const DadosJogo& dadosJogo,
                        bool arcano);

    // Mostra a mensagem e espera o jogador apertar ENTER.
    // Deve ser chamado logo depois de uma leitura com "std::cin >>".
    static void aguardarEnter(const std::string& mensagem);
};

#endif
