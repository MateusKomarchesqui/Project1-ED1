#ifndef HUB_H_INCLUDED
#define HUB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "voidpointers.h"

//------------------------------------File Read-------------------------------------
//              Reads content of file and summon respective functions
//-----------------------------------Precondition-----------------------------------
//                  Pass valid list, otherwize error is expected
//-------------------------------------Return---------------------------------------              
//        TRUE <-- File read successfully | FALSE <-- Case file cannot be read  
//-----------------------------------Arguments--------------------------------------
//    char *type <-- informs reather functions is accessing .geo or .qry file
//               StdList <--  hides internal declaration of struct List
//                          Stdlist <-- reference to list
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to variables
bool fileRead(char *type, StdList Stdlist, VAR var);
//----------------------------------------------------------------------------------

//--------------------------------------HUB---------------------------------------
//                  $~ City were rectangles feel more confortable ~$
//          Calls other functions managing reading and printing rectangles
//-----------------------------------Arguments------------------------------------
//            VAR <--  hides internal declaration of struct variables
//                          var <-- reference to variables
void cityOfRectangles(VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                       Prints rectangles read in .geo file
//---------------------------------Precondition-----------------------------------
//                  Pass valid list, otherwize error is expected
//-----------------------------------Arguments------------------------------------
//               StdList <--  hides internal declaration of struct List
//                          Stdlist <-- reference to list
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to variables
void GEOSvgPrint(StdList Stdlist, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                  Prints resultant rectangles after queries
//---------------------------------Precondition-----------------------------------
//                  Pass valid list, otherwize error is expected
//-----------------------------------Arguments------------------------------------
//               StdList <--  hides internal declaration of struct List
//                          Stdlist <-- reference to list
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to variables
void QRYSvgPrint(StdList Stdlist, VAR var);
//--------------------------------------------------------------------------------

/**/
#endif