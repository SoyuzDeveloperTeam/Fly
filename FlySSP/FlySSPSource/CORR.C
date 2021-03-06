//---------------------------------------------------------------------------
//  CORR.C
//    ������ ������� ��������, ����������� ����������, ���������� �
//    ������������� ����������
//  ����  : ���뭪�� �.�.
//  ����� : 01.00 / 25.09.2000 /
//---------------------------------------------------------------------------
#include <math.h>
#include "ssp.h"

int corr( /* �室�� ��ࠬ���� */
	 double  x[],  /* ��室��� ����� ������� [n*k] */
	 int     n,    /* �᫮ ������� (��ப)  */
	 int     k,    /* �᫮ �������� 䠪�஢ (�⮫�殢)*/
	  /* ��室�� ��ࠬ���� */
	 double *xbar, /* ����� �।��� [m]*/
	 double *std,  /* ����� ��� (ᬥ饭��� �業��) [m]*/
	 double *Kx,   /* ����ਠ樮���� ����� [m*m]
			  � ᨬ������ ᯮᮡ�� �࠭����
			  (m+1)*m/2 ������⮢ */
	 double *Rx)   /* ���५�樮���� ����� [m*m]
			  � ᨬ������ ᯮᮡ�� �࠭����
			  (m+1)*m/2 ������⮢ */
{
int    i,j,l,m1,l1,i1,m;
double fn;
if(!xbar ) return -1;
if(n < 1 ) return -2;
if(k < 1 ) return -3;
fn=1.0/(double)n;
for(j=0;j<k;j++)
	{
	for(xbar[j]=0,i=0;i<n;i++)
		{
		i1=i*k;
		xbar[j]+=(x[i1+j]*fn);
		}
	}
if(Kx)
	{
	for (m1=0, i=0;i<k;m1+=(k-i),i++)
		for (j=i;j<k;j++)
			{
			for (m=j-i,Kx[m1+m]=0,l=0;l<n;l++)
				{
				l1=l*k;
				Kx[m1+m] +=( (x[l1+i]-xbar[i])*(x[l1+j]-xbar[j]) );
				}
			Kx[m1+m]*=fn;
			if(m==0) std[i]=sqrt(Kx[m1]);
			}
	if(Rx)
		for (m1=0, i=0;i<k;m1+=(k-i),i++)
			for (j=i;j<k;j++)
				{
				m=j-i;
				if(std[j]==0 || std[i]==0) return -2;
					else
					if(m==0)Rx[m1+m]=1.0;
					  else Rx[m1+m]=Kx[m1+m]/std[j]/std[i];
				}
	}
/*
	//��ᬥ饭��� �業�� ���
fn=1.0/(double)(n-1);
for(i=0;i<k;i++)
  std[i]=sqrt(std[i]*fn*std[i]*n);
*/
return 0;
}
