#ifndef MONSTRO_H
#define MONSTRO_H

#include <string>
#include "Personagem.h"

class Monstro : public Personagem
{
private:
    int id;

public:
    Monstro();
    Monstro(int id, std::string nome, int habilidade, int energia);
    ~Monstro();

    int getId() const;
};

#endif