#include "Libraries.h"
#include "voidpointers.h"

typedef struct item {
    char ID[1000], FILL[100], STROKE[100];
    float X, Y, W, H;
    int OPACITY_C, OPACITY_P;
    int show;
}Item;

char *getItem_ID(StdItem item) {
    Item *aux = item;
    return(aux->ID);
}

void setItem_ID(StdItem item, char *string) {
    Item *aux = item;
    strcpy(aux->ID, string);
}

char *getItem_FILL(StdItem item) {
    Item *aux = item;
    return(aux->FILL);
}

void setItem_FILL(StdItem item, char *string) {
    Item *aux = item;
    strcpy(aux->FILL, string);
}

char *getItem_STROKE(StdItem item) {
    Item *aux = item;
    return(aux->STROKE);
}

void setItem_STROKE(StdItem item, char *string) {
    Item *aux = item;
    strcpy(aux->STROKE, string);
}

float getItem_X(StdItem item) {
    Item *aux = item;
    return(aux->X);
}

void setItem_X(StdItem item, float value) {
    Item *aux = item;
    aux->X = value;
}

float getItem_Y(StdItem item) {
    Item *aux = item;
    return(aux->Y);
}

void setItem_Y(StdItem item, float value) {
    Item *aux = item;
    aux->Y = value;
}

float getItem_W(StdItem item) {
    Item *aux = item;
    return(aux->W);
}

void setItem_W(StdItem item, float value) {
    Item *aux = item;
    aux->W = value;
}

float getItem_H(StdItem item) {
    Item *aux = item;
    return(aux->H);
}

void setItem_H(StdItem item, float value) {
    Item *aux = item;
    aux->H = value;
}

int getItem_OP_C(StdItem item) {
    Item *aux = item;
    return(aux->OPACITY_C);
}

void setItem_OP_C(StdItem item, int value) {
    Item *aux = item;
    aux->OPACITY_C = value;
}

int getItem_OP_P(StdItem item) {
    Item *aux = item;
    return(aux->OPACITY_P);
}

void setItem_OP_P(StdItem item, int value) {
    Item *aux = item;
    aux->OPACITY_P = value;
}

int getItem_show(StdItem item) {
    Item *aux = item;
    return(aux->show);
}

void setItem_show(StdItem item, int value) {
    Item *aux = item;
    aux->show = value;
}

StdItem createItem() {
    Item *item = calloc(1, sizeof(Item));
    return (item);
}
