#ifndef TIPOS
#define TIPOS

#include <stdbool.h>

typedef enum { M, F } genderType;
typedef enum { Y, N } marriedType, bankCustomerType, employedType, driverType, result;
typedef enum { White, Black, Asian, Other} ethniciType;
typedef enum { ByBirth, ByOtherMeans} citizenType;

/* Todos los atributos numéricos deben ser de tipo decimal, ya que despues de normalizarlos quedan en el intervalo [0,1] */
typedef struct ejemplo {
	genderType gender;
	double age;
	double debt;
	marriedType married;
	bankCustomerType bankCustomer;
	/*char *industry;*/
	ethniciType ethnicity;
	double yearsEmployed;
	/*bool priorDefault;	Ns q es este atributo pero es booleano*/
	employedType employed;
	double creditScore;
	driverType driverLicense;
	citizenType citizen;
	/*double zipCode;*/
	double income;
	result approved; // valor real la clase que vamos a predecir. Debemos compararla con la prediccion para ver si hemos acertado o no
	double distancia; // la lista esta ordenada ascendentemente en funcion del campo distancia, para que podamos tomar los k mas proximos
	bool esOutlier; // true si el valor es un outlier, false en caso contrario
} ejemplo;

#endif
