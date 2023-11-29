#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string.h> 
#include <vector>
#include <errno.h>
#include <random>
#include <chrono>
#include <sys/times.h>
#include <algorithm>

// Srtucture to hold arguments for thread function
struct sum_args{
  int* arr;
  int start;
  int end;
};

// Function to compute sum of array section within a thread
void* array_sum (void* arg){
  sum_args* section = (sum_args*)arg;
  int sum = 0;
  for (int i = section->start;i < section->end;++i){
       sum += section->arr[i];  
    };
    return new int(sum);
    
}

int main (int argc,char **argv){
  // Check if enough command-line arguments are provided
  if (argc < 3){
    std::cerr << strerror(errno);
    exit(errno);
  }

    // Convert command-line arguments to integers
    int array_size = std::stoi(argv[1]);
    int number_of_threads = std::stoi(argv[2]);

    int global_sum = 0;
    // Dynamically allocate memory for the array
    int* arr = new int [array_size];

    // Initialize the array with random values
    for (int i = 0;i < array_size;++i){
        arr[i] = rand();
      };

    // Measure time taken without using threads
    std::chrono::time_point start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0;i < array_size;++i){
        global_sum += arr[i];
      };

    std::chrono::time_point end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end_time - start_time ;
    std::cout <<"Time spent without treads: " << time.count() << std::endl;

    global_sum = 0;

    // Multithreading section 
    pthread_t *threads = new pthread_t[number_of_threads];
    sum_args ** arr_args = new sum_args*[number_of_threads];

    // Create threads and assing array sections to each threads
    for (int i = 0; i < number_of_threads;++i ){
      arr_args[i] = new sum_args;
      arr_args[i]->arr = arr;
      arr_args[i]->start = i * (array_size / number_of_threads);
      arr_args[i]->end = std::min(arr_args[i]->start + (array_size / number_of_threads),array_size);
      start_time = std::chrono::high_resolution_clock::now();
      
      // Create treds and handle errors if any
      int pthread_result = pthread_create (&threads[i],NULL,array_sum,arr_args[i]);
      if (pthread_result != 0 ){
          std::cerr << strerror(pthread_result);
          exit (pthread_result);
      } 
     }

    // Wait for threads to finish,collect results, and update the global sum
    for (int i = 0; i < number_of_threads;++i ){
     void * thread_result ;
     int result = pthread_join(threads[i],&thread_result); thread_result;
     int* sum_result = (int*)thread_result;
     global_sum += *sum_result;
     delete sum_result;
     delete arr_args[i];
    }

    // Deallocate memory for the array 
    delete [] arr_args;
    delete [] arr;

    end_time = std::chrono::high_resolution_clock::now();
    time = end_time - start_time ;
    std::cout <<"Time spent with "<< number_of_threads << " treads: "<< time.count()<<std::endl;
   return 0 ;
}
