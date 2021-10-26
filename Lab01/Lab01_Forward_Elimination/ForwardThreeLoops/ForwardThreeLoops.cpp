#include "SmallGlobals.h"
#include "BigGlobals.h"
#include "SDL/include/SDL.h"



void SmallTriangulationThreeLoops(float matrix[][SMALL + 1], int n);
void BigTriangulationThreeLoops(float matrix[][BIG + 1], int n);
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_TIMER);
	double time =0;
	Uint64 startTime = SDL_GetPerformanceCounter();
	//SmallMatrixImput(smallMatrix, smallIndependent, SMALL);
	//Draw(smallMatrix, SMALL);
	SmallMatrixRand(smallMatrix, smallIndependent, SMALL);
	SmallExpansion(smallMatrix, smallIndependent, smallExpanded, SMALL);
    SmallTriangulationThreeLoops( smallExpanded, SMALL);
	SmallDrawExpanded(smallExpanded, SMALL);
	Uint64 finishTime = SDL_GetPerformanceCounter();
	time = (double)((finishTime - startTime) * 1000) / SDL_GetPerformanceFrequency();
	//time = finishTime - startTime;
	

	Uint64 startTime2 = SDL_GetPerformanceCounter();
	BigMatrixRand(BigMatrix, BigIndependent, BIG);
	BigExpansion(BigMatrix, BigIndependent, BigExpanded, BIG);
	BigTriangulationThreeLoops(BigExpanded, BIG);
	  Uint64 finishTime2 = SDL_GetPerformanceCounter();
	//time = finishTime - startTime;
	double time2 = (double)((finishTime2 - startTime2) * 1000) / SDL_GetPerformanceFrequency();
	cout << "Time to do the small operation: " << fixed << time << endl;
	cout << "Time to do the big operation: " << fixed << time2 << endl;
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
