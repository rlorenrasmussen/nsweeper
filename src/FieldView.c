#include "FieldView.h"

typedef Screen_t* ScreenPtr;

static FieldPtr FIELD_;
static ScreenPtr SCREEN_;

static void drawInterRowLine(ScreenPtr S,
                             unsigned int* lN,
                             const unsigned int cW)
{
  unsigned int colNum = 0;
  (void) sprintf(SCREEN_->buff[*lN]+colNum,"+");
  colNum++;
  for (int j = 0; j < Field_Scale(FIELD_); j++)
  {
    for (int k = 0; k < cW; k++)
    {
      (void) sprintf(SCREEN_->buff[*lN]+colNum,"-");
      colNum++;
    }
    (void) sprintf(SCREEN_->buff[*lN]+colNum,"+");
    colNum++;
  }
  (void) sprintf(SCREEN_->buff[*lN]+colNum,"\n"); (*lN)++;
}

static void drawRow(ScreenPtr S,
                    FieldPtr F,
                    unsigned int* lN,
                    unsigned int* rN,
                    const unsigned int cW,
                    unsigned int* coordinates,
                    unsigned int dim)
{
  unsigned int colNum, cellNum;
  char fieldSymbol[cW];

  colNum = 0;
  cellNum = 0;
  (void) sprintf(SCREEN_->buff[*lN]+colNum,"|");
  colNum++;
  coordinates[dim-2] = *rN;
  
  for (int j = 0; j < Field_Scale(F); j++)
  {
    coordinates[dim-1] = cellNum;
    if (Field_GetRevealed(FIELD_,coordinates))
    {
      if (Field_GetMined(F,coordinates))
      {
        if (Field_GetFlagged(F,coordinates))
        {
          // fieldSymbol = 'M';
          sprintf(fieldSymbol,"M");
        }
        else
        {
          // fieldSymbol = 'X';
          sprintf(fieldSymbol,"X");
        }
      }
      else
      {
        // fieldSymbol = '0';
        sprintf(fieldSymbol,"%d",Field_NumMinesNeighboring(F,coordinates));
      }
    }
    else
    {
      // fieldSymbol = ' ';
      sprintf(fieldSymbol," ");
    }
    (void) sprintf(SCREEN_->buff[*lN]+colNum,"  %s  ",fieldSymbol);
    colNum += 5;
    (void) sprintf(SCREEN_->buff[*lN]+colNum,"|");
    colNum++;
    cellNum++;
  }
  (void) sprintf(SCREEN_->buff[*lN]+colNum,"\n");
}

static void drawPaneVectorControls(ScreenPtr S,
                                   FieldPtr F,
                                   unsigned int cellWidth,
                                   unsigned int* paneVec)
{
  unsigned int startLine,
               endLine,
               endCol;
  const char axes[] = "uvwx";

  endLine = (1+1)*Field_Scale(F) + 1;
  startLine = endLine - 3;
  endCol = (1+cellWidth)*Field_Scale(F) + 1;
  for (int y = startLine; y < endLine; y++)
  {
    int x = endCol;
    char c;
    for (int i = 0; i < 4; i++)
    {
      *(SCREEN_->buff[y]+ x++) = ' ';
    }
    
    for (int i = 0; i < Field_Dimension(F)-2; i++)
    {
      if (startLine == y)
      {
        if (Field_Scale(F)-1 <= paneVec[i])
        {
          c = ' ';
        }
        else
        {
          c = '+';
        }
      }
      else if (startLine + 1 == y)
      {
        c = axes[FIELD_MAX_DIM-Field_Dimension(F)+i];
      }
      else if (startLine + 2 == y)
      {
        if (0 == paneVec[i])
        {
          c = ' ';
        }
        else
        {
          c = '-';
        }
      }
      else
      {
        c = '?';
      }
      *(SCREEN_->buff[y]+ x++) = c;
      *(SCREEN_->buff[y]+ x++) = ' ';
    }
    *(SCREEN_->buff[y] + --x) = '\n';
  }
}

static void clearDisplayBuffer(ScreenPtr S)
{
  for (int y = 0; y < S->H; y++)
  {
    for (int x = 0; x < S->W; x++)
    {
      *(S->buff[y]+x) = 0;
    }
  }
}

void FieldView_Draw(unsigned int* paneVector)
{
  unsigned int lineNum, rowNum, cellNum;
  unsigned int startLine, endLine, endCol;
  unsigned int coordinates[FIELD_MAX_DIM] = {0};
  unsigned int dim;
  char fieldSymbol;
  const unsigned int cellWidth = 5;

  dim = Field_Dimension(FIELD_);

  for (int i = 0; i + 2 < dim; i++)
  {
    coordinates[i] = paneVector[i];
  }

  clearDisplayBuffer(SCREEN_);

  lineNum = 0;
  rowNum = 0;
  cellNum = 0;

  for (int i = 0; i <= Field_Scale(FIELD_); i++)
  {
    drawInterRowLine(SCREEN_,&lineNum,cellWidth);
    drawRow(SCREEN_,FIELD_,&lineNum,&rowNum,cellWidth,coordinates,dim);
    lineNum++;
    cellNum = 0;
    rowNum++;
  }
  drawInterRowLine(SCREEN_,&lineNum,cellWidth);
  drawPaneVectorControls(SCREEN_,FIELD_,cellWidth,paneVector);
}

bool FieldView_Init(FieldPtr F, Screen_t* S)
{
  FIELD_ = F;
  SCREEN_ = S;
  return true;
}

unsigned int FieldView_GetPaneVectorSize(void)
{
  return Field_Dimension(FIELD_);
}