// Σε έναν κύκλο με ακτίνα r η επιφάνεια του είναι πr2 ενώ η επιφάνεια του περιγεγραμμένου στον κύκλο τετραγώνου
// είναι 4r2. Εξετάζοντας το λόγο της επιφάνειας του κύκλου προς την επιφάνεια του τετραγώνου προκύπτει ότι θα
// πρέπει να ισούται με π/4. Αν πραγματοποιηθεί ένα πείραμα στο οποίο θα μετρούνται πόσα από ένα σύνολο
// τυχαίων σημείων πέφτουν εντός του κύκλου τότε ο λόγος του πλήθους των τυχαίων σημείων εντός του κύκλου
// προς το συνολικό πλήθος σημείων θα πρέπει και αυτός να ισούται με π/4. Να γράψετε πρόγραμμα που να
// υπολογίζει χρησιμοποιώντας τον τρόπο που αναφέρθηκε τον αριθμό π. Η εργασία να μοιράζεται σε έναν αριθμό
// διεργασιών. Εκτελέστε το πρόγραμμα για πλήθος 300.000.000 σημείων και για 8 διεργασίες.

// mpicc ask4.c -o ask4
// mpirun --oversubscribe -n 8 ./ask4

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int rank, size;
	long long int i, local_count = 0, total_count = 0;
	long long int num_points = 300000000; // συνολικός αριθμός σημείων
	long long int points_per_proc;
	double x, y;
	unsigned int seed;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	points_per_proc = num_points / size;

	seed = (unsigned int)time(NULL) + rank * 1000;

	for (i = 0; i < points_per_proc; i++)
	{
		x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // [-1,1]
		y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0; // [-1,1]
		if (x * x + y * y <= 1.0)
			local_count++;
	}

	MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		double pi = 4.0 * (double)total_count / (double)(points_per_proc * size);
		printf("Υπολογισμένο π: %.10f\n", pi);
	}

	MPI_Finalize();
	return 0;
}