
#include "Globals.h"
#include "SDL/include/SDL.h"
#include <vector>
#include <algorithm>
#include <iterator>

void TriangulationTwoLoops(vector<vector<float> > &matrix, int n);

int main(int argc, char* argv[])
{
	bool manualImput = false;
	char response;
	cout << "------WELCOME------" << endl;
	cout << "This program will triangulate one small matrix and one big matrix using 2 for loops" << endl;
	cout << "------------------" << endl;
	cout << "The current dimensions set for the two matrices are:" << endl;
	cout << "SMALL matrix is " << SMALL << " X " << SMALL << " plus the independent term" << endl;
	cout << "BIG matrix is " << BIG << " X " << BIG << " plus the independent term" << endl;
	cout << endl << "Do you want to set the values for the small matrix and its independent term manually? (y/n)" << endl;
	cin >> response;
	if (response == 'y') manualImput = true;

	SDL_Init(SDL_INIT_TIMER);
	double smallTime = 0;
	Uint64 smallStartTime = SDL_GetPerformanceCounter();

	if (manualImput) MatrixImput(smallMatrix, smallIndependent, SMALL);
	else MatrixRand(smallMatrix, smallIndependent, SMALL);

	DrawMatrix(smallMatrix, SMALL);
	Expansion(smallMatrix, smallIndependent, smallExpanded, SMALL);
	TriangulationTwoLoops(smallExpanded, SMALL);
	DrawExpanded(smallExpanded, SMALL);

	Uint64 smallFinishTime = SDL_GetPerformanceCounter();
	smallTime = (double)((smallFinishTime - smallStartTime) * 1000) / SDL_GetPerformanceFrequency();
	cout << "Time to do the small triangulation: " << fixed << smallTime << endl;

	cout << "Do you want to exit before the big matrix is triangulated? (y/n)" << endl;
	cin >> response;
	if (response == 'y') return 0;


	Uint64 bigStartTime = SDL_GetPerformanceCounter();

	MatrixRand(bigMatrix, bigIndependent, BIG);
	Expansion(bigMatrix, bigIndependent, bigExpanded, BIG);
	TriangulationTwoLoops(bigExpanded, BIG);

	Uint64 bigFinishTime = SDL_GetPerformanceCounter();
	double bigTime = (double)((bigFinishTime - bigStartTime) * 1000) / SDL_GetPerformanceFrequency();

	cout << "Time to do the big triangulation: " << fixed << bigTime << endl;
	cout << "Program finished, imput any key to exit" << endl;
	cin >> response;
	return 0;
}

void TriangulationTwoLoops(vector<vector<float> >& matrix, int n)
{
	
	for (int i = 0; i < n - 1; i++)
	{
		
		float pivot = matrix[i][i];
		vector<float> rowPivot(matrix[i]);
		vector <float> rowPivotResult(matrix[i]);
		for (int j = i + 1; j < n; j++)
		{
			float subPivot = matrix[j][i];
			vector <float> rowSubPivot(matrix[j]);
			vector<float> rowSubPivotResult(matrix[j]);

			transform(rowPivot.begin(), rowPivot.end(), rowPivotResult.begin(), [subPivot](float& c) {return c * subPivot; });
			transform(rowSubPivot.begin(), rowSubPivot.end(), rowSubPivotResult.begin(), [pivot](float& c) { return c * pivot; });

			transform(rowPivotResult.begin(), rowPivotResult.end(), rowSubPivotResult.begin(), matrix[j].begin(), minus<float>());
			
		}
		
	}
	
}
