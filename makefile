all: creditCard
	./creditCard

main1: colaDobleCreditCard.o info.o leer_datos.o listaOrdenadaEjemplos.o creditCard.o normalizar.o
	gcc -Wall colaDobleCreditCard.o info.o leer_datos.o listaOrdenadaEjemplos.o creditCard.o normalizar.o -lm -o creditCard

colaDobleCreditCard.o: colaDobleCreditCard.c colaDobleCreditCard.h
	gcc -Wall -c colaDobleCreditCard.c

info.o: info.c info.h
	gcc -Wall -c info.c

leer_datos.o: leer_datos.c leer_datos.h
	gcc -Wall -c leer_datos.c

listaOrdenadaEjemplos.o: listaOrdenadaEjemplos.c listaOrdenadaEjemplos.h
	gcc -Wall -c listaOrdenadaEjemplos.c

creditCard.o: creditCard.c
	gcc -Wall -c creditCard.c

normalizar.o: normalizar.c normalizar.h
	gcc -Wall -c normalizar.c

clean:
	rm -f *.o creditCard
