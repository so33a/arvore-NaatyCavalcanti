#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"

ARVORE novaArvore() {
  ARVORE a = malloc(sizeof(struct arvore));  
  a->z = malloc(sizeof(struct node));
  a->raiz = a->z;
  a->raiz->left = a->raiz->right = a->z;
  a->z->left = a->z->right = a->z;
  return a;
}

void imprimePreOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    printf ("%d ", h->key);
    imprimePreOrdemR(a, h->left);
    imprimePreOrdemR(a, h->right);
  }
}

int contaNosR (ARVORE a, link h) {
  if(h == a->z) return 0;
  return 1 + contaNosR(a, h->left) + contaNosR(a, h->right);
}

int contaParesR (ARVORE a, link h) {
  if(h == a->z) 
    return 0;
  if (h->key %2 == 0) 
    return 1 + contaParesR(a, h->left) + contaParesR(a, h->right);
  else
    return  contaParesR(a, h->left) + contaParesR(a, h->right);
}

void imprimePreOrdem (ARVORE a) {
  imprimePreOrdemR(a, a->raiz);
}
void imprimePosOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    imprimePosOrdemR(a, h->left);
    imprimePosOrdemR(a, h->right);
    printf ("%d ", h->key);
  }
}

void imprimePosOrdem (ARVORE a) {
  imprimePosOrdemR(a, a->raiz);
}

void imprimeEmOrdemR (ARVORE a, link h) {
   if (h != a->z) {
     imprimeEmOrdemR(a, h->left);
     printf("%d ", h->key);
     imprimeEmOrdemR(a, h->right);
   }
}

void imprimeEmOrdem (ARVORE a) {
   imprimeEmOrdemR(a, a->raiz); 
}

link buscaR (ARVORE a, link h, int key) {
  if(h == a->z) return NULL;
  if(h->key == key) return h;
  if( h->key < key) 
    return buscaR(a, h->right, key);
  return buscaR(a, h->left, key);
}


link busca (ARVORE a, int key){
  return buscaR(a, a->raiz, key);
}

link novoNo(int key, link l, link r) {
  link x = malloc(sizeof(struct node));
  x->key = key;
  x->left = l;
  x->right = r;
  return x;
}
link inserirR (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key) 
    h->right = inserirR(a, h->right, key);
  else 
    h->left = inserirR(a, h->left, key);
  return h;
}
link inserirT (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key)  {
    h->right = inserirT(a, h->right, key);
    h = rotL(a, h);
  }
  else {
    h->left = inserirT(a, h->left, key);
    h = rotR(a, h);
  }
  return h;
}

void inserirNaRaiz(ARVORE a, int key) {
  a->raiz = inserirT(a, a->raiz, key);
}

void inserir (ARVORE a, int key){
  a->raiz = inserirR(a, a->raiz, key);
}

void imprimeEmLargura (ARVORE a) {
  link aux;
  FILA f = novaFila();
  enfilar(f, a->raiz);
  while (f->primeiro != NULL) {
    aux = desenfilar(f);
    printf ("%d ", aux->key);
    if (aux->left != a->z)  {
      enfilar (f,aux->left);
    }
    if (aux->right != a->z) {
      enfilar (f,aux->right);
    }
  }
  destroiFila(f);
}

link rotL(ARVORE a, link h) {
  link x = h->right;
  h->right = x->left;
  x->left = h;
  return x; 
}
link rotR(ARVORE a, link h) {
  link x = h->left;
  h->left = x->right;
  x->right = h;
  return x;
}

void remover (ARVORE a, int key){
   removerNo(a, busca(a, key));
}

void removerNo (ARVORE a, link node){
	link aux = a->raiz;
    link pai = NULL;
    char direcao;

    if(node == aux ){
        pai = NULL;
    }else if(node->key < aux->key){     //lado esquerdo
        if(node->key == aux->left->key){
            pai = aux;
            direcao = 'e';
        }else{
            removerNo(aux->left, node);
        }
    }else if(node->key >= aux->key){    //lado Direito
        if(node->key == aux->right->key){
            pai = aux;
            direcao = 'd';
        }else{
            removerNo(aux->right, node);
        }
    }

    if(node->left == a->z && node->right == a->z){ ///Node é uma FOLHA
        if(direcao == 'e'){
            pai->left = a->z;
        }else
            pai->right = a->z;
        free(node);
    }else if(node->left != a->z && node->right == a->z){ ///Node tem UM FILHO a ESQUERDA
        if(direcao == 'e'){
            pai->left = node->left;
        }else
            pai->right = node->left;
    }else if(node->left == a->z && node->right != a->z){ ///Node tem UM FILHO a DIREITA
        if(direcao == 'e'){
            pai->left = node->right;
        }else
            pai->right = node->right;
    }else{  /// Node tem DOIS FILHOS
        link auxNode1 = node;
        link auxNode2 = node->left;

        while(auxNode2->right != a->z){
            auxNode1 = auxNode2;
            auxNode2 = auxNode2->right;
        }
        if(auxNode1 != node){
            auxNode1->right = auxNode2->left;
            auxNode2->left = node->left;
        }
        auxNode2->right = node->right;
        a->raiz = auxNode2;
    }
    free(node);
}

void destroiArvore(ARVORE a){
  if(a->raiz != a->z){
        destroiArvore(a->raiz->left);
        destroiArvore(a->raiz->right);
    }
    free(a);
}
