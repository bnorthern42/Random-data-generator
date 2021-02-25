CC=g++
CPPFLAGS=-std=c++11

build:	randocsv.o
	echo 'executable will be named rando.exe '
	$(CC) $(CPPFLAGS) -o rando.exe randocsv.o -fopenmp

randocsv.o:	randocsv.cpp
	$(CC) $(CPPFLAGS) -c randocsv.cpp -fopenmp

clean:
	rm rando.exe
	rm randocsv.o
