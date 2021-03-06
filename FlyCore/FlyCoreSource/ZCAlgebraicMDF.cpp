//-----------------------------------------------------------------------------
// ZCAlgebraicMDF.cpp
// �. ��������� 01.04.2019
//
// �������������� ������������ (������) ��������� �������� �������.
// ������� ��������������� ���������� ��������.
// 
// �������������� ���������:
//		- ���������� ��������������� ������� �������� �����,
//		- �������� ��������� ������� �������� ������� ��������� �����,
//		- ��� ����������� ���������� ������� ����� ������� ���������������� 
//		  ��������� �����,
//		- � �������� ������ (��������) ����� ������������� �� ���� 
//		  � ��������� ����.
//-----------------------------------------------------------------------------
#include <stdafx.h>

#include <FlyChebyshov.h>
#include <FlyCoreSource\\ZCAlgebraicMDF.h>

//-----------------------------------------------------------------------------
// �������� ��������� �������������� ������� ��� ����������� ���������� 
// �� �������.
bool operator < (const ZCAlgebraicMDF& M1, const ZCAlgebraicMDF& M2)
{
	if (M1.begTime < M2.begTime) return true;
	return 0;
}

//-----------------------------------------------------------------------------
ZCAlgebraicMDF::ZCAlgebraicMDF() 
{
	// �������� ��� �������� ������
	Clr();
}

//-----------------------------------------------------------------------------
// ����������� ����������� 
ZCAlgebraicMDF::ZCAlgebraicMDF(const ZCAlgebraicMDF& M) 
{
	// �������� ��� �������� ������
	Clr();
	// ������ ��������� ��������� ����������� �������
	Cpy(M);
}

//-----------------------------------------------------------------------------
// ����������� ��������
ZCAlgebraicMDF::ZCAlgebraicMDF(ZCAlgebraicMDF&& M)
{
	// �������� ��� �������� ������
	Clr();
	// ������� ������
	Move(M);
}

//-----------------------------------------------------------------------------
// ������������ �����������
ZCAlgebraicMDF::ZCAlgebraicMDF(double* T, double* Y, const int N, const int D)
{
	// �������� ��� �������� ������
	Clr();
	// �������� ������������ �������� ������
	if (!T ) throw 1;
	if (!Y ) throw 2;
	if (N<5) throw 3;
	if (D<2) throw 4;
	// �������� ���������������� �������� �� �������� 
	if (Build(T, Y, N, D)) throw 5;
}

//-----------------------------------------------------------------------------
// �������� �����
ZCAlgebraicMDF& ZCAlgebraicMDF::operator = (const ZCAlgebraicMDF& M)
{
	// ������ ��������� ��������� ����������� �������
	Cpy(M);
	// ���������� ������ ����
	return (*this);
}

//-----------------------------------------------------------------------------
// ��������� ��������
ZCAlgebraicMDF& ZCAlgebraicMDF::operator = (ZCAlgebraicMDF&& M)
{
	// ������� ������
	Move(M);
	// ���������� ������ ����
	return (*this);
}

//-----------------------------------------------------------------------------
void ZCAlgebraicMDF::Del() 
{
	if (A) delete[] A;
	Clr();
}

//-----------------------------------------------------------------------------
void ZCAlgebraicMDF::Clr()
{
	A = nullptr;
	Degree  = 0;
	begTime = 0;
	endTime = 0;
	isGenerated = false;
}

//-----------------------------------------------------------------------------
// ����������� ����������� 
void ZCAlgebraicMDF::Cpy(const ZCAlgebraicMDF& M)
{
	if (!M.A) {
		// ���� ������ M �� �������� �������������, �� this ����� ��������
		// � ������ ��� ������������ ���� ��� ���� ���������� 
		if (A) delete[] A;
		// ��������� ���� ����� (�� ���� ��������� ������ this)
		Clr();
		return;
	}

	// ���������� ����������� �������� ���� �� ���������� � ������������
	// ������ M.
	if (A && Degree < M.Degree) {
		// ���� ������ ������������� ���������� �� ��� ������ �� ����������
		// ��� ���� ���� ����������� ������ ������������� �� ������ M,
		// �� A ������������� ��� ������������ ��������� ������������
		// ����������� ������
		delete[] A; A = nullptr;
	}
	// ���� ���������� �� �������� ������ ����������� ������
	if (!A)	A = new double[M.Degree];
	// �������� ������������ ������ M
	memcpy(A, M.A, M.Degree*sizeof(double));
	// �������� ��� ��������� �������� ������ M
	Degree = M.Degree;
	begTime = M.begTime;
	endTime = M.endTime;
	isGenerated = M.isGenerated;
}

