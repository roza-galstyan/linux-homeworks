#include "shared_array.h"
   shared_array::shared_array(const std::string& _name,int size) {
        this->array_name = _name;
        this->size = size;
        // Create or open shared memory object.
        shm_fd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
        if (shm_fd < 0){
        std::cerr << strerror(errno) << std::endl;
          }

        ftruncate(shm_fd, 4096);
        int f_size = size / 4096;

        // Map the shared memory object.
        m_map = mmap(NULL, f_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        arr_mmap = static_cast<char*>(m_map);
       
        }
        
      // Destructor
    shared_array::~shared_array() {
          munmap(m_map, size * sizeof(int));
          close (shm_fd);
          shm_unlink(name.c_str());
        }
      // Operator []
    char& shared_array::operator[] (int ind){
           return arr_mmap[ind]; 
        }

