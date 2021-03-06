/*------------------------------------------------------------------------
  SE13.C
    ����������� �������, �������� �������� ��������
    �  �������������  ������, �  ������� ����������
    ������ �������, ������������ �� ���� ���������-
    ������� ������ ������� ���������� ���������
  ����   : ��ॢ�� �ணࠬ�� ����� SSP �� � �믮���� ���뭪�� �.�.
  �����  : 01.00 / 18.09.1997 /
------------------------------------------------------------------------*/
#include "ssp.h"

/*     ..................................................................

	����ணࠬ�� (SUBROUTINE) se13

	�����祭�� (PURPOSE)
		 ����ணࠬ��  ������  ������⢮ Z1, Z2, ..., Zn
	   ���祭�� �㭪樨  Y(X), �������� ������⢮� Y1,Y2,...,Yn
	   �� ���祭�� � N ࠢ��������� �窠� Xi c 蠣�� Xi-Xi-1
	   (i=2,...,n).
		 �� ����� �६ ��᫥����⥫�� �窠� (Xj-2,Yj-2),
	   (Xj-1,Yj-1), (Xj,Yj)  ��� j = 3,...,n ��ந��� ��᫥����-
	   ⥫쭮���  �����童��� ��ࢮ� �⥯��� ����
				 Wj(X)= Aj*X +Bj
	   ����� � ��� �窠� �������襥 �⪫������ �� Y � ��᫥
	   ���.
		 ��� i=2,...,n-1, � ���� � ������ �窥 Xi �� �᪫�祭���
	   ������� �祪 X1 � Xn, � ����⢥ ᣫ�������� ���祭�� �㭪樨
	   Zi ������ ���᫥���� � �窥 Xi ���祭�� �����童�� Wi+1(X),
	   � ����⢥ Z1 - ���᫥���� � �窥 X1 ���祭�� �����童�� W3(X),
	   � � ����⢥ Zn - ���祭�� �����童�� Wn(X), ���᫥���� �� X=Xn.
		 (TO COMPUTE A VECTOR OF SMOOTHED FUNCTION VALUES
	   GIVEN A VECTOR OF FUNCTION VALUES WHOSE ENTRIES CORRESPOND
	   TO EQUIDISTANTLY SPACED ARGUMENT VALUES.)

	���饭�� � ����ணࠬ�� (USAGE)
	   IER=se13(Y,Z,NDIM);

	���ᠭ�� ��ࠬ��஢ (DESCRIPTION OF PARAMETERS):
	   Y     -  ���ᨢ ����� NDIM �������� ���祭�� �㭪樨
		    (GIVEN VECTOR OF FUNCTION VALUES (DIMENSION NDIM),
	   Z     -  ���ᨢ ����� NDIM ����塞�� ᣫ������� ���祭��
		    �㭪樨
		    (RESULTING VECTOR OF SMOOTHED FUNCTION VALUES
		    (DIMENSION NDIM),
	   NDIM  -  ������⢮ �������� ���祭�� �㭪樨 � ��㬥��
		    (DIMENSION OF VECTORS Y AND Z)
	   �㭪�� �����頥� �������� �訡�� (RESULTING ERROR PARAMETER)
	IER, �ਭ����騩 ���� �� ᫥����� ���祭��:
		    IER =  0, �᫨ �訡�� ��� (NO ERROR);
		    IER = -1, �᫨ NDIM ����� 3
			     (NDIM IS LESS THAN 3).

	�ਬ�砭�� (REMARKS)
	   (1)   �᫨ IER = -1, � ���᫥��� �� �஢�������.
		 (IF IER=-1 THERE HAS BEEN NO COMPUTATION.)
	   (2)   ���ᨢ Z ����� ᮢ������ � Y. �᫨ Y �� ᮢ������
		 � Z, � �� �� �������� � ����� ���᫥���.
		 (Z CAN HAVE THE SAME STORAGE ALLOCATION AS Y.  IF Y
		 IS DISTINCT FROM Z, THEN IT IS NOT DESTROYED.)

	SUBROUTINES AND SUBPROGRAMS REQUIRED
           NONE

	METHOD
	   IF X IS THE (SUPPRESSED) VECTOR OF ARGUMENT VALUES, THEN
           EXCEPT AT THE ENDPOINTS X(1) AND X(NDIM), EACH SMOOTHED
	   VALUE Z(I) IS OBTAINED BY EVALUATING AT X(I) THE LEAST-
           SQUARES POLYNOMIAL OF DEGREE 1 RELEVANT TO THE 3 SUCCESSIVE
	   POINTS (X(I+K),Y(I+K)) K = -1,0,1.  (SEE HILDEBRAND, F.B.,
	   INTRODUCTION TO NUMERICAL ANALYSIS, MC GRAW-HILL, NEW YORK/
	   TORONTO/LONDON, 1956, PP. 295-302.)

     ..................................................................
 */
int se13(double y[], double z[], int ndim)
{
int   i, ier;
double  a, b, c;
double const c5=5.0,     /* 5.0 */
	     ci6=1.0/6.0,/* 0.1666667 */
	     ci3=1.0/3.0;/* 0.3333333 */
/*        TEST OF DIMENSION */
ier = -1;
if( (ndim - 3) < 0 )
  return ier; /*        ERROR EXIT IN CASE NDIM IS LESS THAN 3 */

/*        PREPARE LOOP */
b = ci6*(c5*y[0] + y[1] + y[1] - y[2]);
c = ci6*(c5*y[ndim-1] + y[ndim - 2] + y[ndim - 2] - y[ndim - 3]);
/*        START LOOP */
for( i = 2; i < ndim; i++ ){
	a = b;
	b = ci3 *(y[i - 2] + y[i - 1] + y[i]);
	z[i - 2] = a;
	}
/*        END OF LOOP
	UPDATE LAST TWO COMPONENTS */
z[ndim - 2] = b;
z[ndim - 1] = c;
ier = 0;
return ier;
}

