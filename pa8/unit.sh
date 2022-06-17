#!/usr/bin/bash
g++ -std=c++17 -Wall -c -g MDT.cpp Dictionary.cpp
g++ -std=c++17 -Wall -o MDT MDT.o Dictionary.o
./MDT -v 
