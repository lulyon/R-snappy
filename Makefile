
CC=g++
RC=R CMD COMPILE 
CPPFLAGS=-fPIC -shared -Wall -g -O2
all:snappy.so

snappy.so:r-snappy.o snappy.o snappy-c.o\
	snappy-sinksource.o snappy-stubs-interal.o
	$(CC)  $(CPPFLAGS) -o $@ $^

r-snappy.o:r-snappy.c
	$(RC) $^

snappy.o:snappy/snappy.cc
	$(CC) -o $@ -c $^

snappy-c.o:snappy/snappy-c.cc
	$(CC) -o $@ -c $^

snappy-sinksource.o:snappy/snappy-sinksource.cc
	$(CC) -o $@ -c $^

snappy-stubs-interal.o:snappy/snappy-stubs-internal.cc
	$(CC) -o $@ -c $^

.PHONY:clean

clean:
	rm *.o snappy.so

