#include <stdio.h>
#include <stdlib.h>
#include "colaDobleCreditCard.h"
#include <stdbool.h>

void nuevaColaDC(tipoColaC*c) {
	c->ini = NULL;
	c->fin = NULL;
}

bool esNulo(tipoColaC c) {
	return(c.ini == NULL);
}

void encolarUltimo(tipoColaC *c, genderType a, double b , double d, marriedType e, bankCustomerType f, ethniciType g, double h, employedType i, double j, driverType k, citizenType l, double m, result n){
	celdaColaC *aux;
	aux = (celdaColaC*)malloc(sizeof(celdaColaC));
	if (aux == NULL) {
		printf("Error al reservar memoria\n");
		exit(-1);
	}
	aux->elem.gender = a;
	aux->elem.age = b;
	aux->elem.debt = d;
	aux->elem.married = e;
	aux->elem.bankCustomer = f;
	aux->elem.ethnicity = g;
	aux->elem.yearsEmployed = h;
	aux->elem.employed = i;
	aux->elem.creditScore = j;
	aux->elem.driverLicense = k;
	aux->elem.citizen = l;
	aux->elem.income = m;
	aux->elem.approved;
	aux->elem.distancia = -1;
	aux->elem.esOutlier = false;
	aux->sig = NULL;
	if (esNulo(*c)) {
		aux->ant = NULL;
		c->ini = aux;
		c->fin = aux;
	} else {
		aux->ant = c->fin;
		c->fin->sig = aux;
		c->fin = aux;
	}
}

void desencolarPrimero(tipoColaC *c) {
	if (esNulo(*c)) {
		printf("\tERROR en el modulo colaDobleCreditcard: no se puede desencolar en una cola vacia\n");
	} else {
		celdaColaC *aux;
		aux = c->ini;
		c->ini = aux->sig;
		if (c->ini == NULL) {
			c->fin = NULL;
		} else {
			c->ini->ant = NULL;
		}
		free(aux);
	}
}
