#line 185 "/home/zhy/work/test/splash2-master/codes/null_macros/c.m4.null.POSIX_BARRIER"

#line 1 "main.C"
/*************************************************************************/
/*                                                                       */
/*  Copyright (c) 1994 Stanford University                               */
/*                                                                       */
/*  All rights reserved.                                                 */
/*                                                                       */
/*  Permission is given to use, copy, and modify this software for any   */
/*  non-commercial purpose as long as this copyright notice is not       */
/*  removed.  All other uses, including redistribution in whole or in    */
/*  part, are forbidden without prior written permission.                */
/*                                                                       */
/*  This software is provided with absolutely no warranty and no         */
/*  support.                                                             */
/*                                                                       */
/*************************************************************************/

/*************************************************************************/
/*                                                                       */
/*  SPLASH Ocean Code                                                    */
/*                                                                       */
/*  This application studies the role of eddy and boundary currents in   */
/*  influencing large-scale ocean movements.  This implementation uses   */
/*  dynamically allocated four-dimensional arrays for grid data storage. */
/*                                                                       */
/*  Command line options:                                                */
/*                                                                       */
/*     -nN : Simulate NxN ocean.  N must be (power of 2)+2.              */
/*     -pP : P = number of processors.  P must be power of 2.            */
/*     -eE : E = error tolerance for iterative relaxation.               */
/*     -rR : R = distance between grid points in meters.                 */
/*     -tT : T = timestep in seconds.                                    */
/*     -s  : Print timing statistics.                                    */
/*     -o  : Print out relaxation residual values.                       */
/*     -h  : Print out command line options.                             */
/*                                                                       */
/*  Default: OCEAN -n130 -p1 -e1e-7 -r20000.0 -t28800.0                  */
/*                                                                       */
/*  NOTE: This code works under both the FORK and SPROC models.          */
/*                                                                       */
/*************************************************************************/


#line 42
#include <pthread.h>
#line 42
#include <sys/time.h>
#line 42
#include <unistd.h>
#line 42
#include <stdlib.h>
#line 42
#include <malloc.h>
#line 42
#define MAX_THREADS 32
#line 42
pthread_t PThreadTable[MAX_THREADS];
#line 42


#define DEFAULT_N      258
#define DEFAULT_P        1
#define DEFAULT_E        1e-7
#define DEFAULT_T    28800.0
#define DEFAULT_R    20000.0
#define UP               0
#define DOWN             1
#define LEFT             2
#define RIGHT            3
#define UPLEFT           4
#define UPRIGHT          5
#define DOWNLEFT         6
#define DOWNRIGHT        7
#define PAGE_SIZE     4096

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "decs.h"

struct multi_struct *multi;
struct global_struct *global;
struct locks_struct *locks;
struct bars_struct *bars;

double ****psi;
double ****psim;
double ***psium;
double ***psilm;
double ***psib;
double ***ga;
double ***gb;
double ****work1;
double ***work2;
double ***work3;
double ****work4;
double ****work5;
double ***work6;
double ****work7;
double ****temparray;
double ***tauz;
double ***oldga;
double ***oldgb;
double *f;
double ****q_multi;
double ****rhs_multi;

long nprocs = DEFAULT_P;
double h1 = 1000.0;
double h3 = 4000.0;
double h = 5000.0;
double lf = -5.12e11;
double res = DEFAULT_R;
double dtau = DEFAULT_T;
double f0 = 8.3e-5;
double beta = 2.0e-11;
double gpr = 0.02;
long im = DEFAULT_N;
long jm;
double tolerance = DEFAULT_E;
double eig2;
double ysca;
long jmm1;
double pi;
double t0 = 0.5e-4 ;
double outday0 = 1.0;
double outday1 = 2.0;
double outday2 = 2.0;
double outday3 = 2.0;
double factjacob;
double factlap;
long numlev;
long *imx;
long *jmx;
double *lev_res;
double *lev_tol;
double maxwork = 10000.0;

struct Global_Private *gp;

double *i_int_coeff;
double *j_int_coeff;
long xprocs;
long yprocs;
long *xpts_per_proc;
long *ypts_per_proc;
long minlevel;
long do_stats = 0;
long do_output = 0;

int main(int argc, char *argv[])
{
   long i;
   long j;
   long k;
   long x_part;
   long y_part;
   long d_size;
   long itemp;
   long jtemp;
   double procsqrt;
   long temp = 0;
   double min_total;
   double max_total;
   double avg_total;
   double min_multi;
   double max_multi;
   double avg_multi;
   double min_frac;
   double max_frac;
   double avg_frac;
   long ch;
   extern char *optarg;
   unsigned long computeend;
   unsigned long start;

   {
#line 161
	struct timeval	FullTime;
#line 161

#line 161
	gettimeofday(&FullTime, NULL);
#line 161
	(start) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 161
}

   while ((ch = getopt(argc, argv, "n:p:e:r:t:soh")) != -1) {
     switch(ch) {
     case 'n': im = atoi(optarg);
               if (log_2(im-2) == -1) {
                 printerr("Grid must be ((power of 2)+2) in each dimension\n");
                 exit(-1);
               }
               break;
     case 'p': nprocs = atoi(optarg);
               if (nprocs < 1) {
                 printerr("P must be >= 1\n");
                 exit(-1);
               }
               if (log_2(nprocs) == -1) {
                 printerr("P must be a power of 2\n");
                 exit(-1);
               }
               break;
     case 'e': tolerance = atof(optarg); break;
     case 'r': res = atof(optarg); break;
     case 't': dtau = atof(optarg); break;
     case 's': do_stats = !do_stats; break;
     case 'o': do_output = !do_output; break;
     case 'h': printf("Usage: OCEAN <options>\n\n");
               printf("options:\n");
               printf("  -nN : Simulate NxN ocean.  N must be (power of 2)+2.\n");
               printf("  -pP : P = number of processors.  P must be power of 2.\n");
               printf("  -eE : E = error tolerance for iterative relaxation.\n");
               printf("  -rR : R = distance between grid points in meters.\n");
               printf("  -tT : T = timestep in seconds.\n");
               printf("  -s  : Print timing statistics.\n");
               printf("  -o  : Print out relaxation residual values.\n");
               printf("  -h  : Print out command line options.\n\n");
               printf("Default: OCEAN -n%1d -p%1d -e%1g -r%1g -t%1g\n",
                       DEFAULT_N,DEFAULT_P,DEFAULT_E,DEFAULT_R,DEFAULT_T);
               exit(0);
               break;
     }
   }

   {;}

   jm = im;
   printf("\n");
   printf("Ocean simulation with W-cycle multigrid solver\n");
   printf("    Processors                         : %1ld\n",nprocs);
   printf("    Grid size                          : %1ld x %1ld\n",im,jm);
   printf("    Grid resolution (meters)           : %0.2f\n",res);
   printf("    Time between relaxations (seconds) : %0.0f\n",dtau);
   printf("    Error tolerance                    : %0.7g\n",tolerance);
   printf("\n");

   xprocs = 0;
   yprocs = 0;
   procsqrt = sqrt((double) nprocs);
   j = (long) procsqrt;
   while ((xprocs == 0) && (j > 0)) {
     k = nprocs / j;
     if (k * j == nprocs) {
       if (k > j) {
         xprocs = j;
         yprocs = k;
       } else {
         xprocs = k;
         yprocs = j;
       }
     }
     j--;
   }
   if (xprocs == 0) {
     printerr("Could not find factors for subblocking\n");
     exit(-1);
   }

   minlevel = 0;
   itemp = 1;
   jtemp = 1;
   numlev = 0;
   minlevel = 0;
   while (itemp < (im-2)) {
     itemp = itemp*2;
     jtemp = jtemp*2;
     if ((itemp/yprocs > 1) && (jtemp/xprocs > 1)) {
       numlev++;
     }
   }

   if (numlev == 0) {
     printerr("Must have at least 2 grid points per processor in each dimension\n");
     exit(-1);
   }

   imx = (long *) malloc(numlev*sizeof(long));;
   jmx = (long *) malloc(numlev*sizeof(long));;
   lev_res = (double *) malloc(numlev*sizeof(double));;
   lev_tol = (double *) malloc(numlev*sizeof(double));;
   i_int_coeff = (double *) malloc(numlev*sizeof(double));;
   j_int_coeff = (double *) malloc(numlev*sizeof(double));;
   xpts_per_proc = (long *) malloc(numlev*sizeof(long));;
   ypts_per_proc = (long *) malloc(numlev*sizeof(long));;

   imx[numlev-1] = im;
   jmx[numlev-1] = jm;
   lev_res[numlev-1] = res;
   lev_tol[numlev-1] = tolerance;

   for (i=numlev-2;i>=0;i--) {
     imx[i] = ((imx[i+1] - 2) / 2) + 2;
     jmx[i] = ((jmx[i+1] - 2) / 2) + 2;
     lev_res[i] = lev_res[i+1] * 2;
   }

   for (i=0;i<numlev;i++) {
     xpts_per_proc[i] = (jmx[i]-2) / xprocs;
     ypts_per_proc[i] = (imx[i]-2) / yprocs;
   }
   for (i=numlev-1;i>=0;i--) {
     if ((xpts_per_proc[i] < 2) || (ypts_per_proc[i] < 2)) {
       minlevel = i+1;
       break;
     }
   }

   for (i=0;i<numlev;i++) {
     temp += imx[i];
   }
   temp = 0;
   j = 0;
   for (k=0;k<numlev;k++) {
     for (i=0;i<imx[k];i++) {
       j++;
       temp += jmx[k];
     }
   }

   d_size = nprocs*sizeof(double ***);
   psi = (double ****) malloc(d_size);;
   psim = (double ****) malloc(d_size);;
   work1 = (double ****) malloc(d_size);;
   work4 = (double ****) malloc(d_size);;
   work5 = (double ****) malloc(d_size);;
   work7 = (double ****) malloc(d_size);;
   temparray = (double ****) malloc(d_size);;

   d_size = 2*sizeof(double **);
   for (i=0;i<nprocs;i++) {
     psi[i] = (double ***) malloc(d_size);;
     psim[i] = (double ***) malloc(d_size);;
     work1[i] = (double ***) malloc(d_size);;
     work4[i] = (double ***) malloc(d_size);;
     work5[i] = (double ***) malloc(d_size);;
     work7[i] = (double ***) malloc(d_size);;
     temparray[i] = (double ***) malloc(d_size);;
   }

   d_size = nprocs*sizeof(double **);
   psium = (double ***) malloc(d_size);;
   psilm = (double ***) malloc(d_size);;
   psib = (double ***) malloc(d_size);;
   ga = (double ***) malloc(d_size);;
   gb = (double ***) malloc(d_size);;
   work2 = (double ***) malloc(d_size);;
   work3 = (double ***) malloc(d_size);;
   work6 = (double ***) malloc(d_size);;
   tauz = (double ***) malloc(d_size);;
   oldga = (double ***) malloc(d_size);;
   oldgb = (double ***) malloc(d_size);;

   gp = (struct Global_Private *) malloc((nprocs+1)*sizeof(struct Global_Private));;
   for (i=0;i<nprocs;i++) {
     gp[i].rel_num_x = (long *) malloc(numlev*sizeof(long));;
     gp[i].rel_num_y = (long *) malloc(numlev*sizeof(long));;
     gp[i].eist = (long *) malloc(numlev*sizeof(long));;
     gp[i].ejst = (long *) malloc(numlev*sizeof(long));;
     gp[i].oist = (long *) malloc(numlev*sizeof(long));;
     gp[i].ojst = (long *) malloc(numlev*sizeof(long));;
     gp[i].rlist = (long *) malloc(numlev*sizeof(long));;
     gp[i].rljst = (long *) malloc(numlev*sizeof(long));;
     gp[i].rlien = (long *) malloc(numlev*sizeof(long));;
     gp[i].rljen = (long *) malloc(numlev*sizeof(long));;
     gp[i].multi_time = 0;
     gp[i].total_time = 0;
   }

   subblock();

   x_part = (jm - 2)/xprocs + 2;
   y_part = (im - 2)/yprocs + 2;

   d_size = x_part*y_part*sizeof(double) + y_part*sizeof(double *);

   global = (struct global_struct *) malloc(sizeof(struct global_struct));;
   for (i=0;i<nprocs;i++) {
     psi[i][0] = (double **) malloc(d_size);;
     psi[i][1] = (double **) malloc(d_size);;
     psim[i][0] = (double **) malloc(d_size);;
     psim[i][1] = (double **) malloc(d_size);;
     psium[i] = (double **) malloc(d_size);;
     psilm[i] = (double **) malloc(d_size);;
     psib[i] = (double **) malloc(d_size);;
     ga[i] = (double **) malloc(d_size);;
     gb[i] = (double **) malloc(d_size);;
     work1[i][0] = (double **) malloc(d_size);;
     work1[i][1] = (double **) malloc(d_size);;
     work2[i] = (double **) malloc(d_size);;
     work3[i] = (double **) malloc(d_size);;
     work4[i][0] = (double **) malloc(d_size);;
     work4[i][1] = (double **) malloc(d_size);;
     work5[i][0] = (double **) malloc(d_size);;
     work5[i][1] = (double **) malloc(d_size);;
     work6[i] = (double **) malloc(d_size);;
     work7[i][0] = (double **) malloc(d_size);;
     work7[i][1] = (double **) malloc(d_size);;
     temparray[i][0] = (double **) malloc(d_size);;
     temparray[i][1] = (double **) malloc(d_size);;
     tauz[i] = (double **) malloc(d_size);;
     oldga[i] = (double **) malloc(d_size);;
     oldgb[i] = (double **) malloc(d_size);;
   }
   f = (double *) malloc(im*sizeof(double));;

   multi = (struct multi_struct *) malloc(sizeof(struct multi_struct));;

   d_size = numlev*sizeof(double **);
   if (numlev%2 == 1) {         /* To make sure that the actual data
                                   starts double word aligned, add an extra
                                   pointer */
     d_size += sizeof(double **);
   }
   for (i=0;i<numlev;i++) {
     d_size += ((imx[i]-2)/yprocs+2)*((jmx[i]-2)/xprocs+2)*sizeof(double)+
              ((imx[i]-2)/yprocs+2)*sizeof(double *);
   }

   d_size *= nprocs;

   if (nprocs%2 == 1) {         /* To make sure that the actual data
                                   starts double word aligned, add an extra
                                   pointer */
     d_size += sizeof(double ***);
   }

   d_size += nprocs*sizeof(double ***);
   q_multi = (double ****) malloc(d_size);;
   rhs_multi = (double ****) malloc(d_size);;

   locks = (struct locks_struct *) malloc(sizeof(struct locks_struct));;
   bars = (struct bars_struct *) malloc(sizeof(struct bars_struct));;

   {pthread_mutex_init(&(locks->idlock), NULL);}
   {pthread_mutex_init(&(locks->psiailock), NULL);}
   {pthread_mutex_init(&(locks->psibilock), NULL);}
   {pthread_mutex_init(&(locks->donelock), NULL);}
   {pthread_mutex_init(&(locks->error_lock), NULL);}
   {pthread_mutex_init(&(locks->bar_lock), NULL);}

#if defined(MULTIPLE_BARRIERS)
   {
#line 420
	pthread_barrier_init(&(bars->iteration), NULL, nprocs);
#line 420
}
   {
#line 421
	pthread_barrier_init(&(bars->gsudn), NULL, nprocs);
#line 421
}
   {
#line 422
	pthread_barrier_init(&(bars->p_setup), NULL, nprocs);
#line 422
}
   {
#line 423
	pthread_barrier_init(&(bars->p_redph), NULL, nprocs);
#line 423
}
   {
#line 424
	pthread_barrier_init(&(bars->p_soln), NULL, nprocs);
#line 424
}
   {
#line 425
	pthread_barrier_init(&(bars->p_subph), NULL, nprocs);
#line 425
}
   {
#line 426
	pthread_barrier_init(&(bars->sl_prini), NULL, nprocs);
#line 426
}
   {
#line 427
	pthread_barrier_init(&(bars->sl_psini), NULL, nprocs);
#line 427
}
   {
#line 428
	pthread_barrier_init(&(bars->sl_onetime), NULL, nprocs);
#line 428
}
   {
#line 429
	pthread_barrier_init(&(bars->sl_phase_1), NULL, nprocs);
#line 429
}
   {
#line 430
	pthread_barrier_init(&(bars->sl_phase_2), NULL, nprocs);
#line 430
}
   {
#line 431
	pthread_barrier_init(&(bars->sl_phase_3), NULL, nprocs);
#line 431
}
   {
#line 432
	pthread_barrier_init(&(bars->sl_phase_4), NULL, nprocs);
#line 432
}
   {
#line 433
	pthread_barrier_init(&(bars->sl_phase_5), NULL, nprocs);
#line 433
}
   {
#line 434
	pthread_barrier_init(&(bars->sl_phase_6), NULL, nprocs);
#line 434
}
   {
#line 435
	pthread_barrier_init(&(bars->sl_phase_7), NULL, nprocs);
#line 435
}
   {
#line 436
	pthread_barrier_init(&(bars->sl_phase_8), NULL, nprocs);
#line 436
}
   {
#line 437
	pthread_barrier_init(&(bars->sl_phase_9), NULL, nprocs);
#line 437
}
   {
#line 438
	pthread_barrier_init(&(bars->sl_phase_10), NULL, nprocs);
#line 438
}
   {
#line 439
	pthread_barrier_init(&(bars->error_barrier), NULL, nprocs);
#line 439
}
#else
   {
#line 441
	pthread_barrier_init(&(bars->barrier), NULL, nprocs);
#line 441
}
#endif

   link_all();

   multi->err_multi = 0.0;
   i_int_coeff[0] = 0.0;
   j_int_coeff[0] = 0.0;
   for (i=0;i<numlev;i++) {
     i_int_coeff[i] = 1.0/(imx[i]-1);
     j_int_coeff[i] = 1.0/(jmx[i]-1);
   }

/* initialize constants and variables

   id is a global shared variable that has fetch-and-add operations
   performed on it by processes to obtain their pids.   */

   global->id = 0;
   global->psibi = 0.0;
   pi = atan(1.0);
   pi = 4.*pi;

   factjacob = -1./(12.*res*res);
   factlap = 1./(res*res);
   eig2 = -h*f0*f0/(h1*h3*gpr);

   jmm1 = jm-1 ;
   ysca = ((double) jmm1)*res ;

   im = (imx[numlev-1]-2)/yprocs + 2;
   jm = (jmx[numlev-1]-2)/xprocs + 2;

   if (do_output) {
     printf("                       MULTIGRID OUTPUTS\n");
   }

   {
#line 478
	long	i, Error;
#line 478

#line 478
	for (i = 0; i < (nprocs) - 1; i++) {
#line 478
		Error = pthread_create(&PThreadTable[i], NULL, (void * (*)(void *))(slave), NULL);
#line 478
		if (Error != 0) {
#line 478
			printf("Error in pthread_create().\n");
#line 478
			exit(-1);
#line 478
		}
#line 478
	}
#line 478

#line 478
	slave();
#line 478
};
   {
#line 479
	long	i, Error;
#line 479
	for (i = 0; i < (nprocs) - 1; i++) {
#line 479
		Error = pthread_join(PThreadTable[i], NULL);
#line 479
		if (Error != 0) {
#line 479
			printf("Error in pthread_join().\n");
#line 479
			exit(-1);
#line 479
		}
#line 479
	}
#line 479
};
   {
#line 480
	struct timeval	FullTime;
#line 480

#line 480
	gettimeofday(&FullTime, NULL);
#line 480
	(computeend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 480
}

   printf("\n");
   printf("                       PROCESS STATISTICS\n");
   printf("                  Total          Multigrid         Multigrid\n");
   printf(" Proc             Time             Time            Fraction\n");
   printf("    0   %15.0f    %15.0f        %10.3f\n", gp[0].total_time,gp[0].multi_time, gp[0].multi_time/gp[0].total_time);

   if (do_stats) {
     min_total = max_total = avg_total = gp[0].total_time;
     min_multi = max_multi = avg_multi = gp[0].multi_time;
     min_frac = max_frac = avg_frac = gp[0].multi_time/gp[0].total_time;
     for (i=1;i<nprocs;i++) {
       if (gp[i].total_time > max_total) {
         max_total = gp[i].total_time;
       }
       if (gp[i].total_time < min_total) {
         min_total = gp[i].total_time;
       }
       if (gp[i].multi_time > max_multi) {
         max_multi = gp[i].multi_time;
       }
       if (gp[i].multi_time < min_multi) {
         min_multi = gp[i].multi_time;
       }
       if (gp[i].multi_time/gp[i].total_time > max_frac) {
         max_frac = gp[i].multi_time/gp[i].total_time;
       }
       if (gp[i].multi_time/gp[i].total_time < min_frac) {
         min_frac = gp[i].multi_time/gp[i].total_time;
       }
       avg_total += gp[i].total_time;
       avg_multi += gp[i].multi_time;
       avg_frac += gp[i].multi_time/gp[i].total_time;
     }
     avg_total = avg_total / nprocs;
     avg_multi = avg_multi / nprocs;
     avg_frac = avg_frac / nprocs;
     for (i=1;i<nprocs;i++) {
       printf("  %3ld   %15.0f    %15.0f        %10.3f\n", i,gp[i].total_time,gp[i].multi_time, gp[i].multi_time/gp[i].total_time);
     }
     printf("  Avg   %15.0f    %15.0f        %10.3f\n", avg_total,avg_multi,avg_frac);
     printf("  Min   %15.0f    %15.0f        %10.3f\n", min_total,min_multi,min_frac);
     printf("  Max   %15.0f    %15.0f        %10.3f\n", max_total,max_multi,max_frac);
   }
   printf("\n");

   global->starttime = start;
   printf("                       TIMING INFORMATION\n");
   printf("Start time                        : %16lu\n", global->starttime);
   printf("Initialization finish time        : %16lu\n", global->trackstart);
   printf("Overall finish time               : %16lu\n", computeend);
   printf("Total time with initialization    : %16lu\n", computeend-global->starttime);
   printf("Total time without initialization : %16lu\n", computeend-global->trackstart);
   printf("    (excludes first timestep)\n");
   printf("\n");

   {exit(0);}
}

long log_2(long number)
{
  long cumulative = 1;
  long out = 0;
  long done = 0;

  while ((cumulative < number) && (!done) && (out < 50)) {
    if (cumulative == number) {
      done = 1;
    } else {
      cumulative = cumulative * 2;
      out ++;
    }
  }

  if (cumulative == number) {
    return(out);
  } else {
    return(-1);
  }
}

void printerr(char *s)
{
  fprintf(stderr,"ERROR: %s\n",s);
}

