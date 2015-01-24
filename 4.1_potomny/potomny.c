#include <stdlib.h>
#include <stdio.h>
#include <process.h>

int main(int argc, char *argv[]) {

	int child_pid = fork();

	if (child_pid != 0)
	{
		printf("Jestem procesem potomnym, PID = %d\n",getpid());
	}
	else if (child_pid == 0)
	{
		sleep(3);
		printf("Jestem procesem potomnym potomnego, PID = %d, PPID = %d\n",getpid(),getppid());
	}
	else if (child_pid == -1)
	{
		printf("fork fail");
	}

	//tutaj gdy wartosc bedzie mniejsza niz 3 to bedzie osierocenie potomnych
	sleep(4);
	return EXIT_SUCCESS;
}
