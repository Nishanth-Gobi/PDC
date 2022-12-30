#include <iostream>
#include <omp.h>
#include <unistd.h>
#include <math.h>

using namespace std;

#define ARRAY_SIZE 5

int main(){


    int *arr = new int[ARRAY_SIZE];

    #pragma omp parallel for  

    for(int i=0;i<ARRAY_SIZE;i++){

        sleep(1);
        arr[i] = i*10;
    }

    return 0;
}