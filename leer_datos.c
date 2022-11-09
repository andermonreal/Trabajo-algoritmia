#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"
#include "macros.h"
#include "colaDobleCreditCard.h"

void leer_datos(char *fichero, tipoColaC* cola, struct info *info) { // metemos los datos del CSV en una cola doble
	FILE* archivo = fopen(fichero, "r");
	if (archivo == NULL) {
		printf("Error. El archivo %s no existe o no tienes permisos.\n", fichero);
		exit(-1);
	}
	char linea[500];
	fgets(linea, 500, archivo); // descartamos primera linea (nombres atributos)
	while (fgets(linea, 500, archivo)) {
		char datos[16][100];	//Numero de columnas 16
		char *delimitador = ",\r\n";
		char *token = strtok(linea, delimitador);
		int i = 0;
		while (token && i < 16) {
			strcpy(datos[i], token); // copiamos a datos[i] la columna i
			token = strtok(NULL, delimitador); // siguiente valor hasta la coma
			i++;
		}
		//Adaptar los datos
		genderType gender;
		if(strcmp(datos[0], "0") == 0){
			gender = F;
		}
		else{
			gender = M;
		}
		double age = atof(datos[1]);
		double debt = atof(datos[2]);

		marriedType married;
		if(strcmp(datos[3], "1") == 0){
			married = Y;
		}
		else{
			married = N;
		}

		bankCustomerType bankCustomer;
		if(strcmp(datos[4], "1") == 0){
			bankCustomer = Y;
		}
		else{
			bankCustomer = N;
		}

		//La columna de la industria no nos interesa asi que no la tratamos

		ethniciType ethnicity;
		if(strcmp(datos[6], "White") == 0){
			ethnicity = White;
		}
		else if(strcmp(datos[6], "Black")==0){
			ethnicity = Black;
		}
		else if(strcmp(datos[6], "Asian")== 0){
			ethnicity = Asian;
		}
		else{
			ethnicity = Other;
		}

		double yearsEmployed = atof(datos[7]);

		//La columna de prior default tampoco nos interesa, no la tratamos

		employedType employed;
		if(strcmp(datos[9], "1") == 0){
			employed = Y;
		}
		else{
			employed = N;
		}

		double creditScore = atoi(datos[10]);

		driverType driverLicense;
		if(strcmp(datos[11], "1") == 0){
			driverLicense = Y;
		}
		else{
			driverLicense = N;
		}

		citizenType citizen;
		if(strcmp(datos[12], "ByBirth") == 0){
			citizen = ByBirth;
		}
		else{
			citizen = ByOtherMeans;
		}

		//ZipCode tiene demasiadas opciones asi q no la tratamos

		double income = atoi(datos[14]);

		result approved;
		if(strcmp(datos[15], "1") == 0){
			approved = Y;
		}
		else{
			approved = N;
		}

		encolarUltimo(cola, gender, age, debt, married, bankCustomer, ethnicity, yearsEmployed, employed, creditScore, driverLicense, citizen, income, approved);

		// actualizar maximos y minimos
		info->minAge = min(info->minAge, age);
		info->maxAge = max(info->maxAge, age);
		info->minDebt = min(info->minDebt, debt);
		info->maxDebt = max(info->maxDebt, debt);
		info->minYearsEmployed = min(info->minYearsEmployed, yearsEmployed);
		info->maxYearsEmployed = max(info->maxYearsEmployed, yearsEmployed);
		info->minCreditScore = min(info->minCreditScore, creditScore);
		info->maxCreditScore = max(info->maxCreditScore, creditScore);
		info->minIncome = min(info->minIncome, income);
		info->maxIncome = max(info->maxIncome, income);
	}
	fclose(archivo);
}
