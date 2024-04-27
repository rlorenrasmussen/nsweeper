#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define FIELD_MAX_DIM (6)
#define FIELD_MAX_SCALE (8)

typedef struct Field* FieldPtr;

FieldPtr      Field_Create              (unsigned int dim, unsigned int scale );
void          Field_Destroy             (FieldPtr F                           );
unsigned int  Field_Dimension           (FieldPtr F                           );
unsigned int  Field_Scale               (FieldPtr F                           );
bool          Field_GetRevealed         (FieldPtr F, unsigned int* coordinates);
void          Field_Reveal              (FieldPtr F, unsigned int* coordinates);
void          Field_Unreveal            (FieldPtr F, unsigned int* coordinates);
bool          Field_GetFlagged          (FieldPtr F, unsigned int* coordinates);
void          Field_Flag                (FieldPtr F, unsigned int* coordinates);
void          Field_Unflag              (FieldPtr F, unsigned int* coordinates);
bool          Field_GetMined            (FieldPtr F, unsigned int* coordinates);
void          Field_PlaceMine           (FieldPtr F, unsigned int* coordinates);
void          Field_RemoveMine          (FieldPtr F, unsigned int* coordinates);
unsigned int  Field_NumMinesNeighboring (FieldPtr F, unsigned int* coordinates);

#endif // FIELDMODEL_H
