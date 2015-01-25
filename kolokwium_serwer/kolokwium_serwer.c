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
}

int main(int argc, char *argv[])
{
	int chid; // Kanal komunikacyjny
	pid_t pid; // PID serwera
	int rcvid; // identifikator nadawcy
	struct _msg_info info;
	struct msg received; // odebrana wiad od klienta
	struct msg reply; //nasza odpowiedŸ
	int status = 0;
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
	while(1)
	{
		/* Odebranie komunikatu */
		rcvid = MsgReceive(chid,&received,sizeof(received),&info);
		printf("\tS: Odebrana wiadomosc: %s\n", received.buf);
		printf("\tS: Zakodowany identyfikator nadawcy i polaczenia: %d\n", rcvid);
		/* Jesli nie udalo sie pobrac wiadomosci */
		if(rcvid == -1)
		{
			printf("\tS: Nie moge odebrac wiadomosci: %s\n",
			strerror(errno));
			break; // sprobuj odebrac inna
		}

		/* odpowiedz klientowi */
		strcpy(reply.buf, received.buf);
		MsgReply(rcvid,status,&reply,sizeof(reply));
		//printf("\tS: Status serwera: %d, reply: %s\n",status,reply);
		if(status == -1)
		{
			printf("\tS: Nie moge odpowiedziec: %s\n",
			strerror(errno));
		}
	}
	return EXIT_SUCCESS;
}
