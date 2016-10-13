#!/bin/sh
klee ctrace.foobar.comb.mutex.o 1 2>result.txt 1>&2
