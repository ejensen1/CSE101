// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa5
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
    int len = D.length();
    if(D.length()==1){
        return;
    }
    List E;
    if (D.length() % 2 == 0){
        // D = 0 1 2 3 4 5
        D.moveBack();
        for( int i=0; i<(len/2); i++){
            E.insertAfter(D.movePrev());
        }
        //cout<<"E"<<E<<endl;
        // E = 3 4 5
        D.moveBack();
        for( int i=0; i<(len/2); i++){
            D.eraseBefore();
        }
        //cout<<"D"<<D<<endl;
        // D = 0 1 2
        D.moveFront();
        E.moveFront();

        // D = 0 1 2
        // E = 3 4 5
        for(int i=0; i<=len;i++){
            E.moveNext();
            if (D.length() == D.position()){
                break;
            }
            E.insertBefore(D.moveNext());
        }
        D = E;
    }else{
        // D = 0 1 2 3 4 5 6
        D.moveBack();
        for(int i=0;i<(len/2)+1;i++){
            E.insertAfter(D.movePrev());
        }
        //cout<<"E"<<E<<endl;
        // E = 3 4 5 6
        D.moveBack();
        for(int i=0;i<(len/2)+1;i++){
            D.eraseBefore();
        }
        // D = 0 1 2
        //cout<<"D"<<D<<endl;
        D.moveFront();
        E.moveFront();

        // D = 0 1 2
        // E = 3 4 5 6
        for(int i=0;i<=len;i++){
            E.moveNext();
            if(D.length() == D.position()){
                break;
            }
            E.insertBefore(D.moveNext());
        }
        D = E;
    }
        
}

/*
int main(){
    List A;
    for(int i=0;i<9;i++){
        A.insertBefore(i);
    }
    cout<<"A="<<A<<endl;
    shuffle(A);
    cout<<"A="<<A<<endl;
}
*/

int main(int argc, char * argv[]){
    int deck_size = stoi(argv[1]);
    cout<<"deck size       shuffle count"<<endl;
    cout<<"------------------------------"<<endl;
    List L,C;
    int num_shuffles;
    for(int i=1;i<=deck_size;i++){
        for(int j=0;j<i;j++){
            L.insertBefore(j);
        }
        C = L;

        do{
            shuffle(C);
            num_shuffles++;
            //cout<<"C.front()"<<C.front()<<endl;
            //cout<<"C:"<<C<<endl;
        }while(C.front() != 0);
        cout<<i<<"               "<<num_shuffles<<endl;
        num_shuffles=0;
        L.clear();
        C.clear();

    }
    return(EXIT_SUCCESS);
}