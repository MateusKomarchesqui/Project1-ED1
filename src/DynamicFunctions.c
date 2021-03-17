#include "voidpointers.h"
#include "Variables.h"
#include "ListHeader.h"

/*                 DYNAMIC LIST                 */
typedef struct node {
    void *data;
    struct node *next, *prev;
}   Node;

typedef struct list {
    int size, visits;
    Node *head, *tail;
}   List;

StdNode push(StdList Stdlist, StdItem info) {

    List* list = Stdlist;
    Node* node = calloc(1, sizeof(Node));

    node->data = info;

    node->next = list->head;

    node->prev = NULL;
    list->head = node;
    list->tail = node;
    list->size++;

    list->visits += 2;
    return (node);
}

void pop(StdList Stdlist) {

    List *list = Stdlist;
    if (list->size) {
        Node* pointer = list->head;
        
        list->head = pointer->next;
        pointer->next->prev = NULL;
        list->visits ++;
        free(pointer);
        list->size--;
    }

}

StdNode getPrevious(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        Node *node = Stdnode;
        Node *prevNode = node->prev;
        return (prevNode);
    }
    return NULL;
}

StdNode getNext(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        Node *node = Stdnode;
        Node *nextNode = node->next;
        return (nextNode);
    }
    return NULL;
}

StdNode getFirst(StdList Stdlist) {
    List *list = Stdlist;
    return list->size ? list->head : NULL;
}

StdNode getLast(StdList Stdlist) {
    List *list = Stdlist;
    return list->size ? list->tail : NULL;
}

StdList createList (int NX) {
    List* list = calloc(1, sizeof(List));

    list->size = 0;
    list->visits = 0;
    list->head = NULL;
    list->tail = NULL;

    return (list);
}

int length(StdList Stdlist) {
    if (Stdlist) {
        List* list = Stdlist;
        return (list->size);
    }
    return -1;
}

StdNode insert(StdList Stdlist, StdItem info) {
    List *list = Stdlist;

    if (list->size == 0) {
        return (push(list, info));
    }else {

        Node* pointer = getLast(Stdlist);
        Node* NewNode = calloc(1, sizeof(Node));
        
        NewNode->data = info;

        pointer->next = NewNode;
        NewNode->prev = pointer;
        NewNode->next = NULL;

        list->tail = NewNode;
        list->visits += 2;

        list->size++;
        return(NewNode);
    }

}

StdNode atPos(StdList Stdlist, int index) {

    List *list = Stdlist;
    if (index >= 0 && index < list->size) {
        Node* node = list->head;
        list->visits ++;

        for (int i = 0; i < index; i++) {
            node = node->next;
            list->visits ++;
        }

        return (node);
    }

    printf ("Indice Invalido\n");
    return (NULL);

}

int indexOf(StdList Stdlist, StdNode Stdnode) {

    List *list = Stdlist;
    Node *node = Stdnode;
    if (node != NULL) {
        Node* pointer = list->head;
        list->visits ++;

        int index = 0;
        while (pointer != node && pointer != NULL) {
            pointer = pointer->next;
            index++;
            list->visits ++;
        }

        if (pointer != NULL) 
            return (index);
        
    }

    printf ("No nao pertencente a lista\n");
    return (-1);
}

void erase(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        List *list = Stdlist;
        if (list->head == Stdnode) {
            pop(list);
        }else {
            Node* Current = Stdnode;

            if (Current != NULL) {
                Node* Previous = getPrevious(Stdlist, Stdnode);
                Previous->next = Current->next;
                if (Current->next != NULL)
                    Current->next->prev = Previous;
                free(Current->data);
                free(Current);
                list->size--;
            }
            list->visits += 2;
            
        }
    }

}

StdItem get(StdList Stdlist, StdNode Stdnode) {
    if (Stdnode) {
        Node *node = Stdnode;
        return (node->data);
    }
    return NULL;
}

void freeList(StdList Stdlist) {
    if (Stdlist) {
        List *list = Stdlist;
        if (list->size) {

            do {    
                Node* pointer = list->head;
                StdItem *item = get(Stdlist, pointer);
                list->head = pointer->next;
                free(pointer);
                free(item);
                list->size--;

            } while (list->size != 0);

        }
        free(list);
    }

}

StdNode insertBefore(StdList Stdlist, StdNode Stdnode, StdItem info) {

    if (Stdnode) {
        List *list = Stdlist;
        Node *node = calloc(1, sizeof(Node));
        Node *prevNode = getPrevious(Stdlist, Stdnode);
        Node *nextNode = getNext(Stdlist, Stdnode);

        node->data = info;

        prevNode->next = node;
        node->prev = prevNode;
        node->next = nextNode;
        nextNode->prev = node;
        list->visits += 2;

        return (node);
    }
    return NULL;
}

StdNode insertAfter(StdList Stdlist, StdNode Stdnode, StdItem info) {
    if (Stdnode) {
        List* list = Stdlist;
        Node *node = calloc(1, sizeof(Node));
        Node *prevNode = Stdnode;
        Node *nextNode = getNext(Stdlist, Stdnode);

        node->data = info;

        prevNode->next = node;
        node->prev = prevNode;
        node->next = nextNode;
        nextNode->prev = node;
        list->visits += 2;

        return (node);
    }
    return NULL;
}

int getListVisits(StdList Stdlist) {
    if (Stdlist) {
        List *list = Stdlist;
        return list->visits;
    }
    return 0;
}
