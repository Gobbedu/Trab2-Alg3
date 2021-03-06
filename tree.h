/* =======================================================
 *   Feito por 
 *    Dante Eleutério dos Santos
 *     &&
 *    Eduardo Gobbo Willi Vasconcellos Goncalves
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
t_nodoA *opera(t_nodoA* treeA, char oper, char* c, int argc);
t_nodoA* cria_nodoA(t_nodoA* nodoA, t_nodoB* nodoB);
t_nodoA* search_tree(t_nodoA* nodoA, int index);
t_nodoA *exclui (t_nodoA *no,t_nodoA *raiz) ;
t_nodoA *return_min(t_nodoA *no);
t_nodoA *sucessor (t_nodoA *no);
t_nodoA* A_init(t_nodoA* pai);

void insert_tree(t_nodoA* treeA, t_nodoB* nooB);
void ajustaNoPai(t_nodoA *no, t_nodoA *novo);
void preordem_A(t_nodoA* nodo);
void free_treeA(t_nodoA* raiz);
void free_nodoA(t_nodoA* nodo);
char read_oper(char* c);

/* ARVORE B */
t_nodoB* cria_arvoreB(char* c);
t_nodoB* cria_nodoB(void);

void remove_treeB(t_nodoB* nodo);
void preordem_B(t_nodoB* nodo);

int index_treeB(t_nodoB* nodoB);
int index_strB(char* c);

/* UTILS */
t_nodoA *stream_input(char const *argv[], int argc, t_nodoA* raizA);

void mostra_caminho(t_nodoA* nodo);
void kill(char *msg, int sig);

int my_atoi(char* c, int i, int *diff);
int stop(char* c);

#endif