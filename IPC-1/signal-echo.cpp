#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/ucontext.h>
#include <errno.h>
#include <cstring>
#include <csignal>
void signalHandler(int signum, siginfo_t *info, void *context) {
    if (signum == SIGUSR1) {
        std::cout << "Received a SIGUSR1 signal from process [" << info->si_pid << "] executed by ";

        // Get UID and username of the sender
        uid_t uid = info->si_uid;
        struct passwd *pw = getpwuid(uid);
        if (pw != nullptr) {
            std::cout << uid << " ([" << pw->pw_name << "])" << std::endl;
        } else {
            std::cout << uid << " (Unknown)" << std::endl;
        }

        // Print register values
        unsigned int eip, eax, ebx;
        ucontext_t *uc = (ucontext_t *)context;
        eax = uc->uc_mcontext.gregs[REG_RAX] & 0xFFFFFFFF;
        ebx = uc->uc_mcontext.gregs[REG_RBX] & 0xFFFFFFFF;
        eip = uc->uc_mcontext.gregs[REG_RIP] & 0xFFFFFFFF;

        std::cout << "State of the context: EIP = [" << eip << "], EAX = [" << eax << "], EBX = [" << ebx << "]." << std::endl;
    }
}

int main() {
    
    // Set up sigaction struct
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signalHandler;
    sa.sa_flags = SA_SIGINFO;

    // Register signal handler for SIGUSR1
   int sig_result = sigaction(SIGUSR1, &sa, NULL);
   if (sig_result < 0){
    std::cerr << strerror(errno) << std::endl;
   }

    // Enter infinite loop with a sleep delay
    while (true) {
        std::cout << "loop " << std::endl;
        sleep(10);
    }

    return 0;
}