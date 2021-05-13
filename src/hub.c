#include "hub.h"
#include "voidpointers.h"
#include "Variables.h"
#include "Libraries.h"
#include "ListHeader.h"
#include "ItemStruct.h"
#include "TerminalInputs.h"
#include "FunctionsQRY.h"
#include "report.h"

//--------------------------SET PROCEDURES----------------------------
//               $~ Sets value to Item struct content ~$    
//-----------------------------Arguments------------------------------
//       StdItem <--  hides internal declaration of struct Item
//                     item <-- reference to Item
//                          Value to be set
void setItem_ID(StdItem item, char *string);
void setItem_FILL(StdItem item, char *string);
void setItem_STROKE(StdItem item, char *string);
void setItem_X(StdItem item, float value);
void setItem_Y(StdItem item, float value);
void setItem_W(StdItem item, float value);
void setItem_H(StdItem item, float value);
void setItem_OP_C(StdItem item, int value);
void setItem_OP_P(StdItem item, int value);
void setItem_show(StdItem item, int value);
//--------------------------------------------------------------------
//--------------------------SET PROCEDURES----------------------------
//             $~ Sets value to Variables struct content ~$    
//-----------------------------Arguments------------------------------
//       VAR <--  hides internal declaration of struct Variables
//                    var <-- reference to Variables
//                          Value to be set
void setCC(VAR var, char *string);
void setCP(VAR var, char *string);
void setDEF_SIZE(VAR var, long int num);
void ppVistis(VAR var, int num);
//------------------------------------------------------------------------

/*               File reading FUNCTION                */
bool fileRead(char *type, StdList Stdlist, VAR var) {
    StdList *list = Stdlist;
    
    if (!strcmp(type, "geo")) {

        char *BED_FileGeo = calloc(strlen(getARG_PathBED_geo(var)) + strlen(getARG_geo(var)) + 100, sizeof(char));
        if (strcmp(getARG_PathBED_geo(var), "\0")) sprintf(BED_FileGeo, "%s/%s.geo", getARG_PathBED_geo(var), getARG_geo(var));
        else  sprintf(BED_FileGeo, "%s.geo", getARG_geo(var));
        
        FILE *file = fopen(BED_FileGeo, "r");
        free(BED_FileGeo);

        if (file == NULL) {
            puts("Arquivo .geo nao encontrado.");
            return 0;
        }
        char *buff = calloc(100, sizeof(char));
        float *numBuff = calloc(4, sizeof(int));

        while (fscanf(file, "%s", buff) != -1) {
            if (!strcmp(buff, "nx")) {
                fscanf(file, "%f", numBuff);
        
                setDEF_SIZE(var, (long int)*numBuff);

            }else if (!strcmp(buff, "cc")) {
                fscanf(file, "%s", buff);
                setCC(var, buff);

            }else if (!strcmp(buff, "cp")) {
                fscanf(file, "%s", buff);
                setCP(var, buff);

            }else if (!strcmp(buff, "r")) {

                StdItem item;
                fscanf(file, "%s", buff);
                for (int i = 0; i < 4; i++) 
                    fscanf(file, "%f", (numBuff + i));

                item = createItem();
                setItem_ID(item, buff);
                setItem_X(item, numBuff[0]);
                setItem_Y(item, numBuff[1]);
                setItem_W(item, numBuff[2]);
                setItem_H(item, numBuff[3]);

                if (!strcmp(getCP(var), "@"))
                    setItem_OP_P(item, 0);
                else 
                    setItem_OP_P(item, 1);
                    
                if (!strcmp(getCC(var), "@"))
                    setItem_OP_C(item, 0);
                else 
                    setItem_OP_C(item, 1);

                setItem_FILL(item, getCP(var));
                setItem_STROKE(item, getCC(var));
                setItem_show(item, 1);
                
                insert(Stdlist, item); 


            }
        }
        fclose(file);
        free(buff);
        free(numBuff);

    }else if (!strcmp(type, "qry")){

        char *BED_FileQry = calloc(strlen(getARG_PathBED_qry(var)) + strlen(getARG_qry(var)) + 100, sizeof(char));
        if (strcmp(getARG_PathBED_qry(var), "\0")) sprintf(BED_FileQry, "%s/%s.qry", getARG_PathBED_qry(var), getARG_qry(var));
        else  sprintf(BED_FileQry, "%s.qry", getARG_qry(var));
        FILE *file = fopen(BED_FileQry, "r");
        free(BED_FileQry);

        if (file == NULL) {
            puts("Arquivo .qry nao encontrado.");
            return false;
        }
        char *buff = calloc(100, sizeof(char));
        float *numBuff = calloc(4, sizeof(int));

        while (fscanf(file, "%s", buff) != -1) {
            if (!strcmp(buff, "tp")) {
                functionTP(Stdlist, var);

            }else if (!strcmp(buff, "tpr")) {
                for (int i = 0; i < 4; i++)
                    fscanf(file, "%f", (numBuff + i));
                functionTPR(Stdlist, numBuff[0], numBuff[1], numBuff[2], numBuff[3], var);

            }else if (!strcmp(buff, "dpi")) {
                for (int i = 0; i < 2; i++)
                    fscanf(file, "%f", (numBuff + i));

                functionDPI(Stdlist, numBuff[0], numBuff[1], var);
            }else if (!strcmp(buff, "dr")) {
                fscanf(file, "%s", buff);

                functionDR(Stdlist, buff, var);
            }else if (!strcmp(buff, "bbi")) {
                for (int i = 0; i < 2; i++)
                    fscanf(file, "%f", (numBuff + i));

                functionBBI(Stdlist, numBuff[0], numBuff[1], var);
            }else if (!strcmp(buff, "bbid")) {
                fscanf(file, "%s", buff);

                functionBBID(Stdlist, buff, var);
            }else if (!strcmp(buff, "iid")) {
                fscanf(file, "%s", buff);
                fscanf(file, "%f", numBuff);

                functionIID(Stdlist, buff, *numBuff, var);
            }else if (!strcmp(buff, "diid")) {
                fscanf(file, "%s", buff);
                fscanf(file, "%f", numBuff);

                functionDIID(Stdlist, buff, *numBuff, var);
            }

        }
        fclose(file);
        free(buff);
        free(numBuff);

    }
    return 1;

}

