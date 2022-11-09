#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "info.h"
#include "tipos.h"
#include "normalizar.h"
#include "leer_datos.h"
#include "colaDobleCreditCard.h"
#include "listaOrdenadaEjemplos.h"

void aplicar_wilson(tipoColaC, int);
bool aplicar_knn(tipoColaC, ejemplo *, int);
double calcularDistancia(ejemplo, ejemplo);
result obtenerClaseMasPrometedora(tipoLista, int);
static void mostrar_ejemplo(ejemplo);

int main() {
	struct info info;
	inicializarInfo(&info);

	char fichero[100];
	tipoColaC datasetEntrenamiento;
	nuevaColaDC(&datasetEntrenamiento);
	printf("Introduce el nombre del dataset de entrenamiento: ");
	scanf("%s", fichero);
	leer_datos(fichero, &datasetEntrenamiento, &info);

	tipoColaC datasetPrueba;
	nuevaColaDC(&datasetPrueba);
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

		char wilson;
		printf("\nDesea pre-procesar el conjunto de entrenamiento con Wilson-ENN (s/n)? ");
		scanf(" %c", &wilson);
		if (wilson == 's') {
			printf("Comienzo algoritmo de wilson.\n");
			aplicar_wilson(datasetEntrenamiento, K);
			printf("Fin algoritmo de wilson.\n");
		}
		
		printf("\nComienzo de la clasificacion...\n");
		int aciertos = 0, count = 0;
		celdaColaC *c = datasetPrueba.ini;
		while (c != NULL) {
			printf("Ejemplo #%d\n", count + 1);
			mostrar_ejemplo(c->elem);
			bool exito = aplicar_knn(datasetEntrenamiento, &c->elem, K); // aplicamos knn a cada elemento del dataset de prueba
			if (exito) {
				aciertos++;
			}
			count++;
			c = c->sig;
			printf("\n");
		}
		printf("Fin de la clasificacion\n\n");
		printf("Numero de aciertos: %d\n", aciertos);
		printf("Numero de pruebas: %d\n", count);

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
}

static void mostrar_ejemplo(ejemplo ejemplo) {
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
		bool exito = aplicar_knn(dataset, &c->elem, K);
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
		tmp.approved = c->elem.approved;
		tmp.distancia = calcularDistancia(*ejemplo, c->elem);

		insertar(&lista, tmp);

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