// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa6
#include<iostream>
#include<string>
#include<cmath>
#include<cstdint>

#include"BigInteger.h"
#include"List.h"

using namespace std;

const int p = 9;
const int b = pow(10,p); 

void negateList(List& L);
void sumList(List& S, List A, List B, int sgn1, int sgn2);
int normalizeList(List& L);
void shiftList(List& L, int pp);
void scalarMultList(List& L, ListElement m);

// 0 constructor
BigInteger::BigInteger(){
    signum = 0;
    //digits;
}

// string constructor
BigInteger::BigInteger(std::string s){
    string no_sign = s;
    string p_digits;
    
    // handle sign
    if(s[0]==('+')){
        no_sign = no_sign.substr(1,no_sign.length());
        signum=1;
    }
    else if(s[0]=='-'){
        no_sign = no_sign.substr(1,no_sign.length());
        signum=-1;
    }else{
        signum=1;
    }

    u_int64_t list_ele;
    // pad w 0s
    while(no_sign.length() % p != 0){
        no_sign = "0" + no_sign;
    }

    // iterate thru string from right to left
    for(int i=no_sign.length(); i>0;i-=p){
        p_digits = no_sign.substr(i-p,p);
        list_ele = stol(p_digits);
        if ((list_ele == 0) && (i==p)){
            break;
        }
        digits.insertAfter(list_ele);
        
    }
    digits.moveFront();
    while(digits.peekNext() == 0 && digits.length() != 0){
        digits.eraseAfter();
    }
    //cout<<"digits = "<<digits<<endl;
}

// copy constructor
BigInteger::BigInteger(const BigInteger& N){
//BigInteger::BigInteger(const BigInteger& N):BigInteger(){
    signum = N.signum;
    digits = N.digits;
}

// Destructor
BigInteger::~BigInteger(){
    //delete &digits;
}


// Access functions --------------------------------------------------------

int BigInteger::sign() const{
    return(signum);
}

int BigInteger::compare(const BigInteger& N) const{
    List negative = N.digits;
    scalarMultList(negative,-1);
    List S;
    sumList(S,digits,negative,signum,N.signum);
    return normalizeList(S);
}

// Manipulation procedures -------------------------------------------------

void BigInteger::makeZero(){
    signum=0;
    digits.moveFront();
    while(digits.length()>0){
        digits.eraseAfter();
    }
}

void BigInteger::negate(){
    if(signum==1){
        signum=-1;
    }else if (signum == -1){
        signum = 1;
    }
}

// BigInteger Arithmetic operations ----------------------------------------

BigInteger BigInteger::add(const BigInteger& N) const{
    //BigInteger S = BigInteger();
    BigInteger S;
    List A = List(digits);
    List B = List(N.digits);
    sumList(S.digits,A,B,signum,N.signum);
    S.signum = normalizeList(S.digits);
    return S;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
    int sign = -1 * N.signum;
    BigInteger D;
    List A = List(digits);
    List B = List(N.digits);
    // cout<<"A"<<endl;
    // cout<<A<<endl;
    // cout<<"B"<<endl;
    // cout<<B<<endl;
    sumList(D.digits,A,B,signum,sign);
    // cout<<"D.digits pre norm"<<endl;
    // cout<<D.digits<<endl;
    D.signum = normalizeList(D.digits);
    // cout<<"D.digits post norm"<<endl;
    // cout<<D.digits<<endl;
    return D;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger R;
    
    if(signum == 0 || N.signum == 0){
        return R;
    }
    List A = List(digits);
    List B = List(N.digits);
    List sum;
    int shift = 0;
    //List product;
    List sm_copy;
    for(B.moveBack();B.position() > 0; B.movePrev()){
        // cout<<"---------------------------"<<endl;
        //cout << "product = " << product << endl;
        sm_copy = A;
        // cout<<"factors of sm"<<endl;
        // cout<<sm_copy<<endl;
        // cout<<B.peekPrev()<<endl;
        scalarMultList(sm_copy,B.peekPrev());
        // cout<<"sm_output pre normalize"<<endl;
        // cout<<sm_copy<<endl;
        normalizeList(sm_copy);
        // cout<<"sm_output post normlaize ="<<endl;
        // cout<<sm_copy<<endl;
        shiftList(sm_copy,shift);
        //cout << "sm = " << sm_copy << endl;
        // sum = product + sm _copy
        sum.clear();
        sumList(sum,R.digits,sm_copy,1,1);
        //sumList(sum,product,sm_copy,signum,N.signum);
        //cout << "sum = " << sum << endl;
        normalizeList(sum);
        R.digits = sum;
        //product = sum;
        shift++;
    }
    int return_sign;
    if (signum == N.signum){
        return_sign = 1;
    }else{
        return_sign = -1;
    }
    //R.digits = product;
    R.signum = return_sign;
    return R;
}

