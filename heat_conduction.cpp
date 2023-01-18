#include <bits/stdc++.h>

using namespace std;

#define SIZE 1000
#define NO_OF_ITERATIONS 100

void fillBorderElements(vector< vector<float> > &mat){

    for(int i=0;i<SIZE;i++){

        mat[0][i] = rand() % 10;
        mat[i][0] = rand() % 10;
        mat[SIZE-1][0] = rand() % 10;
        mat[i][SIZE-1] = rand() % 10;
    }
}

void genInitMatrix(vector< vector<float> > &mat){

    for (int i=0;i<SIZE;i++){
        vector<float> row;
        for (int j=0;j<SIZE;j++){
            
            row.push_back(rand() % 10);
        }
        mat.push_back(row);
    }
}

void printMat(const vector< vector<float> > &mat){

    cout<<"--------------------------"<<endl;    
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            cout<<mat[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"--------------------------"<<endl;
}

void nextStep(vector< vector<float> > &mat){

    vector<float> row_memory = mat[0];
    for(int i=1;i<SIZE-1;i++){
        for(int j=1; j<SIZE-1;j++){

            mat[i][j] = (row_memory[j] + mat[i+1][j] + mat[i][j+1] + mat[i][j-1]) / 4.0; 
        }
        row_memory = mat[i];
    }
}

vector< vector<float> > newMat(SIZE-1, vector<float> (SIZE-1, 0));   

void nextStepParallel(vector< vector<float> > &mat){
    
    #pragma omp parallel for collapse(2) 
    for(int i=1;i<SIZE-1;i++){

        for(int j=1;j<SIZE-1;j++){
            
            newMat[i-1][j-1] = (mat[i-1][j] + mat[i+1][j] + mat[i][j-1] + mat[i][j+1]) / 4;
        }    
    }

    #pragma omp parallel for collapse(2)
    for(int k=1;k<SIZE-1;k++){

        for(int l=1;l<SIZE-1;l++){

            mat[k][l] = newMat[k-1][l-1];
        }
    }
}


int main(){

    // vector< vector<float> > mat;
    // genInitMatrix(mat);

    vector< vector<float> > mat(SIZE, vector<float> (SIZE, 0.0));
    fillBorderElements(mat);

    cout<<"Base matrix: "<<endl;
    // printMat(mat);

    for(int i=0;i<NO_OF_ITERATIONS;i++){

        // nextStep(mat);
        nextStepParallel(mat);
        cout<<"Iteration "<<i+1<<endl;        
        // printMat(mat);
    }

    return 0;
}
