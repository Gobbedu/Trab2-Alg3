/* =======================================================
 *   Feito por 
 *    Dante Eleutério dos Santos
 *     &&
 *    Eduardo Gobbo Willi Vasconcellos Goncalves
 *   
 *   GRR20206686
 *   GRR20203892
 *  ======================================================= */

#include "tree.h"

/* =================== ARVORE --A-- =================== */

/* inicializa nodo A */
t_nodoA* A_init(t_nodoA* thisPai)
{
    /* nodo arvore A vazio com chave arvore B vazia */
    t_nodoA* auxA;
    auxA = malloc(sizeof(t_nodoA));
    if( !auxA )
        kill("alocacao raiz falhou", 1);
    
    auxA->pai = thisPai;
    auxA->L = NULL;
    auxA->R = NULL;
    auxA->key=NULL;
    return auxA;
}

/* insere arvore B em arvore A */
void insert_tree(t_nodoA* treeA, t_nodoB* nodoB)
{
    /* se nodo vazio */
    if( !treeA->key){
        treeA->key = nodoB;
    }
    /* se nodoB < key --> L */
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
    /* se arvore ja existe nao inclui */
    else
        remove_treeB(nodoB);
}

t_nodoA* search_tree(t_nodoA* nodoA, int index)
{
    /* Base: nodo vazio*/
    if ((nodoA == NULL) || (nodoA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (index_treeB(nodoA->key) < index)
        return (search_tree(nodoA->R, index));

    /* chave menor que nodo, procura da esquerda */
    else if(index_treeB(nodoA->key) > index)
        return(search_tree(nodoA->L, index));
    
    /* achou a chave */
    else
        return(nodoA);
}

/* retorna menor index a partir de nodo */
t_nodoA *return_min(t_nodoA *nodo){
    if (nodo->L == NULL)
        return nodo;
    else
        return return_min(nodo->L);
}

/* retorna sucessor de nodo */
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

/* ajusta pai de nodo para remocao */
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

/* exclui nodo A e ajusta arvore A*/
t_nodoA *exclui (t_nodoA *nodo,t_nodoA *raiz) 
{
    t_nodoA *s;
    t_nodoA *novaraiz = raiz;

        if (nodo->L == NULL)
        {
            ajustaNoPai(nodo, nodo->R);
            if (nodo==raiz)
            {
                if(!nodo->R)
                    novaraiz=NULL;
                else
                    novaraiz=nodo->R;
            }
            free_nodoA(nodo);
        } 
        else {
            if (nodo->R == NULL)
            {
                ajustaNoPai(nodo, nodo->L);
                if (nodo==raiz)
                    novaraiz=nodo->L;
                free_nodoA(nodo);
            }
            else {            
                s = sucessor (nodo);
                ajustaNoPai(s, s->R);
                s->L = nodo->L;
                s->R = nodo->R;
                nodo->L->pai=s;
                ajustaNoPai(nodo, s);
                if(nodo == raiz)
                    novaraiz=s;             
                free_nodoA(nodo);
            }
        }
        return novaraiz;
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

/* imprive arvore A em pre ordem */
void preordem_A(t_nodoA *no)
{
    int aux;

    if ( no != NULL )
    {
        if ( no->key != NULL )
        {
            aux = index_treeB(no->key);
            if( aux == EMPTY )
                aux = 0;

            printf("[");
            if( no->key->chave != EMPTY )
            {
                preordem_B(no->key);
                printf(" : %d\n", aux);
            }
            
            /* se tem uma folha ou mais */
            if(no->R != NULL || no->L != NULL){
                preordem_A(no->L);
                printf("]\n");
                preordem_A(no->R);
                printf("]\n");
            }
        }
    }
    else
        printf("[\n");
}

/* libera nodo A */
void free_nodoA(t_nodoA* nodoA)
{
    remove_treeB(nodoA->key);
    free(nodoA);
}

/* libera arvore A */
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
