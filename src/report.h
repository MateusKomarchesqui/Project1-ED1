#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Variables.h"
#define ftell_logFile 77 //Ftell of Log.geo after in file template

//-----------------------------------Procedure------------------------------------
//                              Creates List Log.geo
//-----------------------------------Arguments------------------------------------
//                     size && visits <-- Values to be written 
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void createListLog(int size, int visits, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                        Inputs values to report graph
//-----------------------------------Arguments------------------------------------
//               Xporportion && Yproportion <-- Scale in X/Y axis 
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void inputGraphStats(int Xproportion, int Yproportion, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                              Creates report graph
//-----------------------------------Arguments------------------------------------
//               size && visits <-- Values to be written along X/Y axis
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void createGraph(int size, int visits, VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                          $~ Calls report functions ~$
//-----------------------------------Arguments------------------------------------
//               size && visits <-- Values to be written along X/Y axis
//              VAR <--  hides internal declaration of struct variables
//                          var <-- reference to Variables
void LOG_Core(int size, int visits, VAR var);
//--------------------------------------------------------------------------------

/**/
#endif