/*
Να γράψετε πρόγραμμα που να δημιουργεί μια διεργασία παιδί. Η διεργασία γονέας
να υπολογίζει το άθροισμα των ακεραίων από το 1 μέχρι το 100 και να το εμφανίζει
ενώ η διεργασία παιδί να υπολογίζει το άθροισμα των ακεραίων από το 101 μέχρι το 200
και να το εμφανίζει. Στη συνέχεια με τη χρήση pipeline το παιδί να στέλνει το
αποτέλεσμα που υπολόγισε στο γονέα και ο γονέας να εμφανίζει την τιμή που έλαβε και
το άθροισμα και των δύο συνόλων που υπολογίστηκαν. Η έξοδος του προγράμματος να
είναι όπως η ακόλουθη:

Computed sum by parent process is 5050
Computed sum by child process is 15050
Parent receives value 15050 from child
The total sum is 20100
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int totsum;

int main(int argc, char **argv)
{
	int pipe_fd[2];
	pipe(pipe_fd);
	printf("Making a child process...\n\n");
	pid_t pid = fork();

	if (pid > 0) // Parent
	{
		int sum=0;

		for(int i=1;i<=100;i++){
			sum+=i;
		}

		printf("Computed sum by parent process is %d\n", sum);

		wait(NULL);

		int child_sum;
		close(pipe_fd[1]);
		read(pipe_fd[0], &child_sum, sizeof(child_sum));
		printf("Parent receives value %d from child\n", child_sum);


		printf("The total sum is %d\n", sum+child_sum);
		close(pipe_fd[0]);
	}

	else if (pid == 0 ) { // Child Process
		int child_sum=0;
		for(int j=101;j<=200;j++){
			child_sum+=j;
			// printf("%d\n", child_sum); // Testing stuff
		}
		
		printf("Computed sum by child process is %d\n", child_sum);

		close(pipe_fd[0]);
		write(pipe_fd[1], &child_sum, sizeof(child_sum));
		close(pipe_fd[1]);
	}
	
	else {printf("Fork failed\n");} // Failed Fork

	return 0;
}