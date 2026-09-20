#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>

// Base de tudo que tem nome, HABILIDADE e ENERGIA (Jogador e Monstro).
class Personagem
{
protected:
    std::string nome;
    int habilidade;
    int energia;
    int energiaMaxima;

public:
    Personagem();
    Personagem(const std::string& nome, int habilidade, int energia);
    virtual ~Personagem();

    // Nome
    const std::string& getNome() const;
    void setNome(const std::string& novoNome);

    // HABILIDADE
    int getHabilidade() const;
    void setHabilidade(int valor);

    // ENERGIA
    int getEnergia() const;
    int getEnergiaMaxima() const;
    void setEnergia(int valor);
    void setEnergiaMaxima(int valor);

    bool estaVivo() const;

    // Tira energia (nunca fica abaixo de 0)
    void receberDano(int dano);

    // Recupera energia (nunca passa da ENERGIA maxima)
    void curar(int valor);
};

#endif
