#ifdef TEST

#include "unity.h"

#include <string.h>

#include "FieldModel.h"
#include "FieldView.h"

// DONE: given some pane vector, output specified pane to a display buffer
// TODO: render the display buffer onto the screen
// TODO: increment/decrement one axis of pane vector
// TODO: reject out-of-bounds increment/decrement arguments

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
  unsigned int paneVector[1] = {0};
  F = Field_Create(3,3);
  result = FieldView_Init(F,&ScreenBuffer,paneVector);
  TEST_ASSERT_TRUE(result);
}

void test_FieldView_ReportsPaneVectorSize(void)
{
  unsigned int size;
  bool result;
  unsigned int* paneVector;
  for (int i = 2; i <= 6; i++)
  {
    F = Field_Create(i,4);
    paneVector = calloc(i-2,sizeof(unsigned int));
    result = FieldView_Init(F,&ScreenBuffer,paneVector);
    TEST_ASSERT_TRUE(result);
    size = FieldView_GetPaneVectorSize();
    TEST_ASSERT_EQUAL(i-2,size);
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
  (void) FieldView_Init(F,&ScreenBuffer,paneVector);
  FieldView_Draw();
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview1","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void test_FieldView_DrawsCompletePane2ToBuffer(void)
{
  unsigned int paneVector[4] = {7,1,0,6};
  FILE* fptr;
  F = Field_Create(6,8);
  (void) FieldView_Init(F,&ScreenBuffer,paneVector);
  FieldView_Draw();
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview2","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void test_FieldView_DrawsCompletePane3ToBuffer(void)
{
  unsigned int paneVector[4] = {6,1,3,4};
  unsigned int coordinates[6] = {0};
  FILE* fptr;
  F = Field_Create(6,8);
  (void) FieldView_Init(F,&ScreenBuffer,paneVector);

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  coordinates[4] = 0;
  coordinates[5] = 0;
  Field_Reveal(F,coordinates);

  coordinates[5] += 1;
  Field_PlaceMine(F,coordinates);
  Field_Flag(F,coordinates);

  coordinates[5] += 1;
  Field_Flag(F,coordinates);

  coordinates[5] = 2;
  coordinates[3] += 1;
  coordinates[2] -= 1;
  coordinates[1] += 1;
  coordinates[0] -= 1;
  Field_PlaceMine(F,coordinates);

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  for (int j = 1; j < 3; j++)
  {
    coordinates[4] = j;
    for (int i = 0; i < 3; i++)
    {
      coordinates[5] = i;
      Field_Reveal(F,coordinates);
    }
  }

  coordinates[4] = 3;
  coordinates[5] = 3;
  Field_Reveal(F,coordinates);

  coordinates[4] = 4;
  coordinates[5] = 2;
  Field_Flag(F,coordinates);
  
  coordinates[0] = paneVector[0];
  for (int v = paneVector[1]-1; v <= paneVector[1]+1; v++)
  {
    coordinates[1] = v;
    for (int w = paneVector[2]-1; w <= paneVector[2]+1; w++)
    {
      coordinates[2] = w;
      for (int x = paneVector[3]-1; x <= paneVector[3]+1; x++)
      {
        coordinates[3] = x;
        for (int y = 4; y <= 6; y++)
        {
          coordinates[4] = y;
          for (int z = 5; z <= 7; z++)
          {
            coordinates[5] = z;
            if (paneVector[0] == coordinates[0] &&
                paneVector[1] == coordinates[1] &&
                paneVector[2] == coordinates[2] &&
                paneVector[3] == coordinates[3] &&
                5 == y &&
                6 == z)
            {
              continue;
            }
            Field_PlaceMine(F,coordinates);
          }
        }
      }
    }
  }

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  coordinates[4] = 5;
  coordinates[5] = 6;
  Field_Reveal(F,coordinates);

  FieldView_Draw();
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview3","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void test_FieldView_IncrementDecrementPaneVector(void)
{
  unsigned int paneVector[4] = {6,1,3,4};
  unsigned int coordinates[6] = {0};
  FILE* fptr;
  F = Field_Create(6,8);
  (void) FieldView_Init(F,&ScreenBuffer,paneVector);

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  coordinates[4] = 0;
  coordinates[5] = 0;
  Field_Reveal(F,coordinates);

  coordinates[5] += 1;
  Field_PlaceMine(F,coordinates);
  Field_Flag(F,coordinates);

  coordinates[5] += 1;
  Field_Flag(F,coordinates);

  coordinates[5] = 2;
  coordinates[3] += 1;
  coordinates[2] -= 1;
  coordinates[1] += 1;
  coordinates[0] -= 1;
  Field_PlaceMine(F,coordinates);

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  for (int j = 1; j < 3; j++)
  {
    coordinates[4] = j;
    for (int i = 0; i < 3; i++)
    {
      coordinates[5] = i;
      Field_Reveal(F,coordinates);
    }
  }

  coordinates[4] = 3;
  coordinates[5] = 3;
  Field_Reveal(F,coordinates);

  coordinates[4] = 4;
  coordinates[5] = 2;
  Field_Flag(F,coordinates);
  
  coordinates[0] = paneVector[0];
  for (int v = paneVector[1]-1; v <= paneVector[1]+1; v++)
  {
    coordinates[1] = v;
    for (int w = paneVector[2]-1; w <= paneVector[2]+1; w++)
    {
      coordinates[2] = w;
      for (int x = paneVector[3]-1; x <= paneVector[3]+1; x++)
      {
        coordinates[3] = x;
        for (int y = 4; y <= 6; y++)
        {
          coordinates[4] = y;
          for (int z = 5; z <= 7; z++)
          {
            coordinates[5] = z;
            if (paneVector[0] == coordinates[0] &&
                paneVector[1] == coordinates[1] &&
                paneVector[2] == coordinates[2] &&
                paneVector[3] == coordinates[3] &&
                5 == y &&
                6 == z)
            {
              continue;
            }
            Field_PlaceMine(F,coordinates);
          }
        }
      }
    }
  }

  coordinates[0] = 6;
  coordinates[1] = 2;
  coordinates[2] = 3;
  coordinates[3] = 4;
  for (int y = 0; y < 8; y++)
  {
    coordinates[4] = y;
    for (int z = 0; z < 8; z++)
    {
      coordinates[5] = z;
      Field_Reveal(F,coordinates);
    }
  }

  for (int i = 0; i < 4; i++)
  {
    coordinates[i] = paneVector[i];
  }
  coordinates[4] = 5;
  coordinates[5] = 6;
  Field_Reveal(F,coordinates);
  FieldView_Draw();
  FieldView_IncrementPaneVector(1); // increment axis 1 (0-indexed) of the pane vector
  FieldView_Draw();
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview4","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);

  coordinates[0] = 6;
  coordinates[1] = 2;
  coordinates[2] = 3;
  coordinates[3] = 3;
  for (int y = 0; y < 8; y++)
  {
    coordinates[4] = y;
    for (int z = 0; z < 8; z++)
    {
      coordinates[5] = z;
      if (4 > y)
      {
        if (4 > z)
        {
          Field_Reveal(F,coordinates);
        }
        else
        {
          Field_Flag(F,coordinates);
        }
      }
      else
      {
        if (4 > z)
        {
          Field_Flag(F,coordinates);
        }
        else
        {
          Field_Reveal(F,coordinates);
        }
      }
    }
  }
  FieldView_DecrementPaneVector(3); // decrement axis 3 (0-indexed) of the pane vector
  FieldView_Draw();
  fptr = fopen("/home/loren/Dev/c/nsweeper/test/assets/sampleview5","r");
  bufferMatchesFile(ScreenBuffer,fptr);
  fclose(fptr);
}

void ignore_FieldView_ReportsPaneVector(void)
{
}

#endif // TEST
