#ifndef ITEM_H
#define ITEM_H

#include <string>

// Um item do jogo. No arquivo de cena ele é escrito em uma linha:
//     I: nome;tipo;combate;FA;dano
//
//   tipo    c = comum, r = armadura, w = arma
//   combate 1 = pode ser usado em combate, 0 = não pode
//   FA      bônus (ou penalidade) na Força de Ataque.
//           Arma: FA de quem ataca. Armadura: FA do oponente.
//   dano    bônus no dano. Arma: aumenta o dano causado.
//           Armadura: diminui o dano recebido.
class Item
{
private:
    std::string nome;
    char tipo;
    bool combate;
    int fa;
    int dano;

public:
    Item();
    Item(const std::string& nome, char tipo, bool combate, int fa, int dano);

    std::string getNome() const { return nome; }
    char getTipo() const { return tipo; }
    bool getCombate() const { return combate; }
    int getFa() const { return fa; }
    int getDano() const { return dano; }

    // Lê "nome;tipo;combate;FA;dano". Retorna false se o texto estiver errado.
    bool lerDeTexto(const std::string& texto);

    // Faz o caminho inverso (usado para salvar o jogo).
    std::string paraTexto() const;

    // Mostra o item na tela (sem pular linha no final).
    void mostrar() const;
};

#endif
