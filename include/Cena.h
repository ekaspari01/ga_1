#ifndef CENA_H
#define CENA_H

#include <string>
#include <vector>
#include "Decisao.h"

class Cena
{
private:
    int numero;
    std::string texto;
    std::vector<Decisao> decisoes;

public:
    Cena(int numero, const std::string& texto);

    int getNumero() const;
    const std::string& getTexto() const;

    void adicionarDecisao(const Decisao& decisao);
    const std::vector<Decisao>& getDecisoes() const;

    // Mostra o texto da cena
    void mostrar() const;

    // Mostra as opcoes: "numero - texto"
    void mostrarDecisoes() const;
};

#endif
