#include "tree.h"

int main(int argc, char const *argv[])
{
    char oper, inp[MAX_SZ];
    strcpy(inp, "aux");

    /* ====== Testes arvore B ==========
    char entrada[] = "(1(2)(3))";
    char entrada[] = "((((8)1(9))2((7)5(3)))4(9))";
    char entrada[] = "(1(15)(1(51)(1(51)(1(15)(1(15)(1(51)(15)))))))";

    char entrada[] = ((((8)*(9))+((7)/(3)))-(9)) = 65
    char entrada[] = ((9)-(((8)*(9))+((7)/(3)))) = -65
    char entrada[] = (+(1)(+(1)(+(1)(+(1)(+(1)(+(1)(1)))))))
    char entrada[] = (+(0)(+(1)(+(2)(+(3)(+(4)(+(5)(+(6)(+(7)(+(8)(9))))))))))

    t_nodoB *B;
    B = cria_arvoreB(entrada);
    preordem_B(B);
    printf("\n");
*/ 

    t_nodoA treeA;
    
    A_init(&treeA);
    // B_init();

    while(1)
    {
        // le operacao
        fscanf(stdin, "%s", inp);
        if( stop(inp) )
            break;

        oper = read_oper(inp);

        // le string(arvore) a ser operada 
        fscanf(stdin, "%s", inp);
        if( stop(inp) )
            break;
            
        opera(&treeA, oper, inp);
        preordem_A(&treeA);
        printf("\n");
    }

    fprintf(stderr, "end input operator \n");

    return 0;
}
