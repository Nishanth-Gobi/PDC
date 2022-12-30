#include <iostream>
#include <omp.h>

using namespace std;

int main(){

    int sh=1, pv=3;

    // default value of private int is reinitialised to 0
    // default value of shared variable is garbage

    #pragma omp parallel shared(sh) private(pv)
    {   
        #pragma omp critical
        {
            cout<<"thread: "<<omp_get_thread_num()<<endl;
            cout<<"pv val: "<<pv<<endl;
            cout<<"sh val: "<<sh<<endl<<endl;
            sh++;
            pv++;
        }
    }
    return 0;
}