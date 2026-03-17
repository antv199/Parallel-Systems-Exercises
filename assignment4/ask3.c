// Να γράψετε πρόγραμμα που να γεμίζει με τυχαίες ακέραιες τιμές στο διάστημα [1,10] δύο διανύσματα 1000
// θέσεων το καθένα και να υπολογίζει το εσωτερικό τους γινόμενο
// (http://mathinsight.org/dot_product_matrix_notation). Για τον υπολογισμό του εσωτερικού γινομένου η εργασία
// να «σπάσει» σε 4 διεργασίες.

// mpicc ask3.c -o ask3
// mpirun --oversubscribe -n 4 ./ask3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define N 1000

int main(int argc, char *argv[])
{
	int rank, size;
	int a[N], b[N];
	int local_dot = 0, total_dot = 0;
	int chunk, start, end, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	chunk = N / size;
	start = rank * chunk;
	end = (rank == size - 1) ? N : (rank + 1) * chunk;

	// Μόνο η διεργασία 0 γεμίζει τα διανύσματα και τα στέλνει στις υπόλοιπες
	if (rank == 0)
	{
		srand(time(NULL));
		for (i = 0; i < N; i++)
		{
			a[i] = (rand() % 10) + 1;
			b[i] = (rand() % 10) + 1;
		}
	}

	// Διανέμουμε τα διανύσματα σε όλες τις διεργασίες
	int local_a[chunk], local_b[chunk];
	MPI_Scatter(a, chunk, MPI_INT, local_a, chunk, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, chunk, MPI_INT, local_b, chunk, MPI_INT, 0, MPI_COMM_WORLD);

	// Υπολογισμός τοπικού εσωτερικού γινομένου
	for (i = 0; i < chunk; i++)
		local_dot += local_a[i] * local_b[i];

	// Συγκέντρωση των τοπικών αποτελεσμάτων
	MPI_Reduce(&local_dot, &total_dot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
		printf("Το εσωτερικό γινόμενο των δύο διανυσμάτων είναι: %d\n", total_dot);

	MPI_Finalize();
	return 0;
}