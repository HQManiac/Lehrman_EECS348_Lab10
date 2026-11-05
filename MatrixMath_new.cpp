/*
Name: MatrixMath_new
Author: Jacob Lehrman
Description: Cade to implement matrix operations for 
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class Matrix{
    private:
        vector<vector<int>> mat;
        int size;

    public:
        Matrix(int size, vector<vector<int>> raw) : size(size), mat(raw){}

        void display(){
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    cout<< left << setw(9) << mat[i][j];//This will look goofy when printing, but is good enough.
                }
                cout << endl;
            }
        }

        Matrix operator+(Matrix &m){
            Matrix res(size,vector<vector<int>>(size,vector<int>(size,0)));
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    res.mat[i][j] = mat[i][j] + m.mat[i][j];
                }
            }
            return res;
        }

        Matrix operator*(Matrix &m){
            Matrix res(size,vector<vector<int>>(size,vector<int>(size,0)));
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    int sum = 0;
                    for(int k = 0; k < size; k++){
                        sum += mat[i][k] * m.mat[k][j];
                    }
                    res.mat[i][j] = sum;
                }
            }
            return res;
        }

        vector<int> getDiagonals(){
            vector<int> res(2,0);
            for(int i = 0; i < size; i++){
                res[0] += mat[i][i];//Main diagonal
                res[1] += mat[i][size-(i+1)];//Secondary diagonal
            }
            return res;
        }

        Matrix swapRow(int r[]){
            Matrix res(size,mat);
            res.mat[r[0]].swap(res.mat[r[1]]);
            return res;
        }

        Matrix swapCol(int r[]){
            Matrix res(size,mat);
            for(int i = 0; i < size; i++){
                int temp = res.mat[i][r[0]];
                res.mat[i][r[0]] = res.mat[i][r[1]];
                res.mat[i][r[1]] = temp;
            }
            return res;
        }

        void updateIndex(int r, int c, int val){
            mat[r][c] = val;
        }
};

vector<int> simpleSplitter(string s){
    //Modified code sourced from https://www.geeksforgeeks.org/java/how-to-split-a-string-in-cc-python-and-java/
    // A quick way to split strings separated via spaces.
    stringstream ss(s);
    string word;
    vector<int> output;
    int i = 0;
    while (ss >> word) {
        output.push_back(stoi(word));
        i++;
    }
    return output;
}//end simpleSplitter


int main(){
    int N;
    string userFile;
    string line;
    cout << "Enter filename, with extension, for the matricies: ";
    cin >> userFile;
    ifstream file (userFile);
    if (file.is_open()){
        getline(file,line);//The first line contains the size of the Matrix.
        N = stoi(line);
    }

    vector<vector<int>> temp;
    for(int i = 0; i < N; i++){
        getline(file,line);
        temp.push_back(simpleSplitter(line));
    }
    Matrix A(N,temp);

    for(int i = 0; i < N; i++){
        getline(file,line);
        temp[i] = simpleSplitter(line);
    }
    Matrix B(N,temp);

    cout << "Matrix A:" << endl;
    A.display();

    cout << "Matrix B:" << endl;
    B.display();

    cout << "A + B =" << endl;
    Matrix result = A + B;
    result.display();

    cout << "A * B =" << endl;
    result = A * B;
    result.display();

    cout << "Diagonals of matrix A:" << endl;
    vector<int> t = A.getDiagonals();
    cout << "Main: " << t[0] << endl;
    cout << "Secondary: " << t[1] << endl;

    int r[2] = {0,1};
    cout << "Enter first row: ";
    cin >> r[0];
    cout << "Enter second row: ";
    cin >> r[1];
    if(r[0] < N && r[0] >= 0 && r[1] < N && r[1] >= 0){
        cout << "Swapping rows in matrix A:" << endl;
        result = A.swapRow(r);
        result.display();
    }else{
        cout << "Invalid indicies. Swapping with default values (rows 0 and 1.)" << endl;
        cout << "Swapping rows in matrix A:" << endl;
        r[0] = 0;
        r[1] = 1;
        result = A.swapRow(r);
        result.display();
    }

    r[0] = 0;
    r[1] = 1;
    cout << "Enter first collum: ";
    cin >> r[0];
    cout << "Enter second collum: ";
    cin >> r[1];
    if(r[0] < N && r[0] >= 0 && r[1] < N && r[1] >= 0){
        cout << "Swapping collums in matrix A:" << endl;
        result = A.swapCol(r);
        result.display();
    }else{
        cout << "Invalid indicies. Swapping with default values (collums 0 and 1.)" << endl;
        cout << "Swapping collums in matrix A:" << endl;
        r[0] = 0;
        r[1] = 1;
        result = A.swapCol(r);
        result.display();
    }
    int row,col;
    int val = 100;
    cout << "Enter row: ";
    cin >> row;
    cout << "Enter collum: ";
    cin >> col;
    cout << "Enter value: ";
    cin >> val;
    char mat;
    cout << "Enter matrix to update(A or B): ";
    cin >> mat;
    if(row >= 0 && row < N && col >= 0 && col < N){
        if(mat == 'A' || mat == 'a'){
            cout << "Updating matrix A:" << endl;
            A.updateIndex(row,col,val);
            A.display();
        }else{
            cout << "Updating matrix B:" << endl;
            B.updateIndex(row,col,val);
            B.display();
        }
    }else{
        row = col = 0;
        cout << "Invalid indicies. Updating entry at [0,0]." << endl;
        if(mat == 'A' || mat == 'a'){
            cout << "Updating matrix A:" << endl;
            A.updateIndex(row,col,val);
            A.display();
        }else{
            cout << "Updating matrix B:" << endl;
            B.updateIndex(row,col,val);
            B.display();
        }
    }

    return 0;
}//End main