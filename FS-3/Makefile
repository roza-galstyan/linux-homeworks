all:readfile


readfile:readfile.o
	g++ readfile.o
readfile.o:readfile.cpp
	g++ readfile.cpp -o  readfile.o

clean:rm *.o readfile
