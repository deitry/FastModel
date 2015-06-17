#include "stdafx.h"
#include "fileWork.h"
#include <fstream>
#include "func.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
Осуществляет вывод в файл.
*/
int printStateToFile(FMEngState* s, FMEngData* d, char* FileName)
{
   std::ofstream out;
   out.open(FileName,std::ios_base::app);
   if (out.fail())
   {
      return 1;
   }

   out << s->time    << '\t'         // A
       << nd(s,d) << '\t'           // B
       << s->GC*1e6 << '\t'              // C
       << alpha(s,d) << '\t'        // D
       << ntk(s,d)  << '\t'         // E

       << s->PK/100000 << '\t'       // F
       << s->PG/100000 << '\t'       // G

       << Tgaz(s,d) << '\t'         // H
       << Tk(s,d) << '\t'           // I
       << Tvozd(s,d) << '\t'        // J

       << etai(s,d) << '\t'         // K
       << etakad(s,d) << '\t'       // L
       << etat(s,d)  << '\t'        // M
       << etamex(s,d)  << '\t'      // N

       << Gdiz(s,d) << '\t'         // O
       << Gk(s,d) << '\t'           // P
       << Gt(s,d) <<  '\t'          // Q

       << Mi(s,d) - Mpot(s,d) << '\t'  // R
       << Mi(s,d) << '\t'           // S
       << Mpot(s,d) << '\t'         // T
       << Mnagr(s,d) << '\t'        // U
       << Mosh(s,d) <<  '\t'        // V
       << Mk(s,d) << '\t'           // W
       << Mt(s,d)  << '\t'          // X

       << Lkad(s,d)  << '\t'        // Y
       << Ltad(s,d)  << '\t'        // Z
       << rho(s,d)  << '\t'        // AA
		 << s->h		<< '\t'
		 << z(s,d)		<< '\t'
		 //<< (Rvozd*Tvozd(s,d)/Vvp) * (2*Gk(s,d)-Gdiz(s,d))<<  '\t'
       //<< (Rgaz*Tgaz(s,d)/Vvyp) * (Gdiz(s,d)+Gtopl(s,d)-2*Gt(s,d))<<'\t'
       //<< d->temp << '\t'
       //<< s->surge
       << '\n';

   out.close();
   return 0;
}


/**
Осуществляет вывод в файл.
*/
int printHatToFile(char* FileName)
{
   std::ofstream out;
   out.open(FileName,std::ios_base::app);
   if (out.fail())
   {
      return 1;
   }

   out << "время"    << '\t'         // A
       << "nd"			<< '\t'           // B
       << "gc*10^6"	<< '\t'              // C
       << "alpha"		<< '\t'        // D
       << "ntk"		<< '\t'         // E

       << "pk"			<< '\t'       // F
       << "pg"			<< '\t'       // G

       << "tgaz"		<< '\t'         // H
       << "tk"			<< '\t'           // I
       << "tvozd"		<< '\t'        // J

       << "etai"		<< '\t'         // K
       << "etakad"	<< '\t'       // L
       << "etat"		<< '\t'        // M
       << "etamex"	<< '\t'      // N

       << "Gdiz"		<< '\t'         // O
       << "Gk"			<< '\t'           // P
       << "Gt"			<<  '\t'          // Q

       << "Meff"		<< '\t'         // R
       << "Mi"			<< '\t'           // S
       << "Mpot"		<< '\t'         // T
       << "Mnagr"		<< '\t'        // U
       << "Mosh"		<<  '\t'        // V
       << "Mk"			<< '\t'           // W
       << "Mt"			<< '\t'          // X

       << "Lkad"		<< '\t'        // Y
       << "Ltad"		<< '\t'        // Z
       << "rho"		<< '\t'        // AA
		 << "h, мм"		<< '\t'
		 << "z, уставка"		<< '\t'
		 << '\n';

   out.close();
   return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - -

#include <stdarg.h>
void printToFile(char* FileName, ...)
{
   std::ofstream out;
   out.open(FileName,std::ios_base::app);

   
   double* p;
   va_list ap;
   va_start(ap, FileName);
   while (p = va_arg(ap, double*))
   {
      out << *p << '\t';
   }
   va_end(ap);
   out << '\n';
   
   out.close();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -

void clearFile(char* FileName)
{
   // очищаем файл вывода
   std::ofstream f;
   f.open(FileName);
   f.close();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -


