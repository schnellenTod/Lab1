#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

using namespace std;

class MatrixThreeXThree 
{
	double elementsOfMatrix[3][3];
public:
	MatrixThreeXThree () {}
	
	MatrixThreeXThree (double value[3][3]) 
	{
		for (int i = 0; i < 3; ++i) 
		{
			for (int j = 0; j < 3; ++j) 
			{
				elementsOfMatrix[i][j] = value[i][j];
			}
		}
	}
	
	~MatrixThreeXThree () {}
	
	friend ifstream& operator >> (ifstream& inputStream, MatrixThreeXThree& inputMatrix) 
	{
		for (int i = 0; i < 3; ++i) 
		{
			for (int j = 0; j < 3; ++j) 
			{
				inputStream >> inputMatrix.elementsOfMatrix[i][j];
			}
		}
		return inputStream;
	}
	
	friend ofstream& operator << (ofstream& outputStream, MatrixThreeXThree& inputMatrix) 
	{
		for (int i = 0; i < 3; ++i) 
		{
			for (int j = 0; j < 3; ++j) 
			{
				outputStream << inputMatrix.elementsOfMatrix[i][j]<<" ";
			}
			outputStream << endl;
		}
		return outputStream;
	}
	
	double operator () (int rowIndex, int columnIndex) 
	{
		return elementsOfMatrix[rowIndex][columnIndex];
	}
	bool operator == (MatrixThreeXThree compareMatrix) 
	{
		for (int i = 0; i < 3; ++i) 
		{
			for (int j = 0; j < 3; ++j) 
			{
				if ( elementsOfMatrix[i][j] != compareMatrix(i,j) ) 
				{
					return false;
				}
			}
		}
		return true;
	}

	double calculateMinor(double rowIndex, double columnIndex) 
	{
		double factor[4] = {0};
		int index = 0; 
		
		for (int i = 0; i < 3; ++i) 
		{
			for (int j = 0; j < 3; ++j) 
			{
				if ( i != rowIndex && j != columnIndex ) 
				{
					factor[index] = elementsOfMatrix[i][j];
					++index;
				}
			}
		}
		return pow(-1,rowIndex + columnIndex) * ((factor[0]*factor[3]) - (factor[1]*factor[2]));
	}
	
	double calculateDeterminant_3x3() 
	{
		double determinant = 0; 
		
		for (int j = 0; j < 3; ++j) 
		{
			determinant += elementsOfMatrix[0][j] * calculateMinor(0, j);
		}
		
		return determinant;
	}
	
	MatrixThreeXThree Invert() 
	{
		double matrixDeterminant = calculateDeterminant_3x3();
		double resultMatrix[3][3];
		
		if ( matrixDeterminant ) 
		{
			double reverseDeterminant = 1 / matrixDeterminant;
			
			for (int i = 0; i < 3; ++i) 
			{
				for (int j = 0; j < 3; ++j) 
				{
					resultMatrix[j][i] = reverseDeterminant * calculateMinor(i,j);
				}
			}
			
		}
		else {
			for (int i = 0; i < 3; ++i) 
			{
				for (int j = 0; j < 3; ++j) 
				{
					resultMatrix[i][j] = elementsOfMatrix[i][j];
				}
			}
		}
		MatrixThreeXThree resultMatrixThreeXThree(resultMatrix);
		return resultMatrixThreeXThree;
	}
};

int main (int argc, char* argv[]) 
{
	if (argc < 3) {
		cout<<"Usage: <input matrix file> <output matrix file>"<<endl;
	}
	
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) 
	{
		cout<<"input file opening error"<<endl;
		return 1;
	}
	
	ofstream outputFile(argv[2]);
	if (!outputFile.is_open()) 
	{
		cout << "output file opening error" << endl;
		inputFile.close();
		return 1;
	}
	
	MatrixThreeXThree inputMatrix;
	inputFile >> inputMatrix;
	
	double onceMatrix[3][3] = { 0 };

	for (int i = 0; i < 3; ++i)
	{
		onceMatrix[i][i] = 1;
	}
	
	MatrixThreeXThree onceMatrixThreeXThree(onceMatrix);

    MatrixThreeXThree invertMatrix = inputMatrix.Invert();
	if ( invertMatrix == inputMatrix && !(inputMatrix == onceMatrixThreeXThree))
	{
		cout << "Input Matrix's determinant == 0" << endl;
	}
	else 
	{
		outputFile << invertMatrix;
	}
	
	outputFile.close();
	
	return 0;
}