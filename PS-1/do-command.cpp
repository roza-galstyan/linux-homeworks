#include <iostream>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
void do_command(char** argv){
    // Get the starting time.
    struct tms  startt ,endt ;
    clock_t start_time,end_time ;
    start_time = times(&startt);

    // Create a new process.
    int pid = fork();

    // If pid < 0 ,print the error.
    if (pid < 0){
    std::cerr << strerror(errno) << std::endl;
    exit(errno);
    }

    // Childe process.
    if (pid == 0){
        execlp ("ls","ls","-al",NULL);
    }

    // Parent process.
    if (pid > 0){
         int status;
         // Parent process wait for the child process to complete.
         int waitResult = waitpid (pid,&status,0);
         // Get the ending time.
         end_time = times(&endt);
         std::cout << std::endl << "Command completed with"<< " "<< status <<" "
          << "exit code and took" <<" "<< double(end_time - start_time )<< " "
          <<"seconds. " << std::endl;
    }
    
}
int main (int argc,char  * argv [] ){
    // Check if get 2 arguments or not.
    if (argc < 2){    
        std::cerr << strerror(errno) << std::endl;
        exit(1);
    }

    // Add 0 to the end of argv[].
    argv[argc - 1] = nullptr;

    // Call function do.command.
    do_command (argv);

    return 0;
}
