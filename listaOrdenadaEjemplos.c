#include "listaOrdenadaEjemplos.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void nuevaLista(tipoLista *lista) {
	lista->ini = lista->fin = NULL;
}

void insertar(tipoLista *lista, tipoElementoLista elem) {
	celdaLista *nuevaCelda = (celdaLista*)malloc(sizeof(celdaLista));
	if (nuevaCelda == NULL) {
		printf("Error al reservar memoria en insertar.\n");
		exit(-1);
	}
	nuevaCelda->elem = elem;
	celdaLista *celdaActual = lista->ini;
	while (celdaActual != NULL && celdaActual->elem.distancia < elem.distancia) {
		celdaActual = celdaActual->sig;
	}
	if (celdaActual == NULL) {
		nuevaCelda->sig = NULL;
		nuevaCelda->ant = lista->fin;
		if (esNulaLista(*lista)) {
			lista->ini = nuevaCelda;
		} else {
			lista->fin->sig = nuevaCelda;
		}
		lista->fin = nuevaCelda;
	} else {
		nuevaCelda->ant = celdaActual->ant;
		nuevaCelda->sig = celdaActual;
		if (celdaActual->ant == NULL) {
			lista->ini = nuevaCelda;
		} else {
			celdaActual->ant->sig = nuevaCelda;
		}
		celdaActual->ant = nuevaCelda;
	}
}

void eliminarMenor(tipoLista *lista) {
	if (esNulaLista(*lista)) {
		printf("Error en eliminarMenor. La lista está vacía.\n");
		exit(-1);
	}
	celdaLista *tmp = lista->ini;
	if (tmp->sig == NULL) {
		lista->ini = lista->fin = NULL;
	} else {
		lista->ini = tmp->sig;
		tmp->sig->ant = NULL;
	}
	free(tmp);
}

void eliminarMayor(tipoLista *lista) {
	if (esNulaLista(*lista)) {
		printf("Error en eliminarMayor. La lista esta vacia.\n");
		exit(-1);
	}
	celdaLista *tmp = lista->fin;
	if (tmp->ant == NULL) {
		lista->ini = lista->fin = NULL;
	} else {
		lista->fin = tmp->ant;
		tmp->ant->sig = NULL;
	}
	free(tmp);
}

tipoElementoLista consultarMenor(tipoLista lista) {
	if (esNulaLista(lista)) {
		printf("Error en consultarMenor. La lista esta vacia.\n");
		exit(-1);
	}
	return lista.ini->elem;
}

tipoElementoLista consultarMayor(tipoLista lista) {
	if (esNulaLista(lista)) {
		printf("Error en consultarMayor. La lista esta vacia.\n");
		exit(-1);
	}
	return lista.fin->elem;
}

bool estaElemento(tipoLista lista, tipoElementoLista elem) {
	celdaLista *celda = lista.ini;
	while (celda != NULL && celda->elem.distancia <= elem.distancia) {
		if (celda->elem.distancia == elem.distancia)
			return true;
		celda = celda->sig;
	}
	return false;
}

bool esNulaLista(tipoLista lista) {
	return lista.ini == NULL;
}

void imprimirLista (tipoLista l){
	celdaLista *q;
	int i;
	if(esNulaLista(l)){
		printf("Error, lista nula");
		exit(-1);
	}
	q = l.ini;
	while(q->sig != NULL){
		printf("\t%lf", q->elem.distancia);
		printf(" %c", q->elem.approved == Y? 'Y' : 'N');
		q = q->sig;
		i++;
	}
	printf("\t%lf", q->elem.distancia);
	printf(" %c", q->elem.approved == Y? 'Y' : 'N');
	printf("\n");
	printf("\n%d\n", i);
}
