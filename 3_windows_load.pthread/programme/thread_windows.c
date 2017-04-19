// thread_windows.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10

static char OUTPUT_FILENAME[100] = "sequence.log";
static char IF_FILENAME[100] = "occurrence.log";

static long LOOPS = 190000;
static unsigned int THREAD_NUMS = 4;
static unsigned int MCODE_NUMS = 4;

static int sequence[100];
int sequenceOrder;
unsigned int order = 0;
pthread_mutex_t mutex;

void placeholder();
void maliciousePrototype(int o);
void recordMessage();

int ThreadRoutine()
{
    for (unsigned int m = 0; m < MCODE_NUMS; m++)
    {
		maliciousePrototype(m + 1);
    }
    return 0;
}

int ThreadCreation()
{
    pthread_t threads[MAX_THREADS];

    const unsigned int num_threads = THREAD_NUMS;
    unsigned int running_threads = 0;

    for (running_threads = 0; running_threads < num_threads; running_threads++)
    {
		pthread_create(&threads[running_threads], NULL, (void *)ThreadRoutine, NULL);
    }

    for (running_threads = 0; running_threads < num_threads; running_threads++)
    {
		pthread_join(threads[running_threads], NULL);
    }

    return 1;
}

int main(int argc, char *argv[])
{
	int i;

    THREAD_NUMS = atoi(argv[1]);
    MCODE_NUMS = atoi(argv[2]);
    LOOPS = atol(argv[3]);

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 100; i++)
    {
        sequence[i] = 0;
    }
    sequenceOrder = 0;

    ThreadCreation();
    recordMessage();

    //system("pause");
    return 0;
}

inline void placeholder()
{
    int j;
    for (int i = 0; i < LOOPS; i++)
    {
        j = i;
    }
}

void recordMessage()
{
    int i;
    FILE *fp;
    if ((fp = fopen(IF_FILENAME, "a+")) == NULL)
    {
		printf("can't open the file! \n");
    }
    else
    {
		if (order == 4)
		{
		    fprintf(fp, "1\n");
		}
		else
		{
		    fprintf(fp, "0\n");
		}
    }
    fclose(fp);

    if ((fp = fopen(OUTPUT_FILENAME, "a+")) == NULL)
    {
		printf("can't open the file! \n");
    }
    else
    {
		for (i = 0; sequence[i] != 0; i++)
		{
		    fprintf(fp, "%d, ", sequence[i]);
		}
		fprintf(fp, "\n");
    }
    fclose(fp);
}

void maliciousePrototype(int o)
{
    placeholder();
    pthread_mutex_lock(&mutex);
	sequence[sequenceOrder++] = o;
    if ((o - order) == 1)
    {
		order = o;
    }
    pthread_mutex_unlock(&mutex);
}
