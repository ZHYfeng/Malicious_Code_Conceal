/*
** pcopy.c
**
** A multithreaded (raw) disk copying program.
**
** Copyright (c) 1997-2003 Peter Eriksson <pen@lysator.liu.se>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "config.h"

#define _LARGEFILE64_SOURCE 1

#ifdef HAVE_LIBTHREAD
#  define _REENTRANT
#  include <thread.h>
#endif

#ifdef HAVE_LIBPTHREAD
/* #  define _POSIX_C_SOURCE 199506L */
#  include <pthread.h>
#endif


#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <fcntl.h>


char *srcdev=NULL;
char *dstdev=NULL;
int freq = 5;
time_t last = 0;


#ifndef HAVE_LIBPTHREAD
#ifdef HAVE_LIBTHREAD

/* Partial pthreads emulation using UI threads */
#define pthread_t	thread_t
#define pthread_mutex_t	mutex_t
#define pthread_cond_t	cond_t

#define pthread_create(tp,at,st,arg) 	thr_create(NULL,0,st,arg,0,tp)
#define pthread_join(tid,sp) 		thr_join(tid,NULL,sp)
				       
#define pthread_mutex_init(mtx,ma)	mutex_init(mtx, USYNC_THREAD, NULL)
#define pthread_cond_init(cv,ca)	cond_init(cv, USYNC_THREAD, NULL)

#define pthread_mutex_lock(mtx)		mutex_lock(mtx)
#define pthread_mutex_unlock(mtx)	mutex_unlock(mtx)

#define pthread_cond_wait(cv,mtx)	cond_wait(cv,mtx)
#define pthread_cond_signal(cv)		cond_signal(cv)

#else

#error Must have Pthreads or UI Threads!

#endif
#endif

#if SIZEOF_LONG == 8
#  define lseek64 lseek
#  define off64_t unsigned long
#else
#  ifndef HAVE_LSEEK64
#    ifdef HAVE_LLSEEK
#      define lseek64 llseek
#      define off64_t offset_t
#    else
/* No lseek64 or llseek function - use 32bit version */
#      define lseek64 lseek
#      define off64_t unsigned long
#    endif
#  endif
#endif


int buffer_size = 1024*1024;
int queue_size = 8;
int dot_mode = 0;
time_t start;
int silent = 0;


typedef struct buffer
{
    off64_t pos;
    int len;
    int size;
    char *buf;
} buffer_t;


typedef struct queue
{
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
    
    int occupied;
    int nextin;
    int nextout;
    int bsize;

    void **buf;
} queue_t;


int read_fd;
int write_fd;
off64_t read_pos;
off64_t write_pos;

queue_t *write_q;
queue_t *free_q;


int no_write = 0;



int x_pread64(off64_t pos, char *buf, int len)
{
    int res;
    int attempt;
    

    attempt = 0;
    do
    {
	if (read_pos != pos)
	    if (lseek64(read_fd, read_pos = pos, SEEK_SET) < 0)
		return -1;
	
	res = read(read_fd, buf, len);
    } while (res < 0 && attempt++ < 4);

    if (res > 0)
	read_pos += res;
    
    return res;
}

int x_pwrite64(off64_t pos, char *buf, int len)
{
    int res;


    if (no_write)
    {
	res = len;
	write_pos = pos + len;
    }
    else
    {
	if (write_pos =! pos)
	    if (lseek64(write_fd, write_pos = pos, SEEK_SET) < 0)
		return -1;
	
	res = write(write_fd, buf, len);
	if (res > 0)
	    write_pos += res;
    }
    
    return res;
}


queue_t *q_create(int size)
{
    queue_t *qp;

    qp = (queue_t *) malloc(sizeof(*qp));

    pthread_mutex_init(&qp->mutex, NULL);
    pthread_cond_init(&qp->more, NULL);
    pthread_cond_init(&qp->less, NULL);

    qp->bsize = size;
    qp->occupied = 0;
    qp->nextin = 0;
    qp->nextout = 0;

    qp->buf = calloc(qp->bsize, sizeof(qp->buf[0]));
    return qp;
}


