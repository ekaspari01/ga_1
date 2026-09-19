#include "../include/Personagem.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Personagem::Personagem()
{
    nome = "";
    habilidade = 6;
    energia = 12;
    sorte = 6;
}
Personagem::~Personagem()
{

}
void Personagem::setNome(string nome)
{
    this->nome = nome;
}

string Personagem::getNome()
{
    return nome;
}

void Personagem::setHabilidade(int habilidade)
{
    this->habilidade = habilidade;
}

int Personagem::getHabilidade()
{
    return habilidade;
}

void Personagem::setEnergia(int energia)
{
    this->energia = energia;
}

int Personagem::getEnergia()
{
    return energia;
}

void Personagem::setSorte(int sorte)
{
    this->sorte = sorte;
}

int Personagem::getSorte()
{
    return sorte;
}

void Personagem::perderEnergia(int valor)
{
    energia = energia - valor;

    if (energia < 0)
        energia = 0;
}

void Personagem::recuperarEnergia(int valor)
{
    energia = energia - valor;
}

/*bool Personagem::estaVivo()
{
    return energia > 0;
}

bool Personagem::testarSorte()
{
    if (sorte <= 0)
    {
        cout << "Voce nao possui mais pontos de sorte." << endl;
        return false;
    }

    int resultado = rand() % 12 + 1;

    sorte--;

    cout << "Teste de sorte: " << resultado << endl;

    if (resultado <= sorte + 1)
    {
        cout << "Teste de sorte bem-sucedido!" << endl;
        return true;
    }

    cout << "Teste de sorte falhou!" << endl;
    return false;
}
*/
void Personagem::mostrarStatus()
{
    cout << endl;
    cout << "================================" << endl;
    cout << "         PERSONAGEM" << endl;
    cout << "================================" << endl;

    cout << "Nome:       " << nome << endl;
    cout << "Habilidade: " << habilidade << endl;
    cout << "Energia:    " << energia << endl;
    cout << "Sorte:      " << sorte << endl;

    cout << "================================" << endl;
}

void Personagem::criarPersonagem()
{
    int pontos = 12;

    cout << endl;
    cout << "================================" << endl;
    cout << "       CRIACAO DO PERSONAGEM" << endl;
    cout << "================================" << endl;

    cout << "Nome: ";
    cin >> nome;

    habilidade = 6;
    energia = 12;
    sorte = 6;

    cout << endl;
    cout << "Voce possui 12 pontos para distribuir." << endl;
    cout << "Valores iniciais:" << endl;
    cout << "Habilidade: 6" << endl;
    cout << "Energia: 12" << endl;
    cout << "Sorte: 6" << endl;

    while (pontos > 0)
    {
        int escolha;

        cout << endl;
        cout << "Pontos restantes: " << pontos << endl;

        cout << "1 - +1 Habilidade" << endl;
        cout << "2 - +1 Energia" << endl;
        cout << "3 - +1 Sorte" << endl;
        cout << "Escolha: ";
        cin >> escolha;

        if (escolha == 1)
        {
            if (habilidade < 12)
            {
                habilidade++;
                pontos--;
            }
            else
                cout << "Habilidade ja esta no maximo." << endl;
        }
        else if (escolha == 2)
        {
            if (energia < 24)
            {
                energia++;
                pontos--;
            }
            else
                cout << "Energia ja esta no maximo." << endl;
        }
        else if (escolha == 3)
        {
            if (sorte < 12)
            {
                sorte++;
                pontos--;
            }
            else
                cout << "Sorte ja esta no maximo." << endl;
        }
        else
        {
            cout << "Opcao invalida." << endl;
        }
    }

    cout << endl;
    cout << "Personagem criado!" << endl;

    mostrarStatus();
}

/*void Personagem::criarPersonagemAleatorio()
{
    cout << endl;
    cout << "Nome: ";
    cin >> nome;

    habilidade = rand() % 7 + 6;
    energia = rand() % 13 + 12;
    sorte = rand() % 7 + 6;

    cout << endl;
    cout << "Personagem criado aleatoriamente!" << endl;

    mostrarStatus();
}*/