#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

using namespace std;

class MatrixThreeXThree 
{
	double elementsOfMatrix[3][3];
public:
	//Конструктор по умолчанию без аргументов. Неизвестно, что будет лежать в elementsOfMatrixs
	MatrixThreeXThree () {}
	
	//Конструктор данный принимает обычный массив из 9 элементов и присваевает элементы массива элементам матрицы
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
	
	
	//Перегруженный оператор ввода для данного класса
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
	
	//Перегруженный оператор вывода для данного класса
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
	
	//Перегруженный оператор ( ) для получения элемента матрицы (rowIndex, columnIndex)
	double operator () (int rowIndex, int columnIndex) 
	{
		return elementsOfMatrix[rowIndex][columnIndex];
	}
	//Перегруженный оператор сравнения, который поэлементно сравнивает матрицы
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
	
	//Вспомогательный метод, вычисляющий минор 2го порядка с исключающим элементом elementsOfMatrix[rowIndex][columnIndex]
	double calculateMinor(double rowIndex, double columnIndex) 
	{
		//Определитель матрицы 2х2 состоит из двух слагаемых, каждое из которых содержит произведение определенных элементов матрицы. то есть минор состоит из 4 элементов
		double factor[4] = {0}; // собственно переменная которая будет хранить элементы минора
		int index = 0; //Данный индекс отвечает за то, какой элемент минор по порядку
		
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
	
	//Вспомогательный метод для подсчета определителя матрицы 3х3
	double calculateDeterminant_3x3() {
		//Разлагаем на миноры по первой строке. То есть определитель состоит из трех слагаемых вида elementsOfMatrix[0][j] * минор с исключающим элементом (0,j)
		double determinant = 0; //Переменная для хранения суммы произведений элементов на миноры
		
		for (int j = 0; j < 3; ++j) {
			determinant += elementsOfMatrix[0][j] * calculateMinor(0, j);
		}
		
		return determinant;
	}
	
	//Собственно метод инвертирующий матрицу
	MatrixThreeXThree Invert() {
		double matrixDeterminant = calculateDeterminant_3x3();
		double resultMatrix[3][3];
		
		if ( matrixDeterminant ) {
			/*Можем посчитать инвертированную матрицу только в том случае, когда определитель не 0.
				Обратная матрица считается как произведение (1/|A|) * ||A||^T */
			double reverseDeterminant = 1 / matrixDeterminant;// Переменная для хранения первого множителя из формулы выше
			
			//Поскольку нам нужна транспонированная матрица, то цикл обход будет сначала по столбцам потом по строкам
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					resultMatrix[j][i] = reverseDeterminant * calculateMinor(i,j);
				}
			}
			
		}
		else {
			//Если определитель =0 тогда возвратим эту же матрицу
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					resultMatrix[i][j] = elementsOfMatrix[i][j];
				}
			}
		}
		MatrixThreeXThree resultMatrixThreeXThree(resultMatrix);
		return resultMatrixThreeXThree;
	}
};

int main (int argc, char* argv[]) {
	if (argc < 3) {
		cout<<"Usage: <input matrix file> <output matrix file>"<<endl;
	}
	
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) {
		cout<<"input file opening error"<<endl;
		return 1;
	}
	
	ofstream outputFile(argv[2]);
	if (!outputFile.is_open()) {
		cout<<"output file opening error"<<endl;
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