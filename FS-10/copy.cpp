#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include  <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256
int main (int argc,char **argv){
// Check if we got all arguments. 
if (argc < 3){
	std::cerr << "Please provide file path" << std::endl;
	exit (1);
 }

const char * source_file = argv[1];
const char * destination_file = argv[2];
 
// Open the source_file.
int fd = open (source_file,O_RDONLY);
if (fd < 0){
	std::cerr << strerror(errno) << std::endl;
	exit (errno);
}

// Open the destination_file.
int new_fd = open (destination_file,O_WRONLY|O_CREAT|O_TRUNC,0644);
if (new_fd < 0){
	std::cerr << strerror(errno) << std::endl;
	exit (errno);
}
 

// Create a buffer.
char buf[BUFFER_SIZE];

// Read from source_file and write to destination_file. 
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


int data_bytes = 0;
int hole_bytes = 0;
// Hole bytes
int N = 0;
// Data bytes
int M = 0;
// Destination-file size
int file_size = lseek(new_fd,0,SEEK_END);
if (file_size < 0){
	std::cerr << strerror(errno);
	exit(errno);
}
// Go to the beginning of the file.
int offset = lseek (new_fd,0,SEEK_SET);
if (offset < 0){
	std::cerr << strerror(errno);
	exit(errno);
}
// Counting bytes.
 while (offset < file_size){
    hole_bytes = lseek (new_fd,offset,SEEK_DATA);
    if (hole_bytes < 0 ){
		std::cerr << strerror(errno);
	   break;}
    data_bytes = lseek (new_fd,offset,SEEK_HOLE); 
    if (data_bytes < 0 ){
		std::cerr << strerror(errno);
	   break;}

    M += data_bytes ;
	N = hole_bytes ;
	offset = lseek (new_fd,BUFFER_SIZE,SEEK_CUR);
	if (offset < 0){
	std::cerr << strerror(errno);
	break;
} 
}

// Close the source_file.
ssize_t closed = close(fd);
if (closed < 0){
    std::cerr << strerror(errno) << std::endl;
} 

// Close the destination_file.
closed = close (new_fd);
if (closed < 0){
    std::cerr << strerror(errno) << std::endl;
} 
// Print the result.
std::cout << "Successfully copied "
<< M + N <<" bytes (data: " << 
M <<", hole: "<< N << ")." << "\n";

return 0;
}
