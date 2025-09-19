#ifndef OBJETO_H
#define OBJETO_H

struct Objeto
{
    int id;
    float x, y;
    float largura;
};

bool inserirObjeto(Objeto objetos[], int &qtd, int capacidade,
                   int id, float x, float y, float largura);
bool atualizarPosicao(Objeto objetos[], int qtd,
                      int id, float novoX, float novoY);
void imprimirObjetos(Objeto objetos[], int qtd);

#endif
