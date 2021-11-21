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

[ ] corrigir imprime da arvore A
[ ] corrigir imprime da arvore B
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

void opera(t_nodoA *treeA, char oper, char* str_treeB)
{
    /* redireciona para funcao apropriada */
    if( oper == 'i')
    {
        fprintf(stderr, "inserting %s \n", str_treeB);
        insert_tree(treeA, cria_arvoreB(str_treeB));
    }
    else if( oper == 'b')
    {
        fprintf(stderr, "searching %s \n", str_treeB);
        search_for_treeB(treeA, index_strB(str_treeB));
        fprintf(stderr, "A árvore com o valor de indexação %d foi encontrada:\n",index_strB(str_treeB) );
        /*Mostrar o nodo achado*/

    }
    else if( oper == 'r')
    {
        fprintf(stderr, "removing %s \n", str_treeB);
        if( !remove_treeA(treeA, index_strB(str_treeB)) )
            printf("nao foi possivel remover %s, chave %d nao existe\n", str_treeB, index_strB(str_treeB));
    }
}

void insert_tree(t_nodoA* treeA, t_nodoB* nodoB)
{
    /* se nodo vazio */
    if( treeA->key == NULL){
        treeA->key = nodoB;
    }
    /* se nodoB =< key --> L */
    else if( calc_index(treeA->key) >calc_index(nodoB) )
    {
        if( treeA->L == NULL)
            treeA->L = cria_nodoA(treeA, nodoB);
        else
            insert_tree(treeA->L, nodoB);
    }
    /* se nodoB >= key --> R */
    else if( calc_index(treeA->key) < calc_index(nodoB) )
    {
        if( treeA->R == NULL)
            treeA->R = cria_nodoA(treeA, nodoB);
        
        else 
            insert_tree(treeA->R, nodoB);
    }
}

t_nodoB* search_for_treeB(t_nodoA* treeA, int index)
{
    /* Base: nodo vazio*/
    if ((treeA == NULL) || (treeA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (calc_index(treeA->key)<index)
        return (search_for_treeB(treeA->R, index));

    /* chave menor que nodo, procura da esquerda */
    if(calc_index(treeA->key)>index)
        return(search_for_treeB(treeA->L, index));
    
    return(treeA->key);
}

t_nodoA* search_for_treeA(t_nodoA* treeA, int index)
{
    /* Base: nodo vazio*/
    if ((treeA == NULL) || (treeA->key == NULL))
        return NULL;
    
    /* chave maior que nodo, procura na direita */
    if (calc_index(treeA->key)<index)
        return (search_for_treeA(treeA->R, index));

    /* chave menor que nodo, procura da esquerda */
    if(calc_index(treeA->key)>index)
        return(search_for_treeA(treeA->L, index));
    
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

t_nodoA* remove_treeA(t_nodoA* root, int key)
{   
    /* geeks for geeks tem explicacao massa */
    /* https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/?ref=lbp */
    // t_nodoB* aux=NULL;
    // aux = search_for_treeB(treeA, index);
    // if( aux == NULL )
    //     fprintf(stderr, "arvore %i nao encontrada\n", index);
    // else
    //     reorganize_tree(search_for_treeA(treeA,index));
// =====================================================================================
//     struct node* remove_treeA(struct node* root, int key)
// {
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
        printf("[");
        preordem_B(no->key);
        printf("\n");
        preordem_A(no->L);
        preordem_A(no->R);
        printf("]");
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
        if( no->chave != EMPTY && no->chave != NULL)
            printf("%d", no->chave);

        preordem_B(no->L);
        preordem_B(no->R);
        printf(")");
    }
}

/* ===================== UTILS ===================== */


int calc_index(t_nodoB* nodoB)
{
    int index=0;
    index+=nodoB->chave;
    if(nodoB->L!=NULL)
        index+=calc_index(nodoB->L);
    if(nodoB->R!=NULL)
        index+=calc_index(nodoB->R);
    return index;     
}

/* calcula index arvore B com string */
int index_strB(char* entrada)
{
    int i=0;
    int aux = 0;
    int index=0;
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
    //folha->pai = this;
    
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
