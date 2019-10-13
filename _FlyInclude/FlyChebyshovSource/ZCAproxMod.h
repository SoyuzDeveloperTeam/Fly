//-------------------------------------------------------------------------------
// ZCAproxMod.h : 
// ��������� ������ ������������ ��������� �������� �������� �������
// �� ����� ��������� ZCAproxMod - �������
//
// �. ��������� 15.03.2019
//-------------------------------------------------------------------------------
#pragma once
#ifndef ZC_APROX_MOD_H
#define ZC_APROX_MOD_H

enum APROX_MOD_TYPE {APRMOD_CHEBYSHEV = 0, APRMOD_FOURIER = 1};

class FLYCHEBYSHOV_API ZCAproxMod
{
public:
	ZCAproxMod();
	~ZCAproxMod();

	// �������� ������ ������
	void   Clear();
	// ���������� �������� ������, t- ����� �� ������� ����������� 
	// �������� ������ (��������)
	double Calc(double t);
	// �������� �������� �� ��������� ���������� �������
	//		Y   - ������ �������� ���������� ������� 
	//		t   - ������ �������� ��������� ���������� ������� 
	//		N   - ����������� ����� ��������� ������� 
	//		M   - ������� ���������������� ��������
	//		Mod - ������ (�� ��������� - �� ��������)
	int    Build(double* Y, double* t, int N, int M, 
				 APROX_MOD_TYPE Mod=APRMOD_CHEBYSHEV);

	// ���������� �������� ������� ��� ������ �������������� ��������� ()
	double operator() (double t);

protected:
	// ��� ������������
	APROX_MOD_TYPE	AprType;
	// ������� ����������� ������
	double			ArgArea[2];
	// ������������ ��������
	double*			A;
	// ������ �������� 
	int				Degree;
};

//-------------------------------------------------------------------------------
#endif // ZC_APROX_MOD_H
