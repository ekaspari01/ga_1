#ifndef ITEM_H
#define ITEM_H

#include <string>

// Tipos de item (coluna "tipo" do item.txt)
//   CURA     provisoes e pocoes: recupera "valor" de ENERGIA
//   ARMA     soma "valor" na FA do jogador em combate
//   TESOURO  itens de valor (sem uso direto)
//   MAGIA    item que guarda uma magia (a magia e ligada em magia.txt)
//   OUTRO    qualquer outro item
enum class TipoItem
{
    CURA,
    ARMA,
    TESOURO,
    MAGIA,
    OUTRO
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
    Item(int id,
         const std::string& nome,
         TipoItem tipo,
         int valor,
         const std::string& descricao);

    int getId() const;
    const std::string& getNome() const;
    TipoItem getTipo() const;
    int getValor() const;
    const std::string& getDescricao() const;

    // "CURA" -> TipoItem::CURA (sem diferenciar maiusculas de minusculas).
    // Lanca std::invalid_argument se o texto nao for um tipo conhecido.
    static TipoItem tipoDeTexto(const std::string& texto);

    // TipoItem::CURA -> "CURA"
    static std::string textoDoTipo(TipoItem tipo);
};

#endif
