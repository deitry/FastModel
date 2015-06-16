#ifndef FM_FILE_H
#define FM_FILE_H

// - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "state.h"
#include "data.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - -

int printStateToFile(FMEngState* s, FMEngData* d, char* FileName);
void printToFile(char* FileName, ...);
int printHatToFile(char* FileName);

void clearFile(char* FileName);


// - - - - - - - - - - - - - - - - - - - - - - - - - -

#endif