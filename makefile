parametrosCompilacao = -Wall -lm 
nomePrograma = theboys

all: $(nomePrograma)

$(nomePrograma): the_boys.o conjuntos.o eventos.o LEF.o lista_encadeada.o mundo.o
	gcc -o $(nomePrograma) the_boys.o conjuntos.o eventos.o LEF.o lista_encadeada.o mundo.o $(parametrosCompilacao)

the_boys.o: the_boys.c
	gcc -c the_boys.c $(parametrosCompilacao)

conjuntos.o: conjuntos.h conjuntos.c
	gcc -c conjuntos.c $(parametrosCompilacao)

eventos.o: eventos.h eventos.c
	gcc -c eventos.c $(parametrosCompilacao)

LEF.o: LEF.h LEF.c
	gcc -c LEF.c $(parametrosCompilacao)

lista_encadeada.o: lista_encadeada.h lista_encadeada.c
	gcc -c lista_encadeada.c $(parametrosCompilacao)

mundo.o: mundo.h mundo.c
	gcc -c mundo.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
