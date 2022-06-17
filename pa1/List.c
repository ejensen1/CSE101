//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa1
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node previous;
   Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   int cursorIndex;
   Node cursorPosition;
   int length;
   
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->length = 0;
   L->cursorIndex = -1;
   L->cursorPosition = NULL;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.

void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
          deleteFront(*pL);
      }

      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
    if( L==NULL ){
        fprintf(stderr,"List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0){
       return -1;
    }
    return(L->length);
}

int index(List L){
    if (L == NULL){
        fprintf(stderr,"List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->cursorIndex;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      fprintf(stderr,"List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
int back(List L){
    if (L == NULL){
        fprintf(stderr,"List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)){
        fprintf(stderr,"List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

int get(List L){
    if (L == NULL){
        fprintf(stderr,"List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr,"List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex < 0) {
        fprintf(stderr,"List Error: calling get(); List's cusor index not set\n");
        exit(EXIT_FAILURE);
    }
    return L->cursorPosition->data;
}


// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
bool isEmpty(List L){
   if( L==NULL ){
      fprintf(stderr,"List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

// Manipulation procedures ----------------------------------------------------

// Clear
// Resets L to its original empty state
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr,"List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
        
    L->length = 0;
    L->front = 0;
    L->back = 0;
    L->cursorIndex = -1;
    L->cursorPosition = NULL;
    return;
}

void set(List L, int x) {
    if (L == NULL){
        fprintf(stderr,"List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr,"List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex < 0){
        fprintf(stderr,"List Error: calling set() on a List with index < 0\n");
        exit(EXIT_FAILURE);
    }
    
    L->cursorPosition->data = x;
    return;
}

void moveFront(List L) {
    if (L == NULL){
        fprintf(stderr,"List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <=0){
        return;
    }
    L->cursorPosition = L->front;
    L->cursorIndex = 0;
    return;
}
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        return;
    }
    L->cursorPosition = L->back;
    L->cursorIndex = (L->length - 1);
    return;

}
void movePrev(List L) {
    if (L == NULL){
        fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex == -1){
        return;
    }
    if ((L->cursorIndex != -1) && (L->cursorIndex != 0)) {
        L->cursorIndex--;
        L->cursorPosition = L->cursorPosition->previous;
    } else if (L->cursorIndex == 0) {
        L->cursorIndex = -1;
        L->cursorPosition = NULL;
    }
    return;
}

void moveNext(List L) {
    if (L == NULL){
        fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex == -1){
        return;
    }
    if ((L->cursorIndex != -1) && (L->cursorIndex != (L->length - 1))){
        L->cursorIndex++;
        L->cursorPosition = L->cursorPosition->next;
    } else if (L->cursorIndex == (L->length - 1)){
        L->cursorIndex = -1;
        L->cursorPosition = NULL;
    }
    return;


}

void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
    }
    Node N = newNode(x);
    if(L->length <= 0){
        L->front = L->back = N;
        L->length++;
        return;
    } else {
        N->previous = NULL;
        L->front->previous = N;
        N->next = L->front;
        L->front = N;
    }
    L->cursorIndex++;
    L->length++;
    return;

}

void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (isEmpty(L)) {
        L->front = L->back = N;
        L->length++;

        return;
    } else {
        L->back->next = N;
        N->previous = L->back;
        L->back = N;
    }
    L->length++;
    return;
}
void insertBefore(List L, int x) {
    if (L == NULL){
        fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0) {
        fprintf(stderr, "List Error: calling insertBefore();cursor not defined\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->cursorIndex == 0){
        L->front->previous = N;
        N->next = L->front;
        N->previous = NULL;
        L->front = N;
    } else if (L->cursorIndex == (L->length - 1)){
        L->back->previous->next = N;
        N->previous = L->back->previous;
        L->back->previous = N;
        N->next = L->back;
    } else {
        N->previous = L->cursorPosition->previous;
        N->next = L->cursorPosition;
        L->cursorPosition->previous->next = N;
        L->cursorPosition->previous = N;
    }
    L->length++;
    L->cursorIndex++;
    return;

}

void insertAfter(List L, int x) {
    if (L == NULL){
        fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0){
        fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0) {
        fprintf(stderr, "List Error: calling insertAfter();cursor not defined\n");
        exit(EXIT_FAILURE);
    }

    if ((L->length == 1)){
        append(L, x);
        return;
    }
    Node N = newNode(x);
    
    if (L->cursorIndex == 0){
        N->next = L->front->next;
        N->previous = L->front;
        L->front->next->previous = N;
        L->front->next = N;
    } else if (L->cursorIndex == (L->length - 1)){
        N->previous = L->back;
        N->next = NULL;
        L->back->next = N;
        L->back = N;
    } else {
        N->previous = L->cursorPosition;
        N->next = L->cursorPosition->next;
        L->cursorPosition->next->previous = N;
        L->cursorPosition->next = N;
    }
    L->length++;
    return;
}

void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr,"List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr,"List Error: calling deleteFront() on List of length <= 0\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N= L->front;
    if(L->length == 1){
        freeNode(&N);
        L->length = 0;
        L->front = NULL;
        L->back = NULL;
        return;
    }
    /*
    if (L->cursorIndex == 0){
        L->cursorIndex = -1;
    }
    */
    if (L->length > 1) {
        L->front = L->front->next;
    }
    /* 
    else {
        L->front = L->back = NULL;
    }
    */
    L->cursorIndex--;
    L->length--;
    freeNode(&N);
    return;

}

void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr,"List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr,"List Error: calling deleteBack() on List of length <= 0\n");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    N = L->back;
    
    if(L->length == 1){
        freeNode(&N);
        L->length = 0;
        L->front = NULL;
        L->back = NULL;
        L->cursorIndex = -1;
        return;
    }
    
    if (L->cursorIndex == L->length - 1){
        L->cursorIndex = -1;
    }

    if (L->length > 1){
        L->back = L->back->previous;
    } 
    /*else {
        L->back = L->front = NULL;
    }
    */
    L->length--;
    freeNode(&N);
    return;
}

void delete(List L) {
    if (L == NULL){
        fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
    }
    if (L->length <= 0) {
        fprintf(stderr,"List Error: calling delete() on List of length <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursorIndex < 0){
        fprintf(stderr, "List Error: calling delete() on List with undefined cursor\n");
    }
    
    if (L->length == 1){
        clear(L);
    }
    if (L->cursorIndex == 0){
        deleteFront(L);
    }else if (L->cursorIndex == (L->length -1)){
        deleteBack(L);
    } else {
        L->cursorPosition->previous->next = L->cursorPosition->next;
        L->cursorPosition->next->previous = L->cursorPosition->previous;
        L->length--;
    }
    L->cursorPosition = NULL;
    L->cursorIndex = -1;
    return;

        
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.
void printList(FILE* out, List L){
    printf("cursorIndex %d\n", L->cursorIndex);
    printf("inside printList\n");
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    int temp = L->cursorIndex;

    
    int i = 0;
    for(moveFront(L); index(L)>=0; moveNext(L)){
        i++;
        fprintf(out,"%d ", get(L));
    }
    L->cursorIndex = temp;
    return;
}

// equals()
// Returns true (1) if A is same int sequence as B, false (0) otherwise.
bool equals(List A, List B){
    if ((A == NULL) || (B == NULL)){
        fprintf(stderr, "List Error: calling printList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int data; 
    List R = newList();

    for(moveFront(L); index(L)>=0;moveNext(L)){
        data = get(L);
        append(R,data);
    }
    return R;

}
/*
List concatList(List A, List B) {
    if (L == NULL) {
        fprintf(stderr, "List Error: calling printList on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

}
*/


