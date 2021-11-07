#include "tree.h"

/* ARVORE ----A---- */



/* ARVORE ----B---- */
nodoB* cria_arvoreB()
{}


nodoB* cria_nodoB(int chave)
{
    nodoB* nodo;
    nodo = malloc(sizeof(nodoB));
    if (nodo==NULL)
        kill("erro ao alocar nodo",1);
    
    nodo->pai=NULL;


}

/* UTILS */
void kill(char *msg, int signal)
{
    fprintf(stderr, "%s\n", msg);
    exit(signal);
}
