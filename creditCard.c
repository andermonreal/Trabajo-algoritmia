#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "info.h"
#include "tipos.h"
#include "normalizar.h"
#include "leer_datos.h"
#include "colaDobleCreditCard.h"
#include "listaOrdenadaEjemplos.h"

bool aplicar_knn(tipoColaC, ejemplo *, int);
double calcularDistancia(ejemplo, ejemplo);
result obtenerClaseMasPrometedora(tipoLista);

int main() {
	struct info info;
	inicializarInfo(&info);
	struct ejemplo elemento;

	tipoColaC datasetEntrenamiento;
	nuevaColaCC(&datasetEntrenamiento);
	leer_datos("credit_card.csv", &datasetEntrenamiento, &info);


// normalizamos el dataset en la cola que lo hemos introducido
	normalizar(datasetEntrenamiento, info);

	char ch;
	char strin[50];
	do {
		printf("\n----------Introdución de datos----------\n\n");
	//pedimos al usuario el elemento que quiere comparar con el resto para saber el resultado
		printf("Introduce el género de la persona (M o F): ");
		scanf(" %s", strin);
		if(strcmp(strin, "M") == 0){
			elemento.gender = M;
		}
		else{
			elemento.gender = F;
		}
		printf("Introduce la edad de la persona: ");
		scanf("%lf", &elemento.age);
		printf("Introduce la deuda de la persona: ");
		scanf("%lf", &elemento.debt);
		printf("Introduce si la persona está casada o no (Y o N): ");
		scanf(" %s", strin);
		if(strcmp(strin, "Y") == 0){
			elemento.married = Y;
		}
		else{
			elemento.married = N;
		}
		printf("Introduce si la persona es cliente o no del banco (Y o N): ");
		scanf(" %c", strin);
		if(strcmp(strin, "Y") == 0){
			elemento.bankCustomer = Y;
		}
		else{
			elemento.bankCustomer = N;
		}
		printf("Introduce la raza de la persona (Black, White, Asian, Other): ");
		scanf("%s", strin);
		if(strcmp(strin, "White") == 0){
			elemento.ethnicity = White;
		}
		else if(strcmp(strin, "Black")==0){
			elemento.ethnicity = Black;
		}
		else if(strcmp(strin, "Asian")== 0){
			elemento.ethnicity = Asian;
		}
		else{
			elemento.ethnicity = Other;
		}
		printf("Introduce los años que lleva trabajando la persona: ");
		scanf("%lf", &elemento.yearsEmployed);
		printf("Introduce si la persona tiene trabajo o no (Y o N): ");
		scanf(" %c", strin);
		if(strcmp(strin, "N") != 0){
			elemento.employed = Y;
		}
		else{
			elemento.employed = N;
		}
		printf("Introduce la solvencia de la persona: ");
		scanf("%lf", &elemento.creditScore);
		printf("Introduce si la persona tiene o no licencia de conducir (Y o N): ");
		scanf(" %c", strin);
		if(strcmp(strin, "Y") == 0){
			elemento.driverLicense = Y;
		}
		else{
			elemento.driverLicense = N;
		}
		printf("Introduce si la persona está empadronada en la ciudad o no (ByBirth o ByOtherMeans): ");
		scanf("%s", strin);
		if(strcmp(strin, "ByBirth") == 0){
			elemento.citizen = ByBirth;
		}
		else{
			elemento.citizen = ByOtherMeans;
		}
		printf("Introduce los ingresos de la persona: ");
		scanf("%lf", &elemento.income);

		tipoColaC datoAevaluar;
		nuevaColaCC(&datoAevaluar);

		encolarUltimo(&datoAevaluar, elemento.gender, elemento.age, elemento.debt, elemento.married, elemento.bankCustomer, elemento.ethnicity, elemento.yearsEmployed, elemento.employed, elemento.creditScore, elemento.driverLicense, elemento.citizen, elemento.income, N);
	//de momento comparamos solo con un vecino
		normalizar(datoAevaluar, info);

		elemento = elemPrimero(datoAevaluar);
		const int K = 1;

	//Comienzo del KNN
		printf("\nComienzo de la clasificación...\n");
		bool exito = aplicar_knn(datasetEntrenamiento, datoAevaluar.ini, K); //aplicamos knn al elemento nuevo que hemos introducido, comparándolo con el resto de elementos de nuestro dataset
		if(exito){
			printf("La tarjeta de crédito ha sido aprobada\n\n");
		}
		else{
			printf("La tarjeta de crédito NO ha sido aprobada\n\n");
		}
		printf("Fin de la clasificación\n\n");

		printf("¿Desea introducir un nuevo elemento (s/n)? ");
		scanf(" %c", &ch);

	} while (ch == 's');
}

