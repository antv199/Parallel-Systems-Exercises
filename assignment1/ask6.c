/*
Να γράψετε πρόγραμμα που να δέχεται ως παράμετρο γραμμής εντολών έναν
ακέραιο αριθμό και να εμφανίζει το άθροισμα όλων των θετικών ακεραίων που είναι
μικρότεροι ή ίσοι του αριθμού αυτού. Γράψτε δεύτερο πρόγραμμα που να
μοιράζει το φόρτο υπολογισμού του αθροίσματος σε 2 διεργασίες. Μετρήστε με την
εντολή time το χρόνο εκτέλεσης των δύο εναλλακτικών λύσεων για τον υπολογισμό του
αθροίσματος των πρώτων 2.000.000.000 ακέραιων αριθμών.

*/

// SINGLE THREAD
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int compute_sum(int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
    {
        sum += i;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    // Έλεγχος αν υπάρχει η παράμετρος
    if (argc != 2)
    {
        fprintf(stderr, "Παρακαλώ δώστε έναν ακέραιο αριθμό ως παράμετρο.\n");
        return 1;
    }

    // Single Threaded
    printf("Single threaded: \n\n");
    int num = atoll(argv[1]);      // Μετατροπή της παραμέτρου σε ακέραιο αριθμό
    int sum = compute_sum(0, num); // Υπολογισμός του αθροίσματος

    printf("(Single Threaded) Το άθροισμα είναι: %d\n", sum);
    return 0;
}
