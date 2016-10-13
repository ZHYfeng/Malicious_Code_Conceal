#include <assert.h>
#include <pthread.h>

int x=0;

void* t1(void* arg)
{
  x++;
  x++;
  x++;
  x++;
  x++;
}
void* t2(void* arg)
{
  x++;
  x++;
  x++;
  x++;
  x++;
}
void* t3(void* arg)
{
  x++;
  x++;
  x++;
  x++;
  x++;
}
void* t4(void* arg)
{
  x++;
  x++;
  x++;
  x++;
  x++;
}

int main(void)
{
  pthread_t id[4];

  pthread_create(&id[0], NULL, &t1, NULL);
  pthread_create(&id[1], NULL, &t2, NULL);
  pthread_create(&id[2], NULL, &t3, NULL);
  pthread_create(&id[3], NULL, &t4, NULL);
pthread_join(id[0], NULL);
pthread_join(id[1], NULL);
pthread_join(id[2], NULL);
pthread_join(id[3], NULL);
assert(x>=6);
  return 0;
}
