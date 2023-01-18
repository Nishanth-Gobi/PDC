#include <bits/stdc++.h>

using namespace std;

#define ARRAY_SIZE 1000

void merge(int arr[], int start, int mid, int end){

    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1];
    int right[n2];

    for(int i=0; i<n1; i++){

        left[i] = arr[start + i];
    }

    for(int i=0;i<n2; i++){

        right[i] = arr[mid+1 + i];
    }

    int i=0, j=0;
    int k=start;

    while(i<n1 && j<n2){

        if(left[i]<= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k++] = left[i++];
    }

    while(j<n2){
        arr[k++] = right[j++];
    }
    
}

void mergeSort(int arr[], const int start, const int end){

    if(start>=end){
        return;
    }

    int mid = start + (end-start)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, start, mid, end);
}

void parallelMerge(int arr[], int start, int mid, int end){
    
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1];
    int right[n2];

    #pragma omp parallel num_threads(2)
    {
        #pragma omp parallel for
        for(int i=0; i<n1; i++){

            left[i] = arr[start + i];
        }

        #pragma omp parallel for
        for(int i=0;i<n2; i++){

            right[i] = arr[mid+1 + i];
        }
    }

    int i=0, j=0;
    int k=start;

    while(i<n1 && j<n2){

        if(left[i]<= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    #pragma omp parallel
    {
        while(i<n1){
            arr[k++] = left[i++];
        }

        while(j<n2){
            arr[k++] = right[j++];
        }
    }    
}

void parallelMergeSort(int arr[], const int start, const int end){

    if(start>=end){
        return;
    }

    int mid = start + (end-start)/2;

    #pragma omp parallel num_threads(2)
    {
        parallelMergeSort(arr, start, mid);
        parallelMergeSort(arr, mid+1, end);
    }
    merge(arr, start, mid, end);
}

void initArray(int (&arr)[ARRAY_SIZE]){

    for(int i=0;i<ARRAY_SIZE;i++){

        arr[i] = rand()%10;
    }
}

void printArray(string prompt, const int arr[]){

    cout<<"-------------------------------------"<<endl;
    cout<<prompt<<endl;
    cout<<"-------------------------------------"<<endl;
    for(int i=0;i<ARRAY_SIZE;i++){

        cout<<arr[i]<<" ";
    }
    cout<<endl<<"-------------------------------------"<<endl;
}

int main(){

    int arr[ARRAY_SIZE];
    initArray(arr);

    printArray("Original array", arr);

    mergeSort(arr, 0, ARRAY_SIZE-1);
    // parallelMergeSort(arr, 0, ARRAY_SIZE);

    printArray("Merged array", arr);

    return 0;
}