//-----------------------------------------------------------------------------
void ZCAlgebraicMDF::Move(ZCAlgebraicMDF& M)
{
	// ���� this ����� � ��������, �� ������ ��� ������ �� ����� � ������
	// �� �������.
	Del();
	// ����������� ����� ������ � ������� ������������� ������������
	// ������ M.
	A = M.A;
	// �������� ��� ��������� �������� ������ M.
	Degree = M.Degree;
	begTime = M.begTime;
	endTime = M.endTime;
	isGenerated = M.isGenerated;
	// �������� ��� ���� ������ M.
	M.Clr();
}

//-----------------------------------------------------------------------------
ZCAlgebraicMDF::~ZCAlgebraicMDF()
{
	if (A) delete[] A;
}

//-----------------------------------------------------------------------------
double ZCAlgebraicMDF::Calc(double t) const
{
	double F = A[Degree];
	for (int i = Degree; i>0; i--) F = F*t + A[i - 1];
	return F;
}

bool ZCAlgebraicMDF::IsDomainFrom(double t) const
{
	if (!A || !Degree) return false;
	if (t >= begTime && t <= endTime) return true;
	return false;
}

//-----------------------------------------------------------------------------
int ZCAlgebraicMDF::Build(double* T, double* Y, int N, int D) 
{
	// �������� ������������ �������� ������
	if (!T || !Y || N<5) return-1;
	// ��� ������������� ������� ��������� ����� ������ ���-��
	if (A && Degree<D) { delete[] A; A = nullptr; }
	// ��� ������������� ������ ������ �������������
	if (!A) A = new double[D + 1];
	// ������� ��������
	Degree = D;

	// ������� ������� �����. �������� � �� ��������� � �����.���������� ��������
	AproxByChebyshevPolinom(T, Y, N, Degree, A);
	// ����� ������ � ����� ����� ��������� � ������� ��������
	// ������ �������������� ��������� �������� ���������� ����������
	begTime = T[0];
	endTime = T[N - 1];
	// ��������� ������� ��������� ������
	isGenerated = true;
	return 0;
}

//-----------------------------------------------------------------------------
// �������� � ������� ���������� ������ ��� ������� ��������
int ZCAlgebraicMDF::Create(int D, double TB, double TE) 
{
	if (A && D > Degree) { delete[] A; A = nullptr; }
	if (!A) A = new double[D + 1];
	begTime = TB;
	endTime = TE;
	isGenerated = false;
	return 0;
}

//-----------------------------------------------------------------------------
// �������� �� ��������� ��������� �������
int ZCAlgebraicMDF::LoadFromStream(ifstream& f, double TimeFrame) 
{
	if (f.eof()) return-1;
	// ����� ������ ���� ������
	f.read((char*)(&begTime), sizeof(double));
	// ����� ����� ���� ������
	endTime = begTime + TimeFrame;
	// �������� ��������
	if (f.eof()) return 1;
	f.read((char*)(&Degree), sizeof(int));
	// ������ �������������
	if (f.eof()) return 2;
	if (Create(Degree, begTime, begTime + TimeFrame)) return 3;
	f.read((char*)A, (Degree + 1)*sizeof(double));
	return 0;
}

//-----------------------------------------------------------------------------
// ���������� � �������� ��������� �������
int ZCAlgebraicMDF::StoryToStream(ofstream& f) 
{
	// ����� ������ ���� ������
	f.write((const char*)(&begTime), sizeof(double));
	// ������� ��������
	f.write((const char*)(&Degree), sizeof(int));
	// ������ �������������
	if (A) {
		f.write((const char*)(A), (Degree + 1)*sizeof(double));
	}
	return 0;
}

//-----------------------------------------------------------------------------