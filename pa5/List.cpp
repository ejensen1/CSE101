// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa5
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

// Private constructor

// Node constructor

List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors

List::List(){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
//List::List(const List& L): List(){
List::List(const List& L){
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into List
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        //this->insertAfter(N->data);
        this->insertBefore(N->data);
        //moveNext();
        N = N->next;
    }
    moveFront();
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
    frontDummy = nullptr;
    backDummy = nullptr;
    beforeCursor = nullptr;
    afterCursor = nullptr;
}

// Access Functions
int List::length() const{
    return(num_elements);
}

ListElement List::front() const{
    return(frontDummy->next->data);
}

ListElement List::back() const{
    return(backDummy->prev->data);
}

int List::position() const{
    return(pos_cursor);
}

ListElement List::peekNext() const{
    return(afterCursor->data);
}

ListElement List::peekPrev() const{
    return(beforeCursor->data);
}

// Manipulation procedures

void List::clear(){
    moveFront();
    while (num_elements > 0){
        eraseAfter();
    }
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext(){
    if (pos_cursor > num_elements){
        throw std::length_error("Length: moveNext(): trying to move enxt at end of list");
    }
    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

ListElement List::movePrev(){
    if (pos_cursor <= 0){
        throw std::length_error("Length: movePrev(): trying to move previous at front of list");
    }
    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return afterCursor->data;
}

void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x){
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    beforeCursor->data = x;
}

void List::eraseAfter(){
    if( num_elements==0 ){
        throw std::length_error("List: eraseAfter(): empty List");
    }
    if( pos_cursor>=num_elements){
        throw std::out_of_range("List: eraseAfter(): pos_cursor>=num_elements");
    }
    Node* N = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    num_elements--;
    delete(N);
}

void List::eraseBefore(){
    if( num_elements==0 ){
        throw std::length_error("List: eraseAfter(): empty List");
    }
    if( pos_cursor == 0){
        throw std::out_of_range("List: eraseAfter(): pos_cursor==0");
    }
    Node* N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    delete(N);
    num_elements--;
    pos_cursor--;
}

// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if (moveNext() == x){
            return pos_cursor;
        }
    }
    pos_cursor = length();
    return -1;
}

int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        if(movePrev() == x){
            return pos_cursor;
        }
    }
    pos_cursor = 0;
    return -1;
}

void List::cleanup(){
    int temp_cursor = pos_cursor;
    int temp2;
    int x,y;
    moveFront();
    while(pos_cursor < num_elements){
        x = moveNext();
        temp2 = pos_cursor;
        Node* tempN1 = beforeCursor;
        Node *tempN2 = afterCursor;
        while(pos_cursor < num_elements){
            y = moveNext();
            if (y == x){
                if (pos_cursor < temp_cursor){
                    temp_cursor--;
                }
                eraseBefore();
            }
        }
        pos_cursor = temp2;
        beforeCursor = tempN1;
        afterCursor = tempN2;
    }
    moveFront();
    for (int i =1; i< temp_cursor;i++){
        moveNext();
    }
}

List List::concat(const List& L) const{
    List C;
    Node* N;
    N = this->frontDummy->next;
    for( int i=0; i<this->num_elements; i++){
        C.insertBefore(N->data);
        N = N->next;
    }
    N = L.frontDummy->next;
    for( int i=0; i< L.num_elements; i++ ){
        C.insertBefore(N->data);
        N=N->next;
    }
    C.moveFront();
    return C;

}

std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";
    for(N=frontDummy->next; N!=backDummy; N=N->next){
        s += std::to_string(N->data)+" ";
    }
    return s;
}

bool List::equals(const List& L) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->num_elements == L.num_elements );
    N = this->frontDummy;
    M = L.frontDummy;
    while( eq && N!=nullptr){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

std::ostream& operator<< ( std::ostream& stream, const List& L){

    return stream << L.to_string();
}

bool operator== (const List& A, const List& B){
    return A.equals(B);
}

List& List::operator=(const List& L){
    if (this != &L){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
    }
    return *this;
}
