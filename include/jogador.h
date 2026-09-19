#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador
{
private:
    std::string nome;

public:
    Jogador();
    ~Jogador();

    void setNome(std::string nome);
    std::string getNome() const;
};

#endif