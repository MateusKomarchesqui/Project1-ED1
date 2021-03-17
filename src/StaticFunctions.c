#include "voidpointers.h"
#include "Variables.h"
#include "ListHeader.h"

/*                 STATIC LIST                 */
typedef struct Snode {
    int next;
    void *content;
} SNode;

typedef struct SList {
    int size, visits;
    long int DEF_SIZE;
    SNode *array;
    int head, freeSlot, tail;
} SList;

int indexOfNode(StdList Stdlist, StdNode Stdnode) {

    SList *list = Stdlist;
    SNode *node = Stdnode;
    int head = list->head;
    list->visits ++;
    for (int i = 0; i < list->size; i++) {
        if (&list->array[head] == node)
            return (head);

        head = list->array[head].next;
        list->visits ++;
    }

    printf ("No nao pertencente a lista\n");
    return -1;
}

StdNode getPrevious(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        SList *list = Stdlist;
        int index = list->head;
        list->visits ++;
        if (Stdnode == &list->array[list->head]) return NULL;

        for (int i = 0; i < list->size; i++) {
            if (&list->array[list->array[index].next] == Stdnode) 
                return (&list->array[index]);
            index = list->array[index].next;
            list->visits ++;
        }
    }
    return NULL;
}

StdNode getNext(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        SList *list = Stdlist;
        SNode *node = Stdnode;
        list->visits ++;
        if (&list->array[list->tail] == Stdnode) return NULL;
        else return (&list->array[node->next]);
    }
    return NULL;
}

StdNode getFirst(StdList Stdlist) {
    SList *list = Stdlist;
    list->visits ++;
    return list->size ? &list->array[list->head] : NULL;
}

StdNode getLast(StdList Stdlist) {
    SList *list = Stdlist;
    list->visits ++;
    return list->size ? &list->array[list->tail] : NULL;
}

int isFree(StdList Stdlist) {

    SList *list = Stdlist;

    int Verifier[list->DEF_SIZE];
    for (int i = 0; i < list->DEF_SIZE; i++)
        Verifier[i] = 1;

    int current = list->head;
    list->visits++;

    while (current != -1) {
        Verifier[current] = 0;
        current = list->array[current].next;
        
        list->visits++;   
    }

    for (int i = 0; i < list->DEF_SIZE; i++) {
        if (Verifier[i])
            return (i);
    }

    return(-1);

}

StdList createList (int NX) {
    SList* list = calloc(1, sizeof(SList));

    list->array = calloc(NX, sizeof(SNode));

    list->size = 0;
    list->visits = 0;
    list->DEF_SIZE = NX;
    list->head = -1;
    list->tail = -1;

    for (int i = 0; i < NX; i++) {
        list->array[i].next = i + 1;
        list->visits ++;
    }
    
    list->array[NX - 1].next = -1;

    return (list);
}

int length(StdList Stdlist) {
    if (Stdlist) {
        SList *list = Stdlist;
        return (list->size);
    }
    return -1;
}

StdNode insert(StdList Stdlist, StdItem info) {
    SList *list = Stdlist;
    int aux;

    if (list->size == list->DEF_SIZE) {
        puts("Lista Cheia");
        return NULL;
    }

    if (list->freeSlot > -1) {

        if (!list->size) {
            list->array[0].content = info;
            list->array[0].next = -1;
            list->freeSlot = 1;
            list->head = list->tail = 0;
            aux = 0;

        } else {
            list->array[list->tail].next = list->freeSlot;
            list->array[list->freeSlot].content = info;
            aux = list->freeSlot;
            list->array[list->freeSlot].next = -1;
            list->tail = list->freeSlot;
            list->freeSlot = isFree(Stdlist);
        }
        list->size++;
        return (&list->array[aux]);

    }

}

StdNode atPos(StdList Stdlist, int index) {

    SList *list = Stdlist;
    if (index >= 0 && index < list->size) {
        int node = list->head;
        
        list->visits++;

        for (int i = 0; i < index; i++) {
            node = list->array[node].next;
            
            list->visits++;
        }

        return (&list->array[node]);
    }

    printf ("Indice Invalido\n");
    return NULL;

}

int indexOf(StdList Stdlist, StdNode Stdnode) {

    SList *list = Stdlist;
    SNode *node = Stdnode;
    int head = list->head;
    list->visits ++;
    int cont = 0;
    for (int i = 0; i < list->size; i++) {
        if (&list->array[head] == node)
            return (cont);

        head = list->array[head].next;
        list->visits ++;
        cont++;
    }

    printf ("No nao pertencente a lista\n");
    return (-1);
}

void erase(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        SList *list = Stdlist;
        SNode *node = Stdnode;
        free(node->content);
        if (node == &list->array[list->head]) {
            if (list->size) {

                list->head = list->array[list->head].next;
                list->size--;

            }else 
                puts("Lista Vazia.");
            
        }else if (node == &list->array[list->tail]) {
            if (list->size) {

                list->tail = indexOfNode(Stdlist, getPrevious(Stdlist, Stdnode));
                list->size--;

            }else 
                puts("Lista Vazia.");
            
        }else {
            int Current = indexOfNode(list, Stdnode);

            if (Current != -1) {
                SNode *Previous = getPrevious(Stdlist, Stdnode);
                Previous->next = list->array[Current].next;

                list->size--;
            }
                
        }

        list->visits += 2;
        list->freeSlot = isFree(Stdlist);
    }

}

StdItem get(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        SList *list = Stdlist;
        SNode *node = Stdnode;
        list->visits ++;
        return (node->content);
    }
    return NULL;
}

void freeList(StdList Stdlist) {
    if (Stdlist) {
        SList *Slist = Stdlist;
        if (Slist->size) {

            do {    
                int node = Slist->head;
                StdItem item = get(Stdlist, getFirst(Stdlist));
                Slist->head = Slist->array[node].next;
                free(item);
                Slist->size--;

            } while (getFirst(Stdlist));

        }

        free(Slist->array);
        free(Stdlist);
    }
}

StdNode insertBefore(StdList Stdlist, StdNode Stdnode, StdItem info) {

    if (Stdnode) {
        SList *list = Stdlist;
        int newNode = list->freeSlot;
        SNode *prevNode = getPrevious(Stdlist, Stdnode);

        prevNode->next = newNode;
        list->array[newNode].next = indexOfNode(Stdlist, Stdnode);
        list->array[newNode].content = info;
        list->size ++;
        list->freeSlot = isFree(Stdlist);

        return (&list->array[newNode]);
    }
    return NULL;
}

StdNode insertAfter(StdList Stdlist, StdNode Stdnode, StdItem info) {

    if (Stdnode) {
        SList *list = Stdlist;
        int newNode = list->freeSlot;
        SNode *nextNode = getNext(Stdlist, Stdnode);
        SNode *node = Stdnode;

        list->array[newNode].next = indexOfNode(Stdlist, nextNode);
        node->next = newNode;
        list->array[newNode].content = info;
        list->size ++;
        list->freeSlot = isFree(Stdlist);
        
        return (&list->array[newNode]);
    }
    return NULL;

}

int getListVisits(StdList Stdlist) {
    if (Stdlist) {
        SList *list = Stdlist;
        return list->visits;
    }
    return 0;
}
