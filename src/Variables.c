#include "Libraries.h"
#include "Variables.h"

typedef struct variables {

    //Stores position in Color matrix
    int color;

    //Input files names
    char *ARG_PathBED;
    char *ARG_PathBED_qry;
    char *ARG_PathBED_geo;
    char *ARG_PathBSD;
    char *ARG_geo;
    char *ARG_qry;
    char *ARG_Log;
    char *ARG_title;

    //Files paths
    char *BED_DataCollectPath;
    char *BED_tempLog;
    char *BSD_LogGeo;
    char *BSD_LogSvg;
    char *ArqConsTXT;
    char *ArqConsSVG;

    /*                     cityOfRectangles                     */
    //Stroke and fill colors informed via .geo
    char *CC;
    char *CP;

    /*                        STATIC LIST                        */
    //Stores max size of static list informed by nx geo command
    long int DEF_SIZE;

    /*                        BOTH LISTS                         */
    //Stores list visits to be used on report module
    int visits;

}Variables;

void memoryFree(VAR var) {
    Variables *variables = var;

    free(variables->ARG_PathBED);
    free(variables->ARG_PathBED_qry);
    free(variables->ARG_PathBED_geo);
    free(variables->ARG_PathBSD);
    free(variables->ARG_geo);
    free(variables->ARG_qry);
    free(variables->ARG_Log);
    free(variables->ARG_title);

    free(variables->BED_DataCollectPath);
    free(variables->BED_tempLog);
    free(variables->BSD_LogGeo);
    free(variables->BSD_LogSvg);
    free(variables->ArqConsTXT);
    free(variables->ArqConsSVG);

    free(variables->CC);
    free(variables->CP);

    free(var);
}

VAR createVAR() {
    Variables *variables = calloc (1, sizeof(Variables));

    variables->ARG_PathBED = calloc (1, sizeof(char));
    variables->ARG_PathBED_qry = calloc (1, sizeof(char));
    variables->ARG_PathBED_geo = calloc (1, sizeof(char));
    variables->ARG_PathBSD = calloc (1, sizeof(char));
    variables->ARG_geo = calloc (1, sizeof(char));
    variables->ARG_qry = calloc (1, sizeof(char));
    variables->ARG_Log = calloc (1, sizeof(char));
    variables->ARG_title = calloc (1, sizeof(char));

    variables->BED_DataCollectPath = calloc (1, sizeof(char));
    variables->BED_tempLog = calloc (1, sizeof(char));
    variables->BSD_LogGeo = calloc (1, sizeof(char));
    variables->BSD_LogSvg = calloc (1, sizeof(char));
    variables->ArqConsTXT = calloc (1, sizeof(char));
    variables->ArqConsSVG = calloc (1, sizeof(char));

    variables->CC = calloc (1, sizeof(char));
    variables->CP = calloc (1, sizeof(char));

    variables->DEF_SIZE = 0;
    variables->visits = 0;
    variables->color = 0;

    return (variables);

}

char *getARG_PathBED(VAR var) {
    Variables *variables = var;
    return (variables->ARG_PathBED);
}

char *getARG_PathBED_qry(VAR var) {
    Variables *variables = var;
    return (variables->ARG_PathBED_qry);
}

char *getARG_PathBED_geo(VAR var) {
    Variables *variables = var;
    return (variables->ARG_PathBED_geo);
}

char *getARG_PathBSD(VAR var) {
    Variables *variables = var;
    return (variables->ARG_PathBSD);
}

char *getARG_geo(VAR var) {
    Variables *variables = var;
    return (variables->ARG_geo);
}

char *getARG_qry(VAR var) {
    Variables *variables = var;
    return (variables->ARG_qry);
}

char *getARG_Log(VAR var) {
    Variables *variables = var;
    return (variables->ARG_Log);
}

char *getARG_title(VAR var) {
    Variables *variables = var;
    return (variables->ARG_title);
}

char *getBED_DataCollectPath(VAR var) {
    Variables *variables = var;
    return (variables->BED_DataCollectPath);
}

char *getBED_tempLog(VAR var) {
    Variables *variables = var;
    return (variables->BED_tempLog);
}

