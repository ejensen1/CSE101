// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa6
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

using namespace std;

void sumList(List& S, List A, List B, int sgn1, int sgn2);
int normalizeList(List& L);
void shiftList(List& L, int pp);
int main(){
    BigInteger A = BigInteger("-0000000000041085449");
    BigInteger B = BigInteger("6402779357");
    
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"performing A - B"<<endl;
    cout<<"Desired"<<endl;
    cout<<"-6443864806"<<endl;
    cout<<"Actual:"<<endl;
    cout<<A-B<<endl;
    /*
    List A;
    A.insertBefore(-89);
    normalizeList(A);
    cout<<"A = "<<A<<endl;

    A.insertBefore(1);
    A.insertBefore(-90);
    A.insertBefore(9);
    A.insertBefore(73);
    A.insertBefore(0);
    A.insertBefore(-500);
    cout<<"A = "<<A<<endl;
    normalizeList(A);
    cout<<"A = "<<A<<endl;

    A.insertBefore(-90);
    A.insertBefore(9);
    A.insertBefore(73);
    A.insertBefore(0);
    A.insertBefore(-500);

    BigInteger sixteen = BigInteger("16");
    A.insertBefore(1);
    shiftList(A,1);
    cout<<"A = " << A << endl;
    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");





    
    A.insertBefore(4);
    A.insertBefore(8);
    List B;
    List S;
    cout << "S = "<< S << endl;
    cout<<"S = "<< S << endl;
    // normalize checks
    A.insertBefore(1);
    A.insertBefore(-90);
    A.insertBefore(9);
    A.insertBefore(73);
    A.insertBefore(0);
    A.insertBefore(-500);
    normalizeList(A);
    cout<<"A = "<<A<<endl;
    */
    /*
    // add checks
    BigInteger X = BigInteger("109");
    BigInteger Y =BigInteger("101");
    cout<<"X = "<< X << endl;
    cout<<"Y = "<< Y << endl;
    BigInteger Z = X.add(Y);
    cout<<"Z = "<<Z<<endl;
    */
}
