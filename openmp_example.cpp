#include <iostream>

using namespace std;

int main(){

    #pragma omp parallel
    cout<<"Hello!"<<endl;
    return 0;
}