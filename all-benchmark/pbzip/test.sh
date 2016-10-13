#!/bin/sh
klee pbzip2_revise2.o -k -f -p4 ${PWD}/input 2>result.txt 1>&2