char *getBSD_LogGeo(VAR var) {
    Variables *variables = var;
    return (variables->BSD_LogGeo);
}

char *getBSD_LogSvg(VAR var) {
    Variables *variables = var;
    return (variables->BSD_LogSvg);
}

char *getArqConsTXT(VAR var) {
    Variables *variables = var;
    return (variables->ArqConsTXT);
}

char *getArqConsSVG(VAR var) {
    Variables *variables = var;
    return (variables->ArqConsSVG);
}

char *getCC(VAR var) {
    Variables *variables = var;
    return (variables->CC);
}

char *getCP(VAR var) {
    Variables *variables = var;
    return (variables->CP);
}

long int getDEF_SIZE(VAR var) {
    Variables *variables = var;
    return (variables->DEF_SIZE);
}

int getVisits(VAR var) {
    Variables *variables = var;
    return (variables->visits);
}

int getColor(VAR var) {
    Variables *variables = var;
    return(variables->color);
}

void setARG_PathBED(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED = realloc(variables->ARG_PathBED, strlen(string) + 1);
    strcpy(variables->ARG_PathBED, string);
}

void setARG_PathBED_qry(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED_qry = realloc(variables->ARG_PathBED_qry, strlen(string) + 1);
    strcpy(variables->ARG_PathBED_qry, string);
}

void setARG_PathBED_geo(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED_geo = realloc(variables->ARG_PathBED_geo, strlen(string) + 1);
    strcpy(variables->ARG_PathBED_geo, string);
}

void setARG_PathBSD(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBSD = realloc(variables->ARG_PathBSD, strlen(string) + 1);
    strcpy(variables->ARG_PathBSD, string);
}

void setARG_geo(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_geo = realloc(variables->ARG_geo, strlen(string) + 1);    
    strcpy(variables->ARG_geo, string);
}

void setARG_qry(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_qry = realloc(variables->ARG_qry, strlen(string) + 1);    
    strcpy(variables->ARG_qry, string);
}

void setARG_Log(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_Log = realloc(variables->ARG_Log, strlen(string) + 1);    
    strcpy(variables->ARG_Log, string);
}

void setARG_title(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_title = realloc(variables->ARG_title, strlen(string) + 1);    
    strcpy(variables->ARG_title, string);
}

void setBED_DataCollectPath(VAR var, char *string) {
    Variables *variables = var;
    variables->BED_DataCollectPath = realloc(variables->BED_DataCollectPath, strlen(string) + 1);    
    strcpy(variables->BED_DataCollectPath, string);
}

void setBED_tempLog(VAR var, char *string) {
    Variables *variables = var;
    variables->BED_tempLog = realloc(variables->BED_tempLog, strlen(string) + 1);    
    strcpy(variables->BED_tempLog, string);
}

void setBSD_LogGeo(VAR var, char *string) {
    Variables *variables = var;
    variables->BSD_LogGeo = realloc(variables->BSD_LogGeo, strlen(string) + 1);    
    strcpy(variables->BSD_LogGeo, string);

}

void setBSD_LogSvg(VAR var, char *string) {
    Variables *variables = var;
    variables->BSD_LogSvg = realloc(variables->BSD_LogSvg, strlen(string) + 1);    
    strcpy(variables->BSD_LogSvg, string);
}

void setArqConsTXT(VAR var, char *string) {
    Variables *variables = var;
    variables->ArqConsTXT = realloc(variables->ArqConsTXT, strlen(string) + 1);    
    strcpy(variables->ArqConsTXT, string);

}

void setArqConsSVG(VAR var, char *string) {
    Variables *variables = var;
    variables->ArqConsSVG = realloc(variables->ArqConsSVG, strlen(string) + 1);    
    strcpy(variables->ArqConsSVG, string);
}

void setCC(VAR var, char *string) {
    Variables *variables = var;
    variables->CC = realloc(variables->CC, strlen(string) + 1);    
    strcpy(variables->CC, string);
}

void setCP(VAR var, char *string) {
    Variables *variables = var;
    variables->CP = realloc(variables->CP, strlen(string) + 1);    
    strcpy(variables->CP, string);
}   

