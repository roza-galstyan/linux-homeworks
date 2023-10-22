#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
void initialize(int argc, char** argv){
if (argc < 2 ){
    std::cerr << "Please provide file path" << std::endl;
    exit (1);
}

char * file = argv[1];
int fd = open (file,O_RDWR);

if (fd < 0){
    std::cerr << strerror(errno) << std::endl;
    exit (errno);}

ssize_t new_Cin = dup2(fd,0);
ssize_t closed = close (fd);
if(closed < 0 ){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

}

int main(int argc, char** argv)
{
  
  initialize(argc, argv);

// read the string
  std::string input;
  std::cin >> input;
  ssize_t size = input.size();

// reversed string
  std::string reverse(size + 1,'*');

  for (int i=0; i <= size ;++ i){
	reverse[i] = input[size -i];
}


  reverse[size + 1] = '\0';
// print 
  std::cout << reverse << std::endl;
  return 0;
}

