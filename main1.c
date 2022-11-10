#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "info.h"
#include "tipos.h"
#include "normalizar.h"
#include "leer_datos.h"
#include "colaDobleCreditCard.h"
#include "listaOrdenadaEjemplos.h"

bool aplicar_knn(tipoColaC, ejemplo *, int);
double calcularDistancia(ejemplo, ejemplo);
result obtenerClaseMasPrometedora(tipoLista, int);

int main() {
	struct info info;
	inicializarInfo(&info);
	struct ejemplo elemento;
	
	tipoColaC datasetEntrenamiento;
	nuevaColaDC(&datasetEntrenamiento);
	leer_datos("entrenamiento1.csv", &datasetEntrenamiento, &info);


// normalizamos el dataset en la cola que lo hemos introducido
	normalizar(datasetEntrenamiento, info);
	
	char ch;
	do {
		
	//pedimos al usuario el elemento que quiere comparar con el resto para saber el resultado
		printf("Introduce el género de la persona (M o F): ");
		scanf(" %c", &elemento.gender);
		printf("Introduce la edad de la persona: ");
		scanf("%lf", &elemento.age);
		printf("Introduce la deuda de la persona: ");
		scanf("%lf", &elemento.debt);
		printf("Introduce si la persona está casada o no (Y o N): ");
		scanf(" %c", &elemento.married);
		printf("Introduce si la persona es cliente o no del banco (Y o N): ");
		scanf(" %c", &elemento.bankCustomer);
		printf("Introduce la raza de la persona (Black, White, Asian, Other): ");
		scanf("%s", &elemento.ethnicity);
		printf("Introduce los años que lleva trabajando la persona: ");
		scanf("%lf", &elemento.yearsEmployed);
		printf("Introduce si la persona tiene trabajo o no (Y o N): ");
		scanf(" %c", &elemento.employed);
		printf("Introduce la solvencia de la persona: ");
		scanf("%lf", &elemento.creditScore);
		printf("Introduce si la persona tiene o no licencia de conducir (Y o N): ");
		scanf(" %c", &elemento.driverLicense);
		printf("Introduce si la persona está empadronada en la ciudad o no (ByBitrh o ByOtherMeans): ");
		scanf("%s", &elemento.citizen);
		printf("Introduce los ingresos de la persona: ");
		scanf("%lf", &elemento.income);
	
	//de momento comparamos solo con un vecino
		const int K = 1;
		
	//Comienzo del KNN
		printf("\nComienzo de la clasificacion...\n");
		int cont = 0;
		bool exito = aplicar_knn(datasetEntrenamiento, &elemento, K); // aplicamos knn a cada elemento del dataset de prueba
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
	nuevaLista(&lista); // nueva lista ordenada

	celdaColaC *c = dataset.ini;
	while (c != NULL) {

		if (&c->elem == ejemplo || c->elem.esOutlier) { // no comparar un elemento consigo mismo ni con outliers
			c = c->sig;
			continue;
		}

		struct ejemplo tmp;

		tmp.gender = c->elem.gender;
		tmp.age = c->elem.age;
		tmp.debt = c->elem.debt;
		tmp.married = c->elem.married;
		tmp.bankCustomer = c->elem.bankCustomer;
		tmp.ethnicity = c->elem.ethnicity;
		tmp.yearsEmployed = c->elem.yearsEmployed;
		tmp.employed = c->elem.employed;
		tmp.creditScore = c->elem.creditScore;
		tmp.driverLicense = c->elem.driverLicense;
		tmp.citizen = c->elem.citizen;
		tmp.income = c->elem.income;
		tmp.distancia = calcularDistancia(*ejemplo, c->elem);

		insertar(&lista, tmp);

		c = c->sig;
	}
	result clase = obtenerClaseMasPrometedora(lista, K);
	bool b = true;
// imprimimos resultados de la prediccion
	printf("Clase predicha: %c\n", clase == Y? 'Y' : 'N');
	if(clase == N){
		b = false;
	}

	return b;
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

result obtenerClaseMasPrometedora(tipoLista lista, int K) {
	int countClaseN = 0; // numero de veces que aparece la clase N (en los K mas cercanos)
	int countClaseY = 0; // numero de veces que aparece la clase Y (en los K mas cercanos)

	double distanciaTotalClaseN = 0; // suma de todas las distancias hacia clase N (en los K mas cercanos)
	double distanciaTotalClaseY = 0; // suma de todas las distancias hacia clase Y (en los K mas cercanos)

	int i = 0;
	celdaLista *c = lista.ini;
	while(c != NULL && i < K) { // recorremos los k vecinos mas proximos
		if (c->elem.approved == Y) {
			distanciaTotalClaseY += c->elem.distancia;
			countClaseY++;
		} else {
			distanciaTotalClaseN += c->elem.distancia;
			countClaseN++;
		}
		c = c->sig;
		i++;
	}

	double distanciaMediaClaseN = distanciaTotalClaseN / countClaseN;
	double distanciaMediaClaseY = distanciaTotalClaseY / countClaseY;

	printf("La clase Y aparece %d veces. La clase N aparece %d veces.\n", countClaseY, countClaseN);

	if (countClaseN > countClaseY) {
		printf("Gana la clase N.\n");
		return N;
	} else if (countClaseN < countClaseY) {
		printf("Gana la clase Y.\n");
		return Y;
	} else { // empate (ambas clases se repiten el mismo numero de veces)
		printf("Ha habido un empate. Se va a tomar la media de todas las distancias\n");
		printf("Distancia media clase N: %.2lf. Distancia media clase Y: %.2lf.\n", distanciaMediaClaseN, distanciaMediaClaseY);
		if (distanciaMediaClaseN < distanciaMediaClaseY) {
			printf("Gana la clase N.\n");
			return N;
		} else {
			printf("Gana la clase Y.\n");
			return Y;
		}
	}
}
