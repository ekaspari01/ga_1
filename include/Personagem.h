#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>

// Sorteia um número inteiro entre minimo e maximo (inclusive).
int sortear(int minimo, int maximo);

// =====================================================================
// Personagem
//
// [HERANCA]      É a classe PAI de Jogador e de Monstro: o que os dois têm
//                em comum (nome, habilidade, energia) fica aqui.
// [POLIMORFISMO] É ABSTRATA: tem um método virtual puro (forcaDeAtaque = 0),
//                então só se cria Jogador ou Monstro. Cada filho escreve a
//                sua versão do método.
// =====================================================================
class Personagem
{
protected:
    // protected: os filhos enxergam, o resto do programa usa os getters.
    std::string nome;
    int habilidade;
    int energia;
    int energiaMaxima;

public:
    Personagem();
    Personagem(const std::string& nome, int habilidade, int energia);

    // Destrutor virtual: obrigatório em classes com métodos virtuais.
    virtual ~Personagem();

    std::string getNome() const;
    int getHabilidade() const;
    int getEnergia() const;
    int getEnergiaMaxima() const;

    bool estaVivo() const;
    void receberDano(int dano);
    void curar(int valor);

    // Virtual comum: o filho PODE reescrever.
    virtual void mostrarStatus() const;

    // Virtual puro: o filho É OBRIGADO a escrever.
    // Recebe o número do dado e devolve a Força de Ataque (FA).
    virtual int forcaDeAtaque(int dado) const = 0;
};

#endif
