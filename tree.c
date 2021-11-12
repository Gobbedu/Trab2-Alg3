#include "tree.h"

/* sequencia de operacoes :
    ~insert
    cria_arvoreB();
    insert_treeB();

    ~search
    index_strB();
    busca_tree();

    ~remove
    index_strB();
    busca_tree();
    remove_tree();
*/

/* =================== ARVORE --A-- =================== */

/* transforma input string em integer */
void A_init(t_nodoA* treeA)
{
    treeA->pai = NULL;
    treeA->L = NULL;
    treeA->R = NULL;
    treeA->key = NULL;
}

char read_oper(char* c)
{
    if( c[0] == 'i')
    {
        // fprintf(stdout, "insert operator\n");
        return c[0];
    }
    else if( c[0] == 'b')
    {
        // fprintf(stdout, "search operator\n");
        return c[0];
    }
    else if( c[0] == 'r')
    {
        // fprintf(stdout, "remove operator\n");
        return c[0];
    }
    else if( c[0] == '0' )
    {
        // fprintf(stdout, "end operator\n");
        return c[0];
    }
    else
    {
        fprintf(stderr, "%s , operador nao valido\n", c);
        kill("operador invalido", 1);
    }
    return 0;
}

void opera(t_nodoA *treeA, char oper, char* c)
{
    /* redireciona para funcao apropriada */
    if( oper == 'i')
    {
        fprintf(stderr, "inserting %s \n", c);
        insert_tree(treeA, cria_arvoreB(c));
    }
    else if( oper == 'b')
    {
        fprintf(stderr, "searching %s \n", c);
        search_tree(treeA, index_strB(c));
    }
    else if( oper == 'r')
    {
        fprintf(stderr, "removing %s \n", c);
        remove_tree(treeA, index_strB(c));
    }
}

void insert_tree(t_nodoA* treeA, t_nodoB* nodoB)
{
    /* se nodo vazio */
    if( treeA->key == NULL){
        treeA->key = nodoB;
    }
    /* se nodoB =< key --> L */
    else if( index_nodoB(treeA->key) <= index_nodoB(nodoB) )
    {
        if( treeA->L == NULL)
            treeA->L = cria_nodoA(treeA, nodoB);

        else
            insert_tree(treeA->L, nodoB);
    }
    /* se nodoB >= key --> R */
    else if( index_nodoB(treeA->key) >= index_nodoB(nodoB) )
    {
        if( treeA->R == NULL)
            treeA->R = cria_nodoA(treeA, nodoB);
        
        else 
            insert_tree(treeA->R, nodoB);
    }
}

t_nodoB* search_tree(t_nodoA* treeA, int index)
{
    /* TODO */
    
    /* Base: nodo vazio ou chave presente */
    if (treeA == NULL || treeA->key == NULL)
       return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (treeA->key == NULL)
       return search_tree(treeA->R, index);
 
    /* chave menor que nodo, procura da esquerda */
    return search_tree(treeA->L, index);
}

void remove_tree(t_nodoA* treeA, int index)
{   
    /* geeks for geeks tem explicacao massa */
    /* https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/?ref=lbp */
    t_nodoB* aux;
    aux = search_tree(treeA, index);
    if( aux == NULL )
        fprintf(stderr, "arvore %i nao encontrada\n", index);
    /*
    else 
        deleta arvoreB 'aux' 
    */

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
        printf("[");
        preordem_B(no->key);
        printf("\n");
        preordem_A(no->L);
        preordem_A(no->R);
        printf("]");
    }
}
/* ==================== ARVORE --B-- ==================== */
t_nodoB* cria_arvoreB(char* entrada)
{
    /* copiado e colado do T1 */
    int i, aux = 0;
    t_nodoB *raiz, *nodo, *atual;

    // printf("criando %s\n", entrada);

    atual = cria_nodoB();
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

t_nodoB* cria_nodoB(void)
{
    t_nodoB* nodo;
    nodo = malloc(sizeof(t_nodoB));
    if (nodo==NULL)
        kill("erro ao alocar nodo",1);
    
    nodo->pai = NULL;
    nodo->chave = 0;
    nodo->L = NULL;
    nodo->R = NULL;


    return nodo;
}

void preordem_B(t_nodoB *no)
{    
    if (no != NULL)
    {
        printf("(");
        printf("%d", no->chave);
        preordem_B(no->L);
        preordem_B(no->R);
        printf(")");
    }
}

/* ===================== UTILS ===================== */

/* calcula index arvore B com arvore? */
int index_nodoB(t_nodoB* nodoB/*, char* c  */)
{
    /* TODO */
    return 0;
}
/* calcula index arvore B com string? */
int index_strB(char* c)
{
    /* TODO */
    return 0;
}

void place_nodoB(t_nodoB *this, t_nodoB *folha)
{
    /* salva anterior */
    folha->pai = this;
    
    /* se esquerda livre */    
    if( this->L == NULL )
        this->L = folha;
    
    /* se esquerda ocupada */
    else if( this->L != NULL && this->R == NULL)
        this->R = folha;

    /* se ambos ocupado */
    else 
        kill("nao foi possivel colocar folha", 2); 
}

int my_atoi(char* c, int i, int *diff)
{
    int aux, n = 1;
    /* contabiliza quantos caracteres pular ao ler int maior que 9 */
    *diff = 0;
    
    /* numeros '48' == 0 e '57' == 9 */
    if (c[i] >= 48 && c[i] <= 57)
    {
        aux = c[i] - 48; 
    
        /* enquanto proximo caracter for numero */
        while((i+n + 1) < strlen(c) && (c[i + n] >= 48 &&  c[i + n] <= 57) )
        {
            aux *= 10;
            aux += c[i+n] - 48;
            n++;
        }

        *diff = n - 1;

        // printf("aux: %d\n", aux); printf("diff: %d\n", *diff);

        return aux;
    }

    /* caso  contrario */
    fprintf(stderr, "to num: '%c', ", c[i]);
    kill("operacao nao suportada", 2);
    return 0;
}

int stop(char* c)
{
    return !strcmp(c, "0") || !strcmp(c, "");
}
void kill(char *msg, int signal)
{
    fprintf(stderr, "%s\n", msg);
    exit(signal);
}
