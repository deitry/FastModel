#pragma once
#include <fstream>
#include <string>
#include "field.h"

// #define FM_MAXCHAR 48
const int MaxChar = 48;

/**
Характеристика, описывающая все нужные поля
*/
class FMEngData
{
public:
   FMEngData();
   ~FMEngData();

   // исходный режим
   double WD0; // частота вращения двигателя
   double WT0; // частота вращения турбины
   double PK0; // давление в компрессоре
   double PG0; // давление выхлопных газов
   double GC0; // цикловая подача
   double komp20; // исходный режим работы ТК - 0 - один тк, 1 - два тк

   char outFileName[MaxChar]; // имя файла, в который всё по умолчанию будет писаться
   // имя файлов с характеристиками
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



   // поля характеристик
   FMField2* EtaI;   // X - alpha;     Y - ! nd
   FMField2* EtaK;   // X - ntk;       Y - pik
   FMField2* Tg;     // Y - столбцы - PK [бар];  X - строки - alpha
   FMField2* Gk;     // Y - столбцы - pik; X - строки - ntk
};

FMEngData* ReadDataFromFile(char* FileName);

double readValue(std::ifstream* f);
