all:main
		
main:main.o  class.o
	g++ -o main main.o  class.o 

main.o:main.cpp 
	g++ main.cpp -c 
	
class.o:class.cpp class.h 
	g++ class.cpp -c 
	
clean:
	rm *.o
