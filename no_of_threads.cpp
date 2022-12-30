#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;

#define NUMBER_OF_THREADS 4

int main(){

    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        sleep(3 * omp_get_thread_num());
        cout<<"Hello from Thread "<<omp_get_thread_num()<<endl;
    }
}

// num_threads()