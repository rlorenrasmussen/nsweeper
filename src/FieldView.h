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

void FieldView_Draw(unsigned int* paneVector);
bool FieldView_Init(FieldPtr F,Screen_t* S);
unsigned int FieldView_GetPaneVectorSize(void);

#endif // FIELDVIEW_H
