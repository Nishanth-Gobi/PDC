#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

#define NUMBER_OF_THREADS 4
#define MATRIX_SIZE 4

vector< vector<int> > mat1;
vector< vector<int> > mat2;

void randomInitMat(vector< vector<int> > &mat){

    for(int i=0;i<MATRIX_SIZE;i++){
        vector<int> row;
        for(int j=0;j<MATRIX_SIZE;j++){

            row.push_back(rand() % 4 + 1);
        }
        mat.push_back(row);
    }
}

void printMat(vector< vector<int> > &mat, string matName){

    cout<<"-----------------------------------"<<endl;
    cout<<matName<<endl;    
    cout<<"-----------------------------------"<<endl;
    for(int i=0;i<MATRIX_SIZE;i++){
        for(int j=0;j<MATRIX_SIZE;j++){

            cout<<mat[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<"-----------------------------------"<<endl;
}

void getSubMatrix(vector< vector<int> > &matA, vector< vector<int> > &matB, int rowN, int colN){

    int rowN = rowN * MATRIX_SIZE/2;
    int colN = colN * MATRIX_SIZE/2;

    for(int i=0;i<MATRIX_SIZE/2;i++){
        vector<int> row;
        for(int j=0;j<MATRIX_SIZE/2;j++){

            row.push_back(  matA[rowN+i][colN+j]  );
        }
        matB.push_back(row);
    }
}

int main(){

    randomInitMat(mat1);
    printMat(mat1, "Matrix 1");
    randomInitMat(mat2);
    printMat(mat2, "Matrix 2");

    vector< vector<int> > mat1A;
    vector< vector<int> > mat1B;
    vector< vector<int> > mat1C;
    vector< vector<int> > mat1D;

    getSubMatrix(mat1, mat1A, 0, 0);
    printMat(mat1, "Matrix 1A");

    getSubMatrix(mat1, mat1B, 0, 1);
    printMat(mat1, "Matrix 1B");

    getSubMatrix(mat1, mat1C, 1, 0);
    printMat(mat1, "Matrix 1C");

    getSubMatrix(mat1, mat1D, 1, 1);
    printMat(mat1, "Matrix 1D");

    return 0;
}