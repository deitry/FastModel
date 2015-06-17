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
	return (0.15*nd(s,d)+(3.3e-4)*pow((nd(s,d)-WDhh*30/pi),2))/s->WD * 1e3;	// к¬т -> ¬т
}

double pik(FMEngState* s, FMEngData* d)
{
   return s->PK/p0;
}

double pit(FMEngState* s, FMEngData* d)
{
   return 0.167 + 8.33 * s->PG * 1e-6;
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
	return 0;
}

double Gk(FMEngState* s, FMEngData* d)
{
	double pk = s->PK / 1e6;	// перевели в ћѕа
	double pk2 = pk*pk;
	double pk3 = pk2*pk;
	double wt = s->WT;
	double wt3 = pow(wt,3);

	double res = 0;

	if (wt < 2120)
	{
		return 89.41543545302785
			-0.00879000795415012 / (pk3)
			-1439.5522528519639 * pk
			+6319.510686490676 * pk2
			+7.256013472109795e10 / (wt3)
			-2.2713005593233164e12 * pk / (wt3)
			+2.3680096063059855e13 * pk2 / (wt3)
			-8.222532932385562e13 * pk3 / (wt3)
			-0.010748657959520189 * wt
			+0.3039986210758981 * pk * wt
			-1.7045915753724719 * pk2 * wt;
	}
	else
	{
		if (pk < 0.225)
		{
			return 4.8;
		}
		else
		{
			return -20965.910599827283
				+ 335797.4016817637 * pk
				- 2.012916969150105e6 * pk2
            + 5.353987509635247e6 * pk3 
				- 5.331862095349829e6 * pk*pk3;
		}
	}
}

double etakad(FMEngState* s, FMEngData* d)
{
	double pk = s->PK / 1e6;	// перевели в ћѕа
	double pk2 = pk*pk;
	double wt = s->WT;
	double wt2 = wt * wt;

	double res = 0.1
		+ 17.216973270861565
		- 1.1357200897379447 / pk
		- 60.913655082141084 * pk
		+ 53.554344859560175 * pk2
		+ 541.059704073703 / wt
		- 5660.438820687596 * pk / wt
		- 0.011259967484969111 * wt
		+ 0.0006398555128490516 * wt / pk
		+ 0.04993338509721579 * pk * wt
		- 0.04614333410821385 * pk2 * wt
		+ 4.610460258803448e-7 * wt2
		- 3.2798366729319386e-6 * pk * wt2;

   if (res > 0.93) res = 0.93;
   if (res < 0.2)  res = 0.2;

	return res;
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
	double pg = s->PG/1e6;
	double res;

	if ((s->WD < 40) || (pg < 0.11))
	{
		res = s->Gdiz;	// * число компрессоров
	}
	else
	{
		double priv;
		if (pg >= 0.22)
		{
			priv = 52.7453;
		}
		else
		{
			priv = -276.68168535931426
				+ 460.48782725979066 * sqrt(p)
				- 161.0220617848313 * p;
		}

		res = d->kGt * priv * s->PG / (1e5*sqrt(Tgaz(s,d))); // 100000 - pg в бар
	}   

   //if (res < 0.1) res = 0.1;

   return res;
}

double etat(FMEngState* s, FMEngData* d)
{
	double pm = pit(s,d);	// перевели в ћѕа
	double pm2 = pm*pm;
	double wt = s->WT / sqrt(Tgaz(s,d));
	double wt2 = wt * wt;

	double res = (0.1 + 4.155906828953094
		- 1.1471000595372076 / pm2 
		- 3.275625728016122 * pm 
		+ 0.7224314752426421 * pm2
		+ 0.14740419068948443 / wt2
		- 0.5055936439649789 / pm2 / wt
		- 0.024649748109726248 * wt
		+ 0.048473650295958855 * pm * wt
		- 0.012783397148782114 * pm2 * wt 
		- 0.00045881324028008443 * wt2
		+ 0.00021010975960633003 * pm * wt2
		- 0.00003287323684287447 * pm2 * wt2
		);

   if (res > 0.95) res = 0.95;
   if (res < 0.2)  res = 0.2;

   return res*1.0;
}

