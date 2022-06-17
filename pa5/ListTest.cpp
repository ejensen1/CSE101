// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa5
#include<iostream>
#include<stdlib.h>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    List A;
    A.insertAfter(77);
    A.insertAfter(55);
    A.insertAfter(1);
    A.insertAfter(34);
    A.insertAfter(1);
    A.insertAfter(77);
    A.insertAfter(77);
    A.insertAfter(34);

    cout<<A.findNext(99)<<endl;
    cout<<"these 2 should match"<<endl;
    cout<<"position: "<<A.position()<<endl;
    cout<<"length: "<<A.length()<<endl;

    A.moveFront();

    cout<<A.findNext(1)<<endl;
    cout<<A.findNext(1)<<endl;
    cout<<A.findNext(1)<<endl;
}