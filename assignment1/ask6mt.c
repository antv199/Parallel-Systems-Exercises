/*
Να γράψετε πρόγραμμα που να δέχεται ως παράμετρο γραμμής εντολών έναν
ακέραιο αριθμό και να εμφανίζει το άθροισμα όλων των θετικών ακεραίων που είναι
μικρότεροι ή ίσοι του αριθμού αυτού. Γράψτε δεύτερο πρόγραμμα που να
μοιράζει το φόρτο υπολογισμού του αθροίσματος σε 2 διεργασίες. Μετρήστε με την
εντολή time το χρόνο εκτέλεσης των δύο εναλλακτικών λύσεων για τον υπολογισμό του
αθροίσματος των πρώτων 2.000.000.000 ακέραιων αριθμών.

*/

// MUTLI THREADED
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

    int num = atoll(argv[1]);

    // Multi threaded
    printf("Multi threaded: \n\n");
    int mid = num / 2; // Διαχωρισμός εργασιών πρόσθεσης σε 2 ισα μερη
    pid_t pid = fork();   // Δημιουργία πρώτης διεργασίας

    if (pid == -1) // Αποτυχημένο fork
    {
        return 1;
    }

    if (pid == 0) // Διεργασία παιδί - Υπολογισμός του πρώτου μέρους
    {
        int sum1 = compute_sum(1, mid);
        printf("Το άθροισμα του πρώτου μέρους είναι: %d\n", sum1);
        exit(0);
    }
    else // Διεργασία γονέας - Υπολογισμός του δεύτερου μέρους
    {
        int sum2 = compute_sum(mid + 1, num);
        wait(NULL); // Περιμένουμε το παιδί να ολοκληρώσει
        printf("Το άθροισμα του δεύτερου μέρους είναι: %d\n", sum2);
        printf("Το συνολικό άθροισμα είναι: %d\n", sum2 + compute_sum(1, mid));
    }
    return 0;
}
