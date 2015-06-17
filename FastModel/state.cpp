#include "stdafx.h"
#include "state.h"
#include <fstream>
#include "func.h"


// - - - - - - - - - - - - - - - - - - - - - - - - - -
FMEngState::FMEngState()
{
   this->time = 0;
   this->WD = 0;
   this->WT = 0;
   this->PK = 0;
   this->PG = 0;
   this->GC = 0;
   this->Gdiz = 0;
   this->surge =0;
   this->komp2 = 1;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - -

FMEngState::~FMEngState()
{

}

// - - - - - - - - - - - - - - - - - - - - - - - - - -

FMEngState* ReadStateFromFile(char* FileName)
{
   FMEngState* state = new FMEngState;

   // чтение исходных данных из файла
   std::ifstream inf;
   inf.open(FileName);
   
   inf >> state->WD;
   state->WD *= pi/30;   // пересчёт на рад/с
   inf >> state->WT;
   state->WT *= pi/30;
   inf >> state->PK;
   inf >> state->PG;
   inf >> state->GC;
   
   inf.close();

   return state;
}

/**
Создание структуры состояния на основе "данных"
*/
FMEngState* ReadStateFromData(FMEngData* data)
{
   FMEngState* state = new FMEngState;

   state->WD = data->WD0;
   state->WT = data->WT0;
   state->PK = data->PK0;
   state->PG = data->PG0;
   state->GC = data->GC0;
   state->komp2 = data->komp20;

	state->h = data->H0;

   return state; 
}
