#ifndef LISTHEADER_H_INCLUDED
#define LISTHEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "voidpointers.h"

//-------------------------------------------GET PREVIOUS-----------------------------------------------
//                                $~ Returns previous of given Node ~$
//-------------------------------------------Precondition----------------------------------------------- 
//                        Pass valid node of list, otherwize error is expected
//----------------------------------------------Return--------------------------------------------------
//                              Reference to previous node of given node
//                               List Head previous corresponds to NULL              
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of List struct
//                                   Stdlist <-- reference to list
//                          StdNode <-- hides internal declaration of Node struct
//                                Stdnode <-- reference to node of list
StdNode getPrevious(StdList Stdlist, StdNode Stdnode);
//------------------------------------------------------------------------------------------------------

//---------------------------------------------GET NEXT-------------------------------------------------
//                                $~ Returns next of given Node ~$
//-------------------------------------------Precondition----------------------------------------------- 
//                       Pass valid node of list, otherwize error is expected
//----------------------------------------------Return--------------------------------------------------
//                               Reference to next node of given node
//                                List Tail next corresponds to NULL              
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of List struct
//                                   Stdlist <-- reference to list
//                          StdNode <-- hides internal declaration of Node struct
//                                Stdnode <-- reference to node of list
StdNode getNext(StdList Stdlist, StdNode Stdnode);
//------------------------------------------------------------------------------------------------------

//--------------------------------------------GET FIRST-------------------------------------------------
//                                 $~ Returns first node of list ~$
//----------------------------------------------Return--------------------------------------------------
//                            Reference to first node of given list (Head)
//                               Case List Length == 0 Returns NULL              
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of List struct
//                                   Stdlist <-- reference to list
StdNode getFirst(StdList Stdlist);
//------------------------------------------------------------------------------------------------------

//---------------------------------------------GET LAST-------------------------------------------------
//                                  $~ Returns last node of list ~$
//----------------------------------------------Return--------------------------------------------------
//                            Reference to last node of given list (Tail)
//                               Case List Length == 0 Returns NULL              
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of List struct
//                                   Stdlist <-- reference to list
StdNode getLast(StdList Stdlist);
//------------------------------------------------------------------------------------------------------

//-------------------------------------------CREATE LIST------------------------------------------------
//                                    $~ Creates an empty list ~$
//----------------------------------------------Return--------------------------------------------------
//                                      Reference to empty list
//---------------------------------------------Arguments------------------------------------------------
//                  NX <-- number informed in .geo file (determines static list size)
StdList createList (int NX);
//------------------------------------------------------------------------------------------------------

//----------------------------------------------LENGTH--------------------------------------------------
//                                $~ Returns length of given list ~$
//----------------------------------------------Return--------------------------------------------------
//                                       Length of given list
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of List struct
//                                   Stdlist <-- reference to list
int length(StdList Stdlist);
//------------------------------------------------------------------------------------------------------

//----------------------------------------------INSERT--------------------------------------------------
//                               $~ Inserts a new node in the list ~$
//----------------------------------------------Return--------------------------------------------------
//                                    Reference to appended node
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of struct List
//                                   Stdlist <-- reference to list
//                          StdItem <-- hides internal declaration of struct Item
//                              info <-- reference to allocated Item struct
StdNode insert(StdList Stdlist, StdItem info);
//------------------------------------------------------------------------------------------------------

//----------------------------------------AUXILIARY FUNCTION--------------------------------------------
//                             $~ Returns node at given integer position ~$
//----------------------------------------------Return--------------------------------------------------
//                                 Reference to node in given position
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of struct List
//                                   Stdlist <-- reference to list
//                               index <-- index of node to be returned
StdNode atPos(StdList Stdlist, int index);
//------------------------------------------------------------------------------------------------------

//----------------------------------------AUXILIARY FUNCTION--------------------------------------------
//                            $~ Returns integer position of given node ~$
//----------------------------------------------Return--------------------------------------------------
//                                   Integer position of given node 
//---------------------------------------------Arguments------------------------------------------------
//                          StdList <-- hides internal declaration of struct List
//                                   Stdlist <-- reference to list
//                          StdNode <-- hides internal declaration of Node struct
//                                Stdnode <-- reference to node of list
int indexOf(StdList Stdlist, StdNode Stdnode);
//------------------------------------------------------------------------------------------------------

