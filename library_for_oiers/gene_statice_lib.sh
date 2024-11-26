#!/usr/bin/bash

filename=$1

g++ -c $filename.cpp
ar -crv lib$filename.a $filename.o
rm $filename.o
