#!/bin/sh
klee ctrace.foobar.comb.mutex.o 2 2>result.txt 1>&2
