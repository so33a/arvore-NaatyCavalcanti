#include <stdio.h>
#include "arvore.h"

/*
 *           55
 *      44        66
 *   33   45  64     77
 *
 *   em ordem = 33 44 45 55 64 66 77
 *   pos ordem = 33 45 44 64 77 66 55
 *   pre ordem = 55 44 33 45 66 64 77
 *   em largura = 55 44 66 33 45 64 77
 *   
 *
 *   rotR (55) =>
 *             
 *              44
 *          33     55
 *               45  66
 *                  64 77
 *
 *   em largura: 44 33 55 45 66 64 77
 *   
 */
int main () {
  ARVORE a = novaArvore();
  link x;
  int item;
  inserir(a, 55);
  inserir(a, 44);
  inserir(a, 33);
  inserir(a, 66);
  inserir(a, 77);
  inserir(a, 45);
  inserir(a, 64);
  printf ("pre: ");
  imprimePreOrdem(a);
  printf ("\n");
  printf ("pos: ");
  imprimePosOrdem(a);
  printf ("\n");
  printf ("em: ");
  imprimeEmOrdem(a);
  printf ("\n");
  printf ("largura: ");
  imprimeEmLargura(a);
  printf ("\n");

  x = busca(a, 45);
  if (x == NULL) 
    printf ("Nao achou\n");
  else
    printf ("Achou %d \n", x->key);
  
  x = busca(a, 1);
  if (x == NULL) 
    printf ("Nao achou\n");
  else 
    printf ("Achou %d \n", x->key);
 
   x = busca(a, 55);
   a->raiz = rotR(a, x);
   printf ("Em largura depois de rotR(55)\n");
   imprimeEmLargura(a);
   printf("\n");

   a->raiz = rotL(a, a->raiz);
   printf ("Em largura depois de rotL(44)\n");
   imprimeEmLargura(a);
   printf("\n");

   inserirNaRaiz(a, 46);
   printf ("Insere na Raiz o elemento 46\n");
   imprimeEmLargura(a);
   printf("\n");
    
   return 0;
}
