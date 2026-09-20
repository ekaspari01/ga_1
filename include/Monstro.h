#ifndef MONSTRO_H
#define MONSTRO_H

#include <string>
#include <vector>
#include "Personagem.h"

class Monstro : public Personagem
{
private:
    int id;

    // Saque entregue ao jogador quando o monstro e derrotado.
    // Todos sao IDs de item.txt.
    std::vector<int> provisoes;
    std::vector<int> itens;
    std::vector<int> tesouros;

public:
    Monstro();
    Monstro(int id, std::string nome, int habilidade, int energia);
    ~Monstro();

    int getId() const;

    void definirSaque(const std::vector<int>& novasProvisoes,
                      const std::vector<int>& novosItens,
                      const std::vector<int>& novosTesouros)
    {
        provisoes = novasProvisoes;
        itens = novosItens;
        tesouros = novosTesouros;
    }

    const std::vector<int>& getProvisoes() const { return provisoes; }
    const std::vector<int>& getItens() const { return itens; }
    const std::vector<int>& getTesouros() const { return tesouros; }
};

#endif
