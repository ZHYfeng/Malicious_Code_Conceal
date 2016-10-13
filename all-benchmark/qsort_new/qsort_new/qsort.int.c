/* 
 * Copyright (C) 2005 Abel Bennett.
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

/**
 * @author Abel Bennett
 * @date 2002/11/17
 * @version 1.0
 */


#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


#include <alloca.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





size_t merge(int* base, size_t num) {
	size_t begin, end, start, finish;
	start = begin = 0;
	finish = end = num - 1;
	int sambol = base[start];
	int temp;
	while (1) {
		for (; start <= finish; start++) {
			if (base[start] > sambol) {
				break;
			}
		}
		for (; start < finish; finish--) {
			if (base[finish] < sambol) {
				break;
			}
		}
		if (start < finish) {
			temp = base[start];
			base[start] = base[finish];
			base[finish] = temp;
		} else {
			break;
		}
	}
	temp = base[start - 1];
	base[start - 1] = sambol;
	base[begin] = temp;
	return start - 1;
}

void my_qsort(int* base, size_t num) {
	int* ptr;
	unsigned i;
	if (num > 1) {
		int middle = merge(base, num);
		if (middle > 1) {
		    my_qsort(base, middle);
        }
		if (middle < num - 2) {
            my_qsort(base + middle + 1, num - middle - 1);
	    }
	}
}


/**
 * @brief sort base in the order specified by the compare function
 * @param base data array
 * @param nel number of elements in data array
 * @param width size of element in data array
 * @param compare compare function for element in data array
 * @param num_threads number of threads to use
 * @warning <ul><li>default thread attributes used</li></ul>
 * @warning <ul><li>cancellation is disabled</li></ul>
 */
extern void pthread_qsort(int * base, const size_t nel, const size_t num_threads);


/**
 * @brief ctf major version number
 */
#define PTHREAD_CTF_MAJOR 0

/**
 * @brief ctf minor version number
 */
#define PTHREAD_CTF_MINOR 1

/**
 * @brief ctf micro version number
 */
#define PTHREAD_CTF_MICRO 0


/**
 * @brief returns the number of on-line processors
 * @param number number of processors
 * @return
 * 0 is returned on success<br>
 * non-zero error code is returned on failure
 */
extern int pthread_get_nproc(int * number);

/**
 * @brief returns a string representing the pthread_t
 * @param tid pthread_t ID [input]
 * @param buf pointer to a character array
 * @param len maximum length for buffer
 * @return
 * 0 is returned on success<br>
 * non-zero error code is returned on failure
 */
extern int pthread_get_name(const pthread_t tid, char * buf, const size_t len);

/**
 * @brief returns the version of pthreads library
 * @param buf pointer to a character array
 * @param len maximum length for buffer
 * @return
 * 0 is returned on success<br>
 * non-zero error code is returned on failure
 */
extern int pthread_version(char * buf, const size_t len);

/**
 * @brief returns the version of ctf library
 * @param buf pointer to a character array
 * @param len maximum length for buffer
 * @return
 * 0 is returned on success<br>
 * non-zero error code is returned on failure
 */
extern int pthread_ctf_version(char * buf, const size_t len);



struct pthread_qsort_data_t
{
    int * base; /* address of data */
    size_t width; /* size of data element */
    size_t first; /* index of first data (inclusive) */
    size_t last; /* index of last data (inclusive) */
    int (*compare)(const void *, const void *); /* compare function */
    size_t switch_size; /* number of elements to use in threading */
    pthread_mutex_t * mutex; /* lock for thread function */
    pthread_cond_t * cond; /* condition for thread function */
    int * finished; /* return value of thread */
};


static void * pthread_qsort_local_call(void * arg);
/*
    arguments:
        (1) pointer to an initialized pthread_qsort_t [input]
    functionality:
        (1) act as a wrapper to convert from threading function
            call, single argument, to the non-threaded function
            call, multiple arguments
*/

inline static void pthread_qsort_local(int * base, const size_t first, const size_t last, const size_t switch_size);
/*
    arguments:
        (1) pointer to data array [input/output]
        (2) element size [input]
        (3) first index (inclusive) [input]
        (4) last index (inclusive) [input]
        (5) compare function for element in data array [input]
        (6) size to switch to non-threaded qsort [input]
    functionality:
        (1) to sort array in base in the order specified by the
            compare function
*/

