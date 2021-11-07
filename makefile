# =======================================================
#   Feito por 
#    Eduardo Gobbo Willi Vasconcellos Goncalves
#     &&
#    Dante Eleutério dos Santos
#   
#   GRR20206686
#   GRR20203892
#  ======================================================= 

CFLAGS = -Wall -ansi -g -std=c99

# nome do arquivo compilado
NAME = busca

# codigo
CODED = main.c tree.c 
#objetos gerados
objects = main.o  tree.o 


# REGRAS DE COMPILACAO
main: $(objects) 
	gcc -o $(NAME) $(objects) 

main.o: $(CODED)
	gcc $(CFLAGS) -c $(CODED)

clean:
	rm *.o 