/*                  cityOfRectangles                  */
void getNXfromgeo(VAR var) {

    char *BED_FileGeo = calloc(strlen(getARG_PathBED_geo(var)) + strlen(getARG_geo(var)) + 100, sizeof(char));
    if (strcmp(getARG_PathBED_geo(var), "\0")) sprintf(BED_FileGeo, "%s/%s.geo", getARG_PathBED_geo(var), getARG_geo(var));
    else  sprintf(BED_FileGeo, "%s.geo", getARG_geo(var));
    
    FILE *file = fopen(BED_FileGeo, "r");
    free(BED_FileGeo);

    if (file == NULL) return;
    
    char *buff = calloc(100, sizeof(char));
    long int numBuff;

    while (fscanf(file, "%s", buff) != -1) {
        if (!strcmp(buff, "nx")) {
            fscanf(file, "%ld", &numBuff);
            setDEF_SIZE(var, numBuff);

        }
    }
    fclose(file);
    free(buff);

}

void cityOfRectangles(VAR var) {

    getNXfromgeo(var);
    StdList Stdlist = createList(getDEF_SIZE(var));
    /*                running code                */
    long int originalSize = 0;
    bool Working;
    
    Working = fileRead("geo", Stdlist, var);
    if (Working) GEOSvgPrint(Stdlist, var);
    
    originalSize = length(Stdlist);
    
    if (strcmp(getARG_qry(var), "\0")) {
        Working = fileRead("qry", Stdlist, var);
        if (Working) QRYSvgPrint(Stdlist, var);
    }

    LOG_Core(originalSize, getListVisits(Stdlist) + getVisits(var), var);
    
    freeList(Stdlist);
    /*--------------------------------------------*/

}

