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

/* tamanho maximo de uma string no input */
#define MAX_SZ 200

typedef struct t_nodoB 
{
    int chave;
    struct nodoB *pai;
    struct nodoB *L;
    struct nodoB *R;
}t_nodoB;

typedef struct t_nodoA
{
    struct nodoA *pai;
    struct nodoB *key;
    struct nodoA *L;
    struct nodoA *R;
}t_nodoA;

typedef struct Arvore_A
{
    struct t_nodoA *raiz;
}Arvore_A;

typedef struct Arvore_B
{
    struct t_nodoB *raiz;
}Arvore_B;

/* ARVORE A */
char read_oper(char* c);
void opera(t_nodoA* treeA, char oper, char* c);
void insert_tree(t_nodoA* treeA, t_nodoB* nooB);
void search_tree(t_nodoA* treeA, int index);
void remove_tree(t_nodoA* treeA, int index);

void A_init(t_nodoA* treeA);
t_nodoA* cria_nodoA(t_nodoA* nodoA, t_nodoB* nodoB);


/* ARVORE B */


/* UTILS */
int index_strB(char* c);
int index_nodoB(t_nodoB* nodoB);

int my_atoi(char* c, int i, int *diff);

int stop(char* c);
void kill(char *msg, int sig);

#endif