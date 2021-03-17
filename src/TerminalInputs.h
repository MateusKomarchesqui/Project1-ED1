#ifndef TERMINALINPUTS_H_INCLUDED
#define TERMINALINPUTS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//------------------------------------------TERMINAL INPUTS---------------------------------------------
//                 $~ Identify Terminal Inputs and set/create respective strings/tempFiles ~$
//----------------------------------------------Return--------------------------------------------------
//            FALSE <-- Invalid terminal arguments | TRUE <-- Valid terminal arguments                     
//---------------------------------------------Arguments------------------------------------------------
//                                           argc && argv[]
//                    VAR <--  hides internal declaration of struct variables
//                                var <-- reference to Variables
bool TerminalInputsManipulation(int argc, char *argv[], VAR var);
//------------------------------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//             Inputs values to variables stored in Variables struct
//-----------------------------------Arguments------------------------------------
//              VAR <--  hides internal declaration of struct variables
void VarInitialize(VAR var);
//--------------------------------------------------------------------------------

//-----------------------------------Procedure------------------------------------
//                     Creates BSD directory if not existent
//-----------------------------------Arguments------------------------------------
//                      char *Directory =  Path to BSD Dir
void createBSD(char *Directory);
//--------------------------------------------------------------------------------

//----------------------------------------Return--------------------------------------------
//      FALSE <-- Isn't an terminal argument | TRUE <-- Is an terminal argument                     
//---------------------------------------Arguments------------------------------------------
//                char *string <-- string to be compared with valid terminal arguments
bool isArgument(char *string);
//------------------------------------------------------------------------------------------

/**/
#endif