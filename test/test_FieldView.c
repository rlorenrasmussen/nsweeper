#ifdef TEST

#include "unity.h"

// #include "FieldModel.h"
#include "FieldView.h"

// TODO: given some pane vector, output specified pane to a display buffer
// TODO: render the display buffer onto the screen
// TODO: report stored pane vector
// TODO: increment/decrement one axis of pane vector

#define SCREEN_W 100
#define SCREEN_H 60

static FieldPtr F;
static char** ScreenBuffer;

void setUp(void)
{
  F = NULL;
  ScreenBuffer = calloc(SCREEN_H,sizeof(char*));
  for (int i = 0; i < SCREEN_H; i++)
  {
    ScreenBuffer[i] = calloc(SCREEN_H,sizeof(char));
  }
}

void tearDown(void)
{
  Field_Destroy(F);
  for (int i = 0; i < SCREEN_H; i++)
  {
    free(ScreenBuffer[i]);
  }
  free(ScreenBuffer);
}

void test_FieldView_InitializesWithFieldPtr(void)
{
  bool result;
  F = Field_Create(3,3);
  result = FieldView_Init(F);
  TEST_ASSERT_TRUE(result);
}

void test_FieldView_ReportsPaneVectorSize(void)
{
  unsigned int size;
  bool result;
  FieldPtr F;
  for (int i = 1; i <= 6; i++)
  {
    F = Field_Create(i,4);
    result = FieldView_Init(F);
    TEST_ASSERT_TRUE(result);
    size = FieldView_GetPaneVectorSize();
    TEST_ASSERT_EQUAL(i,size);
  }
}

void ignore_FieldView_ReportsPaneVector(void)
{

}

#endif // TEST
