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

/* 
[OK] funcao que calcula index da arvore B
[ ] funcao de excluir arvore B
[ ] funcao de excluir arvore A
[OK] funcao de buscar  arvore B

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
        search_treeB(treeA, index_strB(c));
        fprintf(stderr, "A árvore com o valor de indexação %d foi encontrada:\n",index_strB(c) );
        /*Mostrar o nodo achado*/

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
    else if( index_treeB(treeA->key) >index_treeB(nodoB) )
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

t_nodoB* search_treeB(t_nodoA* treeA, int index)
{
    /* Base: nodo vazio*/
    if ((treeA == NULL) || (treeA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (index_treeB(treeA->key)<index)
        return (search_treeB(treeA->R, index));

    /* chave menor que nodo, procura da esquerda */
    if(index_treeB(treeA->key)>index)
        return(search_treeB(treeA->L, index));
    
    return(treeA->key);
}

t_nodoA* search_treeA(t_nodoA* treeA, int index)
{
    /* Base: nodo vazio*/
    if ((treeA == NULL) || (treeA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (index_treeB(treeA->key)<index)
        return (search_treeA(treeA->R, index));

    /* chave menor que nodo, procura da esquerda */
    if(index_treeB(treeA->key)>index)
        return(search_treeA(treeA->L, index));
    
    return(treeA);
}

void reorganize_tree(t_nodoA* treeA)
{
    if(treeA->L==NULL && treeA->R ==NULL)
        treeA=NULL;
    else
        if(treeA->L!=NULL)
        {
            treeA=treeA->L;
            reorganize_tree(treeA->L);
        }
        else
        {
            treeA=treeA->R;
            reorganize_tree(treeA->R);
        }
}

void remove_tree(t_nodoA* treeA, int index)
{   
    /* geeks for geeks tem explicacao massa */
    /* https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/?ref=lbp */
    t_nodoB* aux=NULL;
    aux = search_treeB(treeA, index);
    if( aux == NULL )
        fprintf(stderr, "arvore %i nao encontrada\n", index);
    else
        reorganize_tree(search_treeA(treeA,index));
            

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
        aux = index_treeB(no->key);
        if( aux == EMPTY )
            aux = 0;

        printf("[");
        preordem_B(no->key);
        printf(" : %d\n", aux);
        preordem_A(no->L);
        preordem_A(no->R);
        printf("]\n");
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
        if( no->chave != EMPTY)
            printf("%d", no->chave);

        preordem_B(no->L);
        preordem_B(no->R);
        printf(")");
    }
}

/* ===================== UTILS ===================== */


int index_treeB(t_nodoB* nodoB)
{
    int index = 0;
    index += nodoB->chave;

    if(nodoB->L != NULL  )
        index += index_treeB(nodoB->L);
    if(nodoB->R != NULL )
        index += index_treeB(nodoB->R);

    return index;     
}

/* calcula index arvore B com string */
int index_strB(char* entrada)
{
    int i=0;
    int aux = 0;
    int index = 0;
    while(entrada[i] != '\0')
    {
        if ( entrada[i] != '(' && entrada[i] != ')')
        {
            index += my_atoi(entrada, i, &aux);
            i += aux;
        }
        i++;
    }
    return index;
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

void stream_input(char const *argv[], int argc, t_nodoA* raizA)
{
    FILE* input_stream;
    char oper, inp[MAX_SZ];


    /* redireciona entrada */
    if( argc == 1)
        input_stream = stdin;
    else if( argc == 2 )
    {
        input_stream = fopen(argv[1], "r");

        while(!feof(input_stream)){
            // le operacao
            fscanf(input_stream, "%s", inp);

            oper = read_oper(inp);

            // le string(arvore) a ser operada 
            fscanf(input_stream, "%s\n", inp);
    
            opera(raizA, oper, inp);
        }
        // volta a ler da entrada
        input_stream = stdin;
        printf("\n");
        preordem_A(raizA);
        printf("\n");
    }
    else
    {
        printf("uso: ./busca (interacao manual)\n)");
        printf("     ./busca entrada.txt (arquivo com operacoes automatizadas)\n");
        kill("", 1);
    }

    /* interacao manual */
    while(1)
    {
        // le operacao
        fscanf(input_stream, "%s", inp);
        if( stop(inp) )
            break;

        oper = read_oper(inp);

        // le string(arvore) a ser operada 
        fscanf(input_stream, "%s", inp);
        if( stop(inp) )
            break;
            
        opera(raizA, oper, inp);
        printf("\n");
        preordem_A(raizA);
        printf("\n");
    }
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

        if(aux == EMPTY)
            return 0;

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
    if(!strcmp(c, "0") || !strcmp(c, ""))
    {
        fprintf(stderr, "end input operator \n");
        return 1;
    }
    return 0;
}
void kill(char *msg, int signal)
{
    fprintf(stderr, "%s\n", msg);
    exit(signal);
}
