#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>

// Classe base: todo personagem (jogador ou monstro) tem HABILIDADE, ENERGIA e SORTE
class Personagem
{
protected:
    std::string nome;
    int habilidade;
    int energia;
    int sorte;

public:
    Personagem();
    Personagem(std::string nome, int habilidade, int energia, int sorte);
    virtual ~Personagem();

    void setNome(std::string nome);
    void setHabilidade(int habilidade);
    void setEnergia(int energia);
    void setSorte(int sorte);

    std::string getNome() const;
    int getHabilidade() const;
    int getEnergia() const;
    int getSorte() const;

    bool estaVivo() const;
    void receberDano(int dano);
};

#endif