//---------------------------------------------REMOVE---------------------------------------------------
//                             $~ Removes given node from given list ~$ 
//-------------------------------------------Precondition----------------------------------------------- 
//                          Pass valid node of list, otherwize error is expected
//--------------------------------------------Arguments-------------------------------------------------
//                       StdList <-- hides internal declaration of struct List
//                                  Stdlist <-- reference to list
//                       StdNode <-- hides internal declaration of struct Node
//                                  Stdnode <-- reference to node
void erase(StdList Stdlist, StdNode Stdnode);
//------------------------------------------------------------------------------------------------------

//-----------------------------------------------GET----------------------------------------------------
//                               $~ Returns reference to Item struct ~$
//-------------------------------------------Precondition----------------------------------------------- 
//                        Pass valid node of list, otherwize error is expected
//----------------------------------------------Return--------------------------------------------------
//                            Returns a reference to given node's Item content 
//--------------------------------------------Arguments-------------------------------------------------
//                       StdList <-- hides internal declaration of struct List
//                                  Stdlist <-- reference to list
//                       StdNode <-- hides internal declaration of struct Node
//                                  Stdnode <-- reference to node
StdItem get(StdList Stdlist, StdNode Stdnode);
//------------------------------------------------------------------------------------------------------

//---------------------------------------------Procedure------------------------------------------------
//                                  $~ Frees memory of given list ~$
//-------------------------------------------Precondition----------------------------------------------- 
//                           Pass valid list, otherwize error is expected
//--------------------------------------------Arguments-------------------------------------------------
//                       StdList <-- hides internal declaration of struct List
//                                  Stdlist <-- reference to list
void freeList(StdList Stdlist);
//------------------------------------------------------------------------------------------------------

//------------------------------------------INSERT BEFORE-----------------------------------------------
//                            $~ Inserts new node before existing one ~$ 
//-------------------------------------------Precondition----------------------------------------------- 
//                       Pass valid node of list, otherwize error is expected
//----------------------------------------------Return--------------------------------------------------
//                                Returns a reference to appended node 
//--------------------------------------------Arguments-------------------------------------------------
//                       StdList <-- hides internal declaration of struct List
//                                  Stdlist <-- reference to list
//                       StdNode <-- hides internal declaration of struct Node
//                                  Stdnode <-- reference to node
//                          StdItem <-- hides internal declaration of struct Item
//                              info <-- reference to allocated Item struct
StdNode insertBefore(StdList Stdlist, StdNode Stdnode, StdItem info);
//------------------------------------------------------------------------------------------------------

//------------------------------------------INSERT AFTER------------------------------------------------
//                             $~ Inserts new node after existing one ~$ 
//-------------------------------------------Precondition----------------------------------------------- 
//                          Pass valid node of list, otherwize error is expected
//----------------------------------------------Return--------------------------------------------------
//                                 Returns a reference to appended node
//--------------------------------------------Arguments-------------------------------------------------
//                       StdList <-- hides internal declaration of struct List
//                                  Stdlist <-- reference to list
//                       StdNode <-- hides internal declaration of struct Node
//                                  Stdnode <-- reference to node
//                          StdItem <-- hides internal declaration of struct Item
//                              info <-- reference to allocated Item struct
StdNode insertAfter(StdList Stdlist, StdNode Stdnode, StdItem info);
//------------------------------------------------------------------------------------------------------

//-----------------------------------------Auxiliar Procedure-----------------------------------------
//-------------------------------------------Precondition--------------------------------------------- 
//                             Pass valid list, otherwize error is expected
//----------------------------------------------Return------------------------------------------------
//                                   Returns a copy of list's visits                     
//---------------------------------------------Arguments----------------------------------------------
//                      StdList <--  hides internal declaration of struct List
//                                  Stdlist <-- reference to list
int getListVisits(StdList Stdlist);
//----------------------------------------------------------------------------------------------------

/**/
#endif