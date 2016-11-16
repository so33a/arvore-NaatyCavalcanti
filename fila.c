#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

FILA novaFila() {
  FILA f = malloc(sizeof(struct fila)) ;
  f->primeiro = NULL;
  f->ultimo = NULL;
  return f;
}

void imprimeFila (FILA f) {
   linkLista l = f->primeiro;
   while (l != NULL) {
     printf ("%d ", l->noArvore->key);
     l = l->next;
   }
   printf ("\n");
}

void enfilar (FILA f, link n) {
  linkLista n1 = malloc(sizeof(struct nodeLista));
  n1->noArvore =  n;
  n1->next = NULL;
  if(f->primeiro == NULL) {
    f->primeiro = n1;
    f->ultimo = n1;
  } else {
    f->ultimo->next = n1; 
    f->ultimo = n1;
  }
}

link desenfilar (FILA f) {
  link aux;
  linkLista aux2;
  if(f->primeiro == NULL) {
    return NULL;
  }
  aux2 = f->primeiro;
  aux =  f->primeiro->noArvore;
  f->primeiro = f->primeiro->next;
  free(aux2); aux2= NULL;
  return aux;
}

void destroiFila(FILA f) {
  while(f->primeiro !=NULL){
    desenfilar(f);
  }
  free(f); f = NULL;
}
