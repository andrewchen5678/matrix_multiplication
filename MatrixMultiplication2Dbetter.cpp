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

class MyMatrix{
public:
/*
	MyMatrix(int** matrix, int n):size(n),startrow(0),startcol(0){
		squareMatrix=matrix;
	}
*/
	//n=dimension of submatrix
	MyMatrix(int* matrix, int rowstart,int colstart,int n):size(n),startrow(rowstart),startcol(colstart){
		
			int** tempPtr=matrix+rowstart;
			squareMatrix=new int*[n];
			for(int i=0;i<n;i++){
				squareMatrix[i]=tempPtr[i]+colstart;
			}
		}else{
			squareMatrix=matrix;
		}
	}	
	friend void addMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n);
	friend void helperDivideAndConquer(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n);
	/*
	//friend MyMatrix operator+ (
	
	MyMatrix& operator+ (MyMatrix& obj){
		for(int i=0;i<size;i++){
			
	}
	MyMatrix& operator* (MyMatrix&);
	MyMatrix& operator= (MyMatrix&);
	*/
	~MyMatrix(){
		//cout<<"destroying...";
		/*
		for(int i=0;i<size;i++){
			delete[] squareMatrix[i];
		}
		*/ 
		if(startcol>0){
			delete[] squareMatrix;
		}
	}
	void getMatrixPtr(int**& returnPtr,int& returnSize){
		returnPtr=squareMatrix;
		returnSize=size;
	}
	int getSize(){
		return size;
	}
	//static void divideAndConquer(const MyMatrix,const MyMatrix,MyMatrix);
private:
/*
	MyMatrix(const MyMatrix& existSquareMatrix,int n,int rowstart,int colstart):size(n){
		squareMatrix = new int*[n-rowstart];
		
	}
*/ 
	int size,startrow,startcol;
	int **squareMatrix;
};

void createMatrix(int **newMatrix,int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int num=rand()%100+1;
			newMatrix[i][j] = num;
		}
	}
}

void printMatrix(const int** matrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			//int num=matrix[i*n+j];
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

//classical way to multiply matrix
void classicalMultiply(const int** firstMatrix, const int** secondMatrix,int** newMatrix, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				newMatrix[i][j]=newMatrix[i][j]+firstMatrix[i][k]*secondMatrix[k][j];
			}
		}
	}
}


void addMatrix(MyMatrix& firstMatrix, MyMatrix& secondMatrix, MyMatrix& newMatrix,int n){
	int** ptr1=firstMatrix.squareMatrix;
	int** ptr2=secondMatrix.squareMatrix;
	int** ptr3=newMatrix.squareMatrix;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ptr3[i][j]=ptr1[i][j]+ptr2[i][j];
		}
	}
}

