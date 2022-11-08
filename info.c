#include "info.h"
#include <float.h>

//Inicializar todo al maximo o minimo posible
void inicializarInfo(struct info *info) {
	info->minAge = info->minDebt = info->minYearsEmployed = info->minCreditScore = info->minIncome = info->minZipCode = DBL_MAX;	//DBL MAX es el maximo valor para un double
	info->maxAge = info->maxDebt = info->maxYearsEmployed = info->maxCreditScore = info->maxIncome = info->maxZipCode = DBL_MIN;	//Lo mismo para el MIN
}
