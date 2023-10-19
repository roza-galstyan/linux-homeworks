#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include  <string.h>
#include <unistd.h>
#define BUFFER_SIZE 10
int main (int argc,char **argv){
if (argc < 3){
	std::cerr << "Please provide file path" << std::endl;
	exit (1);
 }

const char * file = argv[1];
const char * new_file = argv[2];
int fd = open (file,O_RDONLY);
if (fd < 0){
	std::cerr << strerror(errno) << std::endl;
	exit (errno);
}

int new_fd = open (new_file,O_WRONLY|O_CREAT|O_TRUNC,0644);
if (new_fd < 0){
	std::cerr << strerror(errno) << std::endl;
	exit (errno);
}

char buf[BUFFER_SIZE];
while  (true){
	ssize_t read_bytes = read(fd,buf,BUFFER_SIZE);
	if (read_bytes < 0){
		std::cerr << strerror(errno) << std::endl;
		exit (errno);
	}

	if (read_bytes == 0){
		break;
	}

	ssize_t  write_bytes = write(new_fd,buf,read_bytes);
	if(write_bytes < 0){
		std::cerr << strerror(errno) << std::endl;
		exit (errno);
	}


} ;
close (fd);
close (new_fd);
return 0;
}
