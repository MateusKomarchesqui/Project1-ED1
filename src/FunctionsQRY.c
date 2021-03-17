#include "ItemStruct.h"
#include "Variables.h"
#include "voidpointers.h"
#include "ListHeader.h"
#include "Libraries.h"
#include "FunctionsQRY.h"
#include "TerminalInputs.h"

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
void ppVistis(VAR var, int num);
void ppColor(VAR var);
//---------------------------------------------------------------------

/*               File.qry FUNCTIONS               */
typedef struct point {
    float x;
    float y;
}   Point;

/*---------------------------------------------------------------------------*/

float Greatter(float a, float b) {
    return (a > b) ? a : b;
}

float Lesser(float a, float b) {
    return (a < b) ? a : b;
}

bool onLineSeg(st_point sP, st_point sQ, st_point sR) {

    Point *p = sP, *q = sQ, *r = sR;
    if (q->x <= Greatter(p->x, r->x) && q->x >= Lesser(p->x, r->x) && q->y <= Greatter(p->y, r->y) && q->y >= Lesser(p->y, r->y)) return 1;
    return 0;
}

int angleCoef(st_point sP, st_point sQ, st_point sR) { 

    Point *p = sP, *q = sQ, *r = sR;
    float value = (q->y - p->y) * (r->x - q->x) - (q->x - p->x) * (r->y - q->y); 

    if (value == 0) return 0;  
    if (value > 0) return 1;
    if (value < 0) return 2;
} 

bool SegIntersect(st_point sP1, st_point sQ1, st_point sP2, st_point sQ2) { 

    int angle1 = angleCoef(sP1, sQ1, sP2); 
    int angle2 = angleCoef(sP1, sQ1, sQ2); 
    int angle3 = angleCoef(sP2, sQ2, sP1); 
    int angle4 = angleCoef(sP2, sQ2, sQ1); 

    if (angle1 != angle2 && angle3 != angle4) return 1; 
    if (angle1 == 0 && onLineSeg(sP1, sP2, sQ1)) return 1; 
    if (angle2 == 0 && onLineSeg(sP1, sQ2, sQ1)) return 1; 
    if (angle3 == 0 && onLineSeg(sP2, sP1, sQ2)) return 1; 
    if (angle4 == 0 && onLineSeg(sP2, sQ1, sQ2)) return 1; 
  
    return 0;
} 

int rectIntersect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {

    Point A1, A2; //anchor
    A1.x = x1, A1.y = y1, A2.x = x2, A2.y = y2;

    Point B1, B2; //width
    B1.x = x1 + w1, B1.y = y1, B2.x = x2 + w2, B2.y = y2;

    Point C1, C2; //height
    C1.x = x1, C1.y = y1 + h1, C2.x = x2, C2.y = y2 + h2;

    Point D1, D2; //oposite to anchor
    D1.x = x1 + w1, D1.y = y1 + h1, D2.x = x2 + w2, D2.y = y2 + h2;

    if ((A2.x >= A1.x && B2.x <= B1.x) && (A1.y <= A2.y && C1.y >= C2.y)) return 2;
    if ((A1.x >= A2.x && B1.x <= B2.x) && (A2.y <= A1.y && C2.y >= C1.y)) return 3;

    bool intersect = 0;

    st_point a1 = &A1, a2 = &A2;
    st_point b1 = &B1, b2 = &B2;
    st_point c1 = &C1, c2 = &C2;
    st_point d1 = &D1, d2 = &D2;

    //compare a1~b1 with all other #2 segments
    intersect = SegIntersect(a1, b1, a2, b2); if (intersect) return 1;
    intersect = SegIntersect(a1, b1, b2, d2); if (intersect) return 1;
    intersect = SegIntersect(a1, b1, c2, d2); if (intersect) return 1;
    intersect = SegIntersect(a1, b1, a2, c2); if (intersect) return 1;
    //compara b1~d1 with all other #2 segments
    intersect = SegIntersect(b1, d1, a2, b2); if (intersect) return 1;
    intersect = SegIntersect(b1, d1, b2, d2); if (intersect) return 1;
    intersect = SegIntersect(b1, d1, c2, d2); if (intersect) return 1;
    intersect = SegIntersect(b1, d1, a2, c2); if (intersect) return 1;
    //compara c1~d1 with all other #2 segments
    intersect = SegIntersect(c1, d1, a2, b2); if (intersect) return 1;
    intersect = SegIntersect(c1, d1, b2, d2); if (intersect) return 1;
    intersect = SegIntersect(c1, d1, c2, d2); if (intersect) return 1;
    intersect = SegIntersect(c1, d1, a2, c2); if (intersect) return 1;
    //compara a1~c1 with all other #2 segments
    intersect = SegIntersect(a1, c1, a2, b2); if (intersect) return 1;
    intersect = SegIntersect(a1, c1, b2, d2); if (intersect) return 1;
    intersect = SegIntersect(a1, c1, c2, d2); if (intersect) return 1;
    intersect = SegIntersect(a1, c1, a2, c2); if (intersect) return 1;

    if (!intersect) return 0;

}

