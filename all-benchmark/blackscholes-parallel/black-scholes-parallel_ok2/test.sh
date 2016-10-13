#!/bin/sh
klee blackscholes.m4.o 2 ./input/in_4.txt ./output/out_4.txt 2>$PWD/result.txt 1>&2
