#ifndef FM_STATE_H
#define FM_STATE_H

#include "data.h"

/**
���������, ���������� ���������� ��� ���������

� ������ ������� ����� ����������� ���������� ������� ������

C���� �������� ���������� ��� ���������� ������������� �� ������ C

��� ����������, ���������� ����, ����� �������� ������, ����� �������� ��
����� ������ ����������
*/
class FMEngState
{
public:
   FMEngState();
   ~FMEngState();

   // ��������� �����, ������ ��� �� ���� ��� �� �����, � ���������, ������������
   // ������.
   double time;   // ������� �����
   double WD; // ������� �������� ���������
   double WT; // ������� �������� �������
   double PK; // �������� � �����������
   double PG; // �������� ��������� �����
   double GC; // ������� �������� ������
   double Gdiz;
   int surge;  // 0 - �� ��� ������ / 1 - ������
   int komp2;  // 0 - ���� ���������������, 1 - ��� ��
};

FMEngState* ReadStateFromFile(char* FileName);
FMEngState* ReadStateFromData(FMEngData* data);

#endif