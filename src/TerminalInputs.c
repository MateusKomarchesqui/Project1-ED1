#include "voidpointers.h"
#include "TerminalInputs.h"
#include "Variables.h"

//--------------------------SET PROCEDURES----------------------------
//             $~ Sets value to Variables struct content ~$    
//-----------------------------Arguments------------------------------
//       VAR <--  hides internal declaration of struct Variables
//                    var <-- reference to Variables
//                          Value to be set
void setARG_PathBED(VAR var, char *string);
void setARG_PathBED_qry(VAR var, char *string);
void setARG_PathBED_geo(VAR var, char *string);
void setARG_PathBSD(VAR var, char *string);
void setARG_geo(VAR var, char *string);
void setARG_qry(VAR var, char *string);
void setARG_Log(VAR var, char *string);
void setARG_title(VAR var, char *string);
void setBED_DataCollectPath(VAR var, char *string);
void setBED_tempLog(VAR var, char *string);
void setBSD_LogGeo(VAR var, char *string);
void setBSD_LogSvg(VAR var, char *string);
void setArqConsTXT(VAR var, char *string);
void setArqConsSVG(VAR var, char *string);
void catARG_PathBED_qry(VAR var, char *string);
void catARG_PathBED_geo(VAR var, char *string);
void catBED_DataCollectPath(VAR var, char *string);
void catBED_tempLog(VAR var, char *string);
//------------------------------------------------------------------------

/*               TERMINAL INPUTS MANIPULATION               */
bool TerminalInputsManipulation(int argc, char *argv[], VAR var) {

    int ARG_POS_ib = -1, ARG_POS_cb = -1, ARG_POS_fb = -1;

    for (int i = 1; i < argc; i++) {

        if (!strcmp(argv[i], "-e")) {
            if (argv[i + 1]) {
                if (!isArgument(argv[i + 1])) {
                    setARG_PathBED(var, argv[i + 1]);
                    i++;
                }
            }

        }else if (!strcmp(argv[i], "-f")) {
            if (argv[i + 1]) {
                if (!isArgument(argv[i + 1])) {
                    setARG_geo(var, argv[i + 1]);
                    i++;
                }
            }

        }else if (!strcmp(argv[i], "-o")) {
            if (argv[i + 1]) {
                if (!isArgument(argv[i + 1])) {
                    setARG_PathBSD(var, argv[i + 1]);
                    i++;
                }

                createBSD(getARG_PathBSD(var));
            }

        }else if (!strcmp(argv[i], "-q")) {
            if (argv[i + 1]) {
                if (!isArgument(argv[i + 1])) {
                    setARG_qry(var, argv[i + 1]);
                    i++;
                }
            }

        }else if (!strcmp(argv[i], "-ib")) {
            ARG_POS_ib = i;
        }else if (!strcmp(argv[i], "-cb")) {
            ARG_POS_cb = i;
        }else if (!strcmp(argv[i], "-fb")) {
            if (argv[i + 1]) {
                ARG_POS_fb = i;
                if (!isArgument(argv[i + 1])) {
                    setARG_Log(var, argv[i + 1]);
                    i++;
                }
            }
            if (argv[i + 1]) {
                if (!isArgument(argv[i + 1])) {
                    setARG_title(var, argv[i + 1]);
                    i++;
                }
            }
        }
    }

    VarInitialize(var);

    char *aux = calloc(strlen(getARG_geo(var)) + strlen(getARG_PathBED_geo(var)) + 10, sizeof(char));
    if (strcmp(getARG_PathBED_geo(var), "\0")) sprintf(aux, "%s/%s.geo", getARG_PathBED_geo(var), getARG_geo(var));
    else  sprintf(aux, "%s.geo", getARG_geo(var));
    FILE *file = fopen(aux, "r");
    free(aux);

    if (!strcmp(getARG_geo(var), "\0")) {
        puts("Arquivo .geo nao informado.");
        return 0;
    }else if (file == NULL) {
        puts("Arquivo .geo inexistente.");
        return 0;
    }
    fclose(file);
    
    if (!strcmp(getARG_PathBSD(var), "\0")) {
        puts("Path de saida BSD nao informado.");
        return 0;
    }

    if (ARG_POS_ib > -1) {
        FILE *DataCollect = fopen(getBED_DataCollectPath(var), "w");
        fprintf(DataCollect, "-ib");
        fclose(DataCollect);

        FILE *tempLOG = fopen(getBED_tempLog(var), "w");
        fprintf(tempLOG, " ");
        fclose(tempLOG);
    }
    if (ARG_POS_cb > -1) {
        FILE *DataCollect = fopen(getBED_DataCollectPath(var), "r");
        if (DataCollect != NULL) {
            fclose(DataCollect);
            DataCollect = fopen(getBED_DataCollectPath(var), "w");
            fprintf(DataCollect, "-cb");
            fclose(DataCollect);
        }
    }
    if (ARG_POS_fb > -1) {
        FILE *DataCollect = fopen(getBED_DataCollectPath(var), "r");
        if (DataCollect != NULL) {
            fclose(DataCollect);
            DataCollect = fopen(getBED_DataCollectPath(var), "w");
            fprintf(DataCollect, "-fb");
            fclose(DataCollect);
        }
    }


    return 1;

}

