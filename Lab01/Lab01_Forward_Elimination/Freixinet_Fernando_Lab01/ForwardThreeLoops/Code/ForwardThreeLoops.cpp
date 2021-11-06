#include "SmallGlobals.h"
#include "BigGlobals.h"
#include "SDL/include/SDL.h"
using namespace std;



void SmallTriangulationThreeLoops(float matrix[][SMALL + 1], int n);
void BigTriangulationThreeLoops(float matrix[][BIG + 1], int n);

void SmallBackTracking(float matrix[][SMALL + 1], int n, float* result);


int main(int argc, char* argv[])
{
	bool manualImput = false;
	char response;
	cout << "------WELCOME------" << endl;
	cout << "This program will triangulate one small matrix and one big matrix using 3 for loops" << endl;
	cout << "It will also solve the small matrix using backtracking" << endl;
	cout << "------------------" << endl;
	cout << "The current dimensions set for the two matrices are:" << endl;
	cout << "SMALL matrix is " << SMALL << " X " << SMALL << " plus the independent term" << endl;
	cout << "BIG matrix is " << BIG << " X " << BIG << " plus the independent term" << endl;
	cout << endl << "Do you want to set the values for the small matrix and its independent term manually? (y/n)" << endl;
	cin >> response;
	if (response == 'y') manualImput = true;

	SDL_Init(SDL_INIT_TIMER);
	double smallTime =0;
	Uint64 smallStartTime = SDL_GetPerformanceCounter();

	if (manualImput) SmallMatrixImput(smallMatrix, smallIndependent, SMALL);
	else SmallMatrixRand(smallMatrix, smallIndependent, SMALL);
	
	SmallDrawMatrix(smallMatrix, SMALL);
	SmallExpansion(smallMatrix, smallIndependent, smallExpanded, SMALL);
    SmallTriangulationThreeLoops( smallExpanded, SMALL);
	SmallDrawExpanded(smallExpanded, SMALL);

	Uint64 smallFinishTime = SDL_GetPerformanceCounter();
	smallTime = (double)((smallFinishTime - smallStartTime) * 1000) / SDL_GetPerformanceFrequency();
	
	
	SmallCheckConsistency(smallExpanded, SMALL, smallFlag);

	switch (smallFlag)
	{
	case NO_SOLUTION:
	{
		
		cout << endl<< "------This matrix has no solutions------" << endl << endl;;
		
	}break;
	case INFINITE_SOLUTIONS:
	{
		
		cout << endl<<  "------This matrix has infinite solutions------" << endl<<endl;
	}break;
	case ONE_SOLUTION:
	{
		cout << endl<<"------The matrix can be solved for one solution------" <<endl<< endl;
		//fill_n(smallResult, SMALL, 1);
		SmallPrepareResult(smallResult, SMALL);
		SmallPrepareMatrix(smallExpanded, SMALL);
		cout << "Starting backtracking..." << endl<<endl;
		SmallBackTracking(smallExpanded, SMALL, smallResult);
		SmallDrawResult(smallResult, SMALL);
	}break;
	default:
		break;
	}
	cout << "Time to do the small triangulation: " << fixed << smallTime << endl;
	cout << "Do you want to exit before the big matrix is triangulated? (y/n)" << endl;
	cin >> response;
	if (response == 'y') return 0;
	Uint64 bigStartTime = SDL_GetPerformanceCounter();
	BigMatrixRand(BigMatrix, BigIndependent, BIG);
	BigExpansion(BigMatrix, BigIndependent, BigExpanded, BIG);
	BigTriangulationThreeLoops(BigExpanded, BIG);
	  Uint64 bigFinishTime = SDL_GetPerformanceCounter();
	
	double bigTime = (double)((bigFinishTime - bigStartTime) * 1000) / SDL_GetPerformanceFrequency();
	
	cout << "Time to do the big triangulation: " << fixed << bigTime << endl;

	cout << "Program finished, imput any key to exit" << endl;
	cin >> response;
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
	result[n - 1] = matrix[n - 1][n] / matrix[n - 1][n - 1];

		for (int i = n - 2; i >= 0; i--)
		{
			float sum = 0;
			for (int j = n - 1; j >= 0; j--)
			{
				if(matrix[i][j] != 0) sum = sum + (matrix[i][j] * result[j]);
			}
			result[i] = (matrix[i][n] / sum);
		}
	
}
	
