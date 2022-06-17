// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa7

#include<iostream>
#include<string>
#include<stdexcept>
#include<climits>

#include"Dictionary.h"

using namespace std;

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R!=nullptr){
        inOrderString(s,R->left);
        s+=R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s,R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R!= nullptr){
        s+= R->key + "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N){
    if((R != nullptr)||(R!=findMax(R))){

        setValue(R->key,R->val);
        preOrderCopy(R->left,N);
        preOrderCopy(R->right,N);
    }
}

void Dictionary::postOrderDelete(Node* R){
    if (R != nullptr){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        //R = nullptr;
    }
    return;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if ((R == nullptr)||(k == R->key)){
        return R;
    }else if(k<R->key){
        return search(R->left,k);
    }else{
        return search(R->right,k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R){
    Node* temp = R;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    if(size()==0){
        return nullptr;
    }
    Node* temp = R;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp;
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if (N == findMax(root)){
        return nullptr;
    }
    if (N->right != nullptr){
        return findMin(N->right);
    }
    Node* y = N->parent;
    while((y != nullptr) && (N == y->right)){
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if (N == findMin(root)){
        return nullptr;
    }
    if(N->left != nullptr){
        return findMax(N->left);
    }
    Node* y = N->parent;
    while((y!=nullptr)&&(N==y->left)){
        N=y;
        y=y->parent;
    }
    return y;
}

// Class Constructors & Destructors ----------------------------------------

// Node Constructor

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v; 
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Constructor
Dictionary::Dictionary(){
    num_pairs = 0;
    root = nullptr;
    current = nullptr;
    nil = nullptr;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D){
    num_pairs=D.num_pairs;
    preOrderCopy(D.root,findMax(D.root));
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
}

// Destructor

Dictionary::~Dictionary(){
    clear();
    root = nullptr;
    current = nullptr;
    nil = nullptr;
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
    if (search(root,k)== nullptr){
        return false;
    }
    return true;
}

// test this
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
    if(current!=nullptr){
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
    root = nullptr;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
    if(num_pairs==0){
        root=new Node(k,v);
        num_pairs++;
        root->parent = nullptr;
        return;
    }
    
    Node *N = new Node(k,v);
    N->key = k;
    N->val = v;

    Node* y = nil;
    Node* x =  root;
    while(x != nullptr){
        y = x;
        if (N->key == x->key){
            x->val = v;
            // delete N;
            return;
        }
        if (N->key < x->key){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    N->parent = y;
    if (y == nullptr){
        root = N;
    }else if (N->key < y->key){
        y->left = N;
    } else {
        y->right = N;
    }
    num_pairs++;
    return;
}

void Dictionary::Transplant(Node* u, Node* v){
    if (u->parent == nullptr){
        root = v;
    } else if (u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    if (v != nullptr){
        v->parent = u->parent;
    }
}

void Dictionary::remove(keyType k){
    Node *z = search(root,k);
    if (z->left == nullptr){
        Transplant(z,z->right);
    }else if (z->right == nullptr){
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
        current=nullptr;
    }
    delete z;
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
    std::string s;
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
    cout<<"calling operator="<<endl;
    this->clear();
    preOrderCopy(D.root,root);
    return *this;
}

