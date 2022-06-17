//Name: Elliott Jensen 
//CruzID: egjensen
//Assignment: pa1
//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//
// compile:
//
//     gcc -std=c17 -Wall -o FileIO FileIO.c
//
//-----------------------------------------------------------------------------
#define _SVID_SOURCE
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int line_count;
    FILE *in, *out,*countfile;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    countfile = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file, then count and print tokens
    line_count = 0;
    
    int i = 0;

    char buf[1024];

    char ch;
    while((ch=fgetc(countfile))!=EOF){
        if(ch=='\n'){
            line_count++;
        }
    }
    char **words = malloc(line_count * sizeof(char *));
    
    while (fgets(buf, MAX_LEN, in)!=NULL){
        buf[strlen(buf)-1]='\0';

        words[i] = strdup(buf);
        i++;
    }
    List I = newList();// indices
    List S = newList();// sorted indices
    for(i=0;i<line_count;i++){
        append(I,i);
    }

    for(moveFront(I);index(I)>=0;moveNext(I)){
        if (index(I) == 0){
            append(S,0);
            continue;
        }
    
        moveFront(S);
        while ((index(S) != -1) && (strcmp(words[get(I)], words[get(S)])> 0)){
            moveNext(S);
        }
        if (index(S) == -1){
            append(S,get(I));
        }else{
            insertBefore(S,get(I));
        }
    }

    for(moveFront(S);index(S)>=0;moveNext(S)){
        fprintf(out,"%s\n",words[get(S)]);
    }
    free(words);
    freeList(&S);
    freeList(&I);



        
    // close files 
    fclose(in);
    fclose(out);

    return(0);
}
