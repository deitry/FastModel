#ifndef FM_FUNCTIONS_H
#define FM_FUNCTIONS_H

#include "state.h"
#include "data.h"

/**
���������
"��������" � ������������ ���?
*/
const float tau = 0.01;    // ��� �������
const float tout = 0.01;    // ��� ������

const float pi = 3.1415;
const float Rvozd = 287.;  // ������� ����������; �� / ���� �
const float Rgaz = 286.;   // ������� ���������� ������������ �����
const int   i = 16;        // ���������� ���������
const float d_cyl= 0.26;  // ������� ������, �
const float h_cyl = 0.26;  // ��� ������, �
const float V = 1.07*pi * h_cyl*d_cyl*d_cyl/4;     // ? ����� ��������; �^3
const float Hu = 42500000;  // ������ ������� ��������; ��/��
const float Idv = 1000.;     // ������ �������
const float Mpothh = 3240.; // ������ ������ ��������� ���� ?
const float WDhh = 350 * pi / 30;   // ������� ��������� ����
const float Iturb = 0.143;  // ������ ������� ����������������
const float Kvzd = 1.4;    // ���������� �������� ��� �������
const float Kgaz = 1.35;   // ���������� �������� �����
const float kkv = Kvzd/(Kvzd-1);    // ��� ��������
const float kkg = Kgaz/(Kgaz-1);    // ��� ��������
const float T0 = 298.;     // ����������� �������
const float p0 = 101325;   // ����������� ��������, ��
const float pt0 = p0 * 1.02;// �������� � ��������� ����������
const float Vvp = 0.44;    // ����� ��������� ����������
const float Vvyp = 0.44;   // ����� ���������� ����������




// "�����������" - �� ���������������� �����������
double rho(FMEngState* s, FMEngData* d);     // ��������� �������; f(PK, Tvozd)
double Gdiz(FMEngState* s, FMEngData* d);    // ������ ������� ����� ������; f(rho, WD)
double Gtopl(FMEngState* s, FMEngData* d);   // ������ �������
double alpha(FMEngState* s, FMEngData* d);   // ����������� ������� �������; f(Gd, Gtopl)
double Mi(FMEngState* s, FMEngData* d);      // ������������ ������; f(Gtopl, eta_i, WD)
double Mpot(FMEngState* s, FMEngData* d);    // ������ ������
double pik(FMEngState* s, FMEngData* d);     // ������������� ��������
double pit(FMEngState* s, FMEngData* d);     // ������������� ��������
double Lkad(FMEngState* s, FMEngData* d);
double Mk(FMEngState* s, FMEngData* d);
double Qk(FMEngState* s, FMEngData* d);
double Ltad(FMEngState* s, FMEngData* d);
double Mt(FMEngState* s, FMEngData* d);    // ������ �� �������?
double Tk(FMEngState* s, FMEngData* d);
double Gk(FMEngState* s, FMEngData* d);
double Gt(FMEngState* s, FMEngData* d);
double Mnagr(FMEngState* s, FMEngData* d);
double Tvozd(FMEngState* s, FMEngData* d);
double Tgaz(FMEngState* s, FMEngData* d);
double etav(FMEngState* s, FMEngData* d);  // ����������� ����������; f(WD, PK)
double etai(FMEngState* s, FMEngData* d);
double etamex(FMEngState* s, FMEngData* d);
double etakad(FMEngState* s, FMEngData* d);
double etat(FMEngState* s, FMEngData* d);
double gc(FMEngState* s, FMEngData* d);   // �������� ������; f(h, WD) - ������ ������, ����� ������������ �����������.
//double h(FMEngState* s, FMEngData* d);		// ��������� �����
double z(FMEngState* s, FMEngData* d);		// ����������� �����������
double Mosh(FMEngState* s, FMEngData* d);

double nd(FMEngState* s, FMEngData* d);
double ntk(FMEngState* s, FMEngData* d);



#endif