void functionTP(StdList Stdlist, VAR var) {
    
    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\TP//========|\n");
    char SVG_Colors[10][15] = {"darkkhaki", "crimson", "indigo", "lawngreen", "skyblue", "hotpink", "lightcyan", "seagreen", "thistle", "tan"};
    StdItem item, item1, item2;
    StdList *list = Stdlist;
    StdNode *pointer = getFirst(Stdlist), *nextPointer = getNext(Stdlist, pointer);
    ppVistis(var, 2);
    while (pointer != NULL) {

        item = get(Stdlist, pointer);
        setItem_show(item, 0);
        pointer = getNext(Stdlist, pointer);

        ppVistis(var, 1);
    }
    pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    for (int i = 0; i < length(Stdlist) - 1; i++) {
        item1 = get(Stdlist, pointer);
        for (int j = i + 1; j < length(Stdlist); j++) { 
            item2 = get(Stdlist, nextPointer);  
            if (rectIntersect(getItem_X(item1), getItem_Y(item1), getItem_W(item1), getItem_H(item1), getItem_X(item2), getItem_Y(item2), getItem_W(item2), getItem_H(item2))) {
                fprintf(file, "%s/%s\n", getItem_ID(item1), getItem_ID(item2));
                setItem_FILL(item1, SVG_Colors[getColor(var)]);
                setItem_FILL(item2, SVG_Colors[getColor(var)]);
                setItem_show(item1, 1);
                setItem_show(item2, 1);

                setItem_OP_C(item1, 1);
                setItem_OP_C(item2, 1);

                setItem_OP_P(item1, 1);
                setItem_OP_P(item2, 1);

                ppColor(var);
            }
            if (getNext(Stdlist, nextPointer) != NULL) {
                nextPointer = getNext(Stdlist, nextPointer);
                ppVistis(var, 1);
            }
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
        if (getNext(Stdlist, pointer) != NULL) {
            nextPointer = getNext(Stdlist, pointer);
            ppVistis(var, 1);
        }
    }

    
    fprintf(file, "\n");
    fclose(file);
}

void functionTPR(StdList Stdlist, float x, float y, float w, float h, VAR var) {
    
    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\TPR//========|\n");

    StdItem *item1, *item2;
    StdNode *pointer = getFirst(Stdlist), *nextPointer = getNext(Stdlist, pointer);
    char SVG_Colors[10][15] = {"darkkhaki", "crimson", "indigo", "lawngreen", "skyblue", "hotpink", "lightcyan", "seagreen", "thistle", "tan"};
    ppVistis(var, 2);
    while (pointer != NULL) {
        item1 = get(Stdlist, pointer);
        setItem_show(item1, 0);
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }
    pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    for (int i = 0; i < length(Stdlist) - 1; i++) {
        item1 = get(Stdlist, pointer);
        for (int j = i + 1; j < length(Stdlist); j++) {   
            item2 = get(Stdlist, nextPointer);
            if (rectIntersect(getItem_X(item1), getItem_Y(item1), getItem_W(item1), getItem_H(item1), getItem_X(item2), getItem_Y(item2), getItem_W(item2), getItem_H(item2)) && rectIntersect(getItem_X(item1), getItem_Y(item1), getItem_W(item1), getItem_H(item1), x, y, w, h) == 3 && (rectIntersect(getItem_X(item2), getItem_Y(item2), getItem_W(item2), getItem_H(item2), x, y, w, h) == 3)) {
                fprintf(file, "%s/%s\n", getItem_ID(item1), getItem_ID(item2));
                setItem_FILL(item1, SVG_Colors[getColor(var)]);
                setItem_FILL(item2, SVG_Colors[getColor(var)]);
                setItem_show(item1, 1);
                setItem_show(item2, 1);

                setItem_OP_C(item1, 1);
                setItem_OP_C(item2, 1);

                setItem_OP_P(item1, 1);
                setItem_OP_P(item2, 1);

                ppColor(var);
            }
            if (getNext(Stdlist, nextPointer) != NULL) {
                nextPointer = getNext(Stdlist, nextPointer);
                ppVistis(var, 1);
            }
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
        if (getNext(Stdlist, pointer) != NULL) {
            nextPointer = getNext(Stdlist, pointer);
            ppVistis(var, 1);
        }
    }

    fprintf(file, "\n");
    fclose(file);
    
}

bool isInternal(float x, float y, float w, float h, st_point P) {

    Point *point = P;
    return ((point->x >= x) && (point->x <= x + w) && (point->y >= y) && (point->y <= y + h));

}

void functionDPI(StdList Stdlist, float x, float y, VAR var) {
   
    Point point;
    point.x = x, point.y = y;
    st_point P = &point;

    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\DPI//========|\n");
    StdNode *pointer = getFirst(Stdlist);
    StdNode *auxPointer;
    ppVistis(var, 1);
    StdItem *item;

    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (isInternal(getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), P)) {
            fprintf(file, "%s\n", getItem_ID(item));
            auxPointer = pointer;
            pointer = getNext(Stdlist, pointer);
            erase(Stdlist, auxPointer);
        }else 
            pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }

    fprintf(file, "\n");
    fclose(file);

}

