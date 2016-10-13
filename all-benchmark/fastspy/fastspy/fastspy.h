#ifndef _FASTSPYH_
#define _FASTSPYH_
/**/
/* Exported structure or constant and variables used inside fastspy.c        */
/* No Custom File                                                            */
/**/
#include "fstypes.h"


/* *** MACROs used inside fastspy.c *** */
/* *** Note: this is the long value of the address (host ordered)            */
#define MAKESINADDR( b1 , b2 , b3 , b4 )    ( ((b1 << 24) & 0xFF000000) | \
                                              ((b2 << 16) & 0x00FF0000) | \
                                              ((b3 <<  8) & 0x0000FF00) | \
                                              (b4 & 0x000000FF)           )





/* Global variables that have to be seen outside fastspy.c                   */
extern USHORT OutputToFile;
extern UCHAR  OutputFileName[128];

#endif

