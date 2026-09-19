#ifndef DECISAO_H
#define DECISAO_H

#include <string>

class Decisao
{
private:
    int numero;
    std::string texto;
    int proximaCena;

public:
    Decisao();
    Decisao(int numero, std::string texto, int proximaCena);
    ~Decisao();

    void setNumero(int numero);
    void setTexto(std::string texto);
    void setProximaCena(int proximaCena);

    int getNumero() const;
    std::string getTexto() const;
    int getProximaCena() const;
};

#endif