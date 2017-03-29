gcc -c -g3 -pthread -D_POSIX_C_SOURCE=200112 fft.c
gcc fft.o -g3 -pthread -D_POSIX_C_SOURCE=200112 -o FFT -lm