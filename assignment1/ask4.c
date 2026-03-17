/*
Να γράψετε πρόγραμμα που να δημιουργεί μια νέα διεργασία η οποία να καλεί την
εντολή ls. Τοποθετήστε εντολές printf που να εμφανίζουν ότι καλείται ο κώδικας της
διεργασίας γονέα και της διεργασίας παιδί.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Δημιουργία νέας διεργασίας
    pid = fork();

    if (pid < 0) {
        perror("Fork failed"); // Σφάλμα κατά τη δημιουργία της διεργασίας
        return 1;
    } else if (pid == 0) { // Child Process
        printf("Είμαι η διεργασία παιδί με PID: %d\n", getpid());
        
        execlp("ls", "ls", NULL);// Κλήση της εντολής ls
        
        perror("exec failed");// Αν η exec αποτύχει
        return 1;
    } else {
        // Κώδικας της διεργασίας γονέα
        printf("Είμαι η διεργασία γονέα με PID: %d και το PID του παιδιού είναι: %d\n", getpid(), pid);
        
        // Αναμονή για την ολοκλήρωση της διεργασίας παιδί
        wait(NULL);
    }

    return 0;
}
