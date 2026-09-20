#include "../include/ExecutorEventos.h"

#include <iostream>

ExecutorEventos::ExecutorEventos(EstadoJogo& estado,
                                 const DadosJogo& dadosJogo,
                                 Sorteador& sorteador,
                                 Combate& combate)
    : estado(estado),
      dadosJogo(dadosJogo),
      sorteador(sorteador),
      combate(combate)
{
}


int ExecutorEventos::executar(bool primeiraVisita)
{
    Jogador& jogador = estado.jogador;

    for (const Evento& evento : dadosJogo.getEventos())
    {
        if (evento.cena != estado.cenaAtual)
            continue;


        // --------------------------------------------------------
        // ITEM
        // --------------------------------------------------------

        if (evento.tipo == "ITEM")
        {
            if (!primeiraVisita)
                continue;


            const Item* item =
                dadosJogo.encontrarItem(evento.p1);


            if (jogador.getInventario().adicionar(*item))
            {
                std::cout << "\nVoce pegou: "
                          << item->getNome()
                          << "\n";
            }
            else
            {
                std::cout << "\nInventario cheio!\n";
            }
        }


        // --------------------------------------------------------
        // ENERGIA
        // --------------------------------------------------------

        else if (evento.tipo == "ENERGIA")
        {
            if (!primeiraVisita)
                continue;


            if (evento.p1 >= 0)
            {
                jogador.curar(evento.p1);

                std::cout << "\nVoce recuperou "
                          << evento.p1
                          << " de energia.\n";
            }
            else
            {
                jogador.receberDano(-evento.p1);

                std::cout << "\nVoce perdeu "
                          << -evento.p1
                          << " de energia.\n";
            }


            std::cout << "ENERGIA: "
                      << jogador.getEnergia()
                      << "/"
                      << jogador.getEnergiaMaxima()
                      << "\n";


            if (!jogador.estaVivo())
                return -1;
        }


        // --------------------------------------------------------
        // COMBATE
        //
        // evento.p1 = ID do monstro
        // evento.p2 = cena para onde ir apos vencer
        // --------------------------------------------------------

        else if (evento.tipo == "COMBATE")
        {
            // Combate ja vencido: nao repete, segue para a cena de vitoria
            if (estado.venceuCombate(estado.cenaAtual))
                return evento.p2;


            const Monstro* monstro =
                dadosJogo.encontrarMonstro(evento.p1);


            bool podeFugir =
                (estado.cenaAnterior() != -1);


            ResultadoCombate resultado =
                combate.executar(*monstro, podeFugir, estado.arcano);


            // Derrota: o loop principal trata a morte do jogador
            if (resultado == ResultadoCombate::DERROTA)
                return -1;


            // Fuga: volta para a cena anterior.
            // O combate NAO conta como vencido, entao o monstro
            // estara la de novo se o jogador retornar.
            if (resultado == ResultadoCombate::FUGA)
                return estado.cenaAnterior();


            estado.registrarCombateVencido(estado.cenaAtual);

            return evento.p2;
        }


        // --------------------------------------------------------
        // TESTE DE SORTE
        // --------------------------------------------------------

        else if (evento.tipo == "TESTESORTE")
        {
            std::cout << "\nTeste de sorte!\n";

            if (sorteador.testarSorte(jogador))
                return evento.p1;

            return evento.p2;
        }
    }


    return -1;
}
