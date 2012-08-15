//============================================================================
// Name        : MatrixMultiplication.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime> //library for current time
#include <cstdlib> //library for random number
using namespace std;


void createMatrix(int *newMatrix,int n){
	for(int i=0;i<n*n;i++){
			int num=rand()%100+1;
			newMatrix[i] = num;
	}
}

void printMatrix(const int* matrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			//int num=matrix[i*n+j];
			cout << matrix[i*n+j] << " ";
		}
		cout << endl;
	}
}

//classical way to multiply matrix
void classicalMultiply(const int* firstMatrix, const int* secondMatrix,int* newMatrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				int *temp=newMatrix+i*n+j;
				*temp=*temp+*(firstMatrix+i*n+k)*(*(secondMatrix+k*n+j));
			}
		}
	}
}

int main() {
	int n;
	int *firstMatrix, *secondMatrix, *multipliedMatrix;
	long timeBefore, timeAfter;
	cout << "Please enter the size of the matrix: ";
	cin >> n;
	cout << "First matrix: "<<endl;

	firstMatrix=new int[n*n];

	createMatrix(firstMatrix,n);
	//printMatrix((const int*)firstMatrix,n);
	cout << "Second matrix: "<<endl;
	
	secondMatrix=new int[n*n];
	
	createMatrix(secondMatrix,n);
	//printMatrix((const int*)secondMatrix,n);
	
	multipliedMatrix=new int[n*n];
	for(int i=0;i<n*n;i++){
		multipliedMatrix[i]=0;
	}
	cout<<"begin multiplying:"<<endl;
	timeBefore=time(NULL);
	classicalMultiply((const int*)firstMatrix,(const int*)secondMatrix,multipliedMatrix,n);
	timeAfter=time(NULL);
	cout << "After multiply: " << endl;
	//printMatrix((const int*)multipliedMatrix,n);
	cout<< "It took " << (timeAfter-timeBefore) << " seconds for the classical multiplication."<<endl;

	delete[] firstMatrix;
	delete[] secondMatrix;
	delete[] multipliedMatrix;
	return 0;
}

