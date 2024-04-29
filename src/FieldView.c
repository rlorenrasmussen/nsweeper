#include "FieldView.h"

static FieldPtr FIELD_;

bool FieldView_Init(FieldPtr F)
{
  (void) Field_Dimension(F);
  FIELD_ = F;
  return true;
}

unsigned int FieldView_GetPaneVectorSize(void)
{
  return Field_Dimension(FIELD_);
}
