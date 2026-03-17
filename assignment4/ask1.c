// Να γράψετε πρόγραμμα που να δημιουργεί 5 διεργασίες. Η κάθε διεργασία απλά να εμφανίζει έναν τυχαίο
// ακέραιο αριθμό στο διάστημα [1,100] και να τερματίζει. Γράψτε τις εντολές μεταγλώττισης και εκτέλεσης του
// προγράμματος.

// mpicc ask1.c -o ask1
// mpirun --oversubscribe -n 5 ./ask1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size, rand_num;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != 5)
	{
		if (rank == 0)
		{
			printf("Το πρόγραμμα πρέπει να εκτελεστεί με 5 διεργασίες.\n");
		}
		MPI_Finalize();
		return 1;
	}

	srand(time(NULL) + rank * 100); // διαφορετικός seed για κάθε διεργασία
	rand_num = (rand() % 100) + 1;

	printf("Διεργασία %d: Τυχαίος αριθμός = %d\n", rank, rand_num);

	MPI_Finalize();
	return 0;
}
