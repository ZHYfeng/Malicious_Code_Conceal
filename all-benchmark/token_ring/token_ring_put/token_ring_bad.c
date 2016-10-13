#include <pthread.h>
#include <assert.h>

int x1 = 1;
int x2 = 2;
int x3 = 1;
pthread_mutex_t lock;
int flag1 = 0, flag2 = 0, flag3 = 0;

void *t1(void *arg) {
  pthread_mutex_lock(&lock);
  if (!flag2) {
    x1 = (x3 + 1) % 4;
  }
  flag1 = 1;
  pthread_mutex_unlock(&lock);
}

void *t2(void *arg) {
  pthread_mutex_lock(&lock);
  if (!flag3) {
    x2 = x1;
  }
  flag2 = 1;
  pthread_mutex_unlock(&lock);
}

void *t3(void *arg) {
  pthread_mutex_lock(&lock);
  x3 = x2;
  flag3 = 1;
  pthread_mutex_unlock(&lock);
}

void *t4(void *arg) {
  pthread_mutex_lock(&lock);
  if (flag1 && flag2 && flag3)
    // assert(x1 == x2 && x2 == x3); /* BAD */
  pthread_mutex_unlock(&lock);
}

int main() {
  pthread_t id1, id2, id3, id4;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);
  pthread_create(&id3, NULL, t3, NULL);
  pthread_create(&id3, NULL, t4, NULL);

  return 0;
}
