#include <stdio.h>
#include <process.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[]) {
	int res1 = spawnl(P_NOWAIT,"/home/4.1_potomny","1",NULL);
	int res2 = spawnl(P_NOWAIT,"/home/4.1_potomny","2",NULL);
	return EXIT_SUCCESS;
}
