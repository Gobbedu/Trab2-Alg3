#include "tree.h"

/* ===================== UTILS ===================== */
void opera(t_nodoA *treeA, char oper, char* str_treeB)
{
    t_nodoA* aux;
    /* redireciona para funcao apropriada */
    if( oper == 'i')
    {
        fprintf(stderr, "inserting %s : %d\n", str_treeB, index_strB(str_treeB));
        insert_tree(treeA, cria_arvoreB(str_treeB));
    
        printf("\n[");
        preordem_A(treeA);
        printf("]\n\n");
    }
    else if( oper == 'b')
    {
        aux = search_tree(treeA, index_strB(str_treeB));
        if( argc == 2)
            fprintf(stderr, "b %s : %d\n", str_treeB, index_strB(str_treeB));
        if( aux )
        {
            fprintf(stderr, "A árvore com o valor de indexação %d foi encontrada:\n",index_strB(str_treeB) );
            /*Mostrar o nodo achado*/
            while( aux->pai != NULL )
            {
                preordem_B(aux->key);
                aux = aux->pai;
                printf("\n");   
            }
        }
        else    
            fprintf(stderr, "A árvore com o valor de indexação %d nao foi encontrada\n",index_strB(str_treeB) );
    }
    else if( oper == 'r')
    {
        fprintf(stderr, "removing %s : %d\n", str_treeB, index_strB(str_treeB));
        if( !exclui(search_tree(treeA, index_strB(str_treeB))) )
            printf("nao foi possivel remover %s, chave %d nao existe\n", str_treeB, index_strB(str_treeB));

            printf("\n[");
            preordem_A(treeA);
            printf("]\n\n");
    }
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


int index_treeB(t_nodoB* nodoB)
{
    int index = 0;
    if(nodoB!=NULL)
    {
        if( nodoB->chave != EMPTY )
            index += nodoB->chave;

        if(nodoB->L != NULL  )
            index += index_treeB(nodoB->L);
        if(nodoB->R != NULL )
            index += index_treeB(nodoB->R);
    }

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
                
            opera(raizA, oper, inp, argc);
        }
    }
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
        // volta a ler da entrada
        if( raizA->key )
        preordem_A(raizA);
        printf("\n");

        fclose(input_stream);
        input_stream = stdin;
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
