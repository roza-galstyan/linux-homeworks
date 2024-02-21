#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
class shared_array {
    private:
    std::string array_name ;
    int size ;
    char * arr_mmap;
    void * m_map;
    int shm_fd;
    public:
    std::string name = array_name +(std::to_string(size));
    shared_array(const std::string& name, int size);
    ~shared_array();
    char& operator[](int ind);
};