//divide and conquer
void helperDivideAndConquer(MyMatrix& firstMatrixClass, MyMatrix& secondMatrixClass,MyMatrix& newMatrixClass,int n){
	
	if(n<=1){
	//printMatrix((const int**)firstMatrixClass.squareMatrix,n);
	//printMatrix((const int**)secondMatrixClass.squareMatrix,n);
		**newMatrixClass.squareMatrix=**firstMatrixClass.squareMatrix*(**secondMatrixClass.squareMatrix);
		return;
	}
	MyMatrix a11MatrixClass(firstMatrixClass.squareMatrix,0,0,n/2);
	MyMatrix b11MatrixClass(secondMatrixClass.squareMatrix,0,0,n/2);
	MyMatrix c11MatrixClass(newMatrixClass.squareMatrix,0,0,n/2);
	helperDivideAndConquer(a11MatrixClass,b11MatrixClass,c11MatrixClass,n/2); //c11=a11*b11;
	int** temp=new int*[n/2];
	for(int i=0;i<n/2;i++){
		temp[i]=new int[n/2];
	}
	MyMatrix a12MatrixClass(firstMatrixClass.squareMatrix,0,n/2,n/2);
	MyMatrix b21MatrixClass(secondMatrixClass.squareMatrix,n/2,0,n/2);
	MyMatrix *newerMatrixClass= new MyMatrix(temp,0,0,n/2);
	helperDivideAndConquer(a12MatrixClass,b21MatrixClass,*newerMatrixClass,n/2); //temp=a12*b21;
	addMatrix(c11MatrixClass,*newerMatrixClass,c11MatrixClass,n/2);
	
	for(int i=0;i<n/2;i++){
		delete[] temp[i];
	}
	delete[] temp;
	delete newerMatrixClass;
	
	MyMatrix b12MatrixClass(secondMatrixClass.squareMatrix,0,n/2,n/2);
	MyMatrix c12MatrixClass(newMatrixClass.squareMatrix,0,n/2,n/2);
	helperDivideAndConquer(a11MatrixClass,b12MatrixClass,c12MatrixClass,n/2); //c12=a11*b12;

	temp=new int*[n/2];
	for(int i=0;i<n/2;i++){
		temp[i]=new int[n/2];
	}
	MyMatrix b22MatrixClass(secondMatrixClass.squareMatrix,n/2,n/2,n/2);
	newerMatrixClass=new MyMatrix(temp,0,0,n/2);
	helperDivideAndConquer(a12MatrixClass,b22MatrixClass,*newerMatrixClass,n/2); //temp=a12*b22;
	addMatrix(c12MatrixClass,*newerMatrixClass,c12MatrixClass,n/2);
	
	for(int i=0;i<n/2;i++){
		delete[] temp[i];
	}
	delete[] temp;
	delete newerMatrixClass;
	
	MyMatrix a21MatrixClass(firstMatrixClass.squareMatrix,n/2,0,n/2);
	MyMatrix c21MatrixClass(newMatrixClass.squareMatrix,n/2,0,n/2);
	helperDivideAndConquer(a21MatrixClass,b11MatrixClass,c21MatrixClass,n/2); //c21=a21*b11

	temp=new int*[n/2];
	for(int i=0;i<n/2;i++){
		temp[i]=new int[n/2];
	}
	MyMatrix a22MatrixClass(firstMatrixClass.squareMatrix,n/2,n/2,n/2);
	newerMatrixClass=new MyMatrix(temp,0,0,n/2);
	helperDivideAndConquer(a22MatrixClass,b21MatrixClass,*newerMatrixClass,n/2); //temp=a22*b21;
	addMatrix(c21MatrixClass,*newerMatrixClass,c21MatrixClass,n/2);
	
	for(int i=0;i<n/2;i++){
		delete[] temp[i];
	}
	delete[] temp;
	delete newerMatrixClass;
	
	//MyMatrix a21MatrixClass(firstMatrixClass.squareMatrix,n/2,0,n/2);
	MyMatrix c22MatrixClass(newMatrixClass.squareMatrix,n/2,n/2,n/2);
	helperDivideAndConquer(a21MatrixClass,b12MatrixClass,c22MatrixClass,n/2); //c22=a21*b12

	temp=new int*[n/2];
	for(int i=0;i<n/2;i++){
		temp[i]=new int[n/2];
	}
	//MyMatrix a22MatrixClass(firstMatrixClass.squareMatrix,n/2,n/2,n/2);
	newerMatrixClass=new MyMatrix(temp,0,0,n/2);
	helperDivideAndConquer(a22MatrixClass,b22MatrixClass,*newerMatrixClass,n/2); //temp=a22*b22;
	addMatrix(c22MatrixClass,*newerMatrixClass,c22MatrixClass,n/2);
	
	for(int i=0;i<n/2;i++){
		delete[] temp[i];
	}
	delete[] temp;
	delete newerMatrixClass;
}

void divideAndConquer(int** firstMatrix, int** secondMatrix,int** newMatrix,int n){
	//printMatrix((const int**)firstMatrix,n);
	//printMatrix((const int**)secondMatrix,n);
	MyMatrix firstMatrixClass(firstMatrix,0,0,n);
	MyMatrix secondMatrixClass(secondMatrix,0,0,n);
	MyMatrix newMatrixClass(newMatrix,0,0,n);
	helperDivideAndConquer(firstMatrixClass,secondMatrixClass,newMatrixClass,n);
}

