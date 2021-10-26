#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;
#define BIG 50

float BigMatrix[BIG][BIG] = { 0 };
float BigIndependent[BIG] = { 0 };
float BigExpanded[BIG][BIG + 1] = { 0 };
float BigResult[BIG] = { 0 };

void BigMatrixImput(float matrix[][BIG], float* independent, int n)
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
void BigMatrixRand(float matrix[][BIG], float* independent, int n)
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
			cout << "Term [" << i << "] [" << j << "] = " << matrix[i][j] << endl;
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
		cout << "Term [" << i << "] = " << independent[i] << endl;
	}


}

void BigExpansion(float matrix[][BIG], float* independent, float expanded[][BIG + 1], int n)
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

void BigDraw(float matrix[][BIG], int n)
{
	cout << "---Matrix---" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "Term [" << i << "] [" << j << "] = " << matrix[i][j] << endl;
		}
	}

}
void BigDrawExpanded(float matrix[][BIG + 1], int n)
{
	cout << "---Matrix---" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			cout << "Term [" << i << "] [" << j << "] = " << matrix[i][j] << endl;
		}
	}

}