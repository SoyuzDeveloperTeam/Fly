//--------------------------------------------------------------------------------
// ZMForceAtmDMA2004_Gost25645166.CPP
// ���������� ��������� ������������ ��������� �� 
// ���� � 25645.166-2004.
// �. ��������� 07.11.2018.
//
// ��������� �������� ���������� ������ ��������� ������� ��������� �����,
// ����������� �������� ������� ��������� � �� �������� ���������������-���������
// ��������, ��������� �� ��������� ��� � ����������� ������������, ��������� ������,
// ������� ���� � �����, � ����� ��������� ���������� � ������������ �������������.
// ������ ��������� ������� ��������� ����� �������� �� ������ ��������� ������
// �� �������� ����������� ���������� ������������� ��� ����� "������" � ����
// ���������� ��� ������� ���������������� ����� �� ������ � 1964 �� 2000 ���. 
// ��� ���������� ������ ������� ���� ������������� ���������� ��������� ���� 25645.115,
// �������� ��������� � ��������� ������ ��������� ���������.
// ������ ������������� �� ������������ ���������� ��� ��������� ��������
// ����������������� ������������� � ����������� ������������-�������������� �����������
// ���������� ������� ���.
//--------------------------------------------------------------------------------
#include <stdafx.h>
#pragma   hdrstop
#include <FlyMMath.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <FlyCoreSource\\ZSK.h>
#include <FlyCoreSource\\ZMForceAtmDMA2004_Gost25645166.h>
#include <FlyCoreSource\\ZMForceAtmDMA2004_Gost25645166Data.h>

