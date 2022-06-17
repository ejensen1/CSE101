//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa4
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include<stdbool.h>
#include<stdio.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList();

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// index()
// Returns the index of cursor element if defined, -1 otherwise
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
void* front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
void* back(List L);

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
void* get(List L);

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data at the back of L.
void clear(List L);
void set(List L, void* x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x);
void append(List L, void* x);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
void printList(FILE* out,List L);
List concatList(List A, List B);
List reverse(List L);

// deleteFront()
// Deletes data at front of L.
// Pre: !isEmpty(L)
//void deleteFront(List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.
//void printList(List L);

// equals()
// Returns true if A is same int sequence as B, false otherwise.
//bool equals(List A, List B);

#endif