/*                  Geo svg printing                  */
void GEOSvgPrint(StdList Stdlist, VAR var) {

    char *Path = calloc(strlen(getARG_geo(var)) + strlen(getARG_PathBSD(var)) + 100, sizeof(char));
    if (strcmp(getARG_PathBSD(var), "\0")) sprintf(Path, "%s/%s.svg", getARG_PathBSD(var), getARG_geo(var));
    else  sprintf(Path, "%s.svg", getARG_geo(var));
    
    FILE *file = fopen(Path, "w+");

    StdItem *item;
    fprintf(file, "<svg>\n\t");

    StdNode pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    bool opacity;
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        opacity = (getItem_OP_C(item) || getItem_OP_P(item));
        fprintf(file, "<g>\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" stroke-opacity=\"%d\" stroke-width=\"0.5\" fill=\"%s\" fill-opacity=\"%d\"></rect>\n\t<text x=\"%f\" y=\"%f\" font-size=\"3\" font-weight=\"bold\" fill-opacity=\"%d\" alignment-baseline=\"middle\" text-anchor=\"middle\">%s</text>\n</g>\n", getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_STROKE(item), getItem_OP_C(item), getItem_FILL(item), getItem_OP_P(item), getItem_X(item) + 0.5*(getItem_W(item)), getItem_Y(item) + 0.5*(getItem_H(item)), opacity, getItem_ID(item));
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }


    fprintf(file, "</svg>");
    fclose(file);
    free(Path);
}

/*                  Qry svg printing                  */
void QRYSvgPrint(StdList Stdlist, VAR var) { 

    char *BED_FileQry = calloc(strlen(getARG_PathBED(var)) + strlen(getARG_qry(var)) + 100, sizeof(char));
    if (strcmp(getARG_PathBED_qry(var), "\0")) sprintf(BED_FileQry, "%s/%s.qry", getARG_PathBED_qry(var), getARG_qry(var));
    else  sprintf(BED_FileQry, "%s.qry", getARG_qry(var));

    FILE *file = fopen(BED_FileQry, "r");
    if (file == NULL) {
        puts("Arquivo .qry nao encontrado.");
        free(BED_FileQry);
        return;
    }
    fclose(file);
    free(BED_FileQry);

    FILE *QRYresult = fopen(getArqConsSVG(var), "w+");
    fprintf(QRYresult, "<svg>\n\t");

    StdItem *item;
    StdNode *pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        fprintf(QRYresult, "<g>\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" stroke-opacity=\"%d\" stroke-width=\"0.5\" fill=\"%s\" fill-opacity=\"%d\" opacity=\"%d\"></rect>\n\t<text x=\"%f\" y=\"%f\" font-size=\"3\" font-weight=\"bold\" opacity=\"%d\" alignment-baseline=\"middle\" text-anchor=\"middle\">%s</text>\n</g>\n", getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_STROKE(item), getItem_OP_C(item), getItem_FILL(item), getItem_OP_P(item), getItem_show(item), getItem_X(item) + 0.5*(getItem_W(item)), getItem_Y(item) + 0.5*(getItem_H(item)), getItem_show(item), getItem_ID(item));
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }


    char *tempQRY = calloc(strlen(getARG_PathBSD(var)) + strlen("tempQRY") + 100, sizeof(char));
    if (strcmp(getARG_PathBSD(var), "\0")) sprintf(tempQRY, "%s/%s.txt", getARG_PathBSD(var), "tempQRY");
    else  sprintf(tempQRY, "%s.txt", "tempQRY");
    FILE *tempQRYsvg = fopen(tempQRY, "r");
    char *buff = calloc(200, sizeof(char));
    if (tempQRYsvg != NULL) {
        while (!feof(tempQRYsvg)) {
            fgets(buff, 200, tempQRYsvg);
            fprintf(QRYresult, "%s", buff);
        }
        fclose(tempQRYsvg);
        remove(tempQRY);
    }
    
    fprintf(QRYresult, "</svg>");
    free(tempQRY);
    free(buff);
    fclose(QRYresult);
}