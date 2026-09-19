#include "../include/Item.h"
#include <cctype>

Item::Item()
{
    id = 0;
    nome = "";
    tipo = TipoItem::ESPECIAL;
    valor = 0;
    descricao = "";
}

Item::Item(int id, std::string nome, TipoItem tipo, int valor, std::string descricao)
{
    this->id = id;
    this->nome = nome;
    this->tipo = tipo;
    this->valor = valor;
    this->descricao = descricao;
}

Item::~Item()
{
}

int Item::getId() const { return id; }
std::string Item::getNome() const { return nome; }
TipoItem Item::getTipo() const { return tipo; }
int Item::getValor() const { return valor; }
std::string Item::getDescricao() const { return descricao; }

std::string Item::getTipoTexto() const
{
    return tipoParaTexto(tipo);
}

std::string Item::descreverEfeito() const
{
    switch (tipo)
    {
        case TipoItem::ARMA:
            return "+" + std::to_string(valor) + " de habilidade em combate";
        case TipoItem::CURA:
            return "recupera " + std::to_string(valor) + " de energia";
        default:
            return "item especial";
    }
}

TipoItem Item::tipoDeTexto(const std::string& texto)
{
    std::string t = texto;

    for (char& c : t)
    {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    if (t == "ARMA")
    {
        return TipoItem::ARMA;
    }

    if (t == "CURA")
    {
        return TipoItem::CURA;
    }

    return TipoItem::ESPECIAL;
}

std::string Item::tipoParaTexto(TipoItem tipo)
{
    switch (tipo)
    {
        case TipoItem::ARMA:
            return "ARMA";
        case TipoItem::CURA:
            return "CURA";
        default:
            return "ESPECIAL";
    }
}