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
  x++;
  x++;
  x++;
  x++;
  x++;
// 10
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
// 20
x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
// 30
 
}

void* t2(void* arg)
{
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
// 10
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
// 20
x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
  x++;
// 30
 
}

int main(void)
{
  pthread_t id[2];

  pthread_create(&id[0], NULL, &t1, NULL);
  pthread_create(&id[1], NULL, &t2, NULL);
pthread_join(id[0], NULL);
pthread_join(id[1], NULL);
assert(x>=31);
  return 0;
}