double Tgaz(FMEngState* s, FMEngData* d)
{
   double al = alpha(s,d);
	double res = 0;

	if (al < 3.5)
	{
		double pk = s->PK/1e6; //[ћѕа]
		double pk2 = pk*pk;
		double al2 = al*al;
		double wd = s->WD;
		double wd2 = wd*wd;
   
		return 925.9079181370311
			+ 2479.184058524307 * pk
			- 499.15810505669424 * pk*pk
			- 454.03596081380766 * al
			- 584.4317144799517 * pk*al
			+ 89.68494283221727 * al2
			+ 6.54694055966827 * wd
			- 16.076120414199185 * pk*wd
			- 1.703693479167804 * al*wd
			+ 4.078909403395532 * pk*wd*al
			+ 0.00347346602156468 * wd2;
	}
	else
	{
		return 520 - 12 * (al - 3.5);
	}
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
	double al = alpha(s,d);
	double al2 = al*al;
	double wd = s->WD;
	double wd2 = wd*wd;
   
	double res = 0.2931285209439111
		- 0.21362190500615105 / (al2)
		+ 0.008772760911881798 * al
		- 0.0004328716359858314 * al2
		- 2.8518712856825306 / (wd2)
		+ 2.4499480604180577 / (al2 * wd)
		+ 0.006570393693998842 * wd
		- 0.0007699873158573996 * al*wd
		+ 0.000028362480175340455 * al2*wd
		- 0.000050193215779816783 * wd2
		+ 6.837408210849127*0.000001 * al*wd2
		- 2.5104707278778594*0.0000001 * al2*wd2;

	if (res > 0.93) res = 0.93;
   if (res < 0.05)  res = 0.05;

	return res;
}

double etamex(FMEngState* s, FMEngData* d)
{
   return 0;
}

double Mnagr(FMEngState* s, FMEngData* d)
{
	double nd2 = nd(s,d);
	nd2 *= nd2;	// чтобы лишний раз не вызывать

	double res = 0.024 * nd2;

   return res;
}

double Tvozd(FMEngState* s, FMEngData* d)
{
   return 0.23 * Tk(s,d) + 233;
}

double etav(FMEngState* s, FMEngData* d)
{
	double pm = s->PK / 1e6;	// перевели в ћѕа
	double pm2 = pm*pm;
	double wd = s->WD;
	double wd2 = wd * wd;

	double res = (0.8321
		- 0.07857 / pm 
		+ 5.4676 * pm 
		- 12.8134 * pm2
		+ 3.8296 / wd
		- 36.8673 * pm / wd
		+ 0.004146 * wd
		+ 0.6078e-3 * wd / pm
		- 0.05083 * pm * wd
		+ 0.1112 * pm2 * wd
		- 0.4739e-4 * wd2
		+ 0.6785e-4 * pm * wd2
		);

	return res;
}

double Mosh(FMEngState* s, FMEngData* d)
{
   return s->WD * (Mi(s, d) - Mpot(s, d));
}

// ================================================================
//  онтроллер
// ================================================================
double z(FMEngState* s, FMEngData* d)
{
	double zt;
	// пока без пида
	double Nst = d->Nst;
   double err = Nst - nd(s,d);
   double der = err / tau;

   double static ier = s->h/d->Ki;
   // ограничение дл€ интеграла
   if (ier + tau*err <= d->maxGC/d->Ki)
   {
      ier += tau * err;
   }

   zt = d->Kp*err + d->Ki*ier + d->Kd*der;
	
   // ограничени€
	// в св€зи с переходом к рейке нужно будет изменить ограничени€
   //if (h > d->maxGC) h = d->maxGC;
   //if (h < d->minGC) h = d->minGC;

   // ограничение по альфе
   //double hm = s->PK * V * etav(s,d) / (Rvozd*Tvozd(s,d) * 14.3 * d->alphaGC);
   //if (h > hm) h = hm;
	
	// дл€ теста - посто€нное значение
	
	return zt;
}

double gc(FMEngState* s, FMEngData* d)
{
	double ht = s->h;	// чтоб не опрашивать несколько раз
	
	// характеристика рейки
	double res = -0.3 + 0.1 * ht + 0.3e-3 * nd(s,d) - 0.035e-3 * nd(s,d) * ht;

   return res/1000; // перевод в кг/цикл
}