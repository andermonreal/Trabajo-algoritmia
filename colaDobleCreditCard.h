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
	celdaColaC* ini;
	celdaColaC* fin;
}tipoColaC;

void nuevaColaCC(tipoColaC*);

bool esNulo(tipoColaC);

void encolarUltimo(tipoColaC *, genderType, double, double, marriedType, bankCustomerType, ethniciType, double, employedType, double, driverType, citizenType, double, result);

void desencolarPrimero(tipoColaC *);

tipoElementoColaC elemPrimero(tipoColaC);

#endif