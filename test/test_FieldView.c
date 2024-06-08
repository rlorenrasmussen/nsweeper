#ifdef TEST

#include "unity.h"

#include <string.h>

#include "FieldModel.h"
#include "FieldView.h"

// TODO: given some pane vector, output specified pane to a display buffer
// TODO: render the display buffer onto the screen
// TODO: report stored pane vector
// TODO: increment/decrement one axis of pane vector

#define SCREEN_W (100)
#define SCREEN_H (60)

static FieldPtr F;
static Screen_t ScreenBuffer;

static bool bufferMatchesFile(Screen_t S, FILE* FP)
{
  if (NULL == FP)
  {
    return false;
  }
  char line[SCREEN_W+1] = {0};
  for (int i; i < SCREEN_H && fgets(line,SCREEN_W+1,FP); i++)
  {
    if (0 != strcmp(S.buffer[i],line))
    {
      return false;
    }
  }
  return true;
}

void setUp(void)
{
  F = NULL;
  ScreenBuffer.W = SCREEN_W;
  ScreenBuffer.H = SCREEN_H;
  ScreenBuffer.buffer = calloc(SCREEN_H,sizeof(char*));
  for (int i = 0; i < SCREEN_H; i++)
  {
    ScreenBuffer.buffer[i] = calloc(SCREEN_W,sizeof(char));
  }
}

void tearDown(void)
{
  Field_Destroy(F);
  for (int i = 0; i < SCREEN_H; i++)
  {
    free(ScreenBuffer.buffer[i]);
  }
  free(ScreenBuffer.buffer);
}

void test_FieldView_InitializesWithFieldPtr(void)
{
  bool result;
  F = Field_Create(3,3);
  result = FieldView_Init(F,&ScreenBuffer);
  TEST_ASSERT_TRUE(result);
}

void test_FieldView_ReportsPaneVectorSize(void)
{
  unsigned int size;
  bool result;
  for (int i = 1; i <= 6; i++)
  {
    F = Field_Create(i,4);
    result = FieldView_Init(F,&ScreenBuffer);
    TEST_ASSERT_TRUE(result);
    size = FieldView_GetPaneVectorSize();
    TEST_ASSERT_EQUAL(i,size);
  }
}

void test_DrawsGridToDisplayBuffer(void)
{
  unsigned int coordinates[3] = {0};
  unsigned int paneVector[1] = {1};
  FILE* fptr;
  bool match;

  F = Field_Create(3,3);
  for (int i = 0; i < Field_Scale(F); i++)
  {
    coordinates[0] = i;
    for (int j = 0; j < Field_Scale(F); j++)
    {
      coordinates[1] = j;
      for (int k = 0; k < Field_Scale(F); k++)
      {
        coordinates[2] = k;
        if (1 == i && 1 == j && 1 == k)
        {
          continue;
        }
        Field_PlaceMine(F,coordinates);
      }
    }
  }
  (void) FieldView_Init(F,&ScreenBuffer);
  FieldView_Draw(paneVector);
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview1","r");
  match = bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);

  TEST_ASSERT_TRUE(match);
}

void ignore_FieldView_ReportsPaneVector(void)
{
}

#endif // TEST
