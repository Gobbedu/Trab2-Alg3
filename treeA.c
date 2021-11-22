#include "tree.h"

/* =================== ARVORE --A-- =================== */

/* transforma input string em integer */
t_nodoA* A_init(t_nodoA* thisPai)
{
    t_nodoB* auxB;
    auxB = malloc(sizeof(t_nodoB));
    auxB->chave = EMPTY;
    auxB->L = NULL;
    auxB->R = NULL;
    auxB->pai = NULL;

    t_nodoA* auxA;
    auxA = malloc(sizeof(t_nodoA));
    auxA->pai = thisPai;
    auxA->L = NULL;
    auxA->R = NULL;
    auxA->key = auxB;
    return auxA;
}

void insert_tree(t_nodoA* treeA, t_nodoB* nodoB)
{
    /* se nodo vazio */
    if( treeA->key->chave == EMPTY){
        treeA->key = nodoB;
    }
    /* se nodoB =< key --> L */
    else if( index_treeB(treeA->key) > index_treeB(nodoB) )
    {
        if( treeA->L == NULL )
            treeA->L = cria_nodoA(treeA, nodoB);
        else
            insert_tree(treeA->L, nodoB);
    }
    /* se nodoB >= key --> R */
    else if( index_treeB(treeA->key) < index_treeB(nodoB) )
    {
        if( treeA->R == NULL )
            treeA->R = cria_nodoA(treeA, nodoB);
        else
            insert_tree(treeA->R, nodoB);
    }
}

t_nodoA* search_tree(t_nodoA* nodoA, int index)
{
    /* Base: nodo vazio*/
    if ((nodoA == NULL) || (nodoA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (index_treeB(nodoA->key)<index)
        return (search_tree(nodoA->R, index));

    /* chave menor que nodo, procura da esquerda */
    if(index_treeB(nodoA->key)>index)
        return(search_tree(nodoA->L, index));
    
    return(nodoA);
}

t_nodoA *return_min(t_nodoA *nodo){
    if (nodo->L == NULL)
        return nodo;
    else
        return return_min(nodo->L);
}

t_nodoA *sucessor (t_nodoA *nodo){
    t_nodoA *s = NULL;
    if (nodo->R != NULL) 
        return return_min (nodo->R);
    else 
    {
        s = nodo->pai;
        while (s != NULL && nodo == s->R) {
            nodo = s;
            s = s->pai;
        }        
    }
    return s;
}

void ajustaNoPai(t_nodoA *nodo, t_nodoA *novo){
    if (nodo->pai != NULL) {
        if (nodo->pai->L == nodo)
            nodo->pai->L = novo;
        else
            nodo->pai->R = novo;
        if (novo != NULL)
           novo->pai = nodo->pai;
    }
}

int exclui (t_nodoA *nodo) 
{
    t_nodoA *s;
    if (nodo->L == NULL)
    {
        ajustaNoPai(nodo, nodo->R);
        remove_treeB(nodo->key);
        nodo->key=NULL;
        free (nodo);
        nodo=NULL;
        return 1;
    } 
    if (nodo->R == NULL)
    {
        ajustaNoPai(nodo, nodo->L);
        remove_treeB(nodo->key);
        nodo->key=NULL;
        free(nodo);
        nodo=NULL;
        return 1;
    }
    else 
    {            
        s = sucessor (nodo);
        ajustaNoPai(s, s->R);
        s->L = nodo->L;
        s->R = nodo->R;
        nodo->L->pai=s;
        ajustaNoPai(nodo, s);
        remove_treeB(nodo->key);
        nodo->key=NULL;
        free(nodo);
        nodo=NULL;
        return 1;
    }
    return 0;
}

t_nodoA* menorNodo(t_nodoA* nodoA)
{
    t_nodoA* atual;
    atual = nodoA;

    while(atual && atual->L != NULL)
        atual = atual->L;

    return atual;
}

t_nodoA* cria_nodoA(t_nodoA* nodoA, t_nodoB* nodoB)
{
    t_nodoA *aux = malloc(sizeof(t_nodoA));
    aux->key = nodoB;
    aux->pai = nodoA;
    aux->L = NULL;
    aux->R = NULL;
    return aux;
}

void preordem_A(t_nodoA *no)
{
    if (no != NULL)
    {
        int aux;
        if ( no->key != NULL )
        {
            aux = index_treeB(no->key);
            if( aux == EMPTY )
                aux = 0;

            if( no->key != NULL && no->key->chave != EMPTY)
            {
                printf("[");
                preordem_B(no->key);
                printf(" : %d\n", aux);
            }
            
            if(no->R != NULL || no->L != NULL){
                preordem_A(no->L);
                printf("]\n");
                preordem_A(no->R);
                printf("]\n");
            }
        }
    }
    else
    {
        printf("[\n");
    }
}

void free_treeA(t_nodoA* nodoA)
{
    if( nodoA != NULL )
    {
        free_treeA(nodoA->L);
        free_treeA(nodoA->R);
        remove_treeB(nodoA->key);
        free(nodoA);
    }
}
