#!/bin/sh
klee pfscan-1.0.o -Vd 3 ${PWD}/file/ 2>result.txt 1>&2