// Other Functions ---------------------------------------------------------

std::string BigInteger::to_string(){
    if (digits.length() == 0){
        return "0";
    }
    std::string s = "";
    string str_ele;
    for(digits.moveBack();digits.position() > 0;digits.movePrev()){
        str_ele = std::to_string(digits.peekPrev());
        if (digits.position() == 1){
            s = str_ele + s;
            continue;
        }
        while(str_ele.length() < p){
            str_ele = "0" + str_ele;
        }
        s = str_ele + s;
    }
    if (signum == -1){
        s = '-' + s;
    }
    return s;
}

// Helper Functions --------------------------------------------------------

void negateList(List& L){
    uint64_t list_ele;
    for(L.moveBack();L.position()>0;L.movePrev()){
        list_ele = L.peekPrev();
        list_ele = -list_ele;
        L.setBefore(list_ele);
    }
}

void sumList(List& S, List A, List B, int sgn1,int sgn2){
    uint64_t sum;
    // iterate through both lists from right to left
    for(A.moveBack(),B.moveBack();A.position()>0 &&B.position()>0;A.movePrev(),B.movePrev()){
        // do it like this to handle all 4 cases: w and w/o carry out and negatives
        sum = (sgn1 * A.peekPrev()) + (sgn2 * B.peekPrev());
        S.insertAfter(sum);
    }
    // if A is larger, prepend all remaining nodes
    while(A.position()>0){
        S.insertAfter(sgn1 *A.peekPrev());
        A.movePrev();
    }
    // if B is larger, prepend all remaining nodes
    while(B.position()>0){
        S.insertAfter(sgn2 *B.peekPrev());
        B.movePrev();
    }
    // remove leadign 0s
    S.moveFront();
    while(S.peekNext() == 0 && S.length() != 0){
        S.eraseAfter();
    }

}

