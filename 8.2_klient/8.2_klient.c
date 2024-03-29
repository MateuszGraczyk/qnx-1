#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <string.h>
#include <errno.h>
void * __stack_chk_guard = NULL;
int main(int argc, char *argv[])
{
	int server_pid; // PID serwera
	int server_chid; // CHID serwera
	int coid; // COID
	char smsg[256]; // bufor na wiadomosci do wyslania
	int status; // status z funkcji MsgSend()
	char reply[512];

	//Tworzenie pliku z danymi o polaczeniu
	FILE* fd = NULL;
	fd = fopen("/home/test.txt","r");
	if (fd==NULL)
	{
		printf("nie udalo sie otworzyc pliku\n");
		return EXIT_FAILURE;
	}
	fscanf(fd, "%d %d\n", &server_pid, &server_chid);
	fclose(fd);
	//koniec tworzenia pliku



	printf("K: Probuje nawiazac polaczenie z serwerem pid: %d, chid %d\n", server_pid, server_chid);
	/* Tworzenie polaczenia */
	coid = ConnectAttach(ND_LOCAL_NODE, server_pid, server_chid,_NTO_SIDE_CHANNEL,0);
	while(1)
	{
		if (coid == -1)
		{
			printf("K: Nie moge utworzyc polaczenia: %s\n",
			strerror(errno));
			exit(EXIT_FAILURE);
		}
		puts("--Podaj wiadomosc ktora chcesz wyslac--");
		char* dump = fgets(&smsg, 256, stdin);

		//strcpy(smsg, argv[3]);
		printf("K: Wysylam wiadomosc: %s\n", smsg);
		status =
		MsgSend(coid,smsg,sizeof(smsg),reply,sizeof(reply));
		if (status == -1)
		{
			printf("K: sNie moge wyslac wiadomosci: %s\n",
			strerror(errno));
			exit(EXIT_FAILURE);
		}
		printf("K: Otrzymana odpowiedz: %s\n", reply);
		printf("K: Funkcja MsgSend zwrocila status: %d\n", status);
	}
	return EXIT_SUCCESS;
}
