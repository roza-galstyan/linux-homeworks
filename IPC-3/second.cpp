#include "shared_array.h"
#include <iostream>
const char* semaphore = "aaa";
int main() {
    // Adjust size as needed
    shared_array array("array-name", 1000); 

    // Create semaphore for mutual exclusion
    sem_t* sem = sem_open(semaphore, O_CREAT, 0666, 1);
    
    while (true) {
            // Use shared array
            int i = 0;
            sem_wait(sem);
            std::cout << array[i] << " ";
            sem_post(sem);
            ++i;
            std::cout << std::endl;
            // Adjust for desired timing
            sleep(1);
    }
    sem_close(sem);
    sem_unlink(semaphore);
    return 0;
}

