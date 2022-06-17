//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa3
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include<stdbool.h>


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
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L);

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L);

// equals()
// Returns true if List A and List B are in same state, and false otherwise
bool equals(List A, List B);


// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// Enqueue()
// Places new data at the back of L.
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
void printList(FILE* out,List L);
List copyList(List L);
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
