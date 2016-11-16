#ifndef FILA_H
#define FILA_H
#include "arvore.h"

typedef struct nodeLista * linkLista;
struct nodeLista {
  linkLista next;
  link noArvore;
};

typedef struct fila {
  linkLista primeiro;
  linkLista ultimo;
} * FILA;

FILA novaFila();
void enfilar (FILA f, link n);
link desenfilar (FILA f);
void destroiFila(FILA f);

#endif
