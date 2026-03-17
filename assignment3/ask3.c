// Να γράψετε πρόγραμμα που να γεμίζει με τυχαίες ακέραιες τιμές στο διάστημα [1,10] δύο διανύσματα 1000
// θέσεων το καθένα και να υπολογίζει το εσωτερικό τους γινόμενο
// (http://mathinsight.org/dot_product_matrix_notation). Για τον υπολογισμό του εσωτερικού γινομένου η εργασία
// να «σπάσει» σε 4 νήματα.

// gcc ask3.c -fopenmp -o ask3
// ./ask3

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 1000

int main()
{
	int a[SIZE], b[SIZE];
	int total_dot = 0;

	// Γέμισμα των διανυσμάτων με τυχαίες τιμές στο [1,10]
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		a[i] = 1 + rand() % 10;
		b[i] = 1 + rand() % 10;
	}

// Υπολογισμός εσωτερικού γινομένου με 4 νήματα (OpenMP)
#pragma omp parallel for num_threads(4) reduction(+ : dot_product)
	for (int i = 0; i < SIZE; i++)
	{
		total_dot += a[i] * b[i];
	}

	printf("Το εσωτερικό γινόμενο των δύο διανυσμάτων είναι: %d\n", total_dot);
	return 0;
}