#line 185 "/home/zhy/work/test/splash2-master/codes/null_macros/c.m4.null.POSIX_BARRIER"

#line 1 "mdmain.C"
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


#line 17
#include <pthread.h>
#line 17
#include <sys/time.h>
#line 17
#include <unistd.h>
#line 17
#include <stdlib.h>
#line 17
#include <malloc.h>
#line 17
extern pthread_t PThreadTable[];
#line 17


#include <stdio.h>

#include "parameters.h"
#include "mdvar.h"
#include "water.h"
#include "wwpot.h"
#include "cnst.h"
#include "mddata.h"
#include "fileio.h"
#include "split.h"
#include "global.h"

/************************************************************************/

double MDMAIN(long NSTEP, long NPRINT, long NSAVE, long NORD1, long ProcID)
{
    double TVIR = 0.0;
    double TTMV = 0.0;
    double TKIN = 0.0;
    double XTT;
    long i,j,k;
    double POTA,POTR,POTRF;
    double XVIR,AVGT,TEN;
    struct list_of_boxes *new_box, *curr_box;

    for (i=start_end[ProcID]->box[XDIR][FIRST]; i<=start_end[ProcID]->box[XDIR][LAST]; i++) {
        for (j=start_end[ProcID]->box[YDIR][FIRST]; j<=start_end[ProcID]->box[YDIR][LAST]; j++) {
            for (k=start_end[ProcID]->box[ZDIR][FIRST]; k<=start_end[ProcID]->box[ZDIR][LAST]; k++) {
                new_box = (box_list *) malloc(sizeof(box_list));;
                new_box->coord[XDIR] = i;
                new_box->coord[YDIR] = j;
                new_box->coord[ZDIR] = k;
                new_box->next_box = NULL;
                curr_box = my_boxes[ProcID];
                if (curr_box == NULL)
                    my_boxes[ProcID] = new_box;
                else {
                    while (curr_box->next_box != NULL)
                        curr_box = curr_box->next_box;
                    curr_box->next_box = new_box;
                } /* else */
            }
        }
    }

    /* calculate initial value for acceleration */

    INTRAF(&gl->VIR,ProcID);

    {
#line 68
	pthread_barrier_wait(&(gl->start));
#line 68
};

    INTERF(ACC,&gl->VIR,ProcID);

    {
#line 72
	pthread_barrier_wait(&(gl->start));
#line 72
};

    /* MOLECULAR DYNAMICS LOOP */

    for (i=1;i <= NSTEP; i++) {
        TTMV=TTMV+1.00;

        /* POSSIBLE ENHANCEMENT:  Here's where one start measurements to avoid
           cold-start effects.  Recommended to do this at the beginning of the
           second timestep; i.e. if (i == 2).
           */

        /* initialize various shared sums */
        if (ProcID == 0) {
            long dir;
            if (i >= 2) {
                {
#line 88
	struct timeval	FullTime;
#line 88

#line 88
	gettimeofday(&FullTime, NULL);
#line 88
	(gl->trackstart) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 88
};
            }
            gl->VIR = 0.0;
            gl->POTA = 0.0;
            gl->POTR = 0.0;
            gl->POTRF = 0.0;
            for (dir = XDIR; dir <= ZDIR; dir++)
                gl->SUM[dir] = 0.0;
        }

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 99
	struct timeval	FullTime;
#line 99

#line 99
	gettimeofday(&FullTime, NULL);
#line 99
	(gl->intrastart) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 99
};
        }

        {
#line 102
	pthread_barrier_wait(&(gl->start));
#line 102
};

        PREDIC(TLC,NORD1,ProcID);
        INTRAF(&gl->VIR,ProcID);

        {
#line 107
	pthread_barrier_wait(&(gl->start));
#line 107
};

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 110
	struct timeval	FullTime;
#line 110

#line 110
	gettimeofday(&FullTime, NULL);
#line 110
	(gl->intraend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 110
};
            gl->intratime += gl->intraend - gl->intrastart;
        }

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 115
	struct timeval	FullTime;
#line 115

#line 115
	gettimeofday(&FullTime, NULL);
#line 115
	(gl->interstart) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 115
};
        }

        INTERF(FORCES,&gl->VIR,ProcID);

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 121
	struct timeval	FullTime;
#line 121

#line 121
	gettimeofday(&FullTime, NULL);
#line 121
	(gl->interend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 121
};
            gl->intertime += gl->interend - gl->interstart;
        }

        CORREC(PCC,NORD1,ProcID);

        BNDRY(ProcID);

        KINETI(gl->SUM,HMAS,OMAS,ProcID);

        {
#line 131
	pthread_barrier_wait(&(gl->start));
#line 131
};

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 134
	struct timeval	FullTime;
#line 134

#line 134
	gettimeofday(&FullTime, NULL);
#line 134
	(gl->intraend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 134
};
            gl->intratime += gl->intraend - gl->interend;
        }

        TKIN=TKIN+gl->SUM[0]+gl->SUM[1]+gl->SUM[2];
        TVIR=TVIR-gl->VIR;

        /* CHECK if  PRINTING AND/OR SAVING IS TO BE DONE */

        if ( ((i % NPRINT) == 0) || ((NSAVE > 0) && ((i % NSAVE) == 0))) {

            /* if so, call poteng to compute potential energy.  Note
               that we are attributing all the time in poteng to intermolecular
               computation although some of it is intramolecular (see poteng.C) */

            if ((ProcID == 0) && (i >= 2)) {
                {
#line 150
	struct timeval	FullTime;
#line 150

#line 150
	gettimeofday(&FullTime, NULL);
#line 150
	(gl->interstart) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 150
};
            }

            POTENG(&gl->POTA,&gl->POTR,&gl->POTRF,ProcID);

            {
#line 155
	pthread_barrier_wait(&(gl->start));
#line 155
};

            if ((ProcID == 0) && (i >= 2)) {
                {
#line 158
	struct timeval	FullTime;
#line 158

#line 158
	gettimeofday(&FullTime, NULL);
#line 158
	(gl->interend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 158
};
                gl->intertime += gl->interend - gl->interstart;
            }

            POTA=gl->POTA*FPOT;
            POTR=gl->POTR*FPOT;
            POTRF=gl->POTRF*FPOT;
            XVIR=TVIR*FPOT*0.50/TTMV;
            AVGT=TKIN*FKIN*TEMP*2.00/(3.00*TTMV);
            TEN=(gl->SUM[0]+gl->SUM[1]+gl->SUM[2])*FKIN;
            XTT=POTA+POTR+POTRF+TEN;

            /* if it is time to print output as well ... */
            if ((i % NPRINT) == 0 && ProcID == 0) {
                {pthread_mutex_lock(&(gl->IOLock));};
                fprintf(six,"     %5ld %14.5lf %12.5lf %12.5lf %12.5lf \n"
                        ,i,TEN,POTA,POTR,POTRF);
                fprintf(six," %16.3lf %16.5lf %16.5lf\n",XTT,AVGT,XVIR);
                fflush(six);
                {pthread_mutex_unlock(&(gl->IOLock));};
            }

        }

        {
#line 182
	pthread_barrier_wait(&(gl->start));
#line 182
};

        if ((ProcID == 0) && (i >= 2)) {
            {
#line 185
	struct timeval	FullTime;
#line 185

#line 185
	gettimeofday(&FullTime, NULL);
#line 185
	(gl->trackend) = (unsigned long)(FullTime.tv_usec + FullTime.tv_sec * 1000000);
#line 185
};
            gl->tracktime += gl->trackend - gl->trackstart;
        }

    } /* for i */

    return(XTT);

} /* mdmain.c */
