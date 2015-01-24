#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
void * __stack_chk_guard = NULL;

#define BUFSIZE 2
int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];

	//mozna podawac jako argument ale nie tak sie latwiej mi testowalo
	char* path = "/home/plik1.txt";
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	int fd1 = open (path, O_RDONLY, mode);
	int bytes_read = 0;
	int bytes_total=0;
	do
	{
		bytes_read = read(fd1,buffer,BUFSIZE);
		bytes_total += bytes_read;
	}
	while(bytes_read == BUFSIZE);


	printf("przeczytalem %d znakow",bytes_total);
	return EXIT_SUCCESS;
}
