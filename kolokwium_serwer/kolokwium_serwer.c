/* server.c */
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <string.h>
#include <errno.h>
#include <process.h>
void * __stack_chk_guard = NULL;

#define SIZE 256
struct  msg{
	int bytes; //liczba bajtów
	char nick[SIZE];
	int number;
	char buf[SIZE];
	char buf2[SIZE];
	int flag;
};


void* tomulikMistrz(void* arg)
{
	int chid = * ((int*) arg);
	printf("utworzylem watek!! chid:%d\n", chid);
	int rcvid; // identifikator nadawcy
	struct _msg_info info;
	struct msg received; // odebrana wiad od klienta
	struct msg reply; //nasza odpowiedŸ
	int status = 0;

	while(1)
	{
		/* Odebranie komunikatu */
		rcvid = MsgReceive(chid,&received,sizeof(received),&info);
		sleep(10);
		printf("%d: Odebrana wiadomosc: %s\n", pthread_self(), received.buf);
		printf("%d: Zakodowany identyfikator nadawcy i polaczenia: %d\n",pthread_self(), rcvid);
		/* Jesli nie udalo sie pobrac wiadomosci */
		if(rcvid == -1)
		{
			printf("\tS: Nie moge odebrac wiadomosci: %s\n",
			strerror(errno));
			break; // sprobuj odebrac inna
		}

		/* odpowiedz klientowi */
		itoa(pthread_self(), reply.buf, 16);
		strcat(reply.buf, " ");
		strcat(reply.buf, received.buf);

		MsgReply(rcvid,status,&reply,sizeof(reply));
		//printf("\tS: Status serwera: %d, reply: %s\n",status,reply);
		if(status == -1)
		{
			printf("\tS: Nie moge odpowiedziec: %s\n",
			strerror(errno));
		}
	}

	return NULL;
}

#define THREADNUM 2

int main(int argc, char *argv[])
{
	int chid; // Kanal komunikacyjny
	pid_t pid; // PID serwera

	chid = ChannelCreate(0);
	if (chid == -1)
	{
		printf("\tS: Nie moge utworzyc kanalu: %s\n",
		strerror(errno));
		return EXIT_FAILURE;
	}

	pid = getpid();
	//Tworzenie pliku z danymi o polaczeniu
	FILE* fd = NULL;
	fd = fopen("/home/test.txt","w");
	fprintf(fd, "%d %d\n", pid, chid);
	fclose(fd);
	//koniec tworzenia pliku
	printf("\tS: PID serwera: %d, CHID: %d\n", pid, chid);

	int newThreadID[THREADNUM];
	int i;
	for(i=0;i<THREADNUM;i++)
	{
		int rc = pthread_create(&newThreadID[i],NULL, &tomulikMistrz, (void*) &chid);
	}

	for (i=0;i<THREADNUM;i++)
	{
		int status;
		int rc = pthread_join(newThreadID[i], &status);
	}

	return EXIT_SUCCESS;
}
