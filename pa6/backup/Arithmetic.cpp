// Name: Elliott Jensen
// CruzID: egjensen
// Assignment: pa6
//-----------------------------------------------------------------------------
// FileIO.cpp
// Illustrates file input-output commands and text processing using the
// string functions find_first_of(), find_first_not_of() and substr().
// 
// compile:
//
//      g++ -std=c++17 -Wall -o FileIO FileIO.cpp
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"
#include"List.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   string s1,s2,s3;
   getline(in,s1);
   getline(in,s2);
   getline(in,s3);

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger two = BigInteger("2");
   BigInteger three = BigInteger("3");
   BigInteger nine = BigInteger("9");
   BigInteger sixteen = BigInteger("16");
   

   out << A << endl << endl;
   out << B << endl << endl;

   out << A+B << endl << endl;
   out << A-B << endl << endl;
   out << A-A << endl << endl;
   out << (three * A) - (two * B) << endl << endl;
   out << A*B << endl<< endl;
   out << A*A << endl<< endl;
   out << B*B << endl << endl;
   out << (sixteen*B*B*B*B*B)+(nine*A*A*A*A)<<endl;


   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
