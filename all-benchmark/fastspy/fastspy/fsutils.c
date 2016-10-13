#include "fsincludes.h"

#include "fastspy.h"
#include "fsconst.h"

/**/
/* IsAddressNumber, check for validity of the IP address single number (delimitated by dot) */
/*                  asterisks allowed                                                       */
/**/
BOOL IsAddressNumber (char *pNum)
 {
  int nLen = strlen(pNum);
  int i = -1;

  while (++i < nLen)
    if ( (!isdigit((int)pNum[i])) && 
         (pNum[i] != '*')            ) 
      return (FALSE);

  return (TRUE);
 }

/**/
/* IsIPAddress, check if the string is a valid dotted IP Address */
/*              asterisks are not allowed                        */
/**/
BOOL isIPAddress(char *pTarget)
 {
  int   nLen = strlen (pTarget);
  int   i;
  int   nCount = 0;
  
  for (i=0; i<nLen; i++)
   {
    if ((!isdigit((int)pTarget[i])) &&
        (pTarget[i] != '.')            )
     return (FALSE);
    if (pTarget[i] == '.')
      nCount++;
   }

  if (nCount != 3)
    return (FALSE);

  return (TRUE);
 }


/**/
/* IsIPJollyAddress, check if the string is a valid dotted IP Address */
/*              with asterisks                                        */
/**/
BOOL isIPJollyAddress (char *pTarget)
 {
  int   nLen = strlen (pTarget);
  int   i;
  int   nDots = 0, nAsterisks = 0;
  
  for (i=0; i<nLen; i++)
   {
    if ((!isdigit((int)pTarget[i])) &&
        (pTarget[i] != '.')         &&
        (pTarget[i] != '*')            )
     return (FALSE);
    if (pTarget[i] == '.')
      nDots++;
    if (pTarget[i] == '*')
      nAsterisks++;
   }

  if (nDots != 3)
    return (FALSE);

  if (nAsterisks == 0)
    return (FALSE);

  return (TRUE);
 }


void Printf (char *cString)
 {
  FILE *fpOut = NULL;
  if (OutputToFile)
   {
    if ((fpOut = fopen (OutputFileName, "a")) == (FILE *)NULL)
     {
      printf (" ERROR: Cannot open %s to write\n",OutputFileName);
      exit (-1);
     }
   fprintf (fpOut, cString);
   fclose (fpOut);
  }

  printf (cString);
  
 }

void OutWrite (char *RecvBuff, LONG recvLen)
 {
  FILE *fpOut = NULL;
  if (OutputToFile)
   {
    if ((fpOut = fopen (OutputFileName, "a")) == (FILE *)NULL)
     {
      printf (" ERROR: Cannot open %s to write\n",OutputFileName);
      exit (1);
     }
    fwrite (RecvBuff, recvLen, 1 , fpOut);
    fclose (fpOut);
   }
  write (1, RecvBuff, recvLen);
 }

