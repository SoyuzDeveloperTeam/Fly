/*------------------------------------------------------------------------
  CCPY.C
     ������������� ������� ������� � ���� �������
  ����   : ��ॢ�� �ணࠬ�� ����� SSP �� � �믮���� ���뭪�� �.�.
  �����  : 01.00 / 18.09.1997 /
------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "ssp.h"

/*     ..................................................................

	SUBROUTINE CCPY

	PURPOSE
	   ������ �⮫�� �a�p��� � ���e �e��opa

	USAGE
	   ccpy(A,B,R,N,M,MS)

	DESCRIPTION OF PARAMETERS
	   A - NAME OF INPUT MATRIX TO BE SORTED
	   N - NUMBER OF ROWS IN A
	   R - NAME OF ROWS OUTPUT VECTOR
	   N - NUMBER OF ROWS IN A AND R
	   M - NUMBER OF COLUMNS IN A AND R AND LENGTH OF B
	   MS  - ONE DIGIT NUMBER FOR STORAGE MODE OF MATRIX A
		  0 - GENERAL
		  1 - SYMMETRIC
		  2 - DIAGONAL


	SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED
	   LOC
     ..................................................................
 */
void ccpy(double a[], int jn, double r[], int n, int m, int ms)
{
int i,j;
for(i=0;i<n;i++) //横� �� ��� ��ப
    {
    loc(i,jn, &j, n, m, ms);
    r[i]=a[j];
    }
return;
}
