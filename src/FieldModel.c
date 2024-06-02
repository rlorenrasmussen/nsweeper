#include "FieldModel.h"

struct Field
{
  unsigned int dim;
  unsigned int scale;
  bool* revealed;
  bool* flagged;
  bool* mined;
  unsigned int* minedNeighbors;
};

static unsigned int getIndex(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = 0;
  for (int i = 0; i < Field_Dimension(F); i++)
  {
    index *= Field_Scale(F);
    index += coordinates[i];
  }
  return index;
}

static unsigned int ternarySize(unsigned int numPlaces)
{
  unsigned int size = 1;
  for (int i = 0; i < numPlaces; i++)
  {
    size *= 3;
  }
  return size;
}

static void initializeTernary(unsigned int numPlaces, int* ternaryNum)
{
  for (int i = 0; i < numPlaces; i++)
  {
    ternaryNum[i] = -1;
  }
}

static void incrementTernary(unsigned int numPlaces, int* ternaryNum)
{
  for (int i = numPlaces-1; i >= 0; i--)
  {
    ternaryNum[i] += 1;
    if (1 >= ternaryNum[i])
    {
      break;
    }
    ternaryNum[i] = -1;
  }
}

FieldPtr Field_Create(unsigned int dim, unsigned int scale)
{
  if (1 > dim ||
      FIELD_MAX_DIM < dim ||
      1 > scale ||
      FIELD_MAX_SCALE < scale)
  {
    return NULL;
  }
  FieldPtr NewField = calloc(1,sizeof(struct Field));
  NewField->dim = dim;
  NewField->scale = scale;
  unsigned int numCells = 1;
  for (int i = 0; i < dim; i++)
  {
    numCells *= scale;
  }
  NewField->revealed = calloc(numCells,sizeof(bool));
  NewField->flagged = calloc(numCells,sizeof(bool));
  NewField->mined = calloc(numCells,sizeof(bool));
  NewField->minedNeighbors = calloc(numCells,sizeof(unsigned int));
  return NewField;
}

void Field_Destroy(FieldPtr F)
{
  if (NULL == F)
  {
    return;
  }
  free(F->revealed);
  free(F->flagged);
  free(F->mined);
  free(F->minedNeighbors);
  free(F);
}

unsigned int Field_Dimension(FieldPtr F)
{
  return F->dim;
}

unsigned int Field_Scale(FieldPtr F)
{
  return F->scale;
}

bool Field_GetRevealed(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  return F->revealed[index];
}

void Field_Reveal(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  F->revealed[index] = true;
}

void Field_Unreveal(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  F->revealed[index] = false;
}

bool Field_GetFlagged(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  return F->flagged[index];
}

void Field_Flag(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  F->flagged[index] = true;
}

void Field_Unflag(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  F->flagged[index] = false;
}

bool Field_GetMined(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  return F->mined[index];
}

void Field_PlaceMine(FieldPtr F, unsigned int* coordinates)
{
  unsigned int numNeighborsToCheck = ternarySize(Field_Dimension(F));
  unsigned int index;
  int* displacements = calloc(Field_Dimension(F),sizeof(int));
  unsigned int* copy_coordinates = calloc(Field_Dimension(F), sizeof(unsigned int));
  bool notAllZeros;
  bool allCoordinatesValid;
  initializeTernary(Field_Dimension(F),displacements);

  for (int i = 0; i < numNeighborsToCheck; i++)
  {
    notAllZeros = false;
    allCoordinatesValid = true;
    for (int j = 0; j < Field_Dimension(F); j++)
    {
      copy_coordinates[j] = coordinates[j] + displacements[j];
      notAllZeros |= 0 != displacements[j];
      allCoordinatesValid &= (coordinates[j] != 0 || displacements[j] > -1) && Field_Scale(F) > copy_coordinates[j];
    }
    if (notAllZeros && allCoordinatesValid)
    {
      index = getIndex(F,copy_coordinates);
      F->minedNeighbors[index]++;
    }
    incrementTernary(Field_Dimension(F), displacements);
  }

  free(displacements);
  free(copy_coordinates);
  index = getIndex(F,coordinates);
  F->mined[index] = true;
}

void Field_RemoveMine(FieldPtr F, unsigned int* coordinates)
{
  unsigned int numNeighborsToCheck = ternarySize(Field_Dimension(F));
  unsigned int index;
  int* displacements = calloc(Field_Dimension(F),sizeof(int));
  unsigned int* copy_coordinates = calloc(Field_Dimension(F), sizeof(unsigned int));
  bool notAllZeros;
  bool allCoordinatesValid;
  initializeTernary(Field_Dimension(F),displacements);

  for (int i = 0; i < numNeighborsToCheck; i++)
  {
    notAllZeros = false;
    allCoordinatesValid = true;
    for (int j = 0; j < Field_Dimension(F); j++)
    {
      copy_coordinates[j] = coordinates[j] + displacements[j];
      notAllZeros |= 0 != displacements[j];
      allCoordinatesValid &= (0 != coordinates[j] || -1 < displacements[j]) && Field_Scale(F) > copy_coordinates[j];
    }
    if (notAllZeros && allCoordinatesValid)
    {
      index = getIndex(F,copy_coordinates);
      F->minedNeighbors[index]--;
    }
    incrementTernary(Field_Dimension(F), displacements);
  }

  free(displacements);
  free(copy_coordinates);
  index = getIndex(F,coordinates);
  F->mined[index] = false;
}

unsigned int Field_NumMinesNeighboring(FieldPtr F, unsigned int* coordinates)
{
  unsigned int index = getIndex(F,coordinates);
  return F->minedNeighbors[index];
}

