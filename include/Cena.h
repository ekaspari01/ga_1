#ifndef CENA_H
#define CENA_H

#include <string>
#include <vector>
#include "decisao.h"

class Cena
{
private:
    int numero;
    std::string texto;
    std::vector<Decisao> decisoes;

public:
    Cena();
    Cena(int numero, std::string texto);
    ~Cena();

    void setNumero(int numero);
    void setTexto(std::string texto);

    int getNumero() const;
    std::string getTexto() const;

    void adicionarDecisao(Decisao decisao);

    const std::vector<Decisao>& getDecisoes() const;

    void mostrar();
    void mostrarDecisoes();
};

#endif