void functionDR(StdList Stdlist, char *id, VAR var) {

    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\DR//========|\n");
    bool Verifier = 0;
    StdNode *pointer = getFirst(Stdlist), *AUX, *auxPointer;
    ppVistis(var, 1);

    StdItem *item, *item2;

    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (!strcmp(id, getItem_ID(item))) {
            Verifier = 1;
            AUX = pointer;
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }
    if (!Verifier) {
        fprintf(file, "ID inexistente.\n");
        fclose(file);   
        return;
    }
    pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        item2 = get(Stdlist, AUX);
        if (strcmp(getItem_ID(item), id)) {
            if (rectIntersect(getItem_X(item2), getItem_Y(item2), getItem_W(item2), getItem_H(item2), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item)) == 2) {
                fprintf(file, "%s\n", getItem_ID(item)); 
                auxPointer = pointer;
                pointer = getNext(Stdlist, pointer);
                erase(Stdlist, auxPointer);
            } else 
                pointer = getNext(Stdlist, pointer);

            
        } else 
            pointer = getNext(Stdlist, pointer);


        ppVistis(var, 1);
    }
    
    fprintf(file, "\n");
    fclose(file);

}

void functionBBI(StdList Stdlist, float x, float y, VAR var) {
  
    float MinorX = 9999999999999, MinorY = 9999999999999, GreatterW = -1, GreatterH = -1;
    char *AUX = calloc(100, sizeof(char));
    int Aux;
    Point point;
    point.x = x, point.y = y;
    st_point P = &point;

    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\BBI//========|\n");

    StdItem *item;

    StdNode *pointer = getFirst(Stdlist);
    ppVistis(var, 1);

    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (isInternal(getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), P)) {
            fprintf(file, "ID: %s Preenchimento: %s Contorno: %s\n", getItem_ID(item), getItem_FILL(item), getItem_STROKE(item));
            if (getItem_X(item) < MinorX) MinorX = getItem_X(item);
            if (getItem_X(item) + getItem_W(item) > GreatterW) GreatterW = getItem_X(item) + getItem_W(item);
            if (getItem_Y(item) < MinorY) MinorY = getItem_Y(item);
            if (getItem_Y(item) + getItem_H(item) > GreatterH) GreatterH = getItem_Y(item) + getItem_H(item);
            strcpy(AUX, getItem_FILL(item));
            strcpy(getItem_FILL(item), getItem_STROKE(item));
            strcpy(getItem_STROKE(item), AUX);
            
            Aux = getItem_OP_C(item);
            setItem_OP_C(item, getItem_OP_P(item));
            setItem_OP_P(item, Aux);
            
        }

        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }

    GreatterW = GreatterW - MinorX;
    GreatterH = GreatterH - MinorY;

    fprintf(file, "\n");
    fclose(file);
    free(AUX);

    BBI_BBID_tempFileWrite(MinorX, MinorY, GreatterW, GreatterH, x, y, "BBI", var);
}

