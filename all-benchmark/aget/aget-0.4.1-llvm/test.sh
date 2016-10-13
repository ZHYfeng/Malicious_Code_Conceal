#!/bin/sh
# klee AGET http://mirrors.163.com/archlinux/community/os/x86_64/zynaddsubfx-2.5.4-1-x86_64.pkg.tar.xz.sig 2>result.txt 1>&2
# klee AGET  2>result.txt 1>&2
klee AGET http://127.0.0.1/2.txt 2>result.txt 1>&2
# klee --libc=uclibc AGET http://127.0.0.1/2.txt 2>result.txt 1>&2
