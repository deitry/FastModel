#pragma once
/*
����� ����� ������ ������, ������� ����� ��������� ���������
FM = Fast Model
*/

#include "field.h"
#include "data.h"
#include "state.h"

           
// ================================================================


// ================================================================

class FMEngine
{
protected:
   // ����������, ��������������� ��������� ���������
   // ���� ������ � ���� �����, � ��, ��� ��������������, �������� � ����
   // ������� �������. ���� ��� ����� ������� ��������, � �������� ����� ��������������
   // �� ����� ���, ����� ����� ������� �������� �������������
   //
   // ��������, ����� ������������ �������� �������� ����� ���������. � �������� � ���.
   // ������ ��� ����������� ����� ������������ �������� ������ ������� �� ����� ������
   // ��� �������, ����� ����� ����� ����� ������� ������� � ����� ����� ����� ������ ���������
   FMEngState* state; // ������� "���������" �������
   FMEngData*  data;

   // ����������� ������� ��� ���������� ��������� ��������
   // ����� �������� ����������, ����������� � �������
   // UPD: ����� �������� �������������� � ����� ����� �����-�����,
   // �������� �������������� ������ ����� ��������� � ����������� �� �������
   // � ���������������� ����������
   // IN : nTime, nState - �������� �� ������ - �������������! - ����
   double prav_WD(FMEngState* s, FMEngData* d);
   double prav_WT(FMEngState* s, FMEngData* d);
   double prav_PK(FMEngState* s, FMEngData* d);
   double prav_PG(FMEngState* s, FMEngData* d);

public:
   FMEngine();
   ~FMEngine();
   void nextStep();  // ���������, "�����������" ������ �� ��������� ��� �������

   double getTime() {return this->state->time;}
   FMEngState* getState() {return this->state;}
   FMEngData* getData() {return this->data;}
};