int normalizeList(List& L){
    // cout<<"begin normalize"<<endl;
    // cout<<"argument"<<endl;
    // cout<<L<<endl;
    int return_sign = 0;
    if(L.length() == 0){
        return 0;
    }
    int carry_out = 0;
    int64_t curr_ele;
    // iterate from right to left
    for(L.moveBack();L.position()>0;L.movePrev()){
        // cout<<"=================="<<endl;
        // cout<<"num to be normalized"<<endl;
        curr_ele = L.peekPrev();
        // cout<<curr_ele<<endl;
        curr_ele += carry_out;
        // cout<<"w carry out"<<endl;
        // cout<<curr_ele<<endl;
        carry_out = 0;
        if(curr_ele<0){
            // cout<<"too small"<<endl;
            carry_out = floor(curr_ele/double(b));
            // cout<<"carry_out = "<<floor(curr_ele/double(b))<<" = floor("<<curr_ele<<"/"<<double(b)<<endl;
            int64_t b3 = -b;
            int64_t carry_out3 = carry_out;
            int64_t product3 = b3*carry_out3;
            //curr_ele += carry_out * (-1 * b);
            // cout<<"curr_ele pre increase"<<endl;
            // cout<<curr_ele<<endl;
            curr_ele += product3;
            // cout<<"curr_ele post increase"<<endl;
            // cout<<curr_ele<<endl;
            L.setBefore(curr_ele);
        }else{
            // cout<<"num too big or fine"<<endl;
            // cout<<"determining carry out"<<endl;
            // cout<<"carry_out = curr_ele / b"<<endl;
            // cout<<"curr_ele = "<<curr_ele<<endl;
            // cout<<"b = "<<b<<endl;
            carry_out = curr_ele/b;
            // cout<<"carry out"<<endl;
            // cout<<carry_out<<endl;
            // cout<<"cur_ele pre reduction"<<endl;
            // cout<<curr_ele<<endl;
            // cout<<"reducinig curr_ele by "<<carry_out*b<<" = "<<carry_out<<" * "<<b<<endl;
            uint64_t b2 = b;
            uint64_t carry_out2 = carry_out;
            uint64_t product2 = b2*carry_out2;
            // cout<<"product2 = "<<product2<<endl;
            //curr_ele -= carry_out*b;
            curr_ele -= product2;
            // cout<<"new curr_ele"<<endl;
            // cout<<curr_ele<<endl;
            L.setBefore(curr_ele);
        }
        /*
        // if the number is too big
        while (curr_ele >= b){
            carry_out++;
            curr_ele-=b;
        }
        // if the number is too small
        while(curr_ele <0){
            carry_out--;
            curr_ele += b;
        }
        L.setBefore(curr_ele);
        */
        
        /*
        if(curr_ele<0){
            cout<<"curr_ele: "<<curr_ele<<" is too small"<<endl;
            carry_out = curr_ele/b;
            cout<<"carry_out = "<< carry_out <<endl;
            curr_ele = abs(curr_ele % b);
            cout<<"curr_ele = "<< curr_ele <<endl;
            //curr_ele+=(carry_out * (-1 * b));
        }else if (curr_ele>=b){
            cout<<"curr_ele: "<<curr_ele<<" is too big"<<endl;
            carry_out = curr_ele/b;
            cout<<"carry_out = "<< carry_out<< endl;
            curr_ele = curr_ele % b;
            cout<<"curr_ele = "<< curr_ele <<endl;
        }
        L.setBefore(curr_ele);
        */
        /*

            carry_out = curr_ele/b;
            curr_ele = curr_ele % b;
            //curr_ele -= (carry_out * b);
            L.setBefore(curr_ele);
            */
    }
    // if there is still carryout: prepend
    if (carry_out != 0){
        L.insertBefore(carry_out);
    }
    // if leading value is negative go again
    if(L.peekPrev() < 0){
        negateList(L);
        for(L.moveBack();L.position() > 0;L.movePrev()){
            if(L.peekPrev()<0){
                normalizeList(L);
                break;
            }

        }
        //normalizeList(L);
        return_sign = -1;
    }else{
        return_sign = 1;
    }
    // remove leading 0s
    L.moveFront();
    while(L.peekNext() == 0 && L.length() != 0){
        L.eraseAfter();
    }
    return return_sign;
}

void shiftList(List& L, int pp){
    //int stored_position = L.position();

    //scalarMultList(L,pow(b,pp));
    L.moveBack();
    for (int i = 0; i < pp; i++){
        L.insertBefore(0);
    }
    /*
    L.moveBack();
    while(L.position() != stored_position){
        L.movePrev();
    }
    */
}

void scalarMultList(List& L, ListElement m){
    // cout<<"scalarMultList"<<endl;
    // cout<<" L = "<<L<<endl;
    // cout<<"m="<<m<<endl;
    int64_t product;
    int64_t factor1, factor2;
    factor1 = m;
    for (L.moveBack();L.position() > 0; L.movePrev()){
        factor2 = L.peekPrev();
        // cout<<"product = "<<factor1<<"*"<<factor2<<endl;
        product = factor1 * factor2;
        // cout<<"product = "<<product<<endl;
        //product = int64_t(m) * int64_t(L.peekPrev());
        L.setBefore(product);
    }
    //normalizeList(L);
}
// Overriden Operators -----------------------------------------------------

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    return(A.compare(B) == 0);
}

bool operator<( const BigInteger& A, const BigInteger& B ){
    return(A.compare(B)==-1);
}

bool operator<=( const BigInteger& A, const BigInteger& B ){
    return(A.compare(B)==-1||A.compare(B)==0);
}

bool operator>( const BigInteger& A, const BigInteger& B ){
    return(A.compare(B)==1);
}

bool operator>=( const BigInteger& A, const BigInteger& B ){
    return(A.compare(B)==1||A.compare(B)==0);
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return(A.add(B));
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}


BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return B;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}