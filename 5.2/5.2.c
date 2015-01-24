#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
void * __stack_chk_guard = NULL;

double pi = 0;

struct thread_data
{
	double a;
	double b;
	double numSteps;
	double res;
};

void* startThread(void* arg)
{
	int i;
	struct thread_data data;

	//tworzenie kopii struktury
	data = * ((struct thread_data*) arg);

	double x, step, sum = 0.0;
	step = (data.b - data.a) / (double) data.numSteps;
	for (i=0; i < data.numSteps; i++)
	{
		x = (double)(i + 0.5) * step + data.a;
		sum = sum + 4.0 / (1.0 + x * x);
	}
	pi += step * sum;

	printf("(%lf,%lf) -> %lf\n",data.a,data.b, step * sum);
	pthread_exit(NULL);
}

#define NUMTHREAD 30
int main(int argc, char *argv[]) {
	int i;
	void* status;
	pthread_t thread_id[NUMTHREAD];
	struct thread_data* args[NUMTHREAD];
    double x = 0;
    double step = 1./((double) NUMTHREAD);


    //rozpoczynanie
	for(i=0;i<NUMTHREAD;i++)
	{
		struct thread_data data;
		data.a = x;
		data.b = x + step;
		data.numSteps = 100; //ilosc iteracji wykonywanych rpzez kazdy watek
		data.res = 0;
		args[i] = &data;
		x = x + step;
		int rc = pthread_create(&thread_id[i],NULL, &startThread, (void*) &data);
	}

	//czekanie na koniec obliczen watkow
	for(i = 0; i < NUMTHREAD; i++)
	{
		int rc = pthread_join(thread_id[i], &status);
		if (rc)
		{
				printf("Blad. Kod powrotu z funkcji pthread_join():%d\n", rc);
				exit(-1);
		}
		//printf("Watek glowny dolaczyl watek %d o statusie %d\n",i, status);

	}

	printf("Otrzymane przyblizenie PI = %.15lf\n", pi);
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}
