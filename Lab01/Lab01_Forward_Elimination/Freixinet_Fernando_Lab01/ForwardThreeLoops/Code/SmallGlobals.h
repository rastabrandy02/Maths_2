#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;
#define SMALL 5

float smallMatrix[SMALL][SMALL] = { 0 };
float smallIndependent[SMALL] = { 0 };
float smallExpanded[SMALL][SMALL + 1] = { 0 };
float smallResult[SMALL] = { 0 };



int smallFlag;
enum flagIndicator
{
	//  0 for No solution
	//  1 for infinite solution
	//  2 for one solution
	NO_SOLUTION = 0,
	INFINITE_SOLUTIONS,
	ONE_SOLUTION
};
void SmallMatrixImput(float matrix[][SMALL], float* independent, int n)
{
	bool loop = true;

	int imput = 0;
	cout << "Introduce the values for the matrix:" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			loop = true;
			cout << "Term [" << i << "] [" << j << "]" << endl;
			cin >> imput;
			while (loop == true)
			{
				loop = false;

				if (imput > 9 || imput < -9)
				{
					cout << "Invalid value, try one between -9 and 9" << endl;

					cout << "Term [" << i << "] [" << j << "]" << endl;
					cin >> imput;
					loop = true;
				}
			}
			matrix[i][j] = imput;
		}
	}
	imput = 0;
	cout << "Introduce the values for the independent terms:" << endl;
	for (int i = 0; i < n; i++)
	{
		loop = true;
		cout << "Term [" << i << "]" << endl;
		cin >> imput;
		while (loop == true)
		{
			loop = false;

			if (imput > 9 || imput < -9)
			{
				cout << "Invalid value, try one between -9 and 9" << endl;
				cout << "Term [" << i << "]" << endl;
				cin >> imput;
				loop = true;
			}
		}
		independent[i] = imput;
	}


}
void SmallMatrixRand(float matrix[][SMALL], float* independent, int n)
{
	srand(time(NULL));
	bool loop = true;

	int imput = 0;
	cout << "Assigning the values for the matrix:" << endl;
	for (int i = 0; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			loop = true;
			
			imput = rand() % 9;
			if (rand() % 2) imput *= -1;
			
			matrix[i][j] = imput;
			cout << "Term [" << i << "] [" << j << "] = "<<matrix[i][j] << endl;
		}
	}
	imput = 0;
	cout << "Assigning  values for the independent terms:" << endl;
	for (int i = 0; i < n; i++)
	{
		loop = true;
		
		imput = rand() % 9;
		if (rand() % 2) imput *= -1;
		
		independent[i] = imput;
		cout << "Term [" << i << "] = "<<independent[i] << endl;
	}


}

void SmallExpansion(float matrix[][SMALL], float* independent, float expanded[][SMALL + 1], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (j < n) expanded[i][j] = matrix[i][j];
			else if (j == n)expanded[i][j] = independent[i];
		}
	}
}


void SmallCheckConsistency(float matrix[][SMALL + 1], int n, int& flag)
{
	int i, j;
	float sum;
	int aux = 0;
	
	
	flag = NO_SOLUTION;
	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j < n; j++)
			sum = sum + matrix[i][j];
		if (sum == matrix[i][j])
			flag = INFINITE_SOLUTIONS;
	}
	for (int i = 0; i < n + 1; i++)
	{
		if (matrix[i][i] != 0) aux++;
		if (aux == n) flag = ONE_SOLUTION;
	}
}
void SmallPrepareResult(float* result, int n)
{
	for (int i = 0; i < n; i++)
	{
		result[i] = 1;
	}
}
void SmallPrepareMatrix(float matrix[][SMALL + 1], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			if ((matrix[i][j] <= 0.001) && (matrix[i][j] >= -0.001)) matrix[i][j] = 0;
		}
	}
}
void SmallDrawMatrix(float matrix[][SMALL], int n)
{
	cout << "------Matrix------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			if (j == n) cout << "|";
			cout << "[" << i << "] [" << j << "] = " << matrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "------------------" << endl;
}
void SmallDrawExpanded(float matrix[][SMALL + 1], int n)
{
	cout << "------Matrix------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			if (j == n) cout << "|";
			cout << "[" << i << "] [" << j << "] = " << matrix[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "------------------" << endl;

}
void SmallDrawResult(float* result, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Result [" << i << "] = " << result[i] << endl;
	}
}