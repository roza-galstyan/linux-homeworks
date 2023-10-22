#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main (int argc,char** argv){
    if(argc<2){
        std::cerr << "No file." << std::endl;
        exit (1);
    }

    char *filephath=argv[1];
    int opened_file = open(filephath,O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU|S_IRUSR|S_IRGRP|S_IROTH);
    if (opened_file < 0){
        std::cerr << strerror(errno) << std::endl;
        exit (errno);
    }
    std::string s_1 = "first line\n";
    std::string s_2 = "second line\n";

            
    ssize_t bytes = write (opened_file,s_1.c_str(),s_1.size())   ;   
    if (bytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit (errno); 
            }  
             

    int secontfile = dup(opened_file);
    if (secontfile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit (errno); 

    }
   
    bytes= write (opened_file,s_2.c_str(),s_2.size());
     if (bytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit (errno); 
            }  

    close (opened_file);
    close (secontfile);
    return 0;  
      
}
