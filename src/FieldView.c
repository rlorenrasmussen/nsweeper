#include "FieldView.h"

typedef Screen_t* ScreenPtr;

static FieldPtr FIELD_;
static ScreenPtr SCREEN_;

void FieldView_Draw(unsigned int* paneVector)
{
  const char spaces[] = "                                                           ";
  (void) sprintf(SCREEN_->buff[0],"+-----+-----+-----+\n");
  (void) sprintf(SCREEN_->buff[1],"|  X  |  X  |  X  |\n");
  (void) sprintf(SCREEN_->buff[2],"+-----+-----+-----+\n");
  (void) sprintf(SCREEN_->buff[3],"|  X  |  26 |  X  |\n");
  (void) sprintf(SCREEN_->buff[4],"+-----+-----+-----+%s+\n",spaces);
  (void) sprintf(SCREEN_->buff[5],"|  X  |  X  |  X  |%sw\n",spaces);
  (void) sprintf(SCREEN_->buff[6],"+-----+-----+-----+%s-\n",spaces);
}

bool FieldView_Init(FieldPtr F, Screen_t* S)
{
  (void) Field_Dimension(F);
  FIELD_ = F;
  SCREEN_ = S;
  return true;
}

unsigned int FieldView_GetPaneVectorSize(void)
{
  return Field_Dimension(FIELD_);
}