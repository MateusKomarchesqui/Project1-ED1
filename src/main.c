#include "hub.h"
#include "TerminalInputs.h"
#include "variables.h"

int main (int argc, char *argv[]) {

    /*      Cleanest main you will probably see around here ◕ ◡ ◕      */
    VAR var = createVAR();
    if (TerminalInputsManipulation(argc, argv, var))
        cityOfRectangles(var);


    memoryFree(var);
    
    return 0;

}