#ifndef DADOSJOGO_H
#define DADOSJOGO_H

#include <string>
#include <vector>
#include "Cena.h"
#include "Item.h"
#include "Monstro.h"

// Um evento acontece quando o jogador entra em uma cena (linha do evento.txt):
//   ITEM        p1 = id do item
//   ENERGIA     p1 = valor (positivo cura, negativo causa dano)
//   COMBATE     p1 = id do monstro, p2 = cena se vencer
//   TESTESORTE  p1 = cena se tiver sorte, p2 = cena se tiver azar
struct Evento
{
    int cena;
    std::string tipo;
    int p1;
    int p2;
};

// Magia usada na tela de combate (linha do magia.txt):
//   nome|custo_de_energia|dano|id_do_item (opcional)
//
// Personagens ARCANOS lancam qualquer magia gastando energia.
// Os demais personagens so lancam uma magia usando o item ligado a ela
// (idItem); o item e consumido e nao custa energia.
struct Magia
{
    std::string nome;
    int custo;     // energia que o arcano gasta ao lancar
    int dano;      // energia que o monstro perde
    int idItem;    // item que guarda a magia (0 = nenhum)
};


// Dados fixos da historia, carregados dos arquivos .txt
// (cenas, itens, monstros, magias e eventos) e funcoes de busca.
class DadosJogo
{
private:
    std::vector<Cena> cenas;
    std::vector<Item> itens;
    std::vector<Monstro> monstros;
    std::vector<Magia> magias;      // opcional (magia.txt)
    std::vector<Evento> eventos;
    std::vector<int> itensIniciais;  // opcional (inicial.txt)

    void carregarCenas();
    void carregarItens();
    void carregarMonstros();
    void carregarMagias();
    void carregarEventos();
    void carregarItensIniciais();

public:
    // Carrega todos os arquivos. Retorna false se nao houver cenas.
    bool carregar();

    Cena* encontrarCena(int numero);
    const Item* encontrarItem(int id) const;
    const Monstro* encontrarMonstro(int id) const;

    const std::vector<Magia>& getMagias() const;
    const std::vector<Evento>& getEventos() const;

    // IDs dos itens com que o personagem comeca (inicial.txt)
    const std::vector<int>& getItensIniciais() const;

    // A historia tem magia (e portanto personagens arcanos)
    // quando existe o magia.txt com magias validas
    bool temMagia() const;

    // Magia guardada em determinado item (nullptr se o item nao for magico)
    const Magia* encontrarMagiaDoItem(int idItem) const;
};

#endif
