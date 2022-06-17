// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa4
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Matrix.h"
#include "List.h"


typedef struct EntryObj{
    int col;
    double value;
} EntryObj;

typedef struct MatrixObj{
    List *list_arr;
    int size;
    int NNZ;
} MatrixObj;

// Constructors and Desctructors

Entry newEntry(int col, double value){
    Entry E = malloc(sizeof(EntryObj));
    E->col = col;
    E->value = value;
    return E;
}

void freeEntry(Entry* pE){
    if ((pE != NULL) && (*pE != NULL)){
        free(*pE);
        *pE = NULL;
    }
    return;
}

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->list_arr = (List *)calloc(n + 1, sizeof(List));
    for (int i = 0; i < n + 1; i++){
        M->list_arr[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix *pM){
    Matrix M = *pM;
    for (int i = 0; i < size(M); i++){
        freeList(&(M->list_arr[i]));
    }
    return;
    /*
    printf("free\n");
    if (pM == NULL){
        fprintf(stderr, "Matrix Error: calling freeMatrix on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    List curr_list;
    for (int i = 0; i < size(*pM) + 1; i++){
        curr_list = (*pM)->list_arr[i];
        for (int i = 0; i < length(curr_list) + 1; i++){
            deleteFront(curr_list);
        }
        
       // for(moveFront(curr_list); index(curr_list) >= 0; moveNext(curr_list)){
        //    freeEntry(&(get(curr_list)));
       // }
        //for (moveFront(&((*pM)->list_arr[i]));index(&((*pM)->list_arr[i]))>=0;moveNext(&((*pM)->list_arr[i]))){

    }
    for (int i = 0; i < size(*pM) + 1; i++){
        freeList(&((*pM)->list_arr[i]));
    }
    freeList(&curr_list);
    free((*pM)->list_arr);
    free(*pM);
    *pM = NULL;
    printf("returning free\n");
    return;
    */
}

// Accessor functions


int size(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}


int NNZ(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix referece\n");
        exit(EXIT_FAILURE);
    }
    int num_elements = 0;
    for (int i = 1; i < size(M)+ 1; i++){
        num_elements += length(M->list_arr[i]);
    }
    return M->NNZ;
}

int equals(Matrix A, Matrix B){
    if ((A == NULL)||(B == NULL)){
        fprintf(stderr,"Matrix Error: calling equals() on NULL Matrix referent\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)){
        return 0;
    }
    List curr_list1, curr_list2;
    Entry E1, E2;
    for (int i = 1; i < size(A) + 1; i++){
        curr_list1 = A->list_arr[i];
        curr_list2 = B->list_arr[i];
        if (length(curr_list1) != length(curr_list2)){
            return 0;
        }
        moveFront(curr_list2);
        for (moveFront(curr_list1);index(curr_list1)>=0;moveNext(curr_list1)){
            E1 = get(curr_list1);
            E2 = get(curr_list2);
            if ((E1->col != E2->col) || (E1->value != E2->value)){
                return 0;
            }
            moveNext(curr_list2);
            if (index(curr_list2) >= 0){
                break;
            }
        }
    }
    return 1;
}

// Manipulator Functions

void makeZero(Matrix M){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling makeZero() on NULL matrix referece\n");
        exit(EXIT_FAILURE);
    }
    M->NNZ = 0;
    for (int i = 1; i < size(M) + 1; i++){
        /*
        for (moveFront(M->list_arr[i]);index(M->list_arr[i]>=0;moveNext(M->list_arr[i])){
            freeEntry(get(M->list_arr[i]));
        }
        */
       M->list_arr[i] = newList();
    }
    return;
    
}

void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if ((i < 1) || ( i > size(M))){
        fprintf(stderr, "Matrix Error: calling change Entry when i: %d is outside of the matrix size: %d",i,size(M));
        exit(EXIT_FAILURE);
    }
    if ((j < 1) || ( j > size(M))){
        fprintf(stderr, "Matrix Error: calling change Entry when j: %d is outside of the matrix size: %d",j,size(M));
        exit(EXIT_FAILURE);
    }
    

    Entry E = newEntry(j,x);
    List row = M->list_arr[i];

    if (length(row) == 0){
        if(x!=0){
            M->NNZ++;
            append(row, E);
            return;
        } else{
            return;
        }
        /*
        if(x == 0){
            printf("x = 0\n");
            return;
        }
        printf("x!=0\n");
        M->NNZ++;
        append(row, E);
        return;
        */
    }
    moveFront(row);
    Entry curr_entry = front(row);
    // we walk the list and put the cursor on the col that equals j or is greater than j
    while ((index(row) != -1) && (curr_entry->col < j)){
        moveNext(row);
        if (index(row) != -1){
            curr_entry = get(row);
        }
    }
    // if ijth entry != 0
    if (curr_entry->col == j){
        // if x = 0
        if ((x == 0)&& (curr_entry->value != 0)){
            delete(row);
            M->NNZ--;
            return;
        // if x != 0
        } else {
            curr_entry->value = x;
            
            //set(row,E);
            return;
        }
    }
    // if it belongs at the end (ijth entry = 0)
    if(index(row) == -1){
        if (x != 0){
            append(row,E);
            M->NNZ++;
            return;
        } else {
            return;
        }
    // if ijth entry = 0 and it belongs in between two entries
    } else {
        if (x == 0){
            return;
        }
        M->NNZ++;
        insertBefore(row,E);
    }
    return;
}

