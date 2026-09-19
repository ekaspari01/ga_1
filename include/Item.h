#ifndef ITEM_H
#define ITEM_H

#include <string>

enum class TipoItem
{
    ARMA,      // valor = bonus somado a HABILIDADE nos combates (automatico)
    CURA,      // valor = energia recuperada ao usar (item e consumido)
    ESPECIAL   // sem efeito direto (chaves, objetos de historia)
};

class Item
{
private:
    int id;
    std::string nome;
    TipoItem tipo;
    int valor;
    std::string descricao;

public:
    Item();
    Item(int id, std::string nome, TipoItem tipo, int valor, std::string descricao);
    ~Item();

    int getId() const;
    std::string getNome() const;
    TipoItem getTipo() const;
    int getValor() const;
    std::string getDescricao() const;

    std::string getTipoTexto() const;
    std::string descreverEfeito() const;

    // "ARMA" -> TipoItem::ARMA (texto desconhecido vira ESPECIAL)
    static TipoItem tipoDeTexto(const std::string& texto);
    static std::string tipoParaTexto(TipoItem tipo);
};

#endif