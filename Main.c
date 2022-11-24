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


void aplicar_wilson(tipoColaC, int);
bool aplicar_knn_eficiencia(tipoColaC, ejemplo *, int);
bool aplicar_knn_elemento(tipoColaC, ejemplo *, int);
double calcularDistancia(ejemplo, ejemplo);
result obtenerClaseMasPrometedora(tipoLista, int);
// result obtenerClaseMasPrometedoraElemento(tipoLista);
void mostrar_ejemplo(ejemplo);

int main() {
	int x;

	struct info info;
	inicializarInfo(&info);

	printf("Si quieres calcular la precisión del algoritmo pulsa 1, si quieres insertar un nuevo elemento a comprobar pulsa 2, y si quieres aplicar wilson pulsa 3: ");
	scanf(" %d", &x);

	switch(x){
		case 1:
			char fichero[100];
			tipoColaC datasetEntrenamiento;
			nuevaColaCC(&datasetEntrenamiento);
			printf("Introduce el nombre del dataset de entrenamiento: ");
			scanf("%s", fichero);
			leer_datos(fichero, &datasetEntrenamiento, &info);

			tipoColaC datasetPrueba;
			nuevaColaCC(&datasetPrueba);
			printf("\nIntroduce el nombre del dataset de prueba: ");
			scanf("%s", fichero);
			leer_datos(fichero, &datasetPrueba, &info);

			// normalizamos ambos datasets
			normalizar(datasetEntrenamiento, info);
			normalizar(datasetPrueba, info);

			printf("Dataset de entrenamiento (normalizado):\n");
			celdaColaC *c = datasetEntrenamiento.ini;
			while (c != NULL) {
				mostrar_ejemplo(c->elem);
				c = c->sig;
			}

			printf("Dataset de prueba (normalizado):\n");
			c = datasetPrueba.ini;
			while (c != NULL) {
				mostrar_ejemplo(c->elem);
				c = c->sig;
			}

			char ch;
			do {
				int K;
				printf("\nIntroduce K, para elegir los K vecinos mas cercanos: ");
				scanf("%d", &K);

				printf("\nComienzo de la clasificacion...\n");
				int aciertos = 0, count = 0;
				celdaColaC *c = datasetPrueba.ini;
				while (c != NULL) {
					printf("Ejemplo #%d\n", count + 1);
					mostrar_ejemplo(c->elem);
					bool exito = aplicar_knn_eficiencia(datasetEntrenamiento, &c->elem, K); // aplicamos knn a cada elemento del dataset de prueba
					if (exito) {
						aciertos++;
					}
					count++;
					c = c->sig;
					printf("\n");
				}
				printf("Fin de la clasificación\n\n");
				printf("Número de aciertos: %d\n", aciertos);
				printf("Número de pruebas: %d\n", count);

				if (count > 0) {
					float precision = ((float)aciertos / count) * 100;
					printf("Precision total: %.2f%%\n", precision);
				}

				printf("Desea repetir el entrenamiento (s/n)? ");
				scanf(" %c", &ch);

				if (ch == 's') { // resetear valores del dataset de entrenamiento
					celdaColaC *c = datasetEntrenamiento.ini;
					while (c != NULL) {
						c->elem.distancia = -1;
						c->elem.esOutlier = false;
						c = c->sig;
					}
				}
			} while (ch == 's');
			break;

		case 2:

			struct ejemplo elemento;

			tipoColaC datasetEntrenamiento1;
			nuevaColaCC(&datasetEntrenamiento1);
			leer_datos("credit_card.csv", &datasetEntrenamiento1, &info);


		// normalizamos el dataset en la cola que lo hemos introducido
			normalizar(datasetEntrenamiento1, info);


			do {
				char strin[10];

				int K;
				printf("\nIntroduce K, para elegir los K vecinos mas cercanos: ");
				scanf("%d", &K);

				printf("\n----------Introdución de datos----------\n\n");
			//pedimos al usuario el elemento que quiere comparar con el resto para saber el resultado
				printf("Introduce el género de la persona (M o F): ");
				scanf(" %c", strin);
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
				scanf(" %c", strin);
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
				printf("Introduce la raza de la persona (B, W, A, O): ");
				scanf(" %c", strin);
				if(strcmp(strin, "W") == 0){
					elemento.ethnicity = White;
				}
				else if(strcmp(strin, "B")==0){
					elemento.ethnicity = Black;
				}
				else if(strcmp(strin, "A")== 0){
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
				printf("Introduce si la persona está empadronada en la ciudad o no (Y o N): ");
				scanf(" %c", strin);
				if(strcmp(strin, "Y") == 0){
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

			//Comienzo del KNN
				printf("\nComienzo de la clasificación...\n");
				bool exito = aplicar_knn_elemento(datasetEntrenamiento1, datoAevaluar.ini, K); //aplicamos knn al elemento nuevo que hemos introducido, comparándolo con el resto de elementos de nuestro dataset
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
			break;
		case 3:
			int K;
			printf("\nIntroduce K, para elegir los K vecinos mas cercanos: ");
			scanf("%d", &K);
			printf("Comienzo algoritmo de wilson.\n");
			aplicar_wilson(datasetEntrenamiento, K);
			printf("Fin algoritmo de wilson.\n");
			break;
	}
}



void mostrar_ejemplo(ejemplo ejemplo) {
	char *ethnicity[] = { "White", "Black", "Asian", "Other" };
	char *citizen[] = { "ByBirth", "ByOtherMeans" };

	printf("[Gender: %c, Age: %.2lf, Debt: %.2lf, Married: %c, BankCustomer: %c, Ethnicity: %s, YearsEmployed: %.2lf, Employed: %c, CreditScore: %.2lf, DriverLicense: %c, Citizen: %s, Income: %.2lf]\n",
		ejemplo.gender == M? 'M' : 'F', ejemplo.age, ejemplo.debt, ejemplo.married == Y? 'Y' : 'N', ejemplo.bankCustomer == Y? 'Y' : 'N',
		ethnicity[ejemplo.ethnicity], ejemplo.yearsEmployed, ejemplo.employed, ejemplo.creditScore, ejemplo.driverLicense == Y? 'Y' : 'N',
		citizen[ejemplo.citizen], ejemplo.income);
}

void aplicar_wilson(tipoColaC dataset, int K) {
	int elim = 0;
	celdaColaC *c = dataset.ini;
	while (c != NULL) {
		bool exito = aplicar_knn_eficiencia(dataset, &c->elem, K);
		if (!exito) {
			printf("Se ha encontrado un outlier: \n");
			mostrar_ejemplo(c->elem);
			c->elem.esOutlier = true; // marcamos como outlier
			elim++;
		}
		c = c->sig;
		printf("\n");
	}
	printf("Se han eliminado %d outliers del dataset de entrenamiento\n", elim);
}

bool aplicar_knn_elemento(tipoColaC dataset, ejemplo *ejemplo, int K) {
	tipoLista lista;
	nuevaLista(&lista); // nueva lista ordenada de menor a mayor

	celdaColaC *c = dataset.ini;
// Meto todos los elementos a una lista para evitar compararme conmigo mismo y, comparo las distancias hacia mí con cada elemento
	while (c != NULL) {

		// if (&c->elem == ejemplo) { // no comparar un elemento consigo mismo
		// 	c = c->sig;
		// 	continue;
		// }

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
	result clase = obtenerClaseMasPrometedora(lista, K);
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

bool aplicar_knn_eficiencia(tipoColaC dataset, ejemplo *ejemplo, int K) {
	tipoLista lista;
	nuevaLista(&lista); // nueva lista ordenada

	celdaColaC *c = dataset.ini;
	while (c != NULL) {

		if (&c->elem == ejemplo) { // no comparar un elemento consigo mismo
			c = c->sig;
			continue;
		}

		struct ejemplo ej;

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
		ej.approved = c->elem.approved;
		ej.distancia = calcularDistancia(*ejemplo, c->elem);

		insertar(&lista, ej);

		c = c->sig;
	}
	result clase = obtenerClaseMasPrometedora(lista, K);

	// imprimimos resultados de la prediccion
	printf("Clase predicha: %c\n", clase == Y? 'Y' : 'N');
	printf("Clase real: %c\n", ejemplo->approved == Y? 'Y' : 'N');
	if (clase == ejemplo->approved)
		printf("Prediccion correcta\n");
	else
		printf("Prediccion incorrecta\n");

	return clase == ejemplo->approved;
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

