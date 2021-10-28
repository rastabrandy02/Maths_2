#include "SmallGlobals.h"
#include "BigGlobals.h"
#include "SDL/include/SDL.h"
#include <vector>
#include <algorithm>
#include <iterator>



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
	//time = finishTime - startTime;
	time = (double)((finishTime - startTime) * 1000) / SDL_GetPerformanceFrequency();
	


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
	
	
	for (int i = 0; i < n - 1; i++)
	{
		
		float pivot = matrix[i][i];
		int rowPivotStart = i;
		int rowPivotFinish = rowPivotStart + (n + 1);
		vector<float> rowPivot;
		SmallInsertInVector(matrix, SMALL, i, rowPivot);
		
		
		for (int j = i + 1; j < n; j++)
		{
			vector<float> result;
			float subPivot = matrix[j][i];
			int rowSubPivotStart = (n+1) * j;
			int rowSubPivotFinish = rowSubPivotStart + n;
			vector<float> rowSubPivot;
			SmallInsertInVector(matrix, SMALL, j, rowSubPivot);


			transform(rowPivot.begin(), rowPivot.end(), rowPivot.begin(), [subPivot](float& c) {return c * subPivot; });
			transform(rowSubPivot.begin(), rowSubPivot.end(), rowSubPivot.begin(), [pivot](float& c) { return c * pivot; });

			/*transform(rowSubPivot.begin(), rowSubPivot.end(), rowPivot.begin(), back_inserter(result),
				[](float a, float b) { return fabs(a - b); });*/
			transform(rowPivot.begin(), rowPivot.end(), rowSubPivot.begin(), back_inserter(result), minus<float>());
			
			SmallInsertInMatrix(matrix, SMALL, j, result);
			
		}
	}
	
}
void BigTriangulationTwoLoops(float matrix[][BIG + 1], int n)
{
	//i: Pivots
	//j: Subpivots
	for (int i = 0; i < n - 1; i++)
	{


		float pivot = matrix[i][i];
		int rowPivotStart = i;
		int rowPivotFinish = rowPivotStart + (n + 1);
		vector<float> rowPivot;
		BigInsertInVector(matrix, BIG, i, rowPivot);


		for (int j = i + 1; j < n; j++)
		{
			vector<float> result;
			float subPivot = matrix[j][i];
			int rowSubPivotStart = (n + 1) * j;
			int rowSubPivotFinish = rowSubPivotStart + n;
			vector<float> rowSubPivot;
			BigInsertInVector(matrix, BIG, j, rowSubPivot);


			transform(rowPivot.begin(), rowPivot.end(), rowPivot.begin(), [subPivot](float& c) {return c * subPivot; });
			transform(rowSubPivot.begin(), rowSubPivot.end(), rowSubPivot.begin(), [pivot](float& c) { return c * pivot; });

			/*transform(rowSubPivot.begin(), rowSubPivot.end(), rowPivot.begin(), back_inserter(result),
				[](float a, float b) { return fabs(a - b); });*/
			
			transform(rowPivot.begin(), rowPivot.end(), rowSubPivot.begin(), back_inserter(result), minus<float>());
			

			BigInsertInMatrix(matrix, BIG, j, result);

		}
	}
}
