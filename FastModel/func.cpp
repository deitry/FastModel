#include "stdafx.h"
#include "func.h"
#include <math.h>

double rho(FMEngState* s, FMEngData* d)
{
   return s->PK / (Rvozd*Tvozd(s,d));
}

double Gdiz(FMEngState* s, FMEngData* d)
{
   double res = rho(s, d) * i * V * s->WD * etav(s, d) / (4*pi);
   s->Gdiz = res;
   return res;
}

double Gtopl(FMEngState* s, FMEngData* d)
{
   return i * s->GC * s->WD / (4*pi);
}

double alpha(FMEngState* s, FMEngData* d)
{
   return Gdiz(s,d) / (14.3*Gtopl(s,d));
}

double Mi(FMEngState* s, FMEngData* d)
{
   return Hu * Gtopl(s,d) * etai(s,d) / s->WD;
}

double Mpot(FMEngState* s, FMEngData* d)
{
   //return  (1 - etamex(s,d))*Mi(s,d);
   return (5011.2-3861.6)*(nd(s,d)-755)/(1000-755)+3861.6;
   //return (s->WD > WDhh) * (1 - etamex(s,d))*Mi(s,d) + (s->WD <= WDhh) * Mpothh;
   //return Mpothh;
}

double pik(FMEngState* s, FMEngData* d)
{
   return s->PK/p0;
}

double pit(FMEngState* s, FMEngData* d)
{
   return s->PG/pt0;
}

double Lkad(FMEngState* s, FMEngData* d)
{
   return kkv*Rvozd*T0 * (pow((double)pik(s, d),(double)(1/kkv))-1);
}

double Mk(FMEngState* s, FMEngData* d)
{
   return Gk(s,d)*Lkad(s,d) / (etakad(s,d)*(s->WT)); // 0.9 - "поправочный" к-т
}

double Qk(FMEngState* s, FMEngData* d)
{
   double Y = pik(s,d);
   double X = ntk(s,d) * sqrt(298/T0);
   double res = d->Gk->get(X,Y);

   double Razdel =   1.300529704739610e-002*pow(Y,3)
                     -1.546269382722710e-001*pow(Y,2)+
                     1.287019660178377e+000*Y
                     -9.165381390809292e-001;

   if (res < Razdel)
   {
      //res = rho(s, d) * i * V * s->WD * etav(s, d) / (2*4*pi);
      s->surge = 1;
      res = s->Gdiz/2;
      //res = Razdel;
   }
   else
   {
      s->surge = 0;
   }

   if (res < 0.2)
      res = 0.2;

   return d->kGk*res;
}

double Gk(FMEngState* s, FMEngData* d)
{
//   double p = pik(s,d);
   double res = Qk(s,d);//*rho(s,d) * sqrt(T0/298);
//   double Razdel =   1.300529704739610e-002*pow(p,3)
//                     -1.546269382722710e-001*pow(p,2)+
//                     1.287019660178377e+000*p
//                     -9.165381390809292e-001;
//   if (res < Razdel*rho(s,d) * sqrt(T0/298))
//      res = Gdiz(s,d)/2;

   return res;
}

double etakad(FMEngState* s, FMEngData* d)
{
   double Y = Qk(s,d);
   double X = pik(s,d);
   double ek = d->EtaK->get(X,Y);

   if (ek < 0.2) ek = 0.2;

   return ek;
}

double Tk(FMEngState* s, FMEngData* d)
{
   return T0*(1 + (pow((double)pik(s,d),(double)1/kkv)-1)/etakad(s,d));
}

double Ltad(FMEngState* s, FMEngData* d)
{
   return kkg*Rgaz*Tgaz(s,d) * (1 - 1/(pow((double)pit(s, d),(double)(1/kkg))));
}

double Mt(FMEngState* s, FMEngData* d)
{
   return d->kMt*(Gt(s,d)*Ltad(s,d)*etat(s,d)) / s->WT;
}

double Gt(FMEngState* s, FMEngData* d)
{
   double p = pit(s,d);
   double res;
   if (p > 4.0)
   {
      res = 36.5;
   } else {
      res =
      - 3.898876533462284   * pow(p,6)
      + 6.276236198173167e1 * pow(p,5)
      - 4.110872978101943e2 * pow(p,4)
      + 1.400467940135218e3 * pow(p,3)
      - 2.615647249638924e3 * pow(p,2)
      + 2.541988956093366e3 * p
      - 9.722363530138547e2;
   }
   
   if (res < 0.1) res = 0.1;

   return d->kGt*res*s->PG/(100000*sqrt(Tgaz(s,d))); // 100000 - pg в бар
}

double etat(FMEngState* s, FMEngData* d)
{
   double p = pit(s,d);
   double res =
      - 2.422160241342181e-3 * pow(p,4)
      + 2.770000003758912e-2 * pow(p,3)
      - 1.290450394849897e-1 * pow(p,2)
      + 2.703619500930666e-1 * p
      + 6.357810168103999e-1;

   if (res > 0.95) res = 0.95;
   if (res < 0.3)  res = 0.3;

   return res*1.0;
}

double Tgaz(FMEngState* s, FMEngData* d)
{
   double Y = s->PK/100000; //[бар]
   double X = alpha(s,d);
   return d->Tg->get(X,Y);
   //return 900;
}

double nd(FMEngState* s, FMEngData* d)
{                              
   return s->WD*30/pi;
}

double ntk(FMEngState* s, FMEngData* d)
{
   return s->WT*30/pi;
}

double etai(FMEngState* s, FMEngData* d)
{
   double Y = alpha(s, d);
   double X = nd(s,d);

   //return 0.38;
   return d->EtaI->get(X,Y);
}

double etamex(FMEngState* s, FMEngData* d)
{
   return nd(s,d)/4900 + 0.686; // было 0.84;
}

double Mnagr(FMEngState* s, FMEngData* d)
{
   return d->Mnagr;

   //float M0 = 0;
   //float T1 = 40;
   //return M0 + (s->time < T1)* (s->time * M0/T1)  + M0*(s->time >= T1);

   //return 40 * nd(s,d);
   //return 12*(7.453*nd(s,d)-4056);
   //1571 * 6 *(nd(s,d)/1000);
}

double Tvozd(FMEngState* s, FMEngData* d)
{
   return Tk(s,d) - (d->Tonv*(Tk(s,d)/200-1.5));
}

double etav(FMEngState* s, FMEngData* d)
{
   return 1.0;
}

double Mosh(FMEngState* s, FMEngData* d)
{
   return s->WD * (Mi(s, d) - Mpot(s, d));
}

// ================================================================
// Контроллер
// ================================================================
double gc(FMEngState* s, FMEngData* d)
{
   double Nst = d->Nst;
   //double Nst = 400 + 600*s->time / 30;
   double err = Nst - nd(s,d);
   double der = err / tau;

   double static ier = s->GC/d->Ki;
   // ограничение для интеграла
   if (ier + tau*err <= d->maxGC/d->Ki)
   {
      ier += tau * err;
   }

   double h = d->Kp*err + d->Ki*ier + d->Kd*der;

   // ограничения
   if (h > d->maxGC) h = d->maxGC;
   if (h < d->minGC) h = d->minGC;

   // ограничение по альфе
   double hm = s->PK * V * etav(s,d) / (Rvozd*Tvozd(s,d) * 14.3 * d->alphaGC);
   if (h > hm) h = hm;

   return h;
   //return d->GC0;
}