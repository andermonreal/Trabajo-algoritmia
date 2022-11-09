#include <stdlib.h>
#include "colaDobleCreditCard.h"
#include "info.h"

void normalizar(tipoColaC cola, struct info info) {
	// Recorremos la lista para normalizar los datos
	celdaColaC *aux = cola.ini;
	while (aux != NULL) {
		aux->elem.age = (aux->elem.age - info.minAge) / (info.maxAge - info.minAge);
		aux->elem.debt = (aux->elem.debt - info.minDebt) / (info.maxDebt - info.minDebt);
		aux->elem.yearsEmployed = (aux->elem.yearsEmployed - info.minYearsEmployed) / (info.maxYearsEmployed - info.minYearsEmployed);
		aux->elem.creditScore = (aux->elem.creditScore - info.minCreditScore) / (info.maxCreditScore - info.minCreditScore);
		aux->elem.income = (aux->elem.income - info.minIncome) / (info.maxIncome - info.minIncome);
		aux = aux->sig;
	}
}
