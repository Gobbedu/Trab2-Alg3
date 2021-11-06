/* todo */


nodoB* cria_arvoreB()


nodoB* cria_nodoB(int chave)
{
    nodoB* nodo;
    nodo = malloc(sizeof(nodoB));
    if (nodo==NULL)
        kill("erro ao alocar nodo",1);
    
    nodo->pai=NULL;


}
