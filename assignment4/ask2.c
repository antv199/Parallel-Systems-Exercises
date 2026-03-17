// Να γράψετε πρόγραμμα που να δέχεται ως παράμετρο γραμμής εντολών έναν ακέραιο αριθμό και να εμφανίζει το
// άθροισμα όλων των θετικών ακεραίων που είναι μικρότεροι ή ίσοι του αριθμού αυτού (οι σχετικές μεταβλητές να
// δηλωθούν ως τύπου long long). Για τον υπολογισμό του αθροίσματος να χρησιμοποιεί διεργασίες. Υπολογίστε το
// άθροισμα των πρώτων 10.000.000 ακέραιων αριθμών χρησιμοποιώντας 4 διεργασίες. Γράψτε τις εντολές
// μεταγλώττισης και εκτέλεσης του προγράμματος.

// mpicc ask2.c -o ask2
// mpirun --oversubscribe -n 4 ./ask2 10000000

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	long long n, local_sum = 0, total_sum = 0;
	long long start, end, i;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (argc != 2)
	{
		if (rank == 0)
			printf("Χρήση: %s <ακέραιος αριθμός>\n", argv[0]);
		MPI_Finalize();
		return 1;
	}

	n = atoll(argv[1]);
	if (n < 1)
	{
		if (rank == 0)
			printf("Ο αριθμός πρέπει να είναι θετικός.\n");
		MPI_Finalize();
		return 1;
	}

	// Καθορισμός ορίων για κάθε διεργασία
	long long chunk = n / size;
	start = rank * chunk + 1;
	end = (rank == size - 1) ? n : (rank + 1) * chunk;

	for (i = start; i <= end; i++)
		local_sum += i;

	MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
		printf("Το άθροισμα των θετικών ακεραίων μέχρι το %lld είναι: %lld\n", n, total_sum);
	
	MPI_Finalize();
	return 0;
}