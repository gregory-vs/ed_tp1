#include <iostream>
#include "objeto.h"
using namespace std;

// Insere um novo objeto no vetor
bool inserirObjeto(Objeto objetos[], int &qtd, int capacidade,
                    int id, float x, float y, float largura)
{
    if (qtd >= capacidade)
    {
        return false; // vetor cheio
    }
    objetos[qtd].id = id;
    objetos[qtd].x = x;
    objetos[qtd].y = y;
    objetos[qtd].largura = largura;
    qtd++;
    return true;
}

// Atualiza a posição de um objeto pelo ID
bool atualizarPosicao(Objeto objetos[], int qtd,
                        int id, float novoX, float novoY)
{
    for (int i = 0; i < qtd; i++)
    {
        if (objetos[i].id == id)
        {
            objetos[i].x = novoX;
            objetos[i].y = novoY;
            return true;
        }
    }
    return false; // objeto não encontrado
}

// Imprime todos os objetos armazenados
void imprimirObjetos(Objeto objetos[], int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        cout << "Objeto " << objetos[i].id
                << " em (" << objetos[i].x << ", " << objetos[i].y << ")"
                << " largura=" << objetos[i].largura << endl;
    }
}
