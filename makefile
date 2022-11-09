CC=gcc
CFLAGS=-Wall
DEPENDENCIAS=colaDobleCreditCard.o info.o leer_datos.o listaOrdenadaEjemplos.o Main.o normalizar.o

all: Main
	./Main

Main: $(DEPENDENCIAS)
	$(CC) $(CFLAGS) $(DEPENDENCIAS) -lm -o Main

colaDobleCreditCard.o: colaDobleCreditCard.c colaDobleCreditCard.h
	$(CC) $(CFLAGS) -c colaDobleCreditCard.c

info.o: info.c info.h
	$(CC) $(CFLAGS) -c info.c

leer_datos.o: leer_datos.c leer_datos.h
	$(CC) $(CFLAGS) -c leer_datos.c

listaOrdenadaEjemplos.o: listaOrdenadaEjemplos.c listaOrdenadaEjemplos.h
	$(CC) $(CFLAGS) -c listaOrdenadaEjemplos.c

Main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c

normalizar.o: normalizar.c normalizar.h
	$(CC) $(CFLAGS) -c normalizar.c

clean:
	rm -f *.o Main