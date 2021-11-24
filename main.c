/* =======================================================
 *   Feito por 
 *    Eduardo Gobbo Willi Vasconcellos Goncalves
 *     &&
 *    Dante Eleutério dos Santos
 *   
 *   GRR20206686
 *   GRR20203892
 *  ======================================================= */

#include "tree.h"

int main(int argc, char const *argv[])
{
    t_nodoA* raizA;
    raizA = A_init(NULL);

    raizA=stream_input(argv, argc, raizA);

    free_treeA(raizA);

    return 0;
}