void catARG_PathBED(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED = realloc(variables->ARG_PathBED, strlen(string) + strlen(variables->ARG_PathBED) + 1);    
    strcat(variables->ARG_PathBED, string);
}

void catARG_PathBED_qry(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED_qry = realloc(variables->ARG_PathBED_qry, strlen(string) + strlen(variables->ARG_PathBED_qry) + 1);    
    strcat(variables->ARG_PathBED_qry, string);
}

void catARG_PathBED_geo(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBED_geo = realloc(variables->ARG_PathBED_geo, strlen(string) + strlen(variables->ARG_PathBED_geo) + 1);    
    strcat(variables->ARG_PathBED_geo, string);
}

void catARG_PathBSD(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_PathBSD = realloc(variables->ARG_PathBSD, strlen(string) + strlen(variables->ARG_PathBSD) + 1);    
    strcat(variables->ARG_PathBSD, string);
}

void catARG_geo(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_geo = realloc(variables->ARG_geo, strlen(string) + strlen(variables->ARG_geo) + 1);    
    strcat(variables->ARG_geo, string);
}

void catARG_qry(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_qry = realloc(variables->ARG_qry, strlen(string) + strlen(variables->ARG_qry) + 1);    
    strcat(variables->ARG_qry, string);
}

void catARG_Log(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_Log = realloc(variables->ARG_Log, strlen(string) + strlen(variables->ARG_Log) + 1);    
    strcat(variables->ARG_Log, string);
}

void catARG_title(VAR var, char *string) {
    Variables *variables = var;
    variables->ARG_title = realloc(variables->ARG_title, strlen(string) + strlen(variables->ARG_title) + 1);    
    strcat(variables->ARG_title, string);
}

void catBED_DataCollectPath(VAR var, char *string) {
    Variables *variables = var;
    variables->BED_DataCollectPath = realloc(variables->BED_DataCollectPath, strlen(string) + strlen(variables->BED_DataCollectPath) + 1);    
    strcat(variables->BED_DataCollectPath, string);
}

void catBED_tempLog(VAR var, char *string) {
    Variables *variables = var;
    variables->BED_tempLog = realloc(variables->BED_tempLog, strlen(string) + strlen(variables->BED_tempLog) + 1);    
    strcat(variables->BED_tempLog, string);
}

void catBSD_LogGeo(VAR var, char *string) {
    Variables *variables = var;
    variables->BSD_LogGeo = realloc(variables->BSD_LogGeo, strlen(string) + strlen(variables->BSD_LogGeo) + 1);    
    strcat(variables->BSD_LogGeo, string);

}

void catBSD_LogSvg(VAR var, char *string) {
    Variables *variables = var;
    variables->BSD_LogSvg = realloc(variables->BSD_LogSvg, strlen(string) + strlen(variables->BSD_LogSvg) + 1);    
    strcat(variables->BSD_LogSvg, string);
}

void catArqConsTXT(VAR var, char *string) {
    Variables *variables = var;
    variables->ArqConsTXT = realloc(variables->ArqConsTXT, strlen(string) + strlen(variables->ArqConsTXT) + 1);    
    strcat(variables->ArqConsTXT, string);

}

void catArqConsSVG(VAR var, char *string) {
    Variables *variables = var;
    variables->ArqConsSVG = realloc(variables->ArqConsSVG, strlen(string) + strlen(variables->ArqConsSVG) + 1);    
    strcat(variables->ArqConsSVG, string);
}

void catCC(VAR var, char *string) {
    Variables *variables = var;
    variables->CC = realloc(variables->CC, strlen(string) + strlen(variables->CC) + 1);    
    strcat(variables->CC, string);
}

void catCP(VAR var, char *string) {
    Variables *variables = var;
    variables->CP = realloc(variables->CP, strlen(string) + strlen(variables->CP) + 1);    
    strcat(variables->CP, string);
} 

void setDEF_SIZE(VAR var, long int num) {
    Variables *variables = var;
    variables->DEF_SIZE = num;
}

void ppVistis(VAR var, int num) {
    Variables *variables = var;
    variables->visits += num;
}

void ppColor(VAR var) {
    Variables *variables = var;
    if (variables->color < 9) variables->color++;
    else variables->color = 0;
}