inline static void pthread_qsort_split(int * base, const size_t first, const size_t last, size_t * middle);
/*
    arguments:
        (1) pointer to data array [input/output]
        (2) element size [input]
        (3) first index (inclusive) [input]
        (4) last index (inclusive) [input]
        (5) pointer to sorted middle [output]
        (6) compare function for element in data array [input]
    functionality:
        (1) to find sorted middle of base array
*/

inline static void pthread_qsort_swap(int * base, const size_t elem1, const size_t elem2);
/*
    arguments:
        (1) pointer to data array [input/output]
        (2) element size [input]
        (3) element index (inclusive) [input]
        (4) element index (inclusive) [input]
    functionality:
        (1) to swap base array elements first and last
*/


void pthread_qsort(int * base, const size_t nel, const size_t num_threads)
{
    int switch_size;

    switch_size = nel / num_threads;
    if (switch_size < 3) {
        switch_size = 3;
    }
    /* call threaded qsort function */
    pthread_qsort_local(base, 0, (nel - 1), (size_t)switch_size);

    return;
}

static void * pthread_qsort_local_call(void * arg)
{
    struct pthread_qsort_data_t * data = (struct pthread_qsort_data_t *)arg;


    /*
        convert from threaded, single argument, to non-threaded,
        multiple arguments, function call
    */
    pthread_qsort_local(data->base, data->first, data->last, data->switch_size);

    /* lock thread lock */
    if(pthread_mutex_lock(data->mutex) != 0)
    {
        abort();
    }

    (*(data->finished)) = 1;

    /* signal thread caller */
    if(pthread_cond_signal(data->cond) != 0)
    {
        abort();
    }

    /* unlock thread lock */
    if(pthread_mutex_unlock(data->mutex) != 0)
    {
        abort();
    }

    return NULL;
}

inline static void pthread_qsort_local(int * base, const size_t first, const size_t last, const size_t switch_size)
{   
    printf("%d, %d, %d\n", first, last, switch_size);
    int thread_finished;
    size_t middle;
    struct pthread_qsort_data_t work;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, 0);

    pthread_cond_t cond;
    
    pthread_cond_init(&cond, NULL); /* = PTHREAD_COND_INITIALIZER; */

    pthread_t tid;
    pthread_attr_t attr;



    if((last - first) > switch_size)
    {
        /* split the array */
        pthread_qsort_split(base, first, last, &middle);

        /* initialize number of threads completed */
        thread_finished = 0;

        /* copy to threaded function call structure */
        work.base = base;
        work.first = first;
        work.last = (middle - 1);
        work.switch_size = switch_size;
        work.mutex = &mutex;
        work.cond = &cond;
        work.finished = &thread_finished;

        /* initialize thread attributes to default */
        if(pthread_attr_init(&attr) != 0)
        {
            abort();
        }

        /* assign detach attribute */
        if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        {
            abort();
        }

        /* call a new thread for first half of data */
        if(pthread_create(&tid, &attr, pthread_qsort_local_call, &work) != 0)
        {
            abort();
        }

        /* use current thread for second half of data */
        pthread_qsort_local(base, (middle + 1), last, switch_size);

        /* lock local lock */
        if(pthread_mutex_lock(&mutex) != 0)
        {
            abort();
        }

        /* while create thread is working */
        while(thread_finished == 0)
        {
            /* wait for created thread to signal */
            if(pthread_cond_wait(&cond, &mutex) != 0)
            {
                abort();
            }
        }

        /* unlock local lock */
        if(pthread_mutex_unlock(&mutex) != 0)
        {
            abort();
        }

        /* destroy thread attributes */
        if(pthread_attr_destroy(&attr) != 0)
        {
            abort();
        }
    }
    else
    {
        /* call non-threaded libc qsort */
        my_qsort(base + first, (last - first + 1));
    }

    return;
}

