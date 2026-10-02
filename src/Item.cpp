// =====================================================================
// Item.cpp  -  item do jogo (arma, armadura ou item comum)
// =====================================================================

#include "../include/Item.h"

#include <cstdlib>    // atoi
#include <iostream>
#include <sstream>

Item::Item()
    : nome(""), tipo('c'), combate(false), fa(0), dano(0)
{
}


Item::Item(const std::string& nome, char tipo, bool combate, int fa, int dano)
    : nome(nome), tipo(tipo), combate(combate), fa(fa), dano(dano)
{
}


// [ARQUIVO] Lê "nome;tipo;combate;FA;dano".
// O stringstream trata o texto como se fosse um arquivo, e o getline com
// ';' lê um pedaço de cada vez.
bool Item::lerDeTexto(const std::string& texto)
{
    std::stringstream ss(texto);
    std::string n, t, c, f, d;

    std::getline(ss, n, ';');
    std::getline(ss, t, ';');
    std::getline(ss, c, ';');
    std::getline(ss, f, ';');
    std::getline(ss, d, ';');

    // Falta algum pedaço ou o tipo não é c, r ou w: texto inválido
    if (n.empty() || t.empty() || c.empty() || f.empty() || d.empty())
        return false;

    if (t[0] != 'c' && t[0] != 'r' && t[0] != 'w')
        return false;

    nome = n;
    tipo = t[0];
    combate = (atoi(c.c_str()) == 1);
    fa = atoi(f.c_str());
    dano = atoi(d.c_str());

    return true;
}


std::string Item::paraTexto() const
{
    std::string texto = nome + ";";

    texto += tipo;
    texto += ";";
    texto += std::to_string(combate ? 1 : 0) + ";";
    texto += std::to_string(fa) + ";";
    texto += std::to_string(dano);

    return texto;
}


void Item::mostrar() const
{
    std::cout << nome;

    switch (tipo)
    {
        case 'w':
            std::cout << " [arma: FA " << (fa >= 0 ? "+" : "") << fa
                      << ", dano " << (dano >= 0 ? "+" : "") << dano << "]";
            break;

        case 'r':
            std::cout << " [armadura: FA do inimigo " << (fa >= 0 ? "+" : "") << fa
                      << ", dano recebido -" << dano << "]";
            break;

        default:
            std::cout << " [comum]";
            break;
    }

    if (tipo != 'c' && !combate)
        std::cout << " (nao serve em combate)";
}
