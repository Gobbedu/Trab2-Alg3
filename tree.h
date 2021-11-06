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

#define MUL 2147483647
#define DIV 2147483646
#define ADD -2147483646
#define SUB -2147483647

#define OPER_SZ 100


struct nodoB 
{
    struct nodoB *pai;
    int chave;
    struct nodoB *L;
    struct nodoB *R;
};
struct nodoA
{
    struct nodoA *pai;
    struct nodoB *key;
    struct nodoA *L;
    struct nodoA *R;
};

struct Arvore_A
{
    struct nodoA *raiz;
};

struct Arvore_B
{
    struct nodoB *raiz;
};

int opera(struct no *nodo);
int resolve_arvore(struct tree *arvore, struct no *nodo);
int temp(struct tree *arvore, struct no *nodo);
void place_nodo(struct no *galho, struct no *folha);
void cresce_arvore(struct tree *arvore, char* entrada);
void planta_arvore(struct tree *arvore);
int pai_de_folhas(struct no *nodo);
int to_num(char *c, int i, int *diff);
struct no* cria_nodo(void);
int folha(struct no *nodo);
int pai(struct no *nodo);
void kill(char* msg, int sig);


#endif