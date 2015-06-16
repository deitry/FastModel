#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "data.h"
#include "func.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -

FMEngData::FMEngData()
{
   EtaI = 0;
   EtaK = 0;
   Tg   = 0;
   Gk   = 0;

   this->temp = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -

FMEngData::~FMEngData()
{
   if (EtaI != 0) delete EtaI;
   if (EtaK != 0) delete EtaK;
   if (Tg   != 0) delete Tg;
   if (Gk   != 0) delete Gk;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -

FMEngData* ReadDataFromFile(char* FileName)
{
   FMEngData* data = new FMEngData;

   // ������ �������� ������ �� �����
   std::ifstream inf;
   inf.open(FileName);

   // ������ ��������� ������
   data->WD0 = readValue(&inf);
   data->WD0 *= pi/30;   // �������� �� ���/�

   data->WT0 = readValue(&inf);
   data->WT0 *= pi/30;

   data->PK0 = readValue(&inf);
   data->PG0 = readValue(&inf);
   data->GC0 = readValue(&inf);
   data->komp20 = readValue(&inf);

   // ������ ����������
   data->minGC = readValue(&inf);
   data->maxGC = readValue(&inf);
   data->Nst = readValue(&inf);
   data->Kp = readValue(&inf);
   data->Ki = readValue(&inf);
   data->Kd = readValue(&inf);
   data->alphaGC = readValue(&inf);
   data->Mnagr = readValue(&inf);
   data->Tonv = readValue(&inf);                          
   data->Pklap = readValue(&inf);
   data->kGt = readValue(&inf);
   data->kMt = readValue(&inf);
   data->kGk = readValue(&inf);

   // ����� ������
   std::string buf;
   inf >> data->outFileName;
   std::getline(inf, buf, '\n');  // ������� �����������
   inf >> data->etaiFN;
   std::getline(inf, buf, '\n');  // ������� �����������
   inf >> data->etakFN;
   std::getline(inf, buf, '\n');  // ������� �����������
   inf >> data->TgFN;
   std::getline(inf, buf, '\n');  // ������� �����������
   inf >> data->GkFN;
   std::getline(inf, buf, '\n');  // ������� �����������


   inf.close();

   // ������ ������������� �� �����
   data->EtaI = ReadField2FromFile(data->etaiFN);
   data->EtaK = ReadField2FromFile(data->etakFN);
   data->Tg = ReadField2FromFile(data->TgFN);
   data->Gk = ReadField2FromFile(data->GkFN);

   // TODO : ������ ������ �� �����

   return data;
}

double readValue(std::ifstream* f)
{
   std::string buf = "";
   while (buf == "")
   {
      std::getline(*f, buf);
   }

   int i;

   if ((i = buf.find("!")) != buf.length())
   {
      buf = buf.substr(0,i-1);
   }
   double val = atof(buf.c_str());
   //std::getline(*f, buf, '\n');  // ������� �����������
   return val;
}


// - - - - - - - - - - - - - - - - - - - - - - - - - -

