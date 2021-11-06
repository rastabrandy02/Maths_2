#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
using namespace std;
#define SMALL 3
#define BIG 50

vector<vector<float>> smallMatrix;
vector<float>smallIndependent;
vector<vector<float>> smallExpanded;
vector<float>smallResult;

vector<vector<float>> bigMatrix;
vector<float> bigIndependent;
vector<vector<float>> bigExpanded;
vector<float> bigResult;


void MatrixImput(vector<vector<float> >& matrix, vector<float>& independent, int n)
{
	bool loop = true;
	int imput = 0;

	matrix.assign(n, vector<float>(n, 0));
	independent.assign(n, 0);
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
void MatrixRand(vector<vector<float> >& matrix, vector<float>& independent, int n)
{
	srand(time(NULL));
	bool loop = true;
	int imput = 0;

	matrix.assign(n, vector<float>(n, 0));
	independent.assign(n, 0);

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

void Expansion(vector<vector<float> > matrix, vector<float> independent, vector<vector<float>>& expanded, int n)
{
	expanded.assign(n, vector<float>(n + 1, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (j < n) expanded[i][j] = matrix[i][j];
			else if (j == n)expanded[i][j] = independent[i];
		}
	}
}

void DrawMatrix(vector<vector<float> > matrix, int n)
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