// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa4
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"

int main(int argc, char * argv[]){
    FILE *in, *out;
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n",argv[0]);
        exit(1);
    }
    in = fopen(argv[1],"r");
    if (in == NULL){
        printf("Unable to open file %s for reading\n",argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // process the input file and create the graph
    int matrix_size,nnz_a,nnz_b;
    fscanf(in,"%d %d %d\n", &matrix_size,&nnz_a,&nnz_b);
    
    double value;
    int i,j;
    Matrix A = newMatrix(matrix_size);
    int count = 1;
    // build matrix a 
    while((fscanf(in,"%d" "%d" "%lf", &i, &j, &value))!=EOF){
        count++;
        changeEntry(A,i,j,value);
        if(count >nnz_a){
            break;
        }
    }
    count = 0;
    Matrix B =newMatrix(matrix_size);
    // build matrix b
    while((fscanf(in,"%d" "%d" "%lf", &i, &j, &value))!=EOF){
        changeEntry(B,i,j,value);
        if(count >nnz_b){
            break;
        }
        count++;
    }
    fprintf(out,"A has %d non-zero entries:\n",nnz_a);
    printMatrix(out,A);
    fprintf(out,"\n");
    fprintf(out,"B has %d non-zero entries:\n",nnz_b);
    printMatrix(out,B);
    fprintf(out,"\n");

    // scalar multiply

    fprintf(out,"(1.5)*A =\n");
    Matrix C = scalarMult(1.5,A);
    printMatrix(out,C);
    fprintf(out,"\n");

    // sum

    fprintf(out,"A+B =\n");
    //printf("A:\n");
    //printMatrix(stdout,A);
    //printf("B:\n");
    //printMatrix(stdout,B);
    C = sum(A,B);
    printMatrix(out,C);
    fprintf(out,"\n");

    // sum A+A

    fprintf(out,"A+A =\n");
    C = sum(A,A);
    printMatrix(out,C);
    fprintf(out,"\n");

    // diff B-A
    fprintf(out,"B-A =\n");
    C = diff(B,A);
    printMatrix(out,C);
    fprintf(out,"\n");

    // idk what this is
    fprintf(out,"A-A =\n");
    fprintf(out,"\n");

    //Transpose A
    fprintf(out,"Transpose(A) =\n");
    C = transpose(A);
    printMatrix(out,C);
    fprintf(out,"\n");

    // A*B

    fprintf(out,"A*B =\n");
    C = product(A,B);
    printMatrix(out,C);
    fprintf(out,"\n");

    //B*B
    fprintf(out,"B*B =\n");
    C = product(B,B);
    printMatrix(out,C);
    
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(in);
    fclose(out);
    return 0;
}
