/* =======================================================
 *   Feito por 
 *    Eduardo Gobbo Willi Vasconcellos Goncalves
 *     &&
 *    Dante Eleutério dos Santos
 *   
 *   GRR20206686
 *   GRR20203892
 *  ======================================================= */

#ifndef __TREE__
#define __TREE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoB 
{
    struct nodoB *pai;
    int chave;
    struct nodoB *L;
    struct nodoB *R;
}nodoB;
typedef struct nodoA
{
    struct nodoA *pai;
    struct nodoB *key;
    struct nodoA *L;
    struct nodoA *R;
}nodoA;

typedef struct Arvore_A
{
    struct nodoA *raiz;
}Arvore_A;

typedef struct Arvore_B
{
    struct nodoB *raiz;
}Arvore_B;



#endif