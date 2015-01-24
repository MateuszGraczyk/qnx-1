#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
void * __stack_chk_guard = NULL;
struct thread_data
{
	int thread_id; /* ID w¹tku */
	int sum; /* suma kontrolna */
	char *message; /* wiadomosc */
};

void* startThread(void* arg)
{
	struct thread_data data;
	data = * ((struct thread_data*) arg);
	printf("Otrzymana wiadomosc: %s\n", data.message);
	sleep(2);
	puts("watek zakonczyl dzialanie");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int i;
	pthread_t thread_id[8];
	char* messages[8];
	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Polski: Witaj swiecie!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";

	for(i=0;i<8;i++)
	{
		struct thread_data data;
		data.message = messages[i];
		int rc = pthread_create(&thread_id[i], NULL, &startThread, (void*) &data);
	}

	//oczekiwanie na watki inne
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}