//--------------------------------------------------------------------------------
// ������������� � ��������� �������� ��������� ���������� ����������
// F107		-	�������������� ������ ��������� ���������� - ��������� ������ 
//				�������������� ������ �� ����� ������ 10,7 �� (�� ������� 2800 ���), 
//				���������� � �������� ������ ��/�2/���10-22. 
// F81		-	C��������������� ������. ��������� ���������� 
//				�������������� �������� ������� ��������� ���������� F10,7 
//				�� ��� ������� ������ (81 ���). 
// F0		-	������������� ������� ��������� ����������.
//				���������������� ������ F81, ������� 25 � ���������� � �������� 
//				������ ��/�2/���10-22
// K�		-	�������������������� ����������� �������������� (k� - 3-�������) 
//				������ ������������ �������������, ���������� ������.
// k��		-	���������������� �������� 3-������� �������� ������������ 
//				�������������, ������������ ��� ������� ���������.
// Ap		-	������������ �������������� (ap - 3-�������) ������ ������������ 
//				������������� � �������� ������, 2 ��������� (2 �����).
// ro�		-	��������� ������ ���������, ��/�3.
// ro0		-	1,58868�-8 ��������� ������ ��������� �� ������ 120 ��, ��/�3.
// K0, K1, 
// K2, K3, 
// K4		-	���������, �����������:
//				K0 - ��������� ��������� ���������, ��������� � ����������� 
//					 F81 �� F0;
//				K1 - �������� ������ � ������������� ���������;
//				K2 - ����������� ������;
//				K3 - ��������� ���������, ��������� � ����������� F10,7 �� F81;
//				K4 - ����������� ��������� ��������� �� ������������ �������������.
// beta		-	�������� ����� ��������, ��� ������� ������������ ��������� 
//				���������, � �������� � ������������ ��������� ��������� 
//				� �� �������� �������������, ���.
// fi		-	����������� ���� ����� ������ ������������, 
//				��� ������� �������������� ���������, � ������ ������������ 
//				� ������������ ��������� ��������� � �� �������� �������������, ���.
// fi1		-	����������� ������, ������ ���� ������������ ��������� ��������� 
//				�� ��������� � ��������� ������������, ���.
// Ad		-	���������, ��������������� ������� ������������ ������� 
//				�� ��������� ���������.
// d		-	����� ����� �� ������ ����.
// ai, bi, ci, 
// di, ei, li, 
// ni, fi1	-	������������ ������, ������������ ��� ������� ��������� 
//				��������� ��� ��������� ��������� �������������� ������ 
//				��������� ���������� F0.
// ah, bh, ch, 
// dh, eh, 
// lh		-	�������� ������� ���������� ������������� ������ 
//				��� ������� ��������� ���������, ��.
//--------------------------------------------------------------------------------
//	JD         - ��������� ����, ��������������� �������� �������, UTC
//	ISA        - ������� ��������� ����������
//	SUNg       - ���������� ������ � ����������� ����������� ��, [��]
//	SUNte	   - ���������� ������ � ��� ������� �����, [��]
//	XYZg       - ���������� �� � ����������� ����������� ��, [��]
//	ro         - ������� ��������� ��������� � ��/�3
//--------------------------------------------------------------------------------
int DMA_GOST_25645_166_2004(double JD, ISA_DMA ISA, double* SUNg, double* SUNte, double* XYZg, double& ro)
{
	int    i, N, rc = 0 ; 
	double ro0  = 1.58868e-8 ;		// ��������� ������ ��������� �� ������ 120 �� � ��/�3
	double Re   = 6378.136 ;		// ������ �������� ��
	double alfa = 0.0033528037 ;	// �������� ��������������� ������ �����
	double pi   = acos(-1.0) ;

	double adSUN[3] ; ZASCtoAscensionDecination(SUNte, adSUN, false) ; 
	// ������ ����������� ������, �������
	double alfSun = adSUN[0] ;
	// C�������� ������, �������
	double dltSun = adSUN[1] ; 
	// ������������ ������� ������
	double LgSUN  = ValiA(dargum(SUNg[0], SUNg[1]), 0);
	// ���������� �����-������, ��
	double RS  = adSUN[2] ;
	// ���������� �����-��, ��
	double Rka = sqrt(XYZg[0]*XYZg[0]+XYZg[1]*XYZg[1]+XYZg[2]*XYZg[2]) ;
	// ������ ��, �� 
	double h   = Rka-Re*(1.0-alfa*XYZg[2]*XYZg[2]/Rka/Rka) ;

	// ���������� ��� ���� 1500 �� ��� ������������ ����� ��������� ���
	if (h>1500.0) {	ro = 0.0 ; return 0 ; }

	//----------------------------------------------------------------------------
	// ���� ����������� ������ h ����� 120 ��, �� ���������������-��������� �������� 
	// ��������� �� �����������. ��������� ���������   ������������ �� �������
	// ��� ����������� ����������� ��������� (���� 1981 ����)
	if (h<=120.0) {
		if (h<0) h = 0.0 ;
		// ����� ��������� ����
		N = SIZEOFA(LowAtmDMA2004) ;
		for (i=0; i<N; i++) { if (h<LowAtmDMA2004[i].h) break ; }
		// ��������� � �������� ������ ��������� ����
		double hn= i==0? 0 : LowAtmDMA2004[i-1].h ;
		double hk= LowAtmDMA2004[i].h ;
		// ������������ ������������ ��������� ���������
		double a = LowAtmDMA2004[i].a ;
		double k1= LowAtmDMA2004[i].k1 ;
		double k2= LowAtmDMA2004[i].k2 ; 
		// ���������� ��������� ����������� ���������
		ro = a*exp(k1*(h-hn)+k2*(h-hn)*(h-hn)) ;
		return 0 ;
	}

	//----------------------------------------------------------------------------
	// ������������� ������� ��������� ���������� �� ��������������� ������. 
	// ���������� ��������: 75, 100, 125, 150, 175, 200, 250
	double F0   = 125 ;
	// ������-���������� �� 81 ����� �������� �������  F107
	double F81  = 125 ;
	// ������ ��������� ����������, ������ ��������� ������ 
	// �������������� ������ �� �����, ������ 10.7 ��
	double F107 = 125 ;
	// ��������������������, ����������� �������������� 
	// ������ ������������ ����������
	double Kp   = 2 ;
	// ���������������� �������� 3-� ������� �������� 
	// ������������ �������������
	double kpp  = 2 ;

	//----------------------------------------------------------------------------
	// ����������� �������� �������� F107 � F81 ��� �������, 
	// ���������� �� �������� �� -1.7 �����
	F107 = ISA.F107 ;
	F81  = ISA.F81 ;
	Kp   = ISA.Kp ;
	kpp  = ISA.kpp ;

	//----------------------------------------------------------------------------
	// ������ �������������� ��� F0
	// �� ������� ��������� �������� F ���������� ��������, ��������� � �����������
	int iF0 = 0 ;			
	N = SIZEOFA(F0fix) ;
	for (i=0; i<N-1; i++) {	if ((F81-F0fix[i])*(F81-F0fix[i+1])<=0) break ;	}
	if (i==N-1) iF0 = F81<F0fix[0] ? 0:(N-1) ;
	else iF0 = fabs(F81-F0fix[i])<fabs(F81-F0fix[i+1]) ? i:(i+1) ;
	F0 = F0fix[iF0] ;
	
	//----------------------------------------------------------------------------
	// ���������� ������������ ��� 
	//----------------------------------------------------------------------------
	// 1) ����������� ����� ������ ������������� �������������
	//		a[7]					1-� ������ �������������
	//		b[5]					2-� ������ �������������
	//		c[5], n0, n[2], fi1		3-� ������ �������������
	//		d[4]					4-� ������ �������������
	//		e[9], et[4]				5-� ������ �������������
	//		l[5]					7-� ������ �������������
	// 2) ����������� ����� ������ ������������� �������������
	//	  ���������������, ��������������: 
	//		K0sh	������� ��������� ��������� ������ ��������� 
	//				� 11-������ ����� ��������� ����������, 
	//		K1sh	��������� ��������� �������, 
	//		K2sh	������� ������������ �������, 
	//		K3sh	�������������� ������,
	//		K4sh	������������ �������������, 
	// 3) ����������� ���������� ������������ ���
	//		K0, K1, K2, K3, K4
	// 4) ����������� ��������� ���������

	//----------------------------------------------------------------------------
	// K0 
	double l[5] ;					// 7-� ������ �������������
	if (h<lhhi[iF0]) {	// ������ � �������������� ��� ������� ��������� ����
		l[0] = lilow[0][iF0] ; l[1] = lilow[1][iF0] ; l[2] = lilow[2][iF0] ;
		l[3] = lilow[3][iF0] ; l[4] = lilow[4][iF0] ;
	} else {	// ������ � �������������� ��� �������� ��������� ����
		l[0] = lihi[0][iF0] ; l[1] = lihi[1][iF0] ; l[2] = lihi[2][iF0] ;
		l[3] = lihi[3][iF0] ; l[4] = lihi[4][iF0] ;
	}
	// ������������ ��������
	double K0sh = l[0]+(l[1]+(l[2]+(l[3]+l[4]*h)*h)*h)*h ;
	double K0   = 1.0+K0sh*(F81-F0)/F0 ;

	//----------------------------------------------------------------------------
	// ��������������� ������������ ��� ������� K1
	double c[5], n0, n[2], fi1 ;	// 3-� ������ �������������
	if (h<chhi[iF0]) {	// ������ � �������������� ��� ������� ��������� ����
		c[0] = cilow[0][iF0] ; c[1] = cilow[1][iF0] ; c[2] = cilow[2][iF0] ;
		c[3] = cilow[3][iF0] ; c[4] = cilow[4][iF0] ;
		n0   = n0low[iF0] ;
		n[0] = nlow[0][iF0] ; n[1] = nlow[1][iF0] ;
		fi1  = fi1low[iF0] ;  
	} else {	// ������ � �������������� ��� �������� ��������� ����
		c[0] = cihi[0][iF0] ; c[1] = cihi[1][iF0] ; c[2] = cihi[2][iF0] ;
		c[3] = cihi[3][iF0] ; c[4] = cihi[4][iF0] ;
		n0   = n0hi[iF0] ;
		n[0] = nhi[0][iF0] ; n[1] = nhi[1][iF0] ;
		fi1  = fi1hi[iF0] ;
	}

	//----------------------------------------------------------------------------
	// ������ ���� "��" (������ � ��������� ��� K1)
	// fi, ����������� ���� ����� ������ ������������, 
	// ��� ������� �������������� ���������, � ������ ������������ 
	// � ������������ ��������� ��������� � �� �������� �������������, ���.
	//----------------------------------------------------------------------------
	// beta - �������� ����� ��������, ��� ������� ������������ ��������� 
	// ���������, � �������� � ������������ ��������� ��������� 
	// � �� �������� �������������, ���.
	double beta ; 

	// � ����� �������� ��� ���������� ��������� ��������
	// beta = alfSun-(Sz0+wz*tUT)+fi1. 
	// ���:
	//		double Sz0 ; - ������� ����� � �����. �������, ���.
	//		double tUT ; - ��������� ����� � ���.
	//		double wz = 7.292115e-5 ; - ��. ��. �������� �����, ���/�
	// !!!!
	// �� ������ ��������� (Sz0+wz*tUT) ���� �� ��� ����,
	// ��� �������� �¨����� ����� �� ������ ������� tUT ��������� � UTC
	//(tUT - ����� �� �������� ����������� �� ������ ����� � ��������).
	// �����, ����������� ������ alfSun �� ������� �������� ���� 
	// �� �������� (Sz0+wz*tUT) ���� ������������ ������� ������!
	//
	// LgSUN = alfSun-(Sz0+wz*tUT).
	//
	// �� ������. ������� ������ ����� ��������� ���� ��� ���������� 
	// � ���, � ��� �������� - SUNg.
	// ����� ������� ��������� beta = alfSun-(Sz0+wz*tUT)+fi1 ��  ;
	// �����������, � ������ ����� ��������:
	beta = LgSUN+fi1 ;

	// ������� ���� "��"
	double cfi = 1.0/Rka*(
		         XYZg[2]*sin(dltSun)+
		         cos(dltSun)*(XYZg[0]*cos(beta)+XYZg[1]*sin(beta))) ;
	// ������� ���� "��/2"
	double cfi2 = sqrt((1.0+cfi)/2.0) ;

	//----------------------------------------------------------------------------
	// K1
	// ������������ ��������
	double K1sh = c[0]+(c[1]+(c[2]+(c[3]+c[4]*h)*h)*h)*h ; 
	double K1   = K1sh*pow(cfi2, n0+n[0]*h+n[1]*h*h) ;

	//----------------------------------------------------------------------------
	// K2
	double d[4] ;					// 4-� ������ �������������
	if (h<dhhi[iF0]) {	// ������ � �������������� ��� ������� ��������� ����
		d[0] = dilow[0][iF0] ; d[1] = dilow[1][iF0] ; d[2] = dilow[2][iF0] ; 
		d[3] = dilow[3][iF0] ; d[4] = dilow[4][iF0] ;
	} else {	// ������ � �������������� ��� �������� ��������� ����
		d[0] = dihi[0][iF0] ; d[1] = dihi[1][iF0] ; d[2] = dihi[2][iF0] ;
		d[3] = dihi[3][iF0] ; d[4] = dihi[4][iF0] ;
	}
	// ������������ ���������� ����� d, ��������� �� ������ ����
	double d1913 = JD-2419768.0 ;
	double my    = (int)((4.0*d1913-1.0)/1461.0) ;
	// ��� ���� � �������� ���������� �� ����� 
	// double dy = d1913-(int)(1461.0*my/4.0)-1.0+0.125 ; 
	// 1) ���� ������ ��������� ��� �� 12 ����� - �� ���� ������� � 
	//    ���������� �������� 0,5 �����
	// 2) ���� ��� ���� ��� ����� ����� ����� ����� ������� UT1
	//    �� ���� �������� 0.125 ��������� �� �����  
	double dy = d1913-(int)(1461.0*my/4.0)-1.0+0.5 ; 
	// ������������ ��������
	double Ad = Ai[0]+(Ai[1]+(Ai[2]+(Ai[3]+(Ai[4]+
		       (Ai[5]+(Ai[6]+(Ai[7]+Ai[8]*dy)*dy)*dy)*dy)*dy)*dy)*dy)*dy ;
	// ������������ ��������
	double K2sh = d[0]+(d[1]+(d[2]+(d[3]+d[4]*h)*h)*h)*h ;
	double K2   = K2sh*Ad ; 


	//----------------------------------------------------------------------------
	// K3
	double b[5] ;					// 2-� ������ �������������
	if (h<bhhi[iF0]) {	// ������ � �������������� ��� ������� ��������� ����
		b[0] = bilow[0][iF0] ; b[1] = bilow[1][iF0] ; b[2] = bilow[2][iF0] ;
		b[3] = bilow[3][iF0] ; b[4] = bilow[4][iF0] ;
	} else {	// ������ � �������������� ��� �������� ��������� ����
		b[0] = bihi[0][iF0] ; b[1] = bihi[1][iF0] ; b[2] = bihi[2][iF0] ;
		b[3] = bihi[3][iF0] ; b[4] = bihi[4][iF0] ;
	}
	// ������������ ��������
	double K3sh = b[0]+(b[1]+(b[2]+(b[3]+b[4]*h)*h)*h)*h ;
	double K3   = K3sh*(F107-F81)/(F81+fabs(F107-F81)) ;

	//----------------------------------------------------------------------------
	// K4
	double e[9], et[4] ;			// 5-� ������ �������������
	if (h<ehhi[iF0]) { // ������ � �������������� ��� ������� ��������� ����
		e[0] = eilow[0][iF0] ; e[1] = eilow[1][iF0] ; e[2] = eilow[2][iF0] ;
		e[3] = eilow[3][iF0] ; e[4] = eilow[4][iF0] ; e[5] = eilow[5][iF0] ;
		e[6] = eilow[6][iF0] ; e[7] = eilow[7][iF0] ; e[8] = eilow[8][iF0] ;
		et[0] = etilow[0][iF0] ; et[1] = etilow[1][iF0] ;
		et[2] = etilow[2][iF0] ; et[3] = etilow[3][iF0] ;
	} else { // ������ � �������������� ��� �������� ��������� ����
		e[0] = eihi[0][iF0] ; e[1] = eihi[1][iF0] ; e[2] = eihi[2][iF0] ;
		e[3] = eihi[3][iF0] ; e[4] = eihi[4][iF0] ; e[5] = eihi[5][iF0] ;
		e[6] = eihi[6][iF0] ; e[7] = eihi[7][iF0] ; e[8] = eihi[8][iF0] ;
		et[0] = etihi[0][iF0] ; et[1] = etihi[1][iF0] ;
		et[2] = etihi[2][iF0] ;	et[3] = etihi[3][iF0] ;
	}
	double K4 ;
	double K4sh = e[0]+(e[1]+(e[2]+(e[3]+e[4]*h)*h)*h)*h ;
	if (ISA.flag3H) {
		// ���� ������������ 3-������� �������
		K4 = K4sh*(et[0]+(et[1]+(et[2]+et[3]*kpp)*kpp)*kpp) ;
		// �������� ������������ kpp
		// ������ ����������� � ������������� �� 0,25 �����
	} else {
		// ���� ������������ �������������� �������
		K4 = K4sh*(e[5]+(e[6]+(e[7]+e[8]*Kp)*Kp)*Kp) ;
		// �������� ������������ Kp
		// ������ ����������� � ������������� �� 0,6 �����
	}

	//----------------------------------------------------------------------------
	// ��������������� ����������� ��� ��������� ������ ���������
	double a[7] ;					// 1-� ������ �������������
	if (h<ahhi[iF0]) {	// ������ � �������������� ��� ������� ��������� ����
		a[0] = ailow[0][iF0] ; a[1] = ailow[1][iF0] ; a[2] = ailow[2][iF0] ;
		a[3] = ailow[3][iF0] ; a[4] = ailow[4][iF0] ; a[5] = ailow[5][iF0] ;
		a[6] = ailow[6][iF0] ;
	} else {	// ������ � �������������� ��� �������� ��������� ����
		a[0] = aihi[0][iF0] ; a[1] = aihi[1][iF0] ;	a[2] = aihi[2][iF0] ;
		a[3] = aihi[3][iF0] ; a[4] = aihi[4][iF0] ; a[5] = aihi[5][iF0] ;
		a[6] = aihi[6][iF0] ;
	}
	// ��������� ������ ���������
	double roNight = ro0*exp(a[0]+(a[1]+(a[2]+(a[3]+(a[4]+(a[5]+a[6]*h)*h)*h)*h)*h)*h) ;

	//----------------------------------------------------------------------------
	// ��������� ��������� �� ������� ������ � �������� �����
	// (������� ���������)
	ro = roNight*K0*(1.0+K1+K2+K3+K4) ;
	return 0 ;
}

//--------------------------------------------------------------------------------
