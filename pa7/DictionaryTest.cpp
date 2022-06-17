// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa7

#include<iostream>
#include<string>
#include<stdexcept>

#include"Dictionary.h"

using namespace std;


int main(){
    Dictionary A;
    A.setValue("a", 1);
    A.setValue("b", 5);
    A.setValue("e", 10);
    A.setValue("h", 15);
    A.setValue("f", 20);
    A.setValue("i", 100);
    cout<<A<<endl;
    /*
    A.setValue("a",1);
    A.postOrderDelete(A.root);
    cout<<"A.size() = "<<A.size()<<endl;
    cout<<"end of test"<<endl;
    */
    /*
    Dictionary D;
    
    cout<<"D.hasCurrent() = "<<D.hasCurrent()<<endl;
    D.setValue("a",1);
    cout<<"D.hasCurrent() = "<<D.hasCurrent()<<endl;

    D.remove("a");
    cout<<"D.hasCurrent() = "<<D.hasCurrent()<<endl;

    D.setValue("d",1);
    D.setValue("e",1);
    D.setValue("z",1);
    D.begin();

    cout<<"D.size() = "<<D.size()<<endl;

    for(D.begin();D.hasCurrent();D.next()){
        cout<<D.currentKey()<<endl;
        cout<<D.currentVal()<<endl;
    }


    // cout<<D.begin().key<<endl;
    */
    return 0;
}
