/*
Να γράψετε πρόγραμμα που να δέχεται ως παράμετρο γραμμής εντολών έναν
ακέραιο αριθμό. Το πρόγραμμα να δημιουργεί μια διεργασία παιδί, η οποία να
εξετάζει αν η παράμετρος είναι άρτια ή περιττή. Η διεργασία παιδί να τερματίζει με
την εντολή exit επιστρέφοντας την τιμή 0 αν η παράμετρος είναι άρτια αλλιώς να
επιστρέφει την τιμή 1. Η διεργασία γονέας να διαβάζει την τιμή που επιστρέφει η
διεργασία παιδί και να την εμφανίζει
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int totsum;

int main(int argc, char **argv)
{
	if (argc != 2){
		printf("Παρακαλώ δώστε έναν ακέραιο ως launch argument");
		return 1;
	}

	int num = atoi(argv[1]);

	int pipe_fd[2];
	pipe(pipe_fd);
	printf("Making a child process...\n\n");
	pid_t pid = fork();

	if (pid > 0) // Parent
	{
		// Εδώ είναι η διεργασία γονέας
		int status;
		wait(&status); // Περιμένει το παιδί να τερματίσει

		// Εξαγωγή του exit status του παιδιού
		if (WIFEXITED(status)) {
				int exitStatus = WEXITSTATUS(status);
				printf("Η διεργασία παιδί επέστρεψε με την τιμή: %d\n", exitStatus);
		} else {
				printf("Η διεργασία παιδί τερμάτισε με σφάλμα.\n");
		}
	}

	else if (pid == 0 ) { // Child Process
		if (num % 2 == 0) { // άρτιος αριθμός
			exit(0);
		} else { // περιττός αριθμός
			exit(1);
		}
	}
	
	else {printf("Fork failed\n");} // Failed Fork

	return 0;
}