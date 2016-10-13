/* Boyer-Moore string search as found on the internet using Google */

#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bm.h"

#define ASIZE 256 /* Allowed character code values */

#define MAX(a,b) ((a) < (b) ? (b) : (a))

static int xsize = 0;
static int *bmGs = NULL;

static int bmBc[ASIZE];
static unsigned char *saved_x;
static int saved_m;



static void
preBmBc(unsigned char *x, int m, int bmBc[])
{
    int i;
    
    for (i = 0; i < ASIZE; ++i)
	bmBc[i] = m;
    
    for (i = 0; i < m - 1; ++i)
	bmBc[x[i]] = m - i - 1;
}


static void
suffixes(unsigned char *x, int m, int *suff)
{
    int f, g, i;


    f = 0;
    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i)
    {
	if (i > g && suff[i + m - 1 - f] < i - g)
	    suff[i] = suff[i + m - 1 - f];
	else
	{
	    if (i < g)
		g = i;
	    f = i;
	    while (g >= 0 && x[g] == x[g + m - 1 - f])
		--g;
	    suff[i] = f - g;
	}
    }
}


int
preBmGs(unsigned char *x, int m, int bmGs[])
{
    int i, j, *suff;


    suff = (int *) calloc(sizeof(int), xsize);
    if (suff == NULL)
	return -1;
    
    suffixes(x, m, suff);
    
    for (i = 0; i < m; ++i)
	bmGs[i] = m;

    j = 0;
    for (i = m - 1; i >= -1; --i)
	if (i == -1 || suff[i] == i + 1)
	    for (; j < m - 1 - i; ++j)
		if (bmGs[j] == m)
		    bmGs[j] = m - 1 - i;

    for (i = 0; i <= m - 2; ++i)
	bmGs[m - 1 - suff[i]] = m - 1 - i;

    free(suff);
    return 0;
}


int
bm_setup(void *ss, int m)
{
    int i;
    unsigned char *x = (unsigned char *) ss;


    if (bmGs)
    {
	free(bmGs);
	xsize = 0;
    }

    bmGs = (int *) calloc(sizeof(int), m);
    if (bmGs == NULL)
	return -1;
    
    xsize = m;
    
    saved_m = m;
    saved_x = (unsigned char *) malloc(m);
    if (saved_x == NULL)
	return -2;
    
    for (i = 0; i < m; i++)
	saved_x[i] = tolower(x[i]);
    
    /* Preprocessing */
    if (preBmGs((unsigned char *) saved_x, m, bmGs) < 0)
	return -3;
    
    preBmBc((unsigned char *) saved_x, m, bmBc);

    return 0;
}    


int
bm_search(void *buf, int n)
{
    int i, j;
    unsigned char *y;


    y = (unsigned char *) buf;
    
    /* Searching */
    j = 0;
    while (j <= n - saved_m)
    {
	for (i = saved_m - 1;
	     i >= 0 && saved_x[i] == tolower(y[i + j]);
	     --i)
	    ;
	
	if (i < 0)
	{
#if 0
	    printf("Match found at %d\n", j);
	    j += bmGs[0];
#else
	    return j;
#endif
	}
	else
	{
	    int c = tolower(tolower(y[i + j]));

	    j += MAX(bmGs[i], bmBc[c] - saved_m + 1 + i);
	}
    }

    return -1;
}

#if 0
int
main(int argc,
     char *argv[])
{
    int pos;

    
    bm_setup(argv[1], strlen(argv[1]));

    pos = bm_search(argv[2], strlen(argv[2]));

    printf("Match at pos %d\n", pos);

    exit(0);
}
#endif
