// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa8

#include<iostream>
#include<string>
#include<stdexcept>

#include"Dictionary.h"

using namespace std;

int main(){
    Dictionary A;
    A.setValue("plaices",1);
    A.setValue("ambusher",2);
    A.setValue("crosby",3);
    A.setValue("wattles",4);
    A.setValue("pardoner",5);
    A.setValue("pythons",6);
    A.setValue("second",7);
    A.setValue("forms",8);
    A.setValue("impales",9);
    A.setValue("pic",10);
    A.setValue("verticals",11);
    A.setValue("recriminator",12);
    A.setValue("depressants",13);
    A.setValue("cul",14);
    A.setValue("plaices",1);
    A.setValue("ambusher",2);
    A.setValue("crosby",3);
    A.setValue("wattles",4);
    A.setValue("pardoner",5);
    A.setValue("pythons",6);
    A.setValue("second",7);
    A.setValue("forms",8);
    A.setValue("impales",9);
    A.setValue("pic",10);
    cout<<A<<endl;
    cout<<"A.size() = "<<A.size()<<endl;
    A.clear();
    
    return 0;
}
