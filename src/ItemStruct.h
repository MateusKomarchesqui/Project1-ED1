#ifndef ITEMSTRUCT_H_INCLUDED
#define ITEMSTRUCT_H_INCLUDED

#include "voidpointers.h"

//----------------------------GET FUNCTIONS---------------------------
//               $~ Gets a copy of Item struct content ~$
//-----------------------------Precondition---------------------------
//            Pass valid pointer, otherwize error is expected
//-------------------------------Return-------------------------------
//           Returns a copy of value stored in Item struct     
//-----------------------------Arguments------------------------------
//       StdItem <--  hides internal declaration of struct Item
//                     item <-- reference to Item
char *getItem_ID(StdItem item);
char *getItem_FILL(StdItem item);
char *getItem_STROKE(StdItem item);
float getItem_X(StdItem item);
float getItem_Y(StdItem item);
float getItem_W(StdItem item);
float getItem_H(StdItem item);
int getItem_OP_C(StdItem item);
int getItem_OP_P(StdItem item);
int getItem_show(StdItem item);
//--------------------------------------------------------------------

//---------------------------CREATE ITEM------------------------------
//               $~ Allocate memory to Item struct ~$
//------------------------------Return--------------------------------
//  Returns reference pointer to an empty Item struct block of memory
StdItem createItem();
//--------------------------------------------------------------------

/**/
#endif