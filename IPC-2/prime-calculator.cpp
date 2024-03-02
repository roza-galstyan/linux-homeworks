#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
// Function Is m prime number or not .
bool is_prime (int m){
    for (int i = 2;i <= m / 2;++i){
        if (m % i == 0){
         return false;
        }
    }
    return true;
}
// Function to find the mth prime number.
int m_prime_number (int m){
    int i = 1 ;
    while (m != 0){
        ++i;
        if (is_prime(i)){
            --m;
        }
    }
    return i;
}


int main(){

    // Pipes for communication between parent and child processes.
    int pipefd_1 [2];
    int pipefd_2 [2];

    // Create pipes.
    int pipe_result_1 = pipe(pipefd_1);
    if(pipe_result_1 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    int pipe_result_2 = pipe(pipefd_2);
    if(pipe_result_2 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //  Fork to create a child process.
    int pid = fork();
    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    // Parent process.
    if(pid > 0){
        close(pipefd_1[0]);
        close(pipefd_2[1]);
        std::string num;
        int m;
        while(true){
            std::cout << "Please enter the number:" ;
            std::cin >> num ;
            if (num == "exit"){
               return 0;
            }
            m = std::stoi(num);
            int write_res = write(pipefd_1[1],&m,sizeof(int));
            if(write_res < 0){
               std::cerr << strerror(errno) << std::endl;
               exit(errno);
            }
            int m_th_prime_num ;
            int read_res = read(pipefd_2[0],&m_th_prime_num,sizeof(int));
            if(read_res < 0){
               std::cerr << strerror(errno) << std::endl;
               exit(errno);
            }
            std::cout << "Received calculation result of prime("<< m <<")="<< m_th_prime_num << std::endl;
        }
    }

    // Child process.    
    if(pid == 0){
        close(pipefd_1[1]);
        close(pipefd_2[0]);
        while(true){
            int m;
            int read_res = read(pipefd_1[0],&m,sizeof(int));
            if(read_res < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
            int m_th_prime_num  = m_prime_number(m);
            int write_res = write(pipefd_2[1],&m_th_prime_num ,sizeof(int));
            if(write_res < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            } 
        }
    } 
        
    return 0;
}
