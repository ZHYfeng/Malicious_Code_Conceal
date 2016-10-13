#include <pthread.h>
#include <assert.h>
/*
 input: a = 1; b = 0
*/
int x, y;

void * thread1(void * arg)
{
	printf("thread1 = %d\n" , (int) arg);

	x = (int) arg;
	if(x > 0)
		y = y + 1;
	else
		y = y - 1;
}

void * thread2(void * arg)
{  
	printf("thread2 = %d\n" , (int) arg);

	y = (int) arg;
	if(y > 0)
		x = x + 1;
	else
		x = x - 1;
}

int main(int argc, char** argv)
{
  pthread_t  t1, t2;
  int a,b;
  if(argc < 2)
  {
    printf("too few arguments!\n");
	// exit(0);
  }
  //a = atoi(argv[1]);
  //b = atoi(argv[2]);
a = 1;
b = 1;

printf("a = %d\n" , a);
printf("b = %d\n" , b);

  pthread_create(&t1, 0, thread1, (void*)a);
  pthread_create(&t2, 0, thread2, (void*)b);
  
  pthread_join(t1, 0);
  pthread_join(t2, 0);

  assert(y >= 0);
  return 0;
}