/*
void addMatrix(int** firstMatrix, int** secondMatrix, int** newMatrix, int firstRowStart,int firstColumnStart,int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			newMatrix[i+firstRowStart][j+firstColumnStart]=firstMatrix[i][j]+secondMatrix[i][j];
		}
	}
}

//divide and conquer
int** divideAndConquer(int** firstMatrix, int** secondMatrix, 
		int firstRowStart, int firstColumnStart, int secondRowStart, int secondColumnStart, int n){
	int** newMatrix;
	if(n==1){
		newMatrix = new int*[1]; 
		newMatrix[0]=new int[1]; 
		newMatrix[0][0] = firstMatrix[firstRowStart][firstColumnStart]
						  * secondMatrix[secondRowStart][secondColumnStart];
		return newMatrix;
	}
	newMatrix = new int *[n];
	for(int i=0;i<n;i++){
		newMatrix[i]=new int[n];
	}
	int** a11b11=new int *[n/2];
	int** a12b21=new int *[n/2];
	int** a11b12=new int *[n/2];
	int** a12b22=new int *[n/2];
	int** a21b11=new int *[n/2];
	int** a22b21=new int *[n/2];
	int** a21b12=new int *[n/2];
	int** a22b22=new int *[n/2];
	for(int i=0;i<n;i++){
		a11b11[i]=new int[n/2];
		a12b21[i]=new int[n/2];
		a11b12[i]=new int[n/2];
		a12b22[i]=new int[n/2];
		a21b11[i]=new int[n/2];
		a22b21[i]=new int[n/2];
		a21b12[i]=new int[n/2];
		a22b22[i]=new int[n/2];
	}
//		int[][] c12 = new int[n/2][n/2];
//		int[][] c21 = new int[n/2][n/2];
//		int[][] c22 = new int[n/2][n/2];
	a11b11=divideAndConquer(firstMatrix,secondMatrix,firstRowStart,firstColumnStart,secondRowStart, secondColumnStart, n/2);
	a12b21=divideAndConquer(firstMatrix,secondMatrix,firstRowStart,firstColumnStart+n/2,secondRowStart+n/2, secondColumnStart, n/2);
	addMatrix(a11b11,a12b21,newMatrix,0,0,n/2);
	
	a11b12=divideAndConquer(firstMatrix,secondMatrix,firstRowStart,firstColumnStart,secondRowStart, secondColumnStart+n/2, n/2);
	a12b22=divideAndConquer(firstMatrix,secondMatrix,firstRowStart,firstColumnStart+n/2,secondRowStart+n/2, secondColumnStart+n/2, n/2);
	addMatrix(a11b12,a12b22,newMatrix,0,n/2,n/2);
	
	a21b11=divideAndConquer(firstMatrix,secondMatrix,firstRowStart+n/2,firstColumnStart,secondRowStart, secondColumnStart, n/2);
	a22b21=divideAndConquer(firstMatrix,secondMatrix,firstRowStart+n/2,firstColumnStart+n/2,secondRowStart+n/2, secondColumnStart, n/2);
	addMatrix(a21b11,a22b21,newMatrix,n/2,0,n/2);
	
	a21b12=divideAndConquer(firstMatrix,secondMatrix,firstRowStart+n/2,firstColumnStart,secondRowStart, secondColumnStart+n/2, n/2);
	a22b22=divideAndConquer(firstMatrix,secondMatrix,firstRowStart+n/2,firstColumnStart+n/2,secondRowStart+n/2, secondColumnStart+n/2, n/2);
	addMatrix(a21b12,a22b22,newMatrix,n/2,n/2,n/2);
		delete[] a11b11;
		delete[] a12b21;
		delete[] a11b12;
		delete[] a12b22;
		delete[] a21b11;
		delete[] a22b21;
		delete[] a21b12;
		delete[] a22b22;
	return newMatrix;
}
*/
int main() {
	int n;
	int **firstMatrix, **secondMatrix, **multipliedMatrix;
	long timeBefore, timeAfter;
	cout << "Please enter the size of the matrix: ";
	cin >> n;
	cout << "First matrix: "<<endl;
	//MyMatrix test(n);
	//test.getMatrixPtr(firstMatrix,n);

	firstMatrix=new int*[n];
	for(int i=0;i<n;i++){
		firstMatrix[i]=new int[n];
	}

	createMatrix(firstMatrix,n);
	//printMatrix((const int**)firstMatrix,n);
	cout << "Second matrix: "<<endl;
//	MyMatrix test2(n);
//	test2.getMatrixPtr(secondMatrix,n);
	
	secondMatrix=new int*[n];
	for(int i=0;i<n;i++){
		secondMatrix[i]=new int[n];
	}
	
	createMatrix(secondMatrix,n);
	//printMatrix((const int**)secondMatrix,n);
//	MyMatrix test3(n);
//	test3.getMatrixPtr(multipliedMatrix,n);
	
	multipliedMatrix=new int*[n];
	for(int i=0;i<n;i++){
		multipliedMatrix[i]=new int[n];
		for(int j=0;j<n;j++){
			multipliedMatrix[i][j]=0;
		}
	}
	
	cout<<"begin multiplying:"<<endl;
	timeBefore=time(NULL);
	classicalMultiply((const int**)firstMatrix,(const int**)secondMatrix,multipliedMatrix,n);
	timeAfter=time(NULL);
	cout << "After multiply: " << endl;
	//printMatrix((const int**)multipliedMatrix,n);
	cout<< "It took " << (timeAfter-timeBefore) << " seconds for the classical multiplication."<<endl;

/*
	for(int i=0;i<n;i++){
		delete[] firstMatrix[i];
		delete[] secondMatrix[i];
		delete[] multipliedMatrix[i];
	}
	delete[] firstMatrix;
	delete[] secondMatrix;
	delete[] multipliedMatrix;
	*/ 

	timeBefore=time(NULL);
	divideAndConquer(firstMatrix,secondMatrix,multipliedMatrix,n);
	timeAfter=time(NULL);

	cout << "After divide and conquer: " << endl;
	//printMatrix((const int**)multipliedMatrix,n);
	cout<< "It took " << (timeAfter-timeBefore) << " seconds for the divide and conquer."<<endl;
	for(int i=0;i<n;i++){
		delete[] firstMatrix[i];
		delete[] secondMatrix[i];
	}
	for(int i=0;i<n;i++){
		delete[] multipliedMatrix[i];
	}
	delete[] firstMatrix;
	delete[] secondMatrix;
	delete[] multipliedMatrix;
	return 0;
}

