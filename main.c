#include "tree.h"

int main(int argc, char const *argv[])
{
    t_nodoA* raizA;
    raizA = A_init(NULL);

    stream_input(argv, argc, raizA);

    free_treeA(raizA);

    return 0;
}
