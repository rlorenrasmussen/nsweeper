#ifdef TEST

#include "unity.h"

#include "FieldView.h"
#include "mock_FieldModel.h"

// TODO: given some pane vector, output specified pane to a display buffer
// TODO: render the display buffer onto the screen
// TODO: report stored pane vector
// TODO: increment/decrement one axis of pane vector

void setUp(void)
{
  Field_Create_IgnoreAndReturn(NULL);
}

void tearDown(void)
{
}

void test_FieldView_InitializesWithFieldPtr(void)
{
  bool result;
  (void) Field_Dimension_ExpectAndReturn(NULL,3);
  result = FieldView_Init(NULL);
  TEST_ASSERT_TRUE(result);
}

void test_FieldView_ReportsPaneVectorSize(void)
{
  unsigned int size;
  bool result;
  for (int i = 1; i <= 6; i++)
  {
    (void) Field_Dimension_ExpectAndReturn(NULL,i);
    result = FieldView_Init(NULL);
    TEST_ASSERT_TRUE(result);
    (void) Field_Dimension_ExpectAndReturn(NULL,i);
    size = FieldView_GetPaneVectorSize();
    TEST_ASSERT_EQUAL(i,size);
  }
}
#endif // TEST
