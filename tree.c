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
    switch (c[0])
    {
    case 'i':
        return 'i';
        break;
    
    case 'b':
        return 'b';
        break;
    
    case 'r':
        return 'r';
        break;
    
    case '0':
        return '0';
        break;
    
    default:
        fprintf(stderr, "%s , operador nao valido\n", c);
        kill("operador invalido", 1);
        break;
    }
 
    return 0;
}

void opera(t_nodoA *treeA, char oper, char* str_treeB)
{
    /* redireciona para funcao apropriada */
    if( oper == 'i')
    {
        fprintf(stderr, "inserting %s : %d\n", str_treeB, index_strB(str_treeB));
        insert_tree(treeA, cria_arvoreB(str_treeB));
    }
    else if( oper == 'b')
    {
        fprintf(stderr, "searching %s : %d\n", str_treeB, index_strB(str_treeB));
        search_tree(treeA, index_strB(str_treeB));
        fprintf(stderr, "A árvore com o valor de indexação %d foi encontrada:\n",index_strB(str_treeB) );
        /*Mostrar o nodo achado*/

    }
    else if( oper == 'r')
    {
        fprintf(stderr, "removing %s : %d\n", str_treeB, index_strB(str_treeB));
        if( !exclui(search_tree(treeA,index_strB(str_treeB))) )
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
        free (no);
        return 1;
    } 
    else 
    {
        if (no->R == NULL)
        {
            ajustaNoPai(no, no->L);
            remove_treeB(no->key);
            free(no);
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
            free(no);
            return 1;
        }
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
        aux = index_treeB(no->key);
        if( aux == EMPTY )
            aux = 0;

        printf("[");

        if( no->key != NULL){
            preordem_B(no->key);
            printf(" : %d\n", aux);
        }

        preordem_A(no->L);
        preordem_A(no->R);
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

/* ===================== UTILS ===================== */


int index_treeB(t_nodoB* nodoB)
{
    int index = 0;
    if( nodoB->chave != EMPTY )
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
