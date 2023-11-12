#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
void interactiv_shell (std::string command){
    int pid = fork();
    // If pid < 0 ,print the error.
    if (pid < 0){
        std::cerr << strerror(errno) << std::endl ;
        exit(errno);
    }
    // Child process.
    if (pid == 0){
        const char * p = &command[0];
         int result = execlp (p,p,nullptr);
         if (result < 0){
            std::cerr << strerror(errno) <<std::endl;
            exit(errno);
         }
         }
    
    // Parent process.
    if (pid > 0){
        int status;
        int Waitresult = waitpid (pid,&status,0);
    }
}

int main (){
    
    std::string  command = "ls";
    while(command != "exit"){
    std::cin >> command;
    interactiv_shell(command);
    }
    return 0;
    

}