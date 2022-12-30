#include <iostream>
#include <omp.h>

using namespace std;

#define NUMBER_OF_THREADS 4

int main(){


    #pragma omp parallel num_threads(NUMBER_OF_THREADS)
    {
        cout<<"Hi from thread "<<omp_get_thread_num()<<endl;
        #pragma omp barrier
        cout<<"Bye from thread "<<omp_get_thread_num()<<endl;
    }
    return 0;
}