void VarInitialize(VAR var) {
    /*                            Initializing Paths                             */
    //                     Removing extension from ARG_* files                   //

    char *STRING = calloc(1, sizeof(char));
    STRING = realloc(STRING, strlen(getARG_geo(var)) + 1);
    strcpy(STRING, getARG_geo(var));
    int cont = 0, last = 0;
    if (STRING) {
        for (int i = 0; i < strlen(STRING); i++) {
            if (STRING[i] == '.')
                last = cont;
            cont++;
        }
    }  
    if (last) STRING[last] = '\0';
    setARG_geo(var, STRING);

    STRING = realloc(STRING, strlen(getARG_qry(var)) + 1);
    strcpy(STRING, getARG_qry(var));
    cont = 0, last = 0;
    if (STRING) {
        for (int i = 0; i < strlen(STRING); i++) {
            if (STRING[i] == '.')
                last = cont;
            cont++;
        }
    }  
    if (last) STRING[last] = '\0';
    setARG_qry(var, STRING);
    
    //                            BED_DataCollectPath                            //
    setBED_DataCollectPath(var, getARG_PathBSD(var));
    if (strcmp(getARG_PathBSD(var), "\0"))
        catBED_DataCollectPath(var, "/");
    catBED_DataCollectPath(var, "DataCollect.txt");

    //                                BED_tempLog                               //
    setBED_tempLog(var, getARG_PathBSD(var));
    if (strcmp(getARG_PathBSD(var), "\0"))
        catBED_tempLog(var, "/");
    catBED_tempLog(var, "tempLOG.txt");

    //                                BSD_LogGeo                                //
    if (strcmp(getARG_Log(var), "\0")) {
        STRING = realloc(STRING, strlen(getARG_PathBSD(var)) + strlen(getARG_Log(var)) + 10);
        if (strcmp(getARG_PathBSD(var), "\0")) sprintf(STRING, "%s/%s.geo", getARG_PathBSD(var), getARG_Log(var));
        else  sprintf(STRING, "%s.geo", getARG_Log(var));
    }
    setBSD_LogGeo(var, STRING);

    //                                BSD_LogSvg                                //
    if (strcmp(getARG_Log(var), "\0")) {
        STRING = realloc(STRING, strlen(getARG_PathBSD(var)) + strlen(getARG_Log(var)) + 10);
        if (strcmp(getARG_PathBSD(var), "\0")) sprintf(STRING, "%s/%s.svg", getARG_PathBSD(var), getARG_Log(var));
        else  sprintf(STRING, "%s.svg", getARG_Log(var));
    }
    setBSD_LogSvg(var, STRING);


    free(STRING);
    //                 Removing / from ARG_qry file case other DIR              //
    bool check = 0;
    char *auxS = calloc(strlen(getARG_qry(var)) + 1, sizeof(char));
    strcpy(auxS, getARG_qry(var));
    cont = 0, last = 0;
    for (int i = strlen(auxS) - 1; i >= 0; i--) {
        if (auxS[i] == '/') {
            check = 1;
            last = i;
            break;
        }
    }
    free(auxS);
    setARG_PathBED_qry(var, getARG_PathBED(var));
    if (check) {

        if (strcmp(getARG_PathBED(var), "\0"))
            catARG_PathBED_qry(var, "/");
        catARG_PathBED_qry(var, getARG_qry(var));

        char *auxS = calloc(strlen(getARG_PathBED_qry(var)) + 1, sizeof(char));
        strcpy(auxS, getARG_PathBED_qry(var));
        for (int i = strlen(auxS) - 1; i > 0; i--) {
            if (auxS[i] == '/') {
                auxS[i] = '\0';
                break;
            }
        }
        setARG_PathBED_qry(var, auxS);
        free(auxS);
        
        char *temporary = calloc(strlen(getARG_qry(var)) + 1, sizeof(char));
        strcpy(temporary, getARG_qry(var));
        
        int Last = 0;
        for (int i = strlen(temporary) - 1; i > 0; i--) {
            if (temporary[i] == '/') {
                Last = i;
                break;
            }
        }

        char *aux = calloc(strlen(temporary) + 1, sizeof(char));
        for (int i = Last + 1, j = 0; i < strlen(temporary), j < strlen(temporary) - Last -1; i++, j++)
            aux[j] = temporary[i];

        setARG_qry(var, aux);
        free(temporary);
        free(aux);
    }


    //                  Removing / from ARG_geo file case other DIR               //
    check = 0;
    char *AuxSTRING = calloc(strlen(getARG_geo(var)) + 1, sizeof(char));
    strcpy(AuxSTRING, getARG_geo(var));
    cont = 0, last = 0;
    for (int i = strlen(AuxSTRING) - 1; i >= 0; i--) {
        if (AuxSTRING[i] == '/') {
            check = 1;
            last = i;
            break;
        }
    }
    free(AuxSTRING);
    setARG_PathBED_geo(var, getARG_PathBED(var));
    if (check) {

        if (strcmp(getARG_PathBED(var), "\0"))
            catARG_PathBED_geo(var, "/");
        catARG_PathBED_geo(var, getARG_geo(var));

        char *AUXSTRING = calloc(strlen(getARG_PathBED_geo(var)) + 1, sizeof(char));
        strcpy(AUXSTRING, getARG_PathBED_geo(var));
        for (int i = strlen(AUXSTRING) - 1; i > 0; i--) {
            if (AUXSTRING[i] == '/') {
                AUXSTRING[i] = '\0';
                break;
            }
        }
        setARG_PathBED_geo(var, AUXSTRING);
        free(AUXSTRING);
        
        char *temporary = calloc(strlen(getARG_geo(var)) + 1, sizeof(char));
        strcpy(temporary, getARG_geo(var));
        
        int Last = 0;
        for (int i = strlen(temporary) - 1; i > 0; i--) {
            if (temporary[i] == '/') {
                Last = i;
                break;
            }
        }

        char *AUX = calloc(strlen(temporary) + 1, sizeof(char));
        for (int i = Last + 1, j = 0; i < strlen(temporary) + 1, j < strlen(temporary) - Last -1; i++, j++) 
            AUX[j] = temporary[i];
        

        setARG_geo(var, AUX);
        free(temporary);
        free(AUX);
    }

    //                                ArqConsTXT                                //
    char *Name = calloc(strlen(getARG_geo(var)) + strlen(getARG_qry(var)) + 2, sizeof(char));
    sprintf(Name, "%s-%s", getARG_geo(var), getARG_qry(var));
    char *STRING1 = calloc(strlen(getARG_PathBSD(var)) + strlen(Name) + 10, sizeof(char));
    if (strcmp(getARG_PathBSD(var), "\0")) sprintf(STRING1, "%s/%s.txt", getARG_PathBSD(var), Name);
    else  sprintf(STRING1, "%s.txt", Name);
    setArqConsTXT(var, STRING1);

    //                                ArqConsSVG                                //
    STRING1 = realloc(STRING1, strlen(getARG_PathBSD(var)) + strlen(Name) + 10);
    if (strcmp(getARG_PathBSD(var), "\0")) sprintf(STRING1, "%s/%s.svg", getARG_PathBSD(var), Name);
    else  sprintf(STRING1, "%s.svg", Name);
    setArqConsSVG(var, STRING1);
    free(Name);
    free(STRING1);

}

void createBSD(char *Directory) {

    char *path = calloc(strlen(Directory) + 1, sizeof(char));
    int index = 0;

    while (strcmp(path, Directory)) {
        *(path + index) = *(Directory + index);   // '/' atribution
        index++;
        while (*(Directory + index) != '/') {
            if (!*(Directory + index)) break;
            *(path + index) = *(Directory + index);
            index++;
        }
        
        mkdir(path, S_IRWXU);

    }
    free(path);

}

bool isArgument(char *string) {
    return((!strcmp(string, "-lse")) || (!strcmp(string, "-e")) || (!strcmp(string, "-f")) || (!strcmp(string, "-o")) || (!strcmp(string, "-q")) || (!strcmp(string, "-ib")) || (!strcmp(string, "-cb")) || (!strcmp(string, "-fb")));
}