inline static void pthread_qsort_split(int * base, const size_t first, const size_t last, size_t * middle)
{
    short done;
    size_t ii, jj, temp_middle;
    int test_temp;


    /* find the middle of the data */
    temp_middle = (first + last) / 2;

    /* find three median of the three: first, middle, last */

    if(base[temp_middle] < base[first])
    {
        pthread_qsort_swap(base, temp_middle, first);
    }

    if(base[last] < base[first])
    {
        pthread_qsort_swap(base, last, first);
    }

    if(base[last] < base[temp_middle])
    {
        pthread_qsort_swap(base, last, temp_middle);
    }

    /* copy median to temporary location, test_temp */
    test_temp = base[temp_middle];

    /* swap middle with last */
    pthread_qsort_swap(base, temp_middle, last - 1);

    /* initialize variables */
    ii = first;
    jj = last -1;
    done = 0;

    while(done == 0)
    {
        ii++;

        /* while index ii is less than median */
        while(base[ii] < test_temp)
        {
            ii++;
        }

        jj--;

        /* while index jj is greater than median */
        while(base[jj] > test_temp)
        {
            jj--;
        }

        /* if more work to be done */
        if(ii < jj)
        {
            /* swap index ii and jj */
            pthread_qsort_swap(base, ii, jj);
        }
        else
        {
            /* all finished */
            done = 1;
        }
    }

    /* insert median into correct position */
    pthread_qsort_swap(base, ii, last -1);

    /* set median location */
    (*middle) = ii;

    return;
}

inline static void pthread_qsort_swap(int * base, const size_t elem1, const size_t elem2)
{
    int temp;
    temp = base[elem1];
    base[elem1] = base[elem2];
    base[elem2] = temp;
    return;
}








int pthread_ctf_version(char * buf, const size_t len)
{
    (void)snprintf(buf, len, "%d.%d.%d", PTHREAD_CTF_MAJOR,
            PTHREAD_CTF_MINOR, PTHREAD_CTF_MICRO);

    return 0;
}


#if defined(__sun)

#include <stdio.h>
#include <sys/utsname.h>


int pthread_get_nproc(int * number)
{
    if(number == NULL)
    {
        return EFAULT;
    }

    /* get number of processors online */
    if(((*number) = (int)sysconf(_SC_NPROCESSORS_ONLN)) == -1)
    {
        return ENOTSUP;
    }

    return 0;
}

int pthread_get_name(const pthread_t tid, char * buf, const size_t len)
{
    /* convert to a string */
    (void)snprintf(buf, len, "%d", (int)tid);

    return 0;
}

int pthread_version(char * buf, const size_t len)
{
    struct utsname info;


    /* get system uname information */
    if(uname(&info) == -1)
    {
        abort();
    }

    /* write version informatin to string */
    (void)snprintf(buf, len, "%s", info.release);

    return 0;
}

#elif defined(__linux)

int pthread_get_nproc(int * number)
{
    if(number == NULL)
    {
        return EFAULT;
    }

    /* get number of processors online */
    if(((*number) = (int)sysconf(_SC_NPROCESSORS_ONLN)) == -1)
    {
        return ENOTSUP;
    }

    return 0;
}

int pthread_get_name(const pthread_t tid, char * buf, const size_t len)
{
    /* convert to a string */
    (void)snprintf(buf, len, "%d", (int)tid);

    return 0;
}

int pthread_version(char * buf, const size_t len)
{
#if defined(_CS_GNU_LIBPTHREAD_VERSION)
    confstr(_CS_GNU_LIBPTHREAD_VERSION, buf, len);
#else
    (void)snprintf(buf, len, "linuxthreads 0.00");
#endif

    return 0;
}

#elif defined(__sgi)

int pthread_get_nproc(int * number)
{
    if(number == NULL)
    {
        return EFAULT;
    }

    /* get number of processors online */
    if(((*number) = (int)sysconf(_SC_NPROC_ONLN)) == -1)
    {
        return ENOTSUP;
    }

    return 0;
}

int pthread_get_name(const pthread_t tid, char * buf, const size_t len)
{
    /* convert to a string */
    (void)snprintf(buf, len, "%d", (int)tid);

    return 0;
}

int pthread_version(char * buf, const size_t len)
{
    struct utsname info;


    /* get system uname information */
    if(uname(&info) == -1)
    {
        abort();
    }

    /* write version informatin to string */
    (void)snprintf(buf, len, "%s", info.release);

    return 0;
}

