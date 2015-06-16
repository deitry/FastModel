//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FMForm.h"
#include "engine.h"
#include "func.h"
#include "fileWork.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
FMEngine* engine = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
   engine = new FMEngine;
   char* fn = engine->getData()->outFileName;
   clearFile(fn);
   printHatToFile(fn);
   printStateToFile(engine->getState(), engine->getData(), fn);
    
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Button1Click(TObject *Sender)
{
   long double &t1 = 1;
   TryStrToFloat(T1Edit->Text, t1);

   double time0 = engine->getTime();


   while ((engine->getTime() - time0) < t1-tau)
   {
      engine->nextStep();
      FMEngState* eState = engine->getState();
      FMEngData* data = engine->getData();

      TimeEdit->Text = engine->getTime();
      WDEdit->Text = nd(eState, data);

      MoshEdit->Text = ntk(eState, data);

      static int pCnt = 0;  // сколько раз выводили
      if (pCnt <= (eState->time / tout))
      {
         pCnt++;
         printStateToFile(eState, data, data->outFileName);
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete engine;   
}
//---------------------------------------------------------------------------

