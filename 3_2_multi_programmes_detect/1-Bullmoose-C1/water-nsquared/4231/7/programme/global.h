#line 185 "/home/zhy/work/test/splash2-master/codes/null_macros/c.m4.null.POSIX_BARRIER"

#line 1 "global.H"
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

/*  This file contains the declaration of the GlobalMemory
structure and the maximum number of molecules allowed
by the program. */

#define MAXLCKS	4096L

struct GlobalMemory {
    pthread_mutex_t (IOLock);
    pthread_mutex_t (IndexLock);
    pthread_mutex_t (IntrafVirLock);
    pthread_mutex_t (InterfVirLock);
    pthread_mutex_t (FXLock);
    pthread_mutex_t (FYLock);
    pthread_mutex_t (FZLock);
    pthread_mutex_t (KinetiSumLock);
    pthread_mutex_t (PotengSumLock);
    pthread_mutex_t MolLock[MAXLCKS];
    
#line 34
pthread_barrier_t	(start);
#line 34

    
#line 35
pthread_barrier_t	(InterfBar);
#line 35

    
#line 36
pthread_barrier_t	(PotengBar);
#line 36

    long Index;
    double VIR;
    double SUM[3];
    double POTA, POTR, POTRF;
    unsigned long computestart,computeend;
    unsigned long trackstart, trackend, tracktime;
    unsigned long intrastart, intraend, intratime;
    unsigned long interstart, interend, intertime;
};

extern struct GlobalMemory *gl;

/* bndry.C */
void BNDRY(long ProcID);

/* cnstnt.C */
void CNSTNT(long N, double *C);

/* cshift.C */
void CSHIFT(double *XA, double *XB, double XMA, double XMB, double *XL, double BOXH, double BOXL);

/* initia.C */
void INITIA(void);
double xrand(double xl, double xh);

/* interf.C */
void INTERF(long DEST, double *VIR, long ProcID);
void UPDATE_FORCES(long mol, long comp, double *XL, double *YL, double *ZL, double *FF, long ProcID);

/* intraf.C */
void INTRAF(double *VIR, long ProcID);

/* kineti.C */
void KINETI(double *SUM, double HMAS, double OMAS, long ProcID);

/* mdmain.C */
double MDMAIN(long NSTEP, long NPRINT, long NSAVE, long NORD1, long ProcID);

/* poteng.C */
void POTENG(double *POTA, double *POTR, double *PTRF, long ProcID);

/* predcor.C */
void PREDIC(double *C, long NOR1, long ProcID);
void CORREC(double *PCC, long NOR1, long ProcID);

/* syscons.C */
void SYSCNS(void);

/* water.C */
void WorkStart(void);
