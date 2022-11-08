#ifndef COLA_DOBLE_CREDITCARD
#define COLA_DOBLE_CREDITCARD

#include <stdbool.h>
#include "tipos.h"

typedef ejemplo tipoElementoColaC;
typedef struct celdaCC {
	tipoElementoColaC elem;
	struct celdaCC *ant;
	struct celdaCC *sig;
} celdaColaC;

typedef struct tipoCDC {
	celdaColaH* ini;
	celdaColaH* fin;
}tipoColaC;

void nuevaColaDC(tipoColaC*);

bool esNulo(tipoColaC);

void encolarUltimo(tipoColaC *, bool, double, double, bool, bool, char *, char *, double, bool, bool, double, bool, char *, double, double, bool);

void desencolarPrimero(tipoColaC *);

#endif