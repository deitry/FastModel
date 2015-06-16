#ifndef FM_STATE_H
#define FM_STATE_H

#include "data.h"

/**
Структура, содержащая переменные для двигателя

В первую очередь здесь описываются переменные дифуров дизеля

Cразу делается структурой для дальнейшей переносимости на чистый C

Все переменные, вынесенные сюда, будут выделены капсом, чтобы отличать от
более мелких переменных
*/
class FMEngState
{
public:
   FMEngState();
   ~FMEngState();

   // открываем члены, потому что по сути это не класс, а структура, группирующая
   // данные.
   double time;   // текущее время
   double WD; // частота вращения двигателя
   double WT; // частота вращения турбины
   double PK; // давление в компрессоре
   double PG; // давление выхлопных газов
   double GC; // текущая цикловая подача
   double Gdiz;
   int surge;  // 0 - всё как обычно / 1 - помпаж
   int komp2;  // 0 - один турбокомпрессор, 1 - два тк
};

FMEngState* ReadStateFromFile(char* FileName);
FMEngState* ReadStateFromData(FMEngData* data);

#endif