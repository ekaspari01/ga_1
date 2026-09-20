#ifndef DECISAO_H
#define DECISAO_H

#include <string>

// Uma opcao de escolha em uma cena.
// numero  = numero mostrado ao jogador
// proximaCena = cena para onde a escolha leva
class Decisao
{
private:
    int numero;
    std::string texto;
    int proximaCena;

public:
    Decisao(int numero, const std::string& texto, int proximaCena);

    int getNumero() const;
    const std::string& getTexto() const;
    int getProximaCena() const;
};

#endif
