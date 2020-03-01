using namespace std;
#include <string>
#include <iostream>
#include <optional>
#include <fstream>
#include <iomanip>

struct Arguments
{
	string inputFileName;
};


enum Errors {
	INPUT_FILE_WASNT_OPENED,
	INCORRECT_MATRIX,
};

const int MATRIX_SIZE = 3;
const int MINOR_SIZE = 2;

typedef float Matrix[MATRIX_SIZE][MATRIX_SIZE];
typedef float MinorMatrix[MINOR_SIZE][MINOR_SIZE];


optional <Arguments> GetArguments(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Invalid input" << endl;
		cout << "Usage: <inputFileName>" << endl;
		return nullopt;
	}

	Arguments arg;
	arg.inputFileName = argv[1];
	 
	return arg;
}

bool OpenFileAndFillMatrix(std::optional<Arguments>& arg, Matrix& originalMatrix)
{
	ifstream inputFile;
	inputFile.open(arg->inputFileName);

	if (!inputFile.is_open())
	{
		cout << "Failed to open " << arg->inputFileName << " for reading" << endl;
		return false;
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			inputFile >> originalMatrix[i][j];
			if (inputFile.fail())
			{
				cout << "Incorrect matrix" << endl;
				cout << "Matrix should be 3x3 with digit elements" << endl;
				return false;
			}
		}
	}

	return true;
}


float GetMinor(const Matrix matrix, int row, int column)
{
	float minor;
	MinorMatrix minorMatrix;

	for (int i = 0, minorMatrixRow = 0; i < MATRIX_SIZE; i++)
	{
		if (i == row)
		{
			continue;
		}

		for (int j = 0, minorMatrixColumn = 0; j < MATRIX_SIZE; j++)
		{
			if (j == column)
			{
				continue;
			}
			minorMatrix[minorMatrixRow][minorMatrixColumn] = matrix[i][j];
			minorMatrixColumn++;
		}
		minorMatrixRow++;
	}

	minor = minorMatrix[0][0] * minorMatrix[1][1] - minorMatrix[0][1] * minorMatrix[1][0];

	return minor;
}
float GetDeterminant(const Matrix matrix) {

	float determinant = 0; 
	int index = 1;
	for (int j = 0; j < MATRIX_SIZE; j++)
	{
		determinant += matrix[0][j] * index * GetMinor(matrix, 0, j);
		index *= -1;
	}

	return determinant;
}


void GetIntermediaryMatrix(Matrix& intermediaryMatrix, Matrix originalMatrix)
{
	int index = 1;
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			intermediaryMatrix[j][i] = index * GetMinor(originalMatrix, i, j);
			index *= -1;
		}
	}
}


void getInversedMatrix(const Matrix intermediaryMatrix, Matrix& resultMatrix, float determinant)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			resultMatrix[i][j] = intermediaryMatrix[i][j] / determinant;
		}
	}
}

bool InverseMatrix(Matrix& matrix)
{
	float determinant; 
	determinant = GetDeterminant(matrix);
	if (determinant == 0)
	{
		cout << "Determinant is 0. Matrix is not invertible"<<endl;
		return false;
	}

	Matrix intermediaryMatrix;
	GetIntermediaryMatrix(intermediaryMatrix, matrix);
	getInversedMatrix(intermediaryMatrix, matrix, determinant);
	return true;
}


void ShowInvertedMatrix(Matrix& matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if (matrix[i][j] == -0)
			{
				matrix[i][j] = 0;
			}

			cout << setprecision(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char** argv)
{
	optional arg = GetArguments(argc, argv);

	if (!arg)
	{
		return 1;
	}

	Matrix matrix;

	if (!OpenFileAndFillMatrix(arg, matrix))
	{
		return 1;
	}
	
	if (!InverseMatrix(matrix))
	{
		return 1;
	}

	ShowInvertedMatrix(matrix);

	return 0;
}

