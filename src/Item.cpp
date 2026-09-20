#include "../include/Item.h"

#include <cctype>
#include <stdexcept>

Item::Item(int id,
           const std::string& nome,
           TipoItem tipo,
           int valor,
           const std::string& descricao)
    : id(id),
      nome(nome),
      tipo(tipo),
      valor(valor),
      descricao(descricao)
{
}


int Item::getId() const
{
    return id;
}


const std::string& Item::getNome() const
{
    return nome;
}


TipoItem Item::getTipo() const
{
    return tipo;
}


int Item::getValor() const
{
    return valor;
}


const std::string& Item::getDescricao() const
{
    return descricao;
}


TipoItem Item::tipoDeTexto(const std::string& texto)
{
    // Maiusculas e sem espacos nas pontas
    std::string chave;

    for (char c : texto)
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
            chave += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }

    if (chave == "CURA")    return TipoItem::CURA;
    if (chave == "ARMA")    return TipoItem::ARMA;
    if (chave == "TESOURO") return TipoItem::TESOURO;
    if (chave == "MAGIA")   return TipoItem::MAGIA;
    if (chave == "OUTRO")   return TipoItem::OUTRO;

    throw std::invalid_argument("Tipo de item desconhecido: " + texto);
}


std::string Item::textoDoTipo(TipoItem tipo)
{
    switch (tipo)
    {
        case TipoItem::CURA:    return "CURA";
        case TipoItem::ARMA:    return "ARMA";
        case TipoItem::TESOURO: return "TESOURO";
        case TipoItem::MAGIA:   return "MAGIA";
        case TipoItem::OUTRO:   return "OUTRO";
    }

    return "OUTRO";
}
