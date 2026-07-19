CURL = curl

CC = gcc
AR = ar
CFLAGS = -Wall -g

all: main

download-gmp: 
	$(CURL) https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz

mini-gmp: ./third-party/gmp-6.3.0/mini-gmp/mini-gmp.h ./third-party/gmp-6.3.0//mini-gmp/mini-gmp.c
	$(CC) $(CFLAGS) -I.  -c ./third-party/gmp-6.3.0//mini-gmp/mini-gmp.c -o ./third-party/gmp-6.3.0/mini-gmp/mini-gmp.o && \
	$(AR) rcs ./third-party/gmp-6.3.0/mini-gmp/mini-gmp.a ./third-party/gmp-6.3.0/mini-gmp/mini-gmp.o

main: ./app/src/main.c
	$(CC) $(CFLAGS)  -L./third-party/gmp-6.3.0/mini-gmp -l:mini-gmp.a -c ./app/src/main.c -o ./main -static

mini-gmp-emscripten:
	


clean:
	rm -f ../main