void q_push(queue_t *qp, void *item)
{
    pthread_mutex_lock(&qp->mutex);

    while (qp->occupied >= qp->bsize)
	pthread_cond_wait(&qp->less, &qp->mutex);

    assert(qp->occupied < qp->bsize);

    qp->buf[qp->nextin++] = item;
    qp->nextin %= qp->bsize;
    qp->occupied++;

    pthread_cond_signal(&qp->more);
    pthread_mutex_unlock(&qp->mutex);
}


void *q_pop(queue_t *qp)
{
    void *item;


    pthread_mutex_lock(&qp->mutex);
    while (qp->occupied <= 0)
	pthread_cond_wait(&qp->more, &qp->mutex);

    assert(qp->occupied > 0);
  
    item = qp->buf[qp->nextout++];
    qp->nextout %= qp->bsize;
    qp->occupied--;

    pthread_cond_signal(&qp->less);
    pthread_mutex_unlock(&qp->mutex);

    return item;
}


buffer_t *b_create(int size)
{
    buffer_t *bp;


    bp = (buffer_t *) malloc(sizeof(*bp));
    bp->pos = 0;
    bp->len = 0;
    bp->size = size;
    bp->buf = malloc(size);

    return bp;
}

void
spin(time_t now)
{
    static char *spintab = "-\\|/";
    static int pos = 0;
    static time_t last = 0;
    

    if (now == last)
	return;

    last = now;
    putchar(spintab[pos]);
    putchar('\b');
    fflush(stdout);
    pos = (pos+1)&3;
}

    

void *writer(void *foo)
{
    buffer_t *bp;
    long long written = 0;
    long long last_written = 0;
    int len;

    
    while (bp = q_pop(write_q))
    {
	if (x_pwrite64(bp->pos, bp->buf, bp->len) != bp->len)
	{
	    if (!silent)
		putc('\n', stderr);
	    
	    fprintf(stderr,
		    "pcopy: %s: Error: Write of %d bytes failed at "
#if SIZEOF_LONG == 8
		    "%ld"
#else
		    "%lld"
#endif
		    ": %s\n",
		    dstdev, bp->len, bp->pos,
		    strerror(errno));
	    return 1;
	}

	written += bp->len;
	
	bp->pos = 0;
	bp->len = 0;
	q_push(free_q, bp);

	if (!silent)
	{
	    if (dot_mode)
	    {
		putchar('.');
		fflush(stdout);
	    }
	    else
	    {
		time_t now;
		long long mbs;
		
		
		time(&now);
		len = now - start;
		if (len <= 0)
		    len = 1;
		
		if (now > last+freq)
		{
		    mbs = (written-last_written)/freq/1024/1024;

		    last_written = written;
			
#if SIZEOF_LONG == 8
		    printf("\rCopied: %ld MB (%ld MB/sec)     ",
			   written/1024/1024,
			   mbs);
#else
		    printf("\rCopied: %lld MB (%lld MB/sec)     ",
			   written/1024/1024,
			   mbs);
#endif
		    fflush(stdout);
		    last = now;
		}

		spin(now);
	    }
	}
    }

    return NULL;
}


void usage(void)
{
    fprintf(stderr, "Usage: pcopy [options] <source> <destination>\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-s\tSilent mode\n");
    fprintf(stderr, "-q<num>\tQueue size\n");
    fprintf(stderr, "-u<num>\tUpdate frequency (in seconds)\n");
    fprintf(stderr, "-b<num>\tBuffer size (in KBytes)\n");
    fprintf(stderr, "-d\tShow progress as a series of dots\n");
}


