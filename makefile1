CC=gcc
CFLAGS=-Wall
DEPENDENCIAS=colaDobleCreditCard.o info.o leer_datos.o listaOrdenadaEjemplos.o main1.o normalizar.o

all: main1
	./main1

main1: $(DEPENDENCIAS)
	$(CC) $(CFLAGS) $(DEPENDENCIAS) -lm -o main1

colaDobleCreditCard.o: colaDobleCreditCard.c colaDobleCreditCard.h
	$(CC) $(CFLAGS) -c colaDobleCreditCard.c

info.o: info.c info.h
	$(CC) $(CFLAGS) -c info.c

leer_datos.o: leer_datos.c leer_datos.h
	$(CC) $(CFLAGS) -c leer_datos.c

listaOrdenadaEjemplos.o: listaOrdenadaEjemplos.c listaOrdenadaEjemplos.h
	$(CC) $(CFLAGS) -c listaOrdenadaEjemplos.c

main1.o: main1.c
	$(CC) $(CFLAGS) -c main1.c

normalizar.o: normalizar.c normalizar.h
	$(CC) $(CFLAGS) -c normalizar.c

clean:
	rm -f *.o main1
