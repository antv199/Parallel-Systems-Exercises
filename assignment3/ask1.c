// Να γράψετε πρόγραμμα που να δημιουργεί 5 νήματα. Το κάθε νήμα απλά να εμφανίζει έναν τυχαίο ακέραιο
// αριθμό στο διάστημα [1,100] και να τερματίζει. Γράψτε τις εντολές μεταγλώττισης και εκτέλεσης του
// προγράμματος.

// gcc ask1.c -fopenmp -o ask1
// ./ask1

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define T 5

int main()
{

#pragma omp parallel num_threads(T)
	{
		srand(time(NULL)); // Αρχικοποίηση του seed για τυχαίους αριθμούς

		// Κάθε νήμα δημιουργεί το δικό του seed για να αποφευχθούν τα ίδια νούμερα
		unsigned int seed = time(NULL) ^ omp_get_thread_num();
		int rand_num = 1 + rand_r(&seed) % 100;
		printf("Διεργασία %d: Τυχαίος αριθμός = %d\n", omp_get_thread_num(), rand_num);
	}

	return 0;
}