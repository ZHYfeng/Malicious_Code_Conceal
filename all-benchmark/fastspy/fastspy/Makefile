# MAKE FILE FOR UNIX PLATFORMS

CC      = gcc
CFLAGS	= -L. -Wall -O2 -D_REENTRANT  
LIBS	= -lpthread 
SRCS	= fastspy.c fsutils.c unix/fskal.c
HDRS    = fastspy.h fskal.h fsutils.h unix/fsincludes.h unix/fstypes.h unix/fsconst.h
#LDFLAGS=-static
INCLS   = -I. -Iunix
EXES	= fs 
DEBUG   = -g -D_DEBUG_

default: $(EXES)


fs	: $(SRCS:.c=.o) 
	$(CC) $(INCLS) $(DEBUG) $(CFLAGS) $(LIBS) -o $@ $^ 

%.o	: %.c $(HDRS) 
	$(CC) $(INCLS) $(DEBUG) $(CFLAGS) -c $< -o $@

fs_static: $(SRCS:.c=.o) 
	$(CC) $(INCLS) $(DEBUG) $(CFLAGS) $(LIBS) -static -o $@ $? 

all: fs fs_static

dist: all clean
	strip fs
	strip fs_static

clean:
	rm -f *.pdb *.obj *.o core unix/*.o unix/core 
	
clean-dist:
	rm -f *.o core unix/*.o unix/core 
	rm -f fs fs_static	

