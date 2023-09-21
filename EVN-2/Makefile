all:main

main:main.o class.o Sorting.o
	g++ main.o -o main

main.o:main.cpp
	g++ main.cpp -c main.o
class.o:class.h
	g++ class.h -c 
Sorting.o:Sorting.h
	g++ Sorting.h -c 
clean:
	rm *.o 
