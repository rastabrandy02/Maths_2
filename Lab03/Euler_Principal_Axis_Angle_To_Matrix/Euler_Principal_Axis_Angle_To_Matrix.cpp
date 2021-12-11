#include <iostream>
#include <math.h>
using namespace std;

float axis[3] = { 0 };
float paralelAxis[3] = { 0 };
float perpendicularAxis[3] = { 0 };
float storedAxis[3] = { 0 };
float angle;
float matrixRotation[3][3] = { 0 };
float determinant;
bool isTransposeInverse = false;
bool loop = true;
int loopCount = 0;

void GetRotationFromAxisAngle(float* axis, float angle, float rotation[][3], int switchController);
bool EqualToOne(float num);
float GetDeterminant(float matrix[][3]);
bool CheckTransposeInverse(float matrix[][3]);
void PrintResults(float matrix[][3], float determinant, bool transposeInverseCheck);

int main()
{
	cout << "Welcome, this program will create a rotation matrix from the Euler principal anxis and angle" << endl;
	cout << "Introuduce the Euler principal axis:" << endl;
	for(int i=0; i < 3;i++)
	{
		cout << "Intruduce the component in position " << i << endl;
		cin >> storedAxis[i];
	}
	cout << "Introduce the Euler principal angle" << endl;
	cin >> angle;
	for (int i = 0; i < 3; i++)
	{
		axis[i] = storedAxis[i];
		 paralelAxis[i] = storedAxis[i];
		 perpendicularAxis[i] = storedAxis[i];
	}
	while (loop)
	{
		cout << endl << "----------" << endl;
		cout << "Starting loop number: " << loopCount << endl<<endl;
		cout << "Computing the rotation matrix..." << endl;
		switch (loopCount)
		{
		case 0:
		{
			GetRotationFromAxisAngle(axis, angle, matrixRotation, loopCount);
		}break;
		case 1:
		{
			GetRotationFromAxisAngle(paralelAxis, angle, matrixRotation, loopCount);
			
		}break;
		case 2:
		{
			GetRotationFromAxisAngle(perpendicularAxis, angle, matrixRotation, loopCount);
		}break;
		default:
			break;
		}
		
		cout << "Computing the determinant..." << endl;
		determinant = GetDeterminant(matrixRotation);
		cout << "Checking if the transpose is equal to the inverse..." << endl;
		isTransposeInverse = CheckTransposeInverse(matrixRotation);
		PrintResults(matrixRotation, determinant, isTransposeInverse);
		
		loopCount++;
		if (loopCount == 1) cout << endl<< "Next loop we will do the same with a paralel axis" << endl<<endl;
		if (loopCount == 2) cout << endl<< "Next loop we will do the same with a perpendicular axis" << endl<<endl;
		if (loopCount >= 3) loop = false;
		
		
	}
	cout << "Imput any key to exit" << endl;
	char end;
	cin >> end;
	cout << "Exiting the program" << endl;
	
	return 0;
}

bool EqualToOne(float num)
{
	bool ret = false;

	if (num < 1.1f && num > 0.9f) ret = true;
	return ret;
}
void GetRotationFromAxisAngle(float* axis, float angle, float rotation[][3], int switchController)
{
	
	float axisNorm;
	float matrixIdentity[3][3] = { 0 };
	float matrixUU[3][3] = { 0 };
	float matrixVectorProduct[3][3] = { 0 };

	switch (switchController)
	{
		case 0:
		{
			 axisNorm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
			if (EqualToOne(axisNorm) == false)
			{
				for (int i = 0; i < 3; i++)
				{
					axis[i] = axis[i] / axisNorm;
				}
			}
			axisNorm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
			
		}break;
		case 1:
		{
			
				for (int i = 0; i < 3; i++)
				{
					axis[i] = axis[i] * 2;
				}
			
			
		}break;
		case 2:
		{
			
			float aux = axis[0];
			axis[0] = -axis[1];
			axis[1] = aux;
		
		}break;
		default:
			break;
	}
	


	for (int i = 0; i < 3; i++)
	{
		matrixIdentity[i][i] = cos(angle);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrixUU[i][j] = (1 - cos(angle)) * (axis[i] * axis[j]);
		}
	}
	matrixVectorProduct[1][0] = axis[2] * sin(angle);
	matrixVectorProduct[2][0] = -axis[1] * sin(angle);
	matrixVectorProduct[0][1] = -axis[2] * sin(angle);
	matrixVectorProduct[2][1] = axis[0] * sin(angle);
	matrixVectorProduct[0][2] = axis[1] * sin(angle);
	matrixVectorProduct[1][2] = -axis[0] * sin(angle);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rotation[i][j] = matrixIdentity[i][j] + matrixUU[i][j] + matrixVectorProduct[i][j];
		}
	}
}
float GetDeterminant(float matrix[][3])
{
	float result;
	float a = 1.0f;
	for (int i = 0; i < 3; i++)
	{
		a *= matrix[i][i];
	}
	a += (matrix[1][0] * matrix[2][1] * matrix[0][2]);
	a += (matrix[2][0] * matrix[0][1] * matrix[1][2]);
	
	float b = 1.0f;
	for (int i = 0; i < 3; i++)
	{
		b *= matrix[i][2-i];
	}
	b += (matrix[1][2] * matrix[2][1] * matrix[0][0]);
	b += (matrix[2][2] * matrix[0][1] * matrix[1][0]);
	
	result = a - b;
	if (EqualToOne(result)) return 1.0f;
	else return result;
	
}

bool CheckTransposeInverse(float matrix[][3])
{
	float transpose[3][3];
	float mult[3][3] = { 0 };
	int aux = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			transpose[i][j] = matrix[j][i];
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				mult[i][j] += matrix[i][k] * transpose[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (EqualToOne(mult[i][i])) aux++;
	}
	if (aux >= 3) return true;
	else return false;
}
void PrintResults(float matrix[][3], float determinant, bool transposeInverseCheck)
{
	cout << "This is the rotation matrix: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout <<" "<< matrix[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "This is the value of the determinant: " << determinant << endl;
	if (isTransposeInverse) cout << "The transpose of this matrix is equal to it's inverse" << endl;
	else cout << "The transpose and the inverse of this matrix are not the same" << endl;
}