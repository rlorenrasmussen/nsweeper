#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <stdio.h>
#include <string.h>
#include "FieldModel.h"

typedef struct
{
  unsigned int W;
  unsigned int H;
  char** buff;
} Screen_t;

void FieldView_DecrementPaneVector(unsigned int axisNum);
void FieldView_Draw();
unsigned int FieldView_GetPaneVectorSize(void);
void FieldView_IncrementPaneVector(unsigned int axisNum);
bool FieldView_Init(FieldPtr F,Screen_t* S,unsigned int* paneVector);
#endif // FIELDVIEW_H
