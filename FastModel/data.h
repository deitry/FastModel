#pragma once
#include <fstream>
#include <string>
#include "field.h"

// #define FM_MAXCHAR 48
const int MaxChar = 48;

/**
��������������, ����������� ��� ������ ����
*/
class FMEngData
{
public:
   FMEngData();
   ~FMEngData();

   // �������� �����
   double WD0; // ������� �������� ���������
   double WT0; // ������� �������� �������
   double PK0; // �������� � �����������
   double PG0; // �������� ��������� �����
   double GC0; // �������� ������
   double komp20; // �������� ����� ������ �� - 0 - ���� ��, 1 - ��� ��

   char outFileName[MaxChar]; // ��� �����, � ������� �� �� ��������� ����� ��������
   // ��� ������ � ����������������
   char etaiFN[MaxChar];
   char etakFN[MaxChar];
   char TgFN[MaxChar];
   char GkFN[MaxChar];

   double minGC;
   double maxGC;
   double Nst;
   double Kp;
   double Ki;
   double Kd;
   double alphaGC;
   double Mnagr;
   double Tonv;
   double temp;
   double Pklap;
   double kGt, kMt, kGk;



   // ���� �������������
   FMField2* EtaI;   // X - alpha;     Y - ! nd
   FMField2* EtaK;   // X - ntk;       Y - pik
   FMField2* Tg;     // Y - ������� - PK [���];  X - ������ - alpha
   FMField2* Gk;     // Y - ������� - pik; X - ������ - ntk
};

FMEngData* ReadDataFromFile(char* FileName);

double readValue(std::ifstream* f);
