#ifndef EXECUTOREVENTOS_H
#define EXECUTOREVENTOS_H

#include "Combate.h"
#include "DadosJogo.h"
#include "EstadoJogo.h"
#include "Sorteador.h"

// Executa os eventos (evento.txt) da cena em que o jogador esta.
class ExecutorEventos
{
private:
    EstadoJogo& estado;
    const DadosJogo& dadosJogo;
    Sorteador& sorteador;
    Combate& combate;

public:
    ExecutorEventos(EstadoJogo& estado,
                    const DadosJogo& dadosJogo,
                    Sorteador& sorteador,
                    Combate& combate);

    // Retorna o numero da proxima cena, ou -1 se nenhum evento
    // mandou o jogador para outra cena (ou se ele morreu).
    int executar(bool primeiraVisita);
};

#endif
