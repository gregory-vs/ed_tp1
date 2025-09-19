#ifndef CENA_H
#define CENA_H

//int MAX_TRECHOS = 10;

typedef struct {
    int tempo;
    int objId;
    float inicio, fim;
} TrechoVisivel;

typedef struct {
    int tempo;
    TrechoVisivel trechos[10];
    int qtd;
} Cena;

#endif CENA_H
