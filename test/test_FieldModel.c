#ifdef TEST

#include "unity.h"

#include "FieldModel.h"

// DONE: cache numNeighboringMines, increment on PlaceMine, decrement on RemoveMine
// TODO: initializeBoard(coordinates) -- this will place mines randomly but guarantee the given coordinates will be mine-free
// TODO: bloom(coordinates) -- check if uncovered and minedNeighbors==0 -> then reveal all neighbors (like flood, but stops at the first layer of neighbors)
// TODO: save Field to file
// TODO: retrieve Field from file
// TODO: forbid revealing flagged cell
// TODO: change scale max based on dimension (targeting a max memory size)

void setUp(void)
{
}

void tearDown(void)
{
}

void test_FieldModel_CreateAndDestroyFieldPtr(void)
{
  FieldPtr F;

  F = Field_Create(1,1);

  TEST_ASSERT_TRUE(Field_Initialized(F));

  Field_Destroy(F);
}

void test_FieldModel_CreateFailsOnInvalidDimension(void)
{
  FieldPtr F;

  F = Field_Create(0,1);
  TEST_ASSERT_FALSE(Field_Initialized(F));
  Field_Destroy(F);

  F = Field_Create(FIELD_MAX_DIM+1,1);
  TEST_ASSERT_FALSE(Field_Initialized(F));
  Field_Destroy(F);
}

void test_FieldModel_CreateFailsOnInvalidScale(void)
{
  FieldPtr F;

  F = Field_Create(3,0);
  TEST_ASSERT_FALSE(Field_Initialized(F));
  Field_Destroy(F);

  F = Field_Create(3,FIELD_MAX_SCALE+1);
  TEST_ASSERT_FALSE(Field_Initialized(F));
  Field_Destroy(F);
}

void test_FieldModel_GetDimension(void)
{
  FieldPtr F;
  for (int i = 1; i <= FIELD_MAX_DIM; i++)
  {
    F = Field_Create(i,1);
    TEST_ASSERT_EQUAL(i,Field_Dimension(F));
    Field_Destroy(F);
  }
}

void test_FieldModel_GetScale(void)
{
  FieldPtr F;
  for (int i = 1; i <= FIELD_MAX_SCALE; i++)
  {
    F = Field_Create(3,i);
    TEST_ASSERT_EQUAL(i,Field_Scale(F));
    Field_Destroy(F);
  }
}

void test_FieldModel_GetRevealedState(void)
{
  FieldPtr F;
  unsigned int coordinates[3] = {0};
  F = Field_Create(3,3);
  TEST_ASSERT_EQUAL(false,Field_GetRevealed(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_SetRevealedState(void)
{
  FieldPtr F;
  unsigned int coordinates[3] = {0};
  F = Field_Create(3,3);
  Field_Reveal(F,coordinates);
  TEST_ASSERT_TRUE(Field_GetRevealed(F,coordinates));
  Field_Unreveal(F,coordinates);
  TEST_ASSERT_FALSE(Field_GetRevealed(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_GetFlaggedState(void)
{
  FieldPtr F;
  unsigned int coordinates[3] = {0,1,2};
  F = Field_Create(3,3);
  TEST_ASSERT_FALSE(Field_GetFlagged(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_SetFlaggedState(void)
{
  FieldPtr F;
  unsigned int coordinates[4] = {2,0,1,3};
  F = Field_Create(4,4);
  Field_Flag(F,coordinates);
  TEST_ASSERT_TRUE(Field_GetFlagged(F,coordinates));
  Field_Unflag(F,coordinates);
  TEST_ASSERT_FALSE(Field_GetFlagged(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_GetMinedState(void)
{
  FieldPtr F;
  unsigned int coordinates[5] = {1,2,3,4,5};
  F = Field_Create(5,5);
  TEST_ASSERT_FALSE(Field_GetMined(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_SetMinedState(void)
{
  FieldPtr F;
  unsigned int coordinates[6] = {4,1,3,2,5};
  F = Field_Create(6,6);
  Field_PlaceMine(F,coordinates);
  TEST_ASSERT_TRUE(Field_GetMined(F,coordinates));
  Field_RemoveMine(F,coordinates);
  TEST_ASSERT_FALSE(Field_GetMined(F,coordinates));
  Field_Destroy(F);
}

void test_FieldModel_CountMinedNeighbors(void)
{
  FieldPtr F;
  unsigned int coordinates[6] = {0};
  F = Field_Create(6,8);
  Field_PlaceMine(F,coordinates);
  for (int a = 0; a < 8; a++)
  {
    coordinates[0] = a;
    for (int b = 0; b < 8; b++)
    {
      coordinates[1] = b;
      for (int c = 0; c < 8; c++)
      {
        coordinates[2] = c;
        for (int d = 0; d < 8; d++)
        {
          coordinates[3] = d;
          for (int e = 0; e < 8; e++)
          {
            coordinates[4] = e;
            for (int f = 0; f < 8; f++)
            {
              coordinates[5] = f;
              TEST_ASSERT_EQUAL(
                (
                  (
                    (0!=a)||
                    (0!=b)||
                    (0!=c)||
                    (0!=d)||
                    (0!=e)||
                    (0!=f)
                  ) &&
                  1 >= a &&
                  1 >= b &&
                  1 >= c &&
                  1 >= d &&
                  1 >= e &&
                  1 >= f
                ) ? 
                1 : 0,
                Field_NumMinesNeighboring(F,coordinates)
              );
            }
          }
        }
      }
    }
  }
  Field_Destroy(F);
}

void test_FieldModel_OnlyCountsImmediateNeighborsForMines(void)
{
  FieldPtr F;
  unsigned int coordinates[6] = {0};
  F = Field_Create(6,8);
  for (int a = 0; a < 8; a++)
  {
    coordinates[0] = a;
    for (int b = 0; b < 8; b++)
    {
      coordinates[1] = b;
      for (int c = 0; c < 8; c++)
      {
        coordinates[2] = c;
        for (int d = 0; d < 8; d++)
        {
          coordinates[3] = d;
          for (int e = 0; e < 8; e++)
          {
            coordinates[4] = e;
            for (int f = 0; f < 8; f++)
            {
              coordinates[5] = f;
              Field_PlaceMine(F,coordinates);
            }
          }
        }
      }
    }
  }
  coordinates[0] = 1;
  coordinates[1] = 1;
  coordinates[2] = 1;
  coordinates[3] = 1;
  coordinates[4] = 1;
  coordinates[5] = 1;
  TEST_ASSERT_EQUAL(728,Field_NumMinesNeighboring(F,coordinates));
}

#endif // TEST
