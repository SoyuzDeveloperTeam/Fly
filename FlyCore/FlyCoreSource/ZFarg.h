//----------------------------------------------------------------------------
// ZFarg.h
// ���������� �������� ��������������� ����������
//
// �. ��������� 01.03.2019
//----------------------------------------------------------------------------
#ifndef _ZFARG_H
#define _ZFARG_H

enum MODEL_FARG {
	FARG1980=0,			// ��������� ���������� ��������� ��������������� 
						// ���������� �� ������������� IAU 1980 ����, 
						// ��� �� �������� ������� � ��-50...
	FARG2000=1 } ;		// ��������� ���������� ��������� ���������������
						// ���������� �� ������������� IAU 2000 ���� 

// �������� �� ��������� ������ �������� ���������� ������� (������� � 
// ������� � ������� � �������)
#define DEF_MODFARG FARG1980 

//----------------------------------------------------------------------------
// ���������� ��������������� ���������� � ������������ 
// � �������� �������
FLYCORE_API void ZFArg(double t, double *u, char FlagCalc,
					   TIMESCALE Scale=DEFTIME_SCALE,
					   MODEL_FARG ModFarg=DEF_MODFARG) ;

//----------------------------------------------------------------------------
// ���������� ��������������� ���������� � ������������ 
// � ����������� 1980 ����
//		u		 - ���������-������ �� 5-�� ���������� l,l',F,D,Omega � ���.
//		FlagCalc - ���� ������� 
//				   0 - 5 ����������(�� ���������),
//				   1 - 5 + GMST+PI, 
//				   2 - 5 + Planet
//		Scale	 - ������� 
FLYCORE_API void ZFArgIAU1980(double t, double *u, char FlagCalc,
				  TIMESCALE Scale=DEFTIME_SCALE) ;

//----------------------------------------------------------------------------
// ���������� ��������������� ���������� � ������������ 
// � IERS Convention 2003 ����
// ���������� ��������������� ���������� � ������������ � 
//		u		 - ���������-������ �� 5-�� ���������� l,l',F,D,Omega � ���.
//		FlagCalc - ���� ������� 
//				   0 - 5 ����������(�� ���������),
//				   1 - 5 + GMST+PI, 
//				   2 - 5 + Planet
//		Scale	 - ������� 
FLYCORE_API void ZFArgIAU2000(double t, double *u, char FlagCalc,
				  TIMESCALE Scale=DEFTIME_SCALE) ;

//----------------------------------------------------------------------------
// t - ����� TT � ��������� �� J2000.0
// u - ���������-������ �� 9-�� ���������� ������ � ��������
FLYCORE_API void ZArgPlanet(double t, double *u, TIMESCALE Scale = DEFTIME_SCALE);

//----------------------------------------------------------------------------
#endif // #ifndef _ZFARG_H