#else

#error New Operating System for pthread_get_nproc()
#error New Operating System for pthread_get_name()
#error New Operating System for pthread_get_version()

#endif







#define SIZE 7 


static int orig_array[SIZE] = {6, 2, 1, 2, 3, 7, 8};
static int sort_array[SIZE];




int main(void)
{
    int ii, rtn;
    int num_cpus;
    int hour, min;
    float sec;
    struct timeval start, stop;
    //printf("%u, %u\n", orig_array, sort_array);	

    /*for(ii = 0; ii < SIZE; ii++)
    {
        orig_array[ii] = 1;
		sort_array[ii] = orig_array[ii];
    }*/

    /*if(gettimeofday(&start, NULL) != 0)
    {
        fprintf(stderr, "%s: %d: gettimeofday() ERROR: %s\n",
                __FILE__, __LINE__, strerror(errno));
        return EXIT_FAILURE;
    }

    qsort(sort_array, SIZE, sizeof(long), work_long);

    if(gettimeofday(&stop, NULL) != 0)
    {
        fprintf(stderr, "%s: %d: gettimeofday() ERROR: %s\n",
                __FILE__, __LINE__, strerror(errno));
        return EXIT_FAILURE;
    }

    sec = (stop.tv_sec - start.tv_sec) +
            ((stop.tv_usec - start.tv_usec) / 1.0e6);

    min = sec / 60;
    sec = sec - (min * 60);

    hour = min / 60;
    min = min - (hour * 60);

    fprintf(stdout, "qsort test time: %02d:%02d:%07.4f\n",
            hour, min, sec);

    for(ii = 1; ii < SIZE; ii++)
    {
        if(sort_array[ii-1] > sort_array[ii])
        {
            fprintf(stderr, "%s: %d: ERROR: array not sorted\n",
                    __FILE__, __LINE__);
            return EXIT_FAILURE;
        }
    }*/

    for(ii = 0; ii < SIZE; ii++)
    {
        sort_array[ii] = orig_array[ii];
    }

    if((rtn = pthread_get_nproc(&num_cpus)) != 0)
    {
        fprintf(stderr, "%s: %d: pthread_get_nproc() ERROR: %s\n",
                __FILE__, __LINE__, strerror(rtn));
        return EXIT_FAILURE;
    }

    if(num_cpus == 1)
    {
        num_cpus = 4;
    }

#if (defined(__sun) || defined(__sgi))
    pthread_setconcurrency(num_cpus);
#endif

    if(gettimeofday(&start, NULL) != 0)
    {
        fprintf(stderr, "%s: %d: gettimeofday() ERROR: %s\n",
                __FILE__, __LINE__, strerror(errno));
        return EXIT_FAILURE;
    }
	
	for(ii = 0; ii < SIZE; ii++)  {
		printf("%d ", sort_array[ii]);
	}
	printf("\n");

    pthread_qsort(sort_array, SIZE, (size_t)num_cpus);
    //my_qsort(sort_array, SIZE);
    if(gettimeofday(&stop, NULL) != 0)
    {
        fprintf(stderr, "%s: %d: gettimeofday() ERROR: %s\n",
                __FILE__, __LINE__, strerror(errno));
        return EXIT_FAILURE;
    }

    sec = (stop.tv_sec - start.tv_sec) +
            ((stop.tv_usec - start.tv_usec) / 1.0e6);

    min = sec / 60;
    sec = sec - (min * 60);

    hour = min / 60;
    min = min - (hour * 60);

    fprintf(stdout, "pthread_qsort_t test time: %02d:%02d:%07.4f\n",
            hour, min, sec);

    for(ii = 1; ii < SIZE; ii++)
    {
        if(sort_array[ii-1] > sort_array[ii])
        {
            fprintf(stderr, "%s: %d: ERROR: array not sorted\n",
                    __FILE__, __LINE__);
            return EXIT_FAILURE;
        }
    }

	for(ii = 0; ii < SIZE; ii++)  {
		printf("%d ", sort_array[ii]);
	}
	printf("\n");


    return 1;
}

