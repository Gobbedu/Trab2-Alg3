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
#define EMPTY -2147483646

typedef struct t_nodoB 
{
    int chave;
    struct t_nodoB *pai;
    struct t_nodoB *L;
    struct t_nodoB *R;
}t_nodoB;

typedef struct t_nodoA
{
    struct t_nodoA *pai;
    struct t_nodoB *key;
    struct t_nodoA *L;
    struct t_nodoA *R;
}t_nodoA;



/* ARVORE A */
t_nodoB* search_for_treeB(t_nodoA* treeA, int index);
t_nodoA* search_for_treeA(t_nodoA* treeA, int index);
t_nodoA* cria_nodoA(t_nodoA* nodoA, t_nodoB* nodoB);
t_nodoA* remove_treeA(t_nodoA* treeA, int index);
t_nodoA* menorNodo(t_nodoA* nodo);

void insert_tree(t_nodoA* treeA, t_nodoB* nooB);
void opera(t_nodoA* treeA, char oper, char* c);
void reorganize_tree(t_nodoA* treeA);
void preordem_A(t_nodoA* nodo);
void free_treeA(t_nodoA* raiz);
void A_init(t_nodoA* treeA);
char read_oper(char* c);

/* ARVORE B */
void remove_treeB(t_nodoB* nodo);
void preordem_B(t_nodoB* nodo);
t_nodoB* cria_arvoreB(char* c);
t_nodoB* cria_nodoB(void);

/* UTILS */
void stream_input(char const *argv[], int argc, t_nodoA* raizA);

int index_strB(char* c);
int index_nodoB(t_nodoB* nodoB);
int my_atoi(char* c, int i, int *diff);
int index_treeB(t_nodoB* nodoB);

int my_atoi(char* c, int i, int *diff);

int stop(char* c);
void kill(char *msg, int sig);

#endif