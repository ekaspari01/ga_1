#ifndef DECISAO_H
#define DECISAO_H

#include <string>

// Uma opção de escolha de uma cena: o texto que o jogador lê e o número
// da cena para onde a escolha leva (linha "#3: texto" do arquivo).
class Decisao
{
private:
    std::string texto;
    int proximaCena;

public:
    Decisao(const std::string& texto, int proximaCena);

    std::string getTexto() const { return texto; }
    int getProximaCena() const { return proximaCena; }
};

#endif
