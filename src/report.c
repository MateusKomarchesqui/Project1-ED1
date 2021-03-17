#include "report.h"
#include "Variables.h"
#include "voidpointers.h"

//--------------------------SET PROCEDURES----------------------------
//             $~ Sets value to Variables struct content ~$    
//-----------------------------Arguments------------------------------
//       VAR <--  hides internal declaration of struct Variables
//                    var <-- reference to Variables
//                          Value to be set
void setARG_qry(VAR var, char *string);
void ppVistis(VAR var, int num);
//------------------------------------------------------------------------

/*                  REPORT FUNCTIONS                  */
void createListLog(int size, int visits, VAR var) {

    FILE *logFile = fopen(getBSD_LogGeo(var), "w");
    fprintf(logFile, "|========\\\\Coleta de Dados//========|\n");
    fprintf(logFile, "| arquivo.qry |  Tamanho  | Visitas |\n\n");
    fclose(logFile); 

    int MaxSize = 0, MaxVisits = 0;
    logFile = fopen(getBSD_LogGeo(var), "a+");
    FILE *tempLOG = fopen(getBED_tempLog(var), "r");

    char *buff = calloc(100, sizeof(char));
    while (fscanf(tempLOG, "%s", buff) != -1) {
        fscanf(tempLOG, "%s", buff);
        if (atoi(buff) > MaxSize) MaxSize = atoi(buff);
        fscanf(tempLOG, "%s", buff);
        if (atoi(buff) > MaxVisits) MaxVisits = atoi(buff);
    }
    rewind(tempLOG);

    while (fgets(buff, 100, tempLOG))
        fprintf(logFile, "%s\n", buff);
    
    
    fclose(logFile);
    fclose(tempLOG);
    free(buff);
    remove(getBED_tempLog(var));
    remove (getBED_DataCollectPath(var));

    createGraph(MaxSize, MaxVisits, var);
}

void inputGraphStats(int Xproportion, int Yproportion, VAR var) {
    
    FILE *logFile = fopen(getBSD_LogGeo(var), "r");
    if (logFile == NULL) {
        puts("arquivo Log.geo nao existe.");
        return;
    }
    char *buff = calloc(100, sizeof(char));
    FILE *logGraph = fopen(getBSD_LogSvg(var), "a+");
    fseek(logGraph, 0, SEEK_END);

    fprintf(logGraph, "<g class=\"data\" data-setname=\"Log\">\n\t");
    float x, y, AUX;
    
    fseek(logFile, ftell_logFile, SEEK_SET);
    
    while (fscanf(logFile, "%s", buff) != -1) {
        fscanf(logFile, "%s", buff);
        AUX = atoi(buff);
        x = 100 + ((AUX/Xproportion)*100);

        fscanf(logFile, "%s", buff);
        AUX = atoi(buff);
        y = 1100 - ((AUX/Yproportion)*100);

        fprintf(logGraph, "<line x1=\"%d\" x2=\"%d\" y1=\"1100\" y2=\"%d\" stroke=\"red\" stroke-width=\"2\" stroke-dasharray=\"5\"></line>\n\t<line x1=\"100\" x2=\"%d\" y1=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"2\" stroke-dasharray=\"5\"></line>\n\t<circle cx=\"%d\" cy=\"%d\" data-value=\"7.2\" r=\"4\" style = \"stroke : black\"></circle>\n", (int)x, (int)x, (int)y, (int)x, (int)y, (int)y, (int)x, (int)y);

    }
 
    fprintf(logGraph, "</g>\n\n");
    fprintf(logGraph, "</svg>");
    free(buff);
    fclose(logFile);
    fclose(logGraph);

}

