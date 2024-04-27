#include "src/FieldModel.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"
















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



  do {if (((

 ((void *)0)

 ) != (F))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(25)));}} while(0);



  Field_Destroy(F);

}



void test_FieldModel_CreateFailsOnInvalidDimension(void)

{

  FieldPtr F;



  F = Field_Create(0,1);

  UnityAssertEqualNumber((UNITY_INT)((

 ((void *)0)

 )), (UNITY_INT)((F)), (

 ((void *)0)

 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

  Field_Destroy(F);



  F = Field_Create((6)+1,1);

  UnityAssertEqualNumber((UNITY_INT)((

 ((void *)0)

 )), (UNITY_INT)((F)), (

 ((void *)0)

 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

  Field_Destroy(F);

}



void test_FieldModel_CreateFailsOnInvalidScale(void)

{

  FieldPtr F;



  F = Field_Create(3,0);

  UnityAssertEqualNumber((UNITY_INT)((

 ((void *)0)

 )), (UNITY_INT)((F)), (

 ((void *)0)

 ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);

  Field_Destroy(F);



  F = Field_Create(3,(8)+1);

  UnityAssertEqualNumber((UNITY_INT)((

 ((void *)0)

 )), (UNITY_INT)((F)), (

 ((void *)0)

 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);

  Field_Destroy(F);

}



void test_FieldModel_GetDimension(void)

{

  FieldPtr F;

  for (int i = 1; i <= (6); i++)

  {

    F = Field_Create(i,1);

    UnityAssertEqualNumber((UNITY_INT)((i)), (UNITY_INT)((Field_Dimension(F))), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);

    Field_Destroy(F);

  }

}



void test_FieldModel_GetScale(void)

{

  FieldPtr F;

  for (int i = 1; i <= (8); i++)

  {

    F = Field_Create(3,i);

    UnityAssertEqualNumber((UNITY_INT)((i)), (UNITY_INT)((Field_Scale(F))), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

    Field_Destroy(F);

  }

}



void test_FieldModel_GetRevealedState(void)

{

  FieldPtr F;

  unsigned int coordinates[3] = {0};

  F = Field_Create(3,3);

  UnityAssertEqualNumber((UNITY_INT)((

 0

 )), (UNITY_INT)((Field_GetRevealed(F,coordinates))), (

 ((void *)0)

 ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_INT);

  Field_Destroy(F);

}



void test_FieldModel_SetRevealedState(void)

{

  FieldPtr F;

  unsigned int coordinates[3] = {0};

  F = Field_Create(3,3);

  Field_Reveal(F,coordinates);

  do {if ((Field_GetRevealed(F,coordinates))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(93)));}} while(0);

  Field_Unreveal(F,coordinates);

  do {if (!(Field_GetRevealed(F,coordinates))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(95)));}} while(0);

  Field_Destroy(F);

}



void test_FieldModel_GetFlaggedState(void)

{

  FieldPtr F;

  unsigned int coordinates[3] = {0,1,2};

  F = Field_Create(3,3);

  do {if (!(Field_GetFlagged(F,coordinates))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(104)));}} while(0);

  Field_Destroy(F);

}



void test_FieldModel_SetFlaggedState(void)

{

  FieldPtr F;

  unsigned int coordinates[4] = {2,0,1,3};

  F = Field_Create(4,4);

  Field_Flag(F,coordinates);

  do {if ((Field_GetFlagged(F,coordinates))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(114)));}} while(0);

  Field_Unflag(F,coordinates);

  do {if (!(Field_GetFlagged(F,coordinates))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(116)));}} while(0);

  Field_Destroy(F);

}



void test_FieldModel_GetMinedState(void)

{

  FieldPtr F;

  unsigned int coordinates[5] = {1,2,3,4,5};

  F = Field_Create(5,5);

  do {if (!(Field_GetMined(F,coordinates))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(125)));}} while(0);

  Field_Destroy(F);

}



void test_FieldModel_SetMinedState(void)

{

  FieldPtr F;

  unsigned int coordinates[6] = {4,1,3,2,5};

  F = Field_Create(6,6);

  Field_PlaceMine(F,coordinates);

  do {if ((Field_GetMined(F,coordinates))) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(135)));}} while(0);

  Field_RemoveMine(F,coordinates);

  do {if (!(Field_GetMined(F,coordinates))) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(137)));}} while(0);

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

    UnityAssertEqualNumber((UNITY_INT)(((((a!=0)||(b!=0)||(c!=0)||(d!=0)||(e!=0)||(f!=0)) && 1 >= a && 1 >= b && 1 >= c && 1 >= d && 1 >= e && 1 >= f) ? 1 : 0)), (UNITY_INT)((Field_NumMinesNeighboring(F,coordinates))), (

   ((void *)0)

   ), (UNITY_UINT)(165), UNITY_DISPLAY_STYLE_INT)













                                                               ;

  }

  }

  }

  }

  }

  }

  Field_Destroy(F);

}