bool aplicar_knn(tipoColaC dataset, ejemplo *ejemplo, int K) {
	tipoLista lista;
	nuevaLista(&lista); // nueva lista ordenada de menor a mayor

	celdaColaC *c = dataset.ini;
// Meto todos los elementos a una lista para evitar compararme conmigo mismo y, comparo las distancias hacia mí con cada elemento
	while (c != NULL) {

		if (&c->elem == ejemplo) { // no comparar un elemento consigo mismo
			c = c->sig;
			continue;
		}

		struct ejemplo ej; // Una auxiliar temporal donde voy poniendo los datos y metiendolos a la lista

		ej.gender = c->elem.gender;
		ej.age = c->elem.age;
		ej.debt = c->elem.debt;
		ej.married = c->elem.married;
		ej.bankCustomer = c->elem.bankCustomer;
		ej.ethnicity = c->elem.ethnicity;
		ej.yearsEmployed = c->elem.yearsEmployed;
		ej.employed = c->elem.employed;
		ej.creditScore = c->elem.creditScore;
		ej.driverLicense = c->elem.driverLicense;
		ej.citizen = c->elem.citizen;
		ej.income = c->elem.income;
		ej.distancia = calcularDistancia(*ejemplo, c->elem);
		ej.approved = c->elem.approved;

		insertar(&lista, ej);

		c = c->sig;
	}
	imprimirLista(lista);
	result clase = obtenerClaseMasPrometedora(lista);
// imprimimos resultados de la prediccion
	printf("Clase predicha: %c\n", clase == Y? 'Y' : 'N');
	if(clase == N){
		return false;
	}
	else if(clase == Y){
		return true;
	}
	else{
		printf("error en la clase\n");
	}

}

double calcularDistancia(ejemplo ejemplo1, ejemplo ejemplo2) {
	return sqrt(
		(ejemplo1.gender == ejemplo2.gender? 0 : 1)+
		pow(ejemplo1.age - ejemplo2.age, 2) +
		pow(ejemplo1.debt - ejemplo2.debt, 2) +
		(ejemplo1.married == ejemplo2.married? 0 : 1) +
		(ejemplo1.bankCustomer == ejemplo2.bankCustomer? 0 : 1) +
		(ejemplo1.ethnicity == ejemplo2.ethnicity? 0 : 1) +
		pow(ejemplo1.yearsEmployed - ejemplo2.yearsEmployed, 2) +
		(ejemplo1.employed == ejemplo2.employed? 0 : 1) +
		pow(ejemplo1.creditScore - ejemplo2.creditScore, 2) +
		(ejemplo1.driverLicense == ejemplo2.driverLicense? 0 : 1) +
		(ejemplo1.citizen == ejemplo2.citizen? 0 : 1) +
		pow(ejemplo1.income - ejemplo2.income, 2)
	);
}

result obtenerClaseMasPrometedora(tipoLista lista) {

	celdaLista *c = lista.ini; //miramos solo al primer elemento de la lista

//solo hace falta comparar con el primer elemento de la lista ya que es el que menos distancia tiene a nuestro ejemplo y solo queremos comparar con un vecino
	if (c->elem.approved == Y) {
		printf("Gana la clase Y.\n");
		return Y;
	} else {
		printf("Gana la clase N.\n");
		return N;
	}
}