// Arithmetic Operations

Matrix copy(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(size(A));
    List curr_list1;
    Entry E;
    for (int i = 1; i < size(A) + 1; i++){
        curr_list1 = A->list_arr[i];

        for (moveFront(curr_list1);index(curr_list1) >= 0; moveNext(curr_list1)){
            E = get(curr_list1);
            changeEntry(C,i,E->col,E->value);
            //N = newEntry(E->col,E->value;)
            //append(curr_list2,N);
        }
    }
    return C;
}

Matrix transpose(Matrix A){
    if (A == NULL){
        fprintf(stderr, "Matrix Error: calling transpose() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix(size(A));
    List curr_list;
    Entry E;
    for (int i = 1; i < size(A) + 1; i++){
        curr_list = A->list_arr[i];
        for (moveFront(curr_list);index(curr_list) >= 0; moveNext(curr_list)){
            E = get(curr_list);
            changeEntry(T,E->col,i,E->value);
        }
    }
    return T;

}

Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        fprintf(stderr,"Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix S = newMatrix(size(A));
    List curr_list;
    Entry E;
    for (int i = 1; i < size(A) + 1; i++){
        curr_list = A->list_arr[i];
        if (length(curr_list) == 0){
            continue;
        }
        for (moveFront(curr_list);index(curr_list) >= 0; moveNext(curr_list)){
            E = get(curr_list);
            changeEntry(S,i,E->col,(x * (E->value)));
        }
    }
    return S;
}

List addList(List A, List B,bool sign){
    if ((A == NULL) || (B == NULL)){
        fprintf(stderr,"Matrix Error: calling addList() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    List S = newList();
    Entry E1, E2, N;
    int negative_value;
    if (length(A) == 0){
        for(moveFront(B);index(B)>=0;moveNext(B)){
            E1 = get(B);
            negative_value = -(E1->value);
            
            N = newEntry(E1->col,negative_value);
            append(S,N);
        }
        return S;
    }
    
    moveFront(A);
    moveFront(B);
    while((index(A) >= 0) && (index(B) >= 0)){
        E1 = get(A);
        E2 = get(B);
        if (E1->col == E2->col){
            if (sign){
                N = newEntry(E1->col, (E1->value + E2->value));
            } else {
                N = newEntry(E1->col, (E1->value - E2->value));
            }
            append(S,N);
            moveNext(A);
            moveNext(B);
        } else if (E1->col < E2->col){
            N = newEntry(E1->col,E1->value);
            append(S,N);
            moveNext(A);
        } else {
            if(sign){
                N = newEntry(E2->col,E2->value);
            }else{
                negative_value = -(E2->value);
                N=newEntry(E2->col,negative_value);
            }
            append(S,N);
            moveNext(B);
        }
    }
    if ((index(A) == -1) && (index(B) != -1)){
        while(index(B) >= 0){
            E1 = get(B);
            if(sign){
                N = newEntry(E1->col,E1->value);
            }else{
                negative_value = -(E1->value);
                N=newEntry(E1->col,negative_value);
            }
            append(S,E1);
            moveNext(B);
        }
    } 
    else if ((index(A) != -1) && (index(B) == -1)){
        while (index(A) >= 0){
            E1 = get(A);
            append(S,E1);
            moveNext(A);
        }
    }

    return S;
}

Matrix sum(Matrix A, Matrix B){
    if ((A == NULL) && (B == NULL)){
        fprintf(stderr, "Matrix Error: calling sum() on NULL List refernce\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling sum() on Null Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (equals(A,B)){
        Matrix S = scalarMult(2,A);
        return S;
    }
    Matrix S = newMatrix(size(A));
    List L;
    Entry E;
    for (int i = 1; i < size(A)+1; i++){
        L = addList(A->list_arr[i],B->list_arr[i],1);
        for (moveFront(L);index(L)>=0;moveNext(L)){
            E = get(L);
            changeEntry(S,i,E->col,E->value);
        }
    }
    return S;
}

Matrix diff(Matrix A, Matrix B){
    if ((A == NULL) && (B == NULL)){
        fprintf(stderr, "Matrix Error: calling diff() on NULL List refernce\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling sum() on Null Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (NNZ(A) == 0){
        Matrix R = scalarMult(-1,B);
        return R;
    }
    if (equals(A,B)){
        Matrix S = newMatrix(size(A));
        return S;
    }
    Matrix S = newMatrix(size(A));
    List L;
    Entry E;
    for (int i = 1; i < size(A)+1; i++){
        L = addList(A->list_arr[i],B->list_arr[i],0);
        for (moveFront(L);index(L)>=0;moveNext(L)){
            E = get(L);
            changeEntry(S,i,E->col,E->value);
        }
    }
    return S;
}

double dot(List A, List B){
    if (A == NULL || B == NULL){
        fprintf(stderr, "Matrix Error: calling dot on NULL list reference (one of them)\n");
        exit(EXIT_FAILURE);
    }
    /*
    if (length(A) != length(B)){
        fprintf(stderr, "Matrix Error: calling dot on lists of unequal length. A length: %d, B length %d\n",length(A),length(B));
        exit(EXIT_FAILURE);
    }
    */
    /*
    if((length(A) == 0) || (length(B) == 0)){
        return 0;
    }
    */
    
    double dot_product;
    Entry E1, E2;
    moveFront(A);
    moveFront(B);
    while((index(A) >= 0) && (index(B) >= 0)){
        E1 = get(A);
        E2 = get(B);

        if(E1->col == E2->col){
            dot_product += ((E1->value) * (E2->value));
            moveNext(A);
            moveNext(B);
        }
        else if (E1->col < E2->col){
            moveNext(A);
        } else {
            moveNext(B);
        }
    }
    return dot_product;
}

bool fequal(double a, double b)
{
    return fabs(a-b) < 0.0001;
}

Matrix product(Matrix A, Matrix B){
    if ((A == NULL) && (B == NULL)){
        fprintf(stderr, "Matrix Error: calling product() on NULL List refernce\n");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling product() on Null Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix P = newMatrix(size(A));
    Matrix T = transpose(B);
    List L1, L2;
    double dot_product;
    for (int i = 1; i < size(A) + 1; i++){
        //printf("i: %d\n",i);
        L1 = A->list_arr[i];
        for (int j = 1; j < size(T) + 1; j++){
            //printf("j: %d\n",j);
            L2 = T->list_arr[j];
            dot_product = dot(L1,L2);
            //printf("about to call change entry with arguments i: %d, j %d",i,j);
            if (fequal(dot_product,0.0)){
                continue;
            }else{
                changeEntry(P,i,j,dot_product);
            }
        }
    }
    return P;
}

void printEntry(Entry E){
    if (E == NULL){
        fprintf(stderr, "Entry Error: calling printEntry on NULL Entry reference\n");
        exit(EXIT_FAILURE);
    }
    printf("(%d, %.1f)\n",E->col, E->value);
    return;
}

void printMatrix(FILE* out, Matrix M){
    if (M == NULL){
        fprintf(stderr,"Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    List curr_list;
    Entry E;
    for (int i = 1; i < size(M) + 1; i++){
        curr_list = M->list_arr[i];
        if(length(curr_list)==0){
            continue;
        }
        fprintf(out,"%d: ",i);
        for (moveFront(curr_list);index(curr_list) >= 0; moveNext(curr_list)){
            E = get(curr_list);
            fprintf(out,"(%d, %.1f) ", E->col, E->value);
        }
        if(length(curr_list)>=0){
            fprintf(out,"\n");
        }
    }
    return;
}

/*
int main(void){
    Matrix A = newMatrix(10);
    Matrix B = newMatrix(10);
    Matrix C = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(C, 1, 1, 1);
    if (equals(A, C))
      return 1;
    Matrix D = newMatrix(15);
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 3, 1);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);
    if (!equals(A, B))
      return 2;
    changeEntry(A, 1, 3, 0);
    if (equals(A, B))
      return 3;
    changeEntry(A, 1, 1, 0);
    makeZero(B);
    changeEntry(A, 10, 10, 10);
    changeEntry(B, 10, 10, 10);
    if (!equals(A, B))
      return 4;

    freeMatrix(&A);
    freeMatrix(&B);
    A = A = newMatrix(10);
    B = B = newMatrix(10);
    int valcount = 1;
    for (int j = 1; j <= 10; j++) {
      for (int k = 1; k <= 10; k++) {
        // hint: this is 1-10000 left-to-right row-by-row
        changeEntry(A, j, k, valcount++);
      }
      changeEntry(B, j, j, 1); // hint: this is the identity matrix
    }
    freeMatrix(&C);
    freeMatrix(&D);
    C = scalarMult(2, A);
    D = sum(A, A);
    if (!equals(C, D))
        printf("5\n");

    freeMatrix(&C);
    freeMatrix(&D);
    C = scalarMult(-2, A);
    printf("A:\n");
    printMatrix(stdout,A);
    Matrix As1 = diff(A, A);
    printf("DOING SUBTRACTION\n");
    printf("As1\n");
    printMatrix(stdout,As1);
    printf("MINUS\n");
    printMatrix(stdout,A);
    Matrix As2 = diff(As1, A);
    printf("As2\n");
    printMatrix(stdout,As2);
    D = diff(As2, A);
    freeMatrix(&As1);
    freeMatrix(&As2);
    printf("C:\n");
    printMatrix(stdout,C);
    printf("D:\n");
    printMatrix(stdout,D);
    if (!equals(C, D))
        printf("6\n");

    freeMatrix(&C);
    C = product(A, B);
    if (!equals(C, A))
        printf("7\n");

   return 0;
}
*/