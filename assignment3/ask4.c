// Σε έναν κύκλο με ακτίνα r η επιφάνεια του είναι πr2 ενώ η επιφάνεια του περιγεγραμμένου στον κύκλο τετραγώνου
// είναι 4r2. Εξετάζοντας το λόγο της επιφάνειας του κύκλου προς την επιφάνεια του τετραγώνου προκύπτει ότι θα
// πρέπει να ισούται με π/4. Αν πραγματοποιηθεί ένα πείραμα στο οποίο θα μετρούνται πόσα από ένα σύνολο
// τυχαίων σημείων πέφτουν εντός του κύκλου τότε ο λόγος του πλήθους των τυχαίων σημείων εντός του κύκλου
// προς το συνολικό πλήθος σημείων θα πρέπει και αυτός να ισούται με π/4. Να γράψετε πρόγραμμα που να
// υπολογίζει χρησιμοποιώντας τον τρόπο που αναφέρθηκε τον αριθμό π. Η εργασία να μοιράζεται σε έναν αριθμό
// νημάτων. Εκτελέστε το πρόγραμμα για πλήθος 300.000.000 σημείων και για 8 νήματα.

// gcc ask4.c -fopenmp -O2 -o ask4
// ./ask4 300000000 8

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[])
{
	long long total_points = 300000000;
	int threads = 8;

	if (argc == 3)
	{
		total_points = atoll(argv[1]);
		threads = atoi(argv[2]);
	}

	long long in_circle = 0;

#pragma omp parallel num_threads(threads)
	{
		unsigned int seed = time(NULL) ^ omp_get_thread_num();
		long long local_in_circle = 0;
#pragma omp for
		for (long long i = 0; i < total_points; i++)
		{
			double x = (double)rand_r(&seed) / RAND_MAX;
			double y = (double)rand_r(&seed) / RAND_MAX;
			if (x * x + y * y <= 1.0)
				local_in_circle++;
		}
#pragma omp atomic
		in_circle += local_in_circle;
	}

	double pi = 4.0 * (double)in_circle / (double)total_points;
	printf("Υπολογισμένο π: %.10f\n", pi);
	return 0;
}