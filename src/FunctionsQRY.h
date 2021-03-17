#ifndef FUNCTIONSQRY_H_INCLUDED
#define FUNCTIONSQRY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "voidpointers.h"

//------------------------Return---------------------------
//         Returns Greatter value among a and b             
//-----------------------Arguments------------------------- 
//  float a <-- float number  |  float b <-- float number   
float Greatter(float a, float b);
//---------------------------------------------------------

//------------------------Return---------------------------
//           Returns Minor value among a and b              
//-----------------------Arguments-------------------------
//  float a <-- float number  |  float b <-- float number   
float Lesser(float a, float b);
//----------------------------------------------------------

//------------------------Return----------------------------
//      Verifies if r point belongs to pq segment           
//-----------------------Arguments--------------------------
//st_point <-- hides internal declaration of struct point
//sP <-- point P    |   sQ <-- point Q   |    sR <-- point R
bool onLineSeg(st_point sP, st_point sQ, st_point sR);
//----------------------------------------------------------

//------------------------Return----------------------------
//    Returns orientation between three given points        
//-----------------------Arguments--------------------------
//st_point <-- hides internal declaration of struct point
//sP <-- point P    |   sQ <-- point Q   |    sR <-- point R
int angleCoef(st_point sP, st_point sQ, st_point sR);
//----------------------------------------------------------

//---------------------------------Return----------------------------------
//                Verifies if two given line segments intersect            
//--------------------------------Arguments--------------------------------
//       st_point <-- hides internal declaration of struct point        
//sP1 <-- point P1 | sQ1 <-- point Q1 | sP2 <-- point P2 | sQ1 <-- point Q1
bool SegIntersect(st_point sP1, st_point sQ1, st_point sP2, st_point sQ2);
//-------------------------------------------------------------------------

//-------------------------------------Return-------------------------------------
//                   Verifies if two given rectangles intersect                   
// 1 <-- A and B intersect | 2 <-- B is internal to A | 3 <-- A is internal to B  
//------------------------------------Arguments-----------------------------------
// A rectangle's coordinates = (x1, y1) <-- Anchor | w1 <-- width | h1 <-- heigth 
// B rectangle's coordinates = (x2, y2) <-- Anchor | w2 <-- width | h2 <-- heigth 
int rectIntersect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//           Updates all list stored overlaid rectangles, turning opacity 0 
//                         for those who doesn't overlay                   
//-----------------------------------Arguments------------------------------------
//             StdList <--  hides internal declaration of struct List
//                        Stdlist <-- reference to list
//            VAR <--  hides internal declaration of struct variables
//                        var <-- reference to Variables
void functionTP(StdList Stdlist, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//         Updates list stored overlaid rectangles inside given area, turning  
//                    opacity 0 for those who doesn't overlay                   
//-----------------------------------Arguments------------------------------------
//             StdList <--  hides internal declaration of struct List
//                        Stdlist <-- reference to list
//     Given area coordinates = (x, y) <-- Anchor | w <-- width | h <-- heigth
//            VAR <--  hides internal declaration of struct variables
//                        var <-- reference to Variables
void functionTPR(StdList Stdlist, float x, float y, float w, float h, VAR var);
//--------------------------------------------------------------------------------

//-------------------------------Return-----------------------------------
//         Verifies if given point is internal to given rectangle           
//------------------------------Arguments---------------------------------
//  Rectangle coordinates = (x, y) <-- Anchor | w <-- width | h <-- heigth
//         st_point <-- hides internal declaration of struct point
//                           sP <-- point P
bool isInternal(float x, float y, float w, float h, st_point P);
//--------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                  Removes rectangles wich given point is internal                   
//-----------------------------------Arguments------------------------------------
//             StdList <--  hides internal declaration of struct List
//                        Stdlist <-- reference to list
//                           Point coordinates = (x, y)
//            VAR <--  hides internal declaration of struct variables
//                        var <-- reference to Variables
void functionDPI(StdList Stdlist, float x, float y, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//      Removes rectangles totally inside given rectangle referenced by its id                   
//-----------------------------------Arguments------------------------------------
//             StdList <--  hides internal declaration of struct List
//                        Stdlist <-- reference to list
//                                Rectangle's ID
//            VAR <--  hides internal declaration of struct variables
//                        var <-- reference to Variables
void functionDR(StdList Stdlist, char *id, VAR var);
//--------------------------------------------------------------------------------

//-------------------------------------Procedure--------------------------------------
// Draws bounding box wich contains all rectangles for witch a given point is internal                  
//-------------------------------------Arguments--------------------------------------
//               StdList <--  hides internal declaration of struct List
//                          Stdlist <-- reference to list
//                            Point coordinates = (x, y)
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void functionBBI(StdList Stdlist, float x, float y, VAR var);
//------------------------------------------------------------------------------------

//--------------------------------------Procedure---------------------------------------
//   Draws bounding box wich contains all rectangles internal to another given rectangle                   
//--------------------------------------Arguments---------------------------------------
//                StdList <--  hides internal declaration of struct List
//                           Stdlist <-- reference to list
//                                   Rectangle's ID
//               VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void functionBBID (StdList Stdlist, char *id, VAR var);
//--------------------------------------------------------------------------------------

//-----------------------------------------Auxiliar Procedure-----------------------------------------
//                      Manages temporary file responsible for BBI and BBID query                   
//---------------------------------------------Arguments----------------------------------------------
//                      StdList <--  hides internal declaration of struct List
//                                  Stdlist <-- reference to list
// Bounding Box coordinates = (MinorX, MinorY) <-- Anchor | GreatterW <-- width | GreatterH <-- heigth 
//                                     Point coordinates = (x, y)
//                char *function = selects function among BBI and BBID to print on file 
//                     VAR <--  hides internal declaration of struct variables
//                                   var <-- reference to Variables
void BBI_BBID_tempFileWrite(float MinorX, float MinorY, float GreatterW, float GreatterH, float x, float y, char *function, VAR var);
//----------------------------------------------------------------------------------------------------

//--------------------------------------Procedure---------------------------------------
//       Reports data from given id rectangle and its K previous/ next rectangles                   
//--------------------------------------Arguments---------------------------------------
//                StdList <--  hides internal declaration of struct List
//                            Stdlist <-- reference to list
//                                   Rectangle's ID
//                                    K Rectangles
//               VAR <--  hides internal declaration of struct variables
//                             var <-- reference to Variables
void functionIID(StdList Stdlist, char *id, int K, VAR var);
//--------------------------------------------------------------------------------------

//---------------------------------------------Procedure------------------------------------------------
// Reports data from given id rectangle and its K previous/ next rectangles, removing these K rectangles                   
//---------------------------------------------Arguments------------------------------------------------
//                     StdList <--  hides internal declaration of struct List
//                                  Stdlist <-- reference to list
//                                          Rectangle's ID
//                                           K Rectangles
//                    VAR <--  hides internal declaration of struct variables
//                                var <-- reference to Variables
void functionDIID(StdList Stdlist, char *id, int K, VAR var);
//---------------------------------------------------------------------------------------------------------------

/**/
#endif