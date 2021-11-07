#include "tree.h"

int main(int argc, char const *argv[])
{
    char oper, inp[MAX_SZ];
    strcpy(inp, "aux");

    t_nodoA treeA;


    A_init(&treeA);
    // B_init();

    while(1)
    {
        /* le operacao */
        fscanf(stdin, "%s", inp);
        if( stop(inp) )
            break;

        oper = read_oper(inp);

        /* le string(arvore) a ser operada */
        fscanf(stdin, "%s", inp);
        if( stop(inp) )
            break;
            
        opera(&treeA, oper, inp);
    }

    fprintf(stderr, "end input operator \n");

    return 0;
}
