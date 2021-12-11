#include <iostream>
#include <time.h>
using namespace std;

float axis[3] = { 0 };
float angle;
float matrixRotation[3][3] = { 0 };
float trace = 0;

void GetRotationFromAxisAngle(float* axis, float angle, float rotation[][3]);
bool EqualToOne(float num);
float GetTrace(float matrix[][3]);
int main()
{
	srand(NULL);
	cout << "This program will create 108 rotation matrices from a random axis and a incremental angle (from 0 to 1080 degrees)" << endl;
	for (int loop = 0; loop < 108; loop++)
	{
		for (int i = 0; i < 3; i++)
		{
			axis[i] = rand() % 9;
		}

		//Here we get the angle from 0 to 6*PI in degrees
		angle = 10 * loop;

		GetRotationFromAxisAngle(axis, angle, matrixRotation);
		trace = GetTrace(matrixRotation);
		cout << "Matrix number: " << loop << " Angle: " << angle << " Trace: " << trace << endl;
	}
	cout << "Imput any key to exit" << endl;
	char end;
	cin >> end;
	cout << "Exiting the program" << endl;
	return 0;
}
void GetRotationFromAxisAngle(float* axis, float angle, float rotation[][3])
{

	float axisNorm;
	float matrixIdentity[3][3] = { 0 };
	float matrixUU[3][3] = { 0 };
	float matrixVectorProduct[3][3] = { 0 };

		axisNorm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	if (EqualToOne(axisNorm) == false)
	{
		for (int i = 0; i < 3; i++)
		{
			axis[i] = axis[i] / axisNorm;

		}
		axisNorm = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
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

bool EqualToOne(float num)
{
	bool ret = false;

	if (num < 1.1f && num > 0.9f) ret = true;
	return ret;
}
float GetTrace(float matrix[][3])
{
	float result = 0;
	for (int i = 0; i < 3; i++)
	{
		result += matrix[i][i];
	}
	return result;
}