void functionBBID (StdList Stdlist, char *id, VAR var) {

    float MinorX = 9999999999999, MinorY = 9999999999999, GreatterW = -1, GreatterH = -1;
    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\BBID//========|\n");
    StdNode *pointer = getFirst(Stdlist), *AUX;
    ppVistis(var, 1);
    bool Verifier = 0;
    StdItem *item, *item2;
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (!strcmp(id, getItem_ID(item))) {
            Verifier = 1;
            AUX = pointer;
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }
    if (!Verifier) {
        fprintf(file, "ID inexistente.\n");
        fclose(file);   
        return;
    }
    pointer = getFirst(Stdlist);
    ppVistis(var, 1);
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        item2 = get(Stdlist, AUX);
        if (strcmp(getItem_ID(item), id)) {
            if (rectIntersect(getItem_X(item2), getItem_Y(item2), getItem_W(item2), getItem_H(item2), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item)) == 2) {
                fprintf(file, "ID: %s Preenchimento: %s Contorno: %s\n", getItem_ID(item), getItem_FILL(item), getItem_STROKE(item)); 
                if (getItem_X(item) < MinorX) MinorX = getItem_X(item);
                if (getItem_X(item) + getItem_W(item) > GreatterW) GreatterW = getItem_X(item) + getItem_W(item);
                if (getItem_Y(item) < MinorY) MinorY = getItem_Y(item);
                if (getItem_Y(item) + getItem_H(item) > GreatterH) GreatterH = getItem_Y(item) + getItem_H(item);

            }
                
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
    }

    GreatterW = GreatterW - MinorX;
    GreatterH = GreatterH - MinorY;

    fprintf(file, "\n");
    fclose(file);

    BBI_BBID_tempFileWrite(MinorX, MinorY, GreatterW, GreatterH, 0, 0, "BBID", var);

}

void BBI_BBID_tempFileWrite(float MinorX, float MinorY, float GreatterW, float GreatterH, float x, float y, char *function, VAR var) {

    char *tempQRY = calloc(strlen(getARG_PathBSD(var)) + strlen("tempQRY") + 10, sizeof(char));
    if (strcmp(getARG_PathBSD(var), "\0")) sprintf(tempQRY, "%s/%s.txt", getARG_PathBSD(var), "tempQRY");
    else  sprintf(tempQRY, "%s.txt", "tempQRY");
    FILE *tempQRYsvg = fopen(tempQRY, "a+");

    if (MinorX != 9999999999999 && MinorY != 9999999999999 && GreatterW != -10000000000000 && GreatterH != -10000000000000)
        fprintf(tempQRYsvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"red\" stroke-dasharray=\"1\" stroke-width=\"1.2\" fill-opacity=\"0\"></rect>\n\t", MinorX, MinorY, GreatterW, GreatterH);
    if (!strcmp(function, "BBI")) 
        fprintf(tempQRYsvg, "<circle cx=\"%f\" cy=\"%f\" data-value=\"7.2\" r=\"1.5\" style = \"fill : black; stroke : white; stroke-width : 0.5\"></circle>\n\t", x, y);

    fclose(tempQRYsvg);
    free(tempQRY);


}

