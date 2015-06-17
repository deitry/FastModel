#ifndef FM_FUNCTIONS_H
#define FM_FUNCTIONS_H

#include "state.h"
#include "data.h"

/**
Константы
"Облачить" в пространство имён?
*/
const float tau = 0.01;    // шаг расчёта
const float tout = 0.01;    // шаг вывода

const float pi = 3.1415;
const float Rvozd = 287.;  // газовая постоянная; Дж / моль К
const float Rgaz = 286.;   // газовая постоянная отработавших газов
const int   i = 16;        // количество цилиндров
const float d_cyl= 0.26;  // диаметр поршня, м
const float h_cyl = 0.26;  // ход поршня, м
const float V = 1.07*pi * h_cyl*d_cyl*d_cyl/4;     // ? объём цилиндра; м^3
const float Hu = 42500000;  // низшая теплота сгорания; Дж/кг
const float Idv = 1000.;     // момент инерции
const float Mpothh = 3240.; // момент потерь холостого хода ?
const float WDhh = 350 * pi / 30;   // частота холостого хода
const float Iturb = 0.143;  // момент инерции турбокомпрессора
const float Kvzd = 1.4;    // показатель адиабаты для воздуха
const float Kgaz = 1.35;   // показатель адиабаты газов
const float kkv = Kvzd/(Kvzd-1);    // для удобства
const float kkg = Kgaz/(Kgaz-1);    // для удобства
const float T0 = 298.;     // температура воздуха
const float p0 = 101325;   // атмосферное давление, Па
const float pt0 = p0 * 1.02;// давление в выпускном коллекторе
const float Vvp = 0.44;    // объём впускного коллектора
const float Vvyp = 0.44;   // объём выпускного коллектора




// "статические" - не дифференциальные зависимости
double rho(FMEngState* s, FMEngData* d);     // плотность воздуха; f(PK, Tvozd)
double Gdiz(FMEngState* s, FMEngData* d);    // расход воздуха через дизель; f(rho, WD)
double Gtopl(FMEngState* s, FMEngData* d);   // расход топлива
double alpha(FMEngState* s, FMEngData* d);   // коэффициент избытка воздуха; f(Gd, Gtopl)
double Mi(FMEngState* s, FMEngData* d);      // индикаторный момент; f(Gtopl, eta_i, WD)
double Mpot(FMEngState* s, FMEngData* d);    // момент потерь
double pik(FMEngState* s, FMEngData* d);     // относительное давление
double pit(FMEngState* s, FMEngData* d);     // относительное давление
double Lkad(FMEngState* s, FMEngData* d);
double Mk(FMEngState* s, FMEngData* d);
double Qk(FMEngState* s, FMEngData* d);
double Ltad(FMEngState* s, FMEngData* d);
double Mt(FMEngState* s, FMEngData* d);    // момент на турбине?
double Tk(FMEngState* s, FMEngData* d);
double Gk(FMEngState* s, FMEngData* d);
double Gt(FMEngState* s, FMEngData* d);
double Mnagr(FMEngState* s, FMEngData* d);
double Tvozd(FMEngState* s, FMEngData* d);
double Tgaz(FMEngState* s, FMEngData* d);
double etav(FMEngState* s, FMEngData* d);  // коэффициент наполнения; f(WD, PK)
double etai(FMEngState* s, FMEngData* d);
double etamex(FMEngState* s, FMEngData* d);
double etakad(FMEngState* s, FMEngData* d);
double etat(FMEngState* s, FMEngData* d);
double gc(FMEngState* s, FMEngData* d);   // цикловая подача; f(h, WD) - вообще говоря, будет поставляться регулятором.
//double h(FMEngState* s, FMEngData* d);		// положение рейки
double z(FMEngState* s, FMEngData* d);		// управляющее воздействие
double Mosh(FMEngState* s, FMEngData* d);

double nd(FMEngState* s, FMEngData* d);
double ntk(FMEngState* s, FMEngData* d);



#endif