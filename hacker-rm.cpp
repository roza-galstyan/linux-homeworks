#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include  <string.h>
#include <unistd.h>
#define BUFFER_SIZE 19
int main (int argc,char **argv){
if (argc < 2){
	std::cerr << "Please provide file path" << std::endl;
	exit (1);
 }

const char * file = argv[1];
int fd = open (file,O_RDWR);
if (fd < 0){
	std::cerr << strerror(errno) << std::endl;
	exit (errno);
}



char buf[BUFFER_SIZE];
int i=0;

while  (i < BUFFER_SIZE){
 	buf[i]='\0';
 	++i;
	}

struct stat st_buf;
ssize_t fl_info = stat (file,&st_buf) ;
ssize_t  write_bytes ;
int count = 0;
ssize_t fl_size = st_buf.st_size;

while(count < fl_size){
	write_bytes = write (fd,buf,BUFFER_SIZE);
	if(write_bytes < 0){
			std::cerr << strerror(errno) << std::endl;
			exit (errno);}
			count += write_bytes;
}
	
ssize_t rm = unlink (file);
if (rm < 0 ){
	std::cerr << strerror(errno) << std::endl;
		exit (errno);}


return 0;
}