int main(int argc, char *argv[])
{
    int i, size;
    pthread_t tid;
    off64_t pos;
    long long bytes, mbytes;
    int len;
    void *status;
    buffer_t *bp;
    time_t stop;
    
    
    for (i = 1; i < argc && argv[i][0] == '-'; i++)
	switch (argv[i][1])
	{
	  case 's':
	    silent = 1;
	    break;
	    
	  case 'n':
	    no_write = 1;
	    break;
	    
	  case 'd':
	    dot_mode = 1;
	    break;
	    
	  case 'q':
	    queue_size = atoi(argv[i]+2);
	    break;

	  case 'u':
	    freq = atoi(argv[i]+2);
	    break;

	  case 'b':
	    buffer_size = atoi(argv[i]+2)*1024;
	    break;

	  case 'h':
	  default:
	    usage();
	    return 0;
	}
    
    if (i + 2 != argc)
    {
	usage();
	return 1;
    }

    srcdev=argv[i];
    dstdev=argv[i+1];
    
    if (!silent)
    {
	printf("Copying from %s to %s (start in 3 seconds)", srcdev, dstdev);
	fflush(stdout);
	putchar('.');
	fflush(stdout);
	putchar('.');
	fflush(stdout);
	putchar('.');
	putchar('\n');
	fflush(stdout);
    }

#ifdef HAVE_LIBTHREAD
    thr_setconcurrency(4);
#endif
    
    read_fd = open(srcdev, O_RDONLY);
    if (read_fd < 0)
    {
	fprintf(stderr, "pcopy: %s: Source device open failed: %s\n",
		srcdev, strerror(errno));
	return 1;
    }
  
    write_fd = open(dstdev, O_WRONLY+O_SYNC);
    if (write_fd < 0)
    {
	fprintf(stderr, "pcopy: %s: Destination device open failed: %s\n",
		dstdev, strerror(errno));
	return 1;
    }
    
    
    free_q = q_create(queue_size);
    write_q = q_create(queue_size);

    for (i = 0; i < queue_size; i++)
	q_push(free_q, b_create(buffer_size));

    pthread_create(&tid, NULL, writer, NULL);
    pos = 0;
    bytes = 0;

    time(&start);
    time(&last);
  Loop:
    bp = q_pop(free_q);
    size = bp->size;

    while ((len = x_pread64(pos, bp->buf, size)) < 0 && errno == EIO)
    {
	/* XXX: This code more or less assumes that buffer_size is
	   an even multiple of 2 */
	
	if (size > 512)
	{
	    if (!silent)
		putc('\n', stderr);
	    
	    fprintf(stderr,
		    "pcopy: %s: Warning: Problems reading %d bytes at "
#if SIZEOF_LONG == 8
		    "%ld"
#else
		    "%lld"
#endif
		    ": %s\n",
		    srcdev, size, pos, strerror(errno));
	    
	    size >>= 2; /* Try with a smaller size */
	}
	else
	{
	    /* Give up, and return a zero-filled sector */
	    fprintf(stderr,
		    "pcopy: %s: Error: Read of %d bytes at "
#if SIZEOF_LONG == 8
		    "%ld"
#else
		    "%lld"
#endif
		    " failed: %s\n",
		    srcdev, size, pos, strerror(errno));
	    
	    len = size;
	    memset(bp->buf, 0, len);
	    break;
	}
    }

    if (len == 0)
	goto End;
  
    bp->len = len;
    bp->pos = pos;
  
    pos += len;

    bytes += len;
    
    q_push(write_q, bp);
    goto Loop;

  End:
    q_push(write_q, NULL);
    pthread_join(tid, &status);
    
    time(&stop);
    len = stop-start;
    if (len <= 0)
	len = 1;
    
    mbytes = bytes/1024/1024;

    if (!silent)
	putchar('\n');
    
#if SIZEOF_LONG == 8
    printf("%s: Done. Copied %ld MB in %d seconds (%ld MB/s)\n",
	   srcdev, mbytes, len, mbytes/len);
#else
    printf("%s: Done. Copied %lld MB in %d seconds (%lld MB/s)\n",
	   srcdev, mbytes, len, mbytes/len);
#endif
    return 0;
}
