#include "tree.h"

/* =================== ARVORE --A-- =================== */

/* transforma input string em integer */
t_nodoA* A_init(void)
{
    t_nodoB* auxB;
    auxB = malloc(sizeof(t_nodoB));
    auxB->chave = EMPTY;
    auxB->L = NULL;
    auxB->R = NULL;
    auxB->pai = NULL;

    t_nodoA* auxA;
    auxA = malloc(sizeof(t_nodoA));
    auxA->pai = NULL;
    auxA->L = NULL;
    auxA->R = NULL;
    auxA->key = auxB;
    return auxA;
}

void insert_tree(t_nodoA* treeA, t_nodoB* nodoB)
{
    /* se nodo vazio */
    if( treeA->key == NULL){
        treeA->key = nodoB;
    }
    /* se nodoB =< key --> L */
    else if( index_treeB(treeA->key) > index_treeB(nodoB) )
    {
        if( treeA->L == NULL)
            treeA->L = cria_nodoA(treeA, nodoB);
        else
            insert_tree(treeA->L, nodoB);
    }
    /* se nodoB >= key --> R */
    else if( index_treeB(treeA->key) < index_treeB(nodoB) )
    {
        if( treeA->R == NULL)
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

t_nodoA *min(t_nodoA *no){
    if (no->L == NULL)
        return no;
    else
        return min(no->L);
}

t_nodoA *sucessor (t_nodoA *no){
    t_nodoA *s = NULL;
    if (no->R != NULL) 
        return min (no->R);
    else 
    {
        s = no->pai;
        while (s != NULL && no == s->R) {
            no = s;
            s = s->pai;
        }        
    }
    return s;
}

void ajustaNoPai(t_nodoA *no, t_nodoA *novo){
    if (no->pai != NULL) {
        if (no->pai->L == no)
            no->pai->L = novo;
        else
            no->pai->R = novo;
        if (novo != NULL)
           novo->pai = no->pai;
    }
}

int exclui (t_nodoA *no) 
{
    t_nodoA *s;
    if (no->L == NULL)
    {
        ajustaNoPai(no, no->R);
        remove_treeB(no->key);
        no->key=NULL;
        free (no);
        no=NULL;
        return 1;
    } 
    if (no->R == NULL)
    {
        ajustaNoPai(no, no->L);
        remove_treeB(no->key);
        no->key=NULL;
        free(no);
        no=NULL;
        return 1;
    }
    else 
    {            
        s = sucessor (no);
        ajustaNoPai(s, s->R);
        s->L = no->L;
        s->R = no->R;
        no->L->pai=s;
        ajustaNoPai(no, s);
        remove_treeB(no->key);
        no->key=NULL;
        free(no);
        no=NULL;
        return 1;
    }
    return 0;
}

t_nodoA* remove_treeA(t_nodoA* root, int key)
{   
    /* geeks for geeks tem explicacao massa */
    /* https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/?ref=lbp */

    t_nodoA* temp;

    // caso base
    if (root == NULL)
        return root;
 
    // se chave a deletar for menor que chave da raiz a chave esta a esquerda
    if (key < index_treeB(root->key) )
        root->L = remove_treeA(root->L, key);
 
    // se chave a deletar for maior que chave da raiz a chave esta a direita
    else if (key > index_treeB(root->key) )
        root->R = remove_treeA(root->R, key);
 
    // achou a chave a deletar
    else if( key == index_treeB(root->key) )
    {
        // nodo com uma folha
        if (root->L == NULL && root->R != NULL) {
            temp = root->R;
            remove_treeB(root->key);
            free(root);
            return temp;
        }
        else if (root->R == NULL && root->L != NULL) {
            temp = root->L;
            remove_treeB(root->key);
            free(root);
            return temp;
        }
 
        // nodo com duas folhas
        else if( root->L != NULL && root->R != NULL)
        {
            // Get the inorder successor
            // (smallest in the right subtree)
            temp = menorNodo(root->R);
    
            // Copy the inorder
            // successor's content to this node
            root->key = temp->key;
    
            // Delete the inorder successor
            root->R = remove_treeA(root->R, index_treeB(temp->key) );
        }

        // nodo eh folha
        else if( root->L == NULL && root->R == NULL )
        {
            remove_treeB(root->key);
            free(root);
            root = NULL;
        }
    }
    // nao achou a chave a deletar, retorna nada
    else    
        return NULL;

    return root;
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
        printf("[");
        if ( no->key != NULL )
        {
            aux = index_treeB(no->key);
            if( aux == EMPTY )
                aux = 0;

            if( no->key != NULL && no->key->chave != EMPTY)
            {
                preordem_B(no->key);
                printf(" : %d\n", aux);
            }

            preordem_A(no->L);
            preordem_A(no->R);
        }
        printf("]\n");
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

