#include "SmallGlobals.h"
#include "BigGlobals.h"
#include "SDL/include/SDL.h"




void SmallTriangulationThreeLoops(float matrix[][SMALL + 1], int n);
void BigTriangulationThreeLoops(float matrix[][BIG + 1], int n);

void SmallBackTracking(float matrix[][SMALL + 1], int n, float* result);


int main(int argc, char* argv[])
{
	
	SDL_Init(SDL_INIT_TIMER);
	double smallTime =0;
	Uint64 smallStartTime = SDL_GetPerformanceCounter();
	//SmallMatrixImput(smallMatrix, smallIndependent, SMALL);
	//SmallDrawMatrix(smallMatrix, SMALL);
	SmallMatrixRand(smallMatrix, smallIndependent, SMALL);
	SmallExpansion(smallMatrix, smallIndependent, smallExpanded, SMALL);
    SmallTriangulationThreeLoops( smallExpanded, SMALL);
	SmallDrawExpanded(smallExpanded, SMALL);
	Uint64 smallFinishTime = SDL_GetPerformanceCounter();
	smallTime = (double)((smallFinishTime - smallStartTime) * 1000) / SDL_GetPerformanceFrequency();
	//time = finishTime - startTime;
	
	SmallCheckConsistency(smallExpanded, SMALL, smallFlag);

	switch (smallFlag)
	{
	case NO_SOLUTION:
	{
		cout << "This matrix has no solutions" << endl;
	}break;
	case INFINITE_SOLUTIONS:
	{
		cout << "This matrix has infinite solutions" << endl;
	}break;
	case ONE_SOLUTION:
	{
		cout << "The matrix can be solved for one solution" << endl;
		//fill_n(smallResult, SMALL, 1);
		SmallPrepareResult(smallResult, SMALL);
		SmallPrepareMatrix(smallExpanded, SMALL);
		cout << "Starting backtracking..." << endl;
		SmallBackTracking(smallExpanded, SMALL, smallResult);
		SmallDrawResult(smallResult, SMALL);
	}break;
	default:
		break;
	}
	
	Uint64 bigStartTime = SDL_GetPerformanceCounter();
	//BigMatrixRand(BigMatrix, BigIndependent, BIG);
	//BigExpansion(BigMatrix, BigIndependent, BigExpanded, BIG);
	//BigTriangulationThreeLoops(BigExpanded, BIG);
	  Uint64 bigFinishTime = SDL_GetPerformanceCounter();
	//time = finishTime - startTime;
	double bigTime = (double)((bigFinishTime - bigStartTime) * 1000) / SDL_GetPerformanceFrequency();
	cout << "Time to do the small triangulation: " << fixed << smallTime << endl;
	cout << "Time to do the big triangulation: " << fixed << bigTime << endl;
	return 0;
}
void SmallTriangulationThreeLoops(float matrix[][SMALL + 1], int n)
{
	//i: Pivots
	//j: Subpivots
	//k: Current row elements
	for (int i = 0; i < n - 1; i++)
	{
		float pivot = matrix[i][i];
		for(int j = i+1; j < n; j++)
		{
			float subPivot = matrix[j][i];
			for (int k = i; k < n + 1; k++)
			{
				matrix[j][k] = (pivot * matrix[j][k]) - (subPivot * matrix[i][k]);
			}
		}
	}
}
void BigTriangulationThreeLoops(float matrix[][BIG + 1], int n)
{
	//i: Pivots
	//j: Subpivots
	//k: Current row elements
	for (int i = 0; i < n - 1; i++)
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
	}
}

void SmallBackTracking(float matrix[][SMALL + 1], int n, float* result)
{
	
	
		for (int i = n - 1; i >= 0; i--)
		{
			float sum = 0;
			for (int j = n - 1; j >= 0; j--)
			{
				//result[j] = matrix[j][i]/(matrix[j][k] * result[k])
				sum += matrix[i][j] * result[j];
			}
			result[i] = matrix[i][n+1] / sum;
		}
	
}
	
