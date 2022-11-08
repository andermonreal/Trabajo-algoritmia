#ifndef TIPOS
#define TIPOS

#include <stdbool.h>


/* Todos los atributos numéricos deben ser de tipo decimal, ya que despues de normalizarlos quedan en el intervalo [0,1] */
typedef struct ejemplo {
	bool gender;
	double age;
	double debt;
	bool married;
	bool bankCustomer;
	char *industry;
	char *ethnicity;
	double yearsEmployed;
	bool priorDefault;	//Ns q es este atributo pero es booleano
	bool employed;
	double creditScore;
	bool driverLicense;
	char *citizen;
	double zipCode;
	double income;
	bool approved; // valor real la clase que vamos a predecir. Debemos compararla con la prediccion para ver si hemos acertado o no
	double distancia; // la lista esta ordenada ascendentemente en funcion del campo distancia, para que podamos tomar los k mas proximos
	bool esOutlier; // true si el valor es un outlier, false en caso contrario
} ejemplo;

#endif
