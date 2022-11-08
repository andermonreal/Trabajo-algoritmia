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

void encolarUltimo(tipoColaC * c, bool a, double b, double d, bool e, bool f, char *g, char *h, double i, bool j, bool k, double l, bool m, char *n, double o, double p, bool q) {
	celdaColaC *aux;
	aux = (celdaColaC*)malloc(sizeof(celdaColaC));
	if (aux == NULL) {
		printf("Error al reservar memoria\n");
		exit(-1);
	}
	aux->elem.edad = a;
	aux->elem.sexo = b;
	aux->elem.CPT = d;
	aux->elem.RBP = e;
	aux->elem.colesterol = f;
	aux->elem.FBS = g;
	aux->elem.RECG = h;
	aux->elem.MaxHR = i;
	aux->elem.EA = j;
	aux->elem.OP = k;
	aux->elem.STS = l;
	aux->elem.HD = m;
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