void createGraph(int size, int visits, VAR var) {

    FILE *logGraph = fopen(getBSD_LogSvg(var), "w");
    //header
    fprintf(logGraph, "<svg viewBox=\"0 0 2200 1200\">\n<rect width=\"100%%\" height=\"100%%\" fill=\"#e1A141\"/>\n\n");
    fprintf(logGraph, "<g class=\"eixo X\" id=\"eixoX\">\n\t<line x1=\"90\" x2=\"2100\" y1=\"1100\" y2=\"1100\" style = \"stroke : black\"></line>\n</g>\n");
    fprintf(logGraph, "<g class=\"eixo Y\" id=\"eixoY\">\n\t<line x1=\"100\" x2=\"100\" y1=\"100\" y2=\"1110\" style = \"stroke : black\"></line>\n</g>\n\n");
    
    //X axis
    int Xsize = 100;
    if (size > 100) Xsize = size + 100;
    fprintf(logGraph, "<g class=\"divisoes eixoX\">\n\t");
    for (int i = 200; i <= 2100; i += 100)
        fprintf(logGraph, "<line x1=\"%d\" x2=\"%d\" y1=\"1090\" y2=\"1100\" style = \"stroke : black\"></line>\n\t", i, i);
    
    fprintf(logGraph, "<text x=\"90\" y=\"1115\" font-size=\"15\">0</text>\n\t");
    for (int i = 300, j = (Xsize/10); i <= 2100, j <= Xsize; i += 200, j += (Xsize/10))
        fprintf(logGraph, "<text x=\"%d\" y=\"1115\" font-size=\"15\">%d</text>\n\t", i, j);

    fprintf(logGraph, "<text x=\"1000\" y=\"60\" class=\"label-title\" font-size=\"25\" font-weight=\"bold\">%s</text>\n", getARG_title(var));
    fprintf(logGraph, "<text x=\"1000\" y=\"1130\" class=\"label-title\" font-size=\"15\" font-weight=\"bold\">Tamanho</text>\n</g>\n\n");

    //Y axis
    int Ysize = 200;
    if (visits > 200) Ysize = visits;
    fprintf(logGraph, "<g class=\"divisoes eixoY\">\n\t");
    for (int i = 100; i <= 1050; i += 50)
        fprintf(logGraph, "<line x1=\"100\" x2=\"110\" y1=\"%d\" y2=\"%d\" style = \"stroke : black\"></line>\n\t", i, i);
    for (int i = 100, j = Ysize; i <= 1000, j >= (Ysize/10); i += 100, j -= (Ysize/10))
        fprintf(logGraph, "<text x=\"70\" y=\"%d\" font-size=\"15\">%d</text>\n\t", i, j);
    fprintf(logGraph, "<text x=\"30\" y=\"550\" class=\"label-title\" font-size=\"15\" font-weight=\"bold\">Visitas</text>\n</g>\n\n");

    fclose(logGraph);
    inputGraphStats((Xsize/20), (Ysize/10), var);

}

void LOG_Core(int size, int visits, VAR var) {

    char *buff = calloc(4, sizeof(char));
    if (!strcmp(getARG_qry(var), "\0")) 
        setARG_qry(var, "None");
    
    FILE *DataCollect = fopen(getBED_DataCollectPath(var), "r"), *tempLOG;
    if (DataCollect != NULL) {
        fscanf(DataCollect, "%s", buff);

        if (!strcmp(buff, "-ib")) {
            
            tempLOG = fopen(getBED_tempLog(var), "w");
            fprintf(tempLOG, "%s %d %d\n", getARG_qry(var), size, visits);
            fclose(tempLOG);

        }else if (!strcmp(buff, "-cb")) {
            
            tempLOG = fopen(getBED_tempLog(var), "a+");
            fprintf(tempLOG, "%s %d %d\n", getARG_qry(var), size, visits);
            fclose(tempLOG);

            FILE *DataCollect = fopen(getBED_DataCollectPath(var), "w");
            fprintf(DataCollect, " ");
            fclose(DataCollect);

        }else if (!strcmp(buff, "-fb")) {
            
            tempLOG = fopen(getBED_tempLog(var), "a+");
            fprintf(tempLOG, "%s %d %d\n", getARG_qry(var), size, visits);
            fclose(tempLOG);
            
            createListLog(size, visits, var);
        }
        fclose(DataCollect);
    }

    free(buff);
}
