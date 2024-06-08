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

static void bufferMatchesFile(Screen_t S, FILE* FP)
{
  bool fileExhausted;
  char line[SCREEN_W+1] = {0};
  if (NULL == FP)
  {
    return;
  }
  fileExhausted = false;
  for (int i; i < SCREEN_H; i++)
  {
    if (!fileExhausted && fgets(line,SCREEN_W+1,FP))
    {
      TEST_ASSERT_EQUAL_STRING(line,S.buff[i]);
    }
    else
    {
      fileExhausted = true;
      // TODO: test for empty strings after EOF
      // TEST_ASSERT_EQUAL(0,S.buff[i][0]);
    }
  }
}

void setUp(void)
{
  F = NULL;
  ScreenBuffer.W = SCREEN_W;
  ScreenBuffer.H = SCREEN_H;
  ScreenBuffer.buff = calloc(SCREEN_H,sizeof(char*));
  for (int i = 0; i < SCREEN_H; i++)
  {
    ScreenBuffer.buff[i] = calloc(SCREEN_W,sizeof(char));
  }
}

void tearDown(void)
{
  Field_Destroy(F);
  for (int i = 0; i < SCREEN_H; i++)
  {
    free(ScreenBuffer.buff[i]);
  }
  free(ScreenBuffer.buff);
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

void test_FieldView_DrawsCompletePane1ToBuffer(void)
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
          Field_Reveal(F,coordinates);
          continue;
        }
        Field_PlaceMine(F,coordinates);
        Field_Reveal(F,coordinates);
      }
    }
  }
  (void) FieldView_Init(F,&ScreenBuffer);
  FieldView_Draw(paneVector);
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview1","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void test_FieldView_DrawsCompletePane2ToBuffer(void)
{
  unsigned int paneVector[4] = {7,1,0,6};
  FILE* fptr;
  F = Field_Create(6,8);
  (void) FieldView_Init(F,&ScreenBuffer);
  FieldView_Draw(paneVector);
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview2","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void ignore_FieldView_ReportsPaneVector(void)
{
}

#endif // TEST
