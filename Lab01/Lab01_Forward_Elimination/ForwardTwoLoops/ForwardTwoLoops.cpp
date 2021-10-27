#include "SmallGlobals.h"
#include "BigGlobals.h"
#include "SDL/include/SDL.h"
#include <vector>



void SmallTriangulationTwoLoops(float matrix[][SMALL + 1], int n);
void BigTriangulationTwoLoops(float matrix[][BIG + 1], int n);
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_TIMER);
	double time = 0;
	Uint64 startTime = SDL_GetPerformanceCounter();
	//SmallMatrixImput(smallMatrix, smallIndependent, SMALL);
	//Draw(smallMatrix, SMALL);
	SmallMatrixRand(smallMatrix, smallIndependent, SMALL);
	SmallExpansion(smallMatrix, smallIndependent, smallExpanded, SMALL);
	SmallTriangulationTwoLoops(smallExpanded, SMALL);
	SmallDrawExpanded(smallExpanded, SMALL);
	Uint64 finishTime = SDL_GetPerformanceCounter();
	time = (double)((finishTime - startTime) * 1000) / SDL_GetPerformanceFrequency();
	//time = finishTime - startTime;


	Uint64 startTime2 = SDL_GetPerformanceCounter();
	BigMatrixRand(BigMatrix, BigIndependent, BIG);
	BigExpansion(BigMatrix, BigIndependent, BigExpanded, BIG);
	BigTriangulationTwoLoops(BigExpanded, BIG);
	Uint64 finishTime2 = SDL_GetPerformanceCounter();
	//time = finishTime - startTime;
	double time2 = (double)((finishTime2 - startTime2) * 1000) / SDL_GetPerformanceFrequency();
	cout << "Time to do the small operation: " << fixed << time << endl;
	cout << "Time to do the big operation: " << fixed << time2 << endl;
	return 0;
}
void SmallTriangulationTwoLoops(float matrix[][SMALL + 1], int n)
{
	//i: Pivots
	//j: Subpivots
	//k: Current row elements
	/*for (int i = 0; i < n - 1; i++)
	{
		float pivot = matrix[i][i];
		for (int j = i + 1; j < n; j++)
		{
			float subPivot = matrix[j][i];
			for (int k = i; k < n + 1; k++)
			{
				matrix[j][k] = (pivot * matrix[j][k]) - (subPivot * matrix[i][k]);
			}
		}
	}*/
	for (int i = 0; i < n - 1; i++)
	{
		int rowPivotStart = (n + 1) * i + i;
		//int rowPivotFinish = n*i + n - i;
		int rowPivotFinish = rowPivotStart + (n - i);
		vector <float> rowPivot (matrix + rowPivotStart , matrix + rowPivotFinish);
		
		for (int j = i + 1; j < n; j++)
		{
			int rowSubPivotStart = n * (i + 1) + (i + 1) + i;
			int rowSubPivotFinish = rowSubPivotStart + (n - i);
			vector<float> rowSubpivot(matrix + rowSubPivotStart, matrix + rowSubPivotFinish);
			//matrix[j] = ;
			rowPivot *= matrix[i][i];
			rowSubpivot = (matrix[i][i] * rowSubpivot) - (matrix[j][i] * rowPivot);
		}
	}
}
void BigTriangulationTwoLoops(float matrix[][BIG + 1], int n)
{
	//i: Pivots
	//j: Subpivots
	//k: Current row elements
	/*for (int i = 0; i < n - 1; i++)
	{
		float pivot = matrix[i][i];
		for (int j = i + 1; j < n; j++)
		{
			float subPivot = matrix[j][i];
			for (int k = i; k < n + 1; k++)
			{
				matrix[j][k] = (pivot * matrix[j][k]) - (subPivot * matrix[i][k]);
			}
		}
	}*/
}
