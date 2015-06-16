#include "stdafx.h"
#include <fstream>
#include "engine.h"
#include "func.h"
#include "fileWork.h"

char* inFileName  = "data\\in.txt";

// ================================================================

FMEngine::FMEngine()
{
   this->data = ReadDataFromFile(inFileName);
   this->state = ReadStateFromData(this->data);
}

FMEngine::~FMEngine()
{
   if (this->state) delete this->state;
   if (this->data)  delete this->data;
}


// ================================================================
// Основа метода Рунге-Кутты
// ================================================================
/**
Переход на следующий шаг расчёта
*/
void FMEngine::nextStep()
{
   FMEngState nState = *this->state;

   double kWD[4], kWT[4], kPK[4], kPG[4]; // ?? промежуточные значения для метода Рунге-Кутты
   // текущее состояние для расчёта

   // коэффициенты для Рунге-Кутты 4го порядка. Потом оформлю по-другому
   // Поскольку не обобщение на произвольный метод не предвидится, оставляем так
   // Иначе А - двумерный массив
   float A[3] = {0.5, 0.5, 1.};
   float C[3] = {0.5, 0.5, 1.};
   float B[4] = {1., 2., 2., 1.};

   // интегрирование по Рунге-Кутте
   // инициализация
   for (int i = 0; i < 4; i++)
   {
      // расчёт текущего состояния для шага
      if (i > 0)
      {
         nState.time = this->state->time + tau*C[i-1];
         nState.WD = this->state->WD + tau*A[i-1] * kWD[i-1];
         nState.WT = this->state->WT + tau*A[i-1] * kWT[i-1];
         nState.PK = this->state->PK + tau*A[i-1] * kPK[i-1];
         nState.PG = this->state->PG + tau*A[i-1] * kPG[i-1];
      }
      // вспомогательные значения
      kWD[i] = prav_WD(&nState, this->data);
      kWT[i] = prav_WT(&nState, this->data);
      kPK[i] = prav_PK(&nState, this->data);
      kPG[i] = prav_PG(&nState, this->data);
   }

   // окончательный расчёт новых значений
   this->state->time += tau;
   this->state->WD += (tau/6) * (B[0]*kWD[0] + B[1]*kWD[1] + B[2]*kWD[2] + B[3]*kWD[3]);
   this->state->WT += (tau/6) * (B[0]*kWT[0] + B[1]*kWT[1] + B[2]*kWT[2] + B[3]*kWT[3]);
   //if (this->state->WT < 18000*pi/30) this->state->WT = 18000*pi/30;
   this->state->PK += (tau/6) * (B[0]*kPK[0] + B[1]*kPK[1] + B[2]*kPK[2] + B[3]*kPK[3]);

   this->data->temp = (tau/6) * (B[0]*kPK[0] + B[1]*kPK[1] + B[2]*kPK[2] + B[3]*kPK[3]);
   this->state->PG += (tau/6) * (B[0]*kPG[0] + B[1]*kPG[1] + B[2]*kPG[2] + B[3]*kPG[3]);
   this->state->GC = gc(this->state,this->data);  // пересчёт регулирующего воздействия - цикловой подачи
   if ( 0 && (this->data->Pklap) && (this->state->surge))
   {
      this->state->PK -= this->data->Pklap;
      this->state->PG += this->data->Pklap;
   }
}

// ================================================================
// Правые части дифуров
// ================================================================

/**
dWD/dt = (Mi - Mpot - Mnagr) / Id
*/
double FMEngine::prav_WD(FMEngState* s, FMEngData* d)
{
   return (Mi(s,d) - Mpot(s,d) - Mnagr(s,d)) / Idv;
}

/**
dWT/dt = (Mt - Mkomp) / It
*/
double FMEngine::prav_WT(FMEngState* s, FMEngData* d)
{
   return (Mt(s,d) - Mk(s,d)) / Iturb;
}

/**
dPK/dt = Rvozd*Tvozd *(Gk - Gd) / Vvp
*/
double FMEngine::prav_PK(FMEngState* s, FMEngData* d)
{
   // от Серёги
   // dpk/dt = (Rvozd*Tvozd(Tk)/Vvpusk)*(Gk(state.WT,state.PK)-Gdiz+Grecirk*StepRecirk);
   return (Rvozd*Tvozd(s,d)/Vvp) *
      ((1+s->komp2)*Gk(s,d)-Gdiz(s,d));    // +Grecirk*StepRecirk - обговорим
      // Grecirk - максимальный расход
      // StepRecirc - степень рециркуляции, рассчитывается регулятором
}

/**
dPG/dt = Rg * Tg * (Gd + Gtopl - Gt) / Vvip
*/
double FMEngine::prav_PG(FMEngState* s, FMEngData* d)
{
   // от Серёги
   // dPG/dt = (Rg*Tg())/Vvyp)*(Gdiz+Gtopl-Gt()-Grecirk*StepRecirk);
   return (Rgaz*Tgaz(s,d)/Vvyp) *
      (Gdiz(s,d)+Gtopl(s,d)-(1+s->komp2)*Gt(s,d));   // -Grecirk*StepRecirk
}


// ================================================================





