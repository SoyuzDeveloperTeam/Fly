//-------------------------------------------------------------------------------
// MagicSolution.h 
// �. ��������� 28.03.2019
//-------------------------------------------------------------------------------
#ifndef MAGIC_SOLUTION_H
#define MAGIC_SOLUTION_H

//-------------------------------------------------------------------------------
class  ZCPrintManager;
class  ZMSC;
struct ZSMagicLnsSolution;
struct ZNU;
struct ZSLoopFact;
struct ZSFlightRule;

//-------------------------------------------------------------------------------
// ������ ���������� ���������
//
// ���������� ������������� �������� ������� ������ ������� ���������� L-�������
// ������� ������� �����. �������������� ��������� �������� ��� ������ �������� 
// ������� ������ �� 11-�� �� 33-��.
// ������� �� ���������� ������� ��������������� ����������� ���������
// ZSMagicLnsSolution* MS.
// ������ �������� � ������ ��������  ZMSC& KA, ��� ��������� ������� ZNU& NU.
// ���������� ������� ����������� ���������� ���������� �������� � ��������� 
// ������ ���������� ZSLoopFact* P1r, P2r, PNr, PRr.
// ������� ���������� ����� ���������� ������������� �������� ���������� 
// � ��������� ZSFlightRule* Ur.
//-------------------------------------------------------------------------------
FLYMAGICLNS_API int MagicSolution(
	ZSMagicLnsSolution* MS,			// ������ ������� ������
	ZCPrintManager    * PrintMng,	// ��������� ����������������
	FILE  *pf,					// ��������� �������� ��� ����������� �������
	ZLSF  &LSF,					// ���������� ����� ��� ��� ������� ������ ������� 
	ZMSC  &KA,					// ������ �������� ��
	ZNU   &NU,					// ��������� ������� ��������
	ZCExternalEquationsDefinition* EED,
	ZSLoopFact   *P1r=nullptr,	// ���-� ����. �� ����� 1-�� ��������
	ZSLoopFact   *P2r=nullptr,	// ���-� ����. �� ����� 2-�� ��������
	ZSLoopFact   *PNr=nullptr,	// ���-� ����. �� �������� ����� � ���-�� �����
	ZSLoopFact   *PRr=nullptr,	// ��������� ��������� �������� �� �������� ����� 
	ZSFlightRule *Ur =nullptr); // ����������� ��������� ��������� ����������

//-------------------------------------------------------------------------------
#endif // MAGIC_SOLUTION_H