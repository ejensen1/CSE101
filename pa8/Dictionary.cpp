// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa8

#include<iostream>
#include<string>
#include<stdexcept>
#include<climits>

#include"Dictionary.h"

#define RED 1
#define BLACK 0

using namespace std;

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R!=nil){
        inOrderString(s,R->left);
        s+=R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s,R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R!= nil){
        s+= R->key + "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N){
    if((R != nil)||(R!=findMax(R))){
        setValue(R->key,R->val);
        preOrderCopy(R->left,N);
        preOrderCopy(R->right,N);
    }
}

void Dictionary::postOrderDelete(Node* R){
    if (R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        //R = nil;
    }
    return;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if ((R == nil)||(k == R->key)){
        return R;
    }else if(k<R->key){
        return search(R->left,k);
    }else{
        return search(R->right,k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R){
    Node* temp = R;
    while(temp->left != nil){
        temp = temp->left;
    }
    return temp;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if(size()==0){
        return nil;
    }
    Node* temp = R;
    while(temp->right != nil){
        temp = temp->right;
    }
    return temp;
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == findMax(root)){
        return nil;
    }
    if (N->right != nil){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while((y != nil) && (N == y->right)){
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == findMin(root)){
        return nil;
    }
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while((y!=nil)&&(N==y->left)){
        N=y;
        y=y->parent;
    }
    return y;
}

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    Node* y = N->right;
    N->right = y->left;
    /*
    if (y->left != nil){
        y->left->parent;
    }
    */
    y->parent = N->parent;
    if(N->parent==nil){
        root = y;
    }else if(N==N->parent->left){
        N->parent->left=y;
    }else{
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
    return;
}

void Dictionary::RightRotate(Node* N){
    //cout<<"inside right rotate"<<endl;
    //cout<<to_string()<<endl;
    Node* y = N->left;
    N->left = y->right;
    if(y->right != nil){
        //cout<<"if1"<<endl;
        y->right->parent=N;
    }
    y->parent = N->parent;
    if(N->parent == nil){
        //cout<<"if2"<<endl;
        root=y;
    }else if(N==N->parent->right){
        //cout<<"else if"<<endl;
        N->parent->right = y;
    }else{
        //cout<<"else"<<endl;
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
    //cout<<"exiting right rotate"<<endl;
    //cout<<to_string()<<endl;
    return;
}

void Dictionary::RB_InsertFixUp(Node* N){
    Node* y;
    while(N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            y = N->parent->parent->right;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else{
                // its here
                //cout<<to_string()<<endl;
                if(N==N->parent->right){
                    N=N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }else{
            y = N->parent->parent->left;
            if(y->color == RED){
                N->parent->color = BLACK;
                y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else{
                if(N==N->parent->left){
                    N=N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent==nil){
        root=v;
    }else if(u==u->parent->left){
        u->parent->left=v;
    }else{
        u->parent->right=v;
    }
    v->parent=u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N){
    while(N!=root&&N->color==BLACK){
        if(N==N->parent->left){
            Node* w = N->parent->right;
            if(w->color==RED){
                w->color=BLACK;
                N->parent->color=RED;
                LeftRotate(N->parent);
                w=N->parent->right;
            }
            if(w->left->color==BLACK&&w->right->color==BLACK){
                w->color=RED;
                N=N->parent;
            }else{
                if(w->right->color==BLACK){
                    w->left->color=BLACK;
                    w->color=RED;
                    RightRotate(w);
                    w=N->parent->right;
                }
                w->color=N->parent->color;
                N->parent->color=BLACK;
                w->right->color=BLACK;
                LeftRotate(N->parent);
                N=root;
            }
        }else{
            Node* w = N->parent->left;
            if(w->color==RED){
                w->color=BLACK;
                N->parent->color=RED;
                RightRotate(N->parent);
                w=w->parent->left;
            }
            if(w->right->color==BLACK&&w->left->color==BLACK){
                w->color=RED;
                N=N->parent;
            }else{
                if(w->left->color==BLACK){
                    w->right->color=BLACK;
                    w->color=RED;
                    LeftRotate(w);
                    w=N->parent->left;
                }
                w->color=N->parent->color;
                N->parent->color=BLACK;
                w->left->color=BLACK;
                RightRotate(N->parent);
                N=root;
            }
        }
    }
    N->color=BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* x;
    Node* y = N;
    int y_original_color = y->color;
    if(N->left==nil){
       x=N->right;
       RB_Transplant(N,N->right);
    }else if(N->right==nil){
        x=N->left;
        RB_Transplant(N,N->left);
    }else{
        y=findMin(N->right);
        y_original_color = y->color;
        x=y->right;
        if(y->parent==N){
            x->parent=y;
        }else{
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent=y;
        }
        RB_Transplant(N,y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if(y_original_color==BLACK){
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors ----------------------------------------

// Node Constructor

Dictionary::Node::Node(keyType k, valType v){
/*
    if(this == root){
        root->parent = nil;
    }
    if(this == nil){
        this->parent = nil;
    }
*/
    key = k;
    val = v; 
    //color = BLACK;
    parent=nullptr;
    right=nullptr;
    left=nullptr;
    //color = BLACK;
    /*
    parent=nil;
    left = nil;
    right = nil;
    */
}

// Constructor
Dictionary::Dictionary(){
    nil = new Node("\0",INT_MIN);
    root = nil;
    current = nil;
    nil->color = BLACK;
    num_pairs = 0;
    /*
    num_pairs = 0;
    root = nullptr;
    current = nullptr;
    */
    //nil->parent=nullptr;
    //nil->right=nullptr;
    //root->parent=nil;
    //root->left = nil;
    //root->right = nil;
    //nil->left=nullptr;
    //nil->parent=nil;
    //nil->left = nil;
    //nil->right = nil;

    

    //cout<<"setting parent to nil"<<endl;
    //cout<<"exiting creation"<<endl;
    //nil = nullptr;
    //current = nil;
    //root = nil;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D):Dictionary(){
    //num_pairs=D.num_pairs;
/*
    cout<<"calling copy constructor"<<endl;
    clear();
    preOrderCopy(D.root,findMax(D.root));
*/
    //num_pairs=D.num_pairs;
/*
    cout<<"calling copy constructor"<<endl;
    num_pairs=D.num_pairs;
    cout<<"pre preOrderCopy"<<endl;
    preOrderCopy(D.root,findMax(D.root));
    cout<<"post preOrderCopy"<<endl;
    current=D.current;
    return;

    clear();
    preOrderCopy(D.root,findMax(D.root));
    return;
    if(size()!=0){
        clear();
    }
    num_pairs = D.num_pairs;
    preOrderCopy(D.root,root);
*/
}

// Destructor

Dictionary::~Dictionary(){
    //cout<<"calling delete"<<endl;
/*
    clear();
    root = nullptr;
    current = nullptr;
    nil = nullptr;
*/
    // postOrderDelete(root);
}

// Access functions --------------------------------------------------------

//delete
// Dictionary::Node* Dictionary::getRoot(){
//     return root;
// }

int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const{
    if(size()==0){
        return false;
    }
    if (search(root,k)== nil){
        return false;
    }
    return true;
}

valType& Dictionary::getValue(keyType k) const{
    if(contains(k)==false){
        throw std::logic_error("Dictionary: getValue(): contains() = false");
    }
    return search(root,k)->val;
}

bool Dictionary::hasCurrent() const{
    if(size()==0){
        return false;
    }
    if(current!=nil){
        return true;
    }
    return false;
}

keyType Dictionary::currentKey() const{
    if(hasCurrent()==false){
        throw std::logic_error("Dictionary: currentKey(): accessing val when current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if(hasCurrent()==false){
        throw std::logic_error("Dictionary: currentVal(): accessing val when current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

void Dictionary::clear(){
    if(size()==0){
        return;
    }
    postOrderDelete(root);
    root = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
    Node* z = new Node(k,v);
    Node* y = nil;
    Node* x = root;
    while(x!=nil){
        y=x;
        if(z->key==x->key){
            x->val=v;
            return;
        }
        if(z->key<x->key){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    z->parent = y;
    if(y==nil){
        root=z;
    }else if(z->key<y->key){
        y->left = z;
    }else{
        y->right = z;
    }
    z->left=nil;
    z->right=nil;
    z->color=RED;
    RB_InsertFixUp(z);
    num_pairs++;
    return;
}

void Dictionary::Transplant(Node* u, Node* v){
    if (u->parent == nil){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    if (v != nil){
        v->parent = u->parent;
    }
}

void Dictionary::remove(keyType k){
    Node *z = search(root,k);
    if (z->left == nil){
        Transplant(z,z->right);
    }else if (z->right == nil){
        Transplant(z,z->left);
    }else{
        Node* y = findMin(z->right);
        if (y->parent != z){
            Transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z,y);
        y->left = z->left;
        y->left->parent =y;
    }
    num_pairs--;
    if((hasCurrent())&&(k==currentKey())){
        current=nil;
    }
}

void Dictionary::begin(){
    if (num_pairs != 0){
        current = findMin(root);
    }
}

void Dictionary::end(){
    current = findMax(root);
}

void Dictionary::next(){
    current = findNext(current);
}

void Dictionary::prev(){
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// Dictionary::Node* Dictionary::search

std::string Dictionary::to_string() const{
    std::string s="";
    inOrderString(s,root);

    return s;
}

std::string Dictionary::pre_string() const{
    std::string s="";
    preOrderString(s,root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const{
    if((size()==0)&&(D.size()==0)){
       return true; 
    }else if (size()!=D.size()){
        return false;
    }
    string s1 = "";
    string s2 = "";
    preOrderString(s1,root);
    preOrderString(s2,root);
    return (s1 == s2);
}

// Overloaded Operators ----------------------------------------------------
 std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
     return stream << D.to_string();
 }

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
    this->clear();
    preOrderCopy(D.root,root);
    return *this;
}
