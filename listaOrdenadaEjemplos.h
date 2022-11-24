#ifndef LISTA_ORDENADA_EJEMPLOS
#define LISTA_ORDENADA_EJEMPLOS

#include <stdbool.h>
#include "tipos.h"

typedef ejemplo tipoElementoLista;
typedef struct celdaL {
	tipoElementoLista elem;
	struct celdaL *sig;
	struct celdaL *ant;
}celdaLista;
typedef struct tipoL {
	celdaLista *ini;
	celdaLista *fin;
}tipoLista;

void nuevaLista(tipoLista *);

void insertar(tipoLista *, tipoElementoLista);

void eliminarMenor(tipoLista *);

void eliminarMayor(tipoLista *);

tipoElementoLista consultarMenor(tipoLista);

tipoElementoLista consultarMayor(tipoLista);

bool estaElemento(tipoLista, tipoElementoLista);

bool esNulaLista(tipoLista);

void concatenar(tipoLista *, tipoLista *);

#endif