#include "tree.h"

int main(int argc, char const *argv[])
{
    t_nodoA raizA;
    A_init(&raizA);

    stream_input(argv, argc, &raizA);

    preordem_A(&raizA);

    return 0;
}