void functionIID(StdList Stdlist, char *id, int K, VAR var) {

    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\IID//========|\n");
    bool Verifier = 0;
    int index = 0;
    StdItem *item;
    StdNode *pointer = getFirst(Stdlist);
    ppVistis(var, 1);

    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (!strcmp(id, getItem_ID(item))) {
            Verifier = 1;
            break;
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
        index++;
    }
    if (!Verifier) {
        fprintf(file, "ID inexistente.\n");
        fclose(file);   
        return;
    }
    item = get(Stdlist, pointer);
    fprintf(file, "ID: %s Âncora:(%f, %f) Largura: %f Altura: %f Contorno: %s Preenchimento: %s\n", getItem_ID(item), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_FILL(item), getItem_STROKE(item));

    bool sign = 1;
    if (K < 0) {
        K = K*-1;
        sign = 0;
    }

    if (sign) {
        if (K > length(Stdlist) - 1)
            K = length(Stdlist) - 1;
    }else if (!sign) {
        if (K > index)
            K = index;

    }

    for (int i = 0; i < K; i++) {
        if (sign) {
            if (getNext(Stdlist, pointer) != NULL) pointer = getNext(Stdlist, pointer);
            else break;
        }else if (!sign) {
            if (getPrevious(Stdlist, pointer) != NULL) pointer = getPrevious(Stdlist, pointer);
            else break;
        }
        item = get(Stdlist, pointer);
        fprintf(file, "ID: %s Âncora:(%f, %f) Largura: %f Altura: %f Contorno: %s Preenchimento: %s\n", getItem_ID(item), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_FILL(item), getItem_STROKE(item));

        ppVistis(var, 1);
    }

    fprintf(file, "\n");
    fclose(file);

}

void functionDIID(StdList Stdlist, char *id, int K, VAR var) {

    FILE *file = fopen(getArqConsTXT(var), "a+");
    fprintf(file, "|========\\\\DIID//========|\n");
    bool Verifier = 0;
    int index = 0;
    StdNode *pointer = getFirst(Stdlist), *AUX;
    ppVistis(var, 1);
    StdItem *item;
    while (pointer != NULL) {
        item = get(Stdlist, pointer);
        if (!strcmp(id, getItem_ID(item))) {
            Verifier = 1;
            break;
        }
        pointer = getNext(Stdlist, pointer);
        ppVistis(var, 1);
        index++;
    }
    if (!Verifier) {
        fprintf(file, "ID inexistente.\n");
        fclose(file);   
        return;
    }
    item = get(Stdlist, pointer);
    fprintf(file, "ID: %s Âncora:(%f, %f) Largura: %f Altura: %f Contorno: %s Preenchimento: %s\n", getItem_ID(item), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_FILL(item), getItem_STROKE(item));
    bool sign = 1;
    if (K < 0) {
        K = K*-1;
        sign = 0;
    }

    if (sign) {
        if (K > length(Stdlist) - 1)
            K = length(Stdlist) - 1;
    }else if (!sign) {
        if (K > index)
            K = index;

    }
    
    bool conditional = 1; 
    if (sign) {
        if (getNext(Stdlist, pointer) != NULL) pointer = getNext(Stdlist, pointer);
        else conditional = 0;
    }else if (!sign) {
        if (getPrevious(Stdlist, pointer) != NULL) pointer = getPrevious(Stdlist, pointer);
        else conditional = 0;
    }

    if (conditional) {
        for (int i = 0; i < K; i++) {
            item = get(Stdlist, pointer);
            fprintf(file, "ID: %s Âncora:(%f, %f) Largura: %f Altura: %f Contorno: %s Preenchimento: %s\n", getItem_ID(item), getItem_X(item), getItem_Y(item), getItem_W(item), getItem_H(item), getItem_FILL(item), getItem_STROKE(item));            
            AUX = pointer;
            if (sign) {
                if (getNext(Stdlist, pointer) != NULL) pointer = getNext(Stdlist, pointer);
                else {
                    AUX = pointer;
                    erase(Stdlist, AUX);
                    break;
                }
            }else if (!sign) {
                if (getPrevious(Stdlist, pointer) != NULL) pointer = getPrevious(Stdlist, pointer);
                else {
                    AUX = pointer;
                    erase(Stdlist, AUX);
                    break;
                }
            }
            erase(Stdlist, AUX);

            ppVistis(var, 1);

        }

    }

    fprintf(file, "\n");
    fclose(file);

}
