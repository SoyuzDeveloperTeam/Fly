/*------------------------------------------------------------------------
  SMPY.C
          
  ĸâŽā   : ĨāĨĸŽ¤ ¯āŽŖā ŦŦë ¯ ĒĨâ  SSP ­   ĸë¯ŽĢ­¨Ģ  áë­ĒŽĸ ..
  Ĩāá¨ī  : 01.00 / 18.09.1997 /
------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "ssp.h"

/*     ..................................................................

	SUBROUTINE SMPY

        PURPOSE
           MULTIPLY EACH ELEMENT OF A MATRIX BY A SCALAR TO FORM A
           RESULTANT MATRIX

        USAGE
           CALL SMPY(A,C,R,N,M,MS)

        DESCRIPTION OF PARAMETERS
           A - NAME OF INPUT MATRIX
           C - SCALAR
           R - NAME OF OUTPUT MATRIX
           N - NUMBER OF ROWS IN MATRIX A AND R
           M - NUMBER OF COLUMNS IN MATRIX A AND R
           MS  - ONE DIGIT NUMBER FOR STORAGE MODE OF MATRIX A (AND R)
                  0 - GENERAL
		  1 - SYMMETRIC
                  2 - DIAGONAL

        REMARKS
           NONE

        SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED
           LOC

        METHOD
           SCALAR IS MULTIPLIED BY EACH ELEMENT OF MATRIX

     ..................................................................
 */
void smpy(double a[], double c, double r[], int n, int m, int ms)
{
int i, it;

/*        COMPUTE VECTOR LENGTH, IT  */
loc( n-1, m-1, &it, n, m, ms );

/*        MULTIPLY BY SCALAR      */
for( i = 0; i <= it; i++ )
	r[i] = a[i]*c;
return;
}

