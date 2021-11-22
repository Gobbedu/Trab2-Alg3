#include "tree.h"
/* ==================== ARVORE --B-- ==================== */

t_nodoB* cria_arvoreB(char* entrada)
{
    int i, aux = 0;
    t_nodoB *raiz, *nodo, *atual;

    // printf("criando %s\n", entrada);

    atual = NULL;
    raiz = NULL;
    i = 0;
    while(entrada[i] != '\0')
    {
        /*
        printf("lendo %c\n", entrada[i]);
        */
        if (entrada[i] == '(')
        {
            /* se raiz nao existe ( primeiro nodo ) */
            if( raiz == NULL )
            {
                raiz = cria_nodoB();
                atual = raiz;
            }
            /* insere novo nodo */
            else
            {
                nodo = cria_nodoB();
                /* assing pai */
                nodo->pai = atual;
                /* se esquerda livre */    
                if( atual->L == NULL )
                    atual->L = nodo;
                /* se esquerda ocupada */
                else if(atual->R == NULL)
                    atual->R = nodo;
                /* se ambos ocupado */
                else 
                    kill("nao foi possivel colocar folha", 2); 
                atual = nodo;
            }

            
        }    
        else if (entrada[i] == ')' && atual != raiz )
            atual = atual->pai;
    
        else if ( entrada[i] != '(' && entrada[i] != ')')
        {
            // atual->chave = atoi(entrada[i]);
            atual->chave = my_atoi(entrada, i, &aux);
            i += aux;
        }
        
        i++;
    }

    return raiz;
}

void remove_treeB(t_nodoB* nodoB)
{
    /* remove arvore inteira */
    if( nodoB != NULL )
    {
        remove_treeB(nodoB->L);
        remove_treeB(nodoB->R);
        free(nodoB);
    }
}

t_nodoB* cria_nodoB(void)
{
    t_nodoB* nodo;
    nodo = malloc(sizeof(t_nodoB));
    if (nodo==NULL)
        kill("erro ao alocar nodo",1);
    
    nodo->pai = NULL;
    nodo->chave = EMPTY;
    nodo->L = NULL;
    nodo->R = NULL;


    return nodo;
}

void preordem_B(t_nodoB *no)
{    
    if (no != NULL)
    {
        printf("(");
        if( no->chave != EMPTY )
            printf("%d", no->chave);

        preordem_B(no->L);
        preordem_B(no->R);
        printf(")");
    }
}

