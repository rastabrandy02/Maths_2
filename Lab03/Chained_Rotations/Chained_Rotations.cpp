#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

float eulerAxis[3];
float eulerAngle;
float matrix[3][3];
float alpha;
float beta;
float gamma;
float quaternion[4];
float vector[3];

void GetMatrixFromAxisAngle(float* axis, float angle, float matrix[][3]);
void GetEulerAnglesFromMatrix(float matrix[][3], float& alpha, float& beta, float& gamma);
void GetAxisAngleFromMatrix(float matrix[][3], float* axis, float& angle);
void GetQuaternionFromAxisAngle(float* axis, float angle, float* quaternion);
void GetAxisAngleFromQuaternion(float* quaternion, float* axis, float& angle);
void GetVectorFromAxisAngle(float* axis, float angle, float* vector);
void GetAxisAngleFromVector(float* vector, float* axis, float& angle);
bool EqualToOne(float num);
float GetTrace(float matrix[][3]);

void PrintEulerAxisAngle(float* axis, float angle);
void PrintMatrix(float matrix[][3]);
void PrintEulerAngles(float alpha, float beta, float gamma);
void PrintQuaternion(float* quaternion);
void PrintVector(float* vector);
int main()
{
	srand(time(NULL));
	cout << "This program will chain between different representations of the same rotation" << endl;
	cout << "We will start with a random Euler principal axis and angle:" << endl;
	cout << endl;
	for (int i = 0; i < 3; i++)
	{
		eulerAxis[i] = rand() % 9;
	}
	eulerAngle = rand()%90 * DEGTORAD;
	float axisNorm = sqrt(eulerAxis[0] * eulerAxis[0] + eulerAxis[1] * eulerAxis[1] + eulerAxis[2] * eulerAxis[2]);
	if (EqualToOne(axisNorm) == false)
	{
		for (int i = 0; i < 3; i++)
		{
			eulerAxis[i] = eulerAxis[i] / axisNorm;

		}

	}
	PrintEulerAxisAngle(eulerAxis, eulerAngle);
	cout << endl;

	GetMatrixFromAxisAngle(eulerAxis, eulerAngle, matrix);
	PrintMatrix(matrix);
	cout << endl;

	cout << "With this matrix we will find the euler angles (ALPHA, BETA & GAMMA):" << endl;
	GetEulerAnglesFromMatrix(matrix, alpha, beta, gamma);
	PrintEulerAngles(alpha, beta, gamma);
	cout << endl;

	cout << "With the matrix we will also find the Euler principal axis and angle:" << endl;
	GetAxisAngleFromMatrix(matrix, eulerAxis, eulerAngle);
	PrintEulerAxisAngle(eulerAxis, eulerAngle);
	cout << endl;

	cout << "Using the Euler principal axis and angle, we will find the quaternion: " << endl;
	GetQuaternionFromAxisAngle(eulerAxis, eulerAngle, quaternion);
	PrintQuaternion(quaternion);
	cout << endl;

	cout << "We will use the quaternion to find the Euler principal axis and angle: " << endl;
	GetAxisAngleFromQuaternion(quaternion, eulerAxis, eulerAngle);
	PrintEulerAxisAngle(eulerAxis, eulerAngle);
	cout << endl;

	cout << "Using the Euler principal axis and angle, we will find the rotation vector: " << endl;
	GetVectorFromAxisAngle(eulerAxis, eulerAngle, vector);
	PrintVector(vector);
	cout << endl;

	cout << "Finally, we will use the rotation vector to find the Euler principal axis and angle: " << endl;
	GetAxisAngleFromVector(vector, eulerAxis, eulerAngle);
	PrintEulerAxisAngle(eulerAxis, eulerAngle);
	return 0;
}


void GetMatrixFromAxisAngle(float* axis, float angle, float matrix[][3])
{
	float axisNorm;
	float matrixIdentity[3][3] = { 0 };
	float matrixUU[3][3] = { 0 };
	float matrixVectorProduct[3][3] = { 0 };

	

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
			matrix[i][j] = matrixIdentity[i][j] + matrixUU[i][j] + matrixVectorProduct[i][j];
		}
	}
}
void GetEulerAnglesFromMatrix(float matrix[][3], float& alpha, float& beta, float& gamma)
{
	beta = RADTODEG * (-asin(matrix[2][0]));
	gamma = RADTODEG * atan2f(matrix[0][0] / cos(beta), matrix[1][0] / cos(beta));
	alpha = RADTODEG * atan2f(matrix[2][1] / cos(beta), matrix[2][2] / cos(beta));
	if (alpha < 0) alpha = alpha + 180;
	if (gamma < 0) gamma = gamma + 180;
}
void GetAxisAngleFromMatrix(float matrix[][3], float* axis, float& angle)
{
	float transposed[3][3] = { 0 };
	float matrixVectorProduct[3][3] = { 0 };

	angle = acos((GetTrace(matrix) - 1) / 2);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			transposed[i][j] = matrix[j][i];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrixVectorProduct[i][j] = (matrix[i][j] - transposed[i][j]) / (2*sin(angle));
		}
	}
	axis[0] = (matrixVectorProduct[2][1] - matrixVectorProduct[1][2]) / 2;
	axis[1] = (matrixVectorProduct[0][2] - matrixVectorProduct[2][0]) / 2;
	axis[2] = (matrixVectorProduct[1][0] - matrixVectorProduct[0][1]) / 2;
}
void GetQuaternionFromAxisAngle(float* axis, float angle, float* quaternion)
{
	quaternion[0] = cos(angle / 2);
	for (int i = 0; i < 3; i++)
	{
		quaternion[i+ 1] = axis[i] * sin(angle / 2);
	}
}
void GetAxisAngleFromQuaternion(float* quaternion, float* axis, float& angle)
{
	
	angle = 2 * acos(quaternion[0]);
	for (int i = 0; i < 3; i++)
	{
		axis[i] = quaternion[i + 1] / sqrt(1 - pow(quaternion[0], 2));
	}
	
}
void GetVectorFromAxisAngle(float* axis, float angle, float* vector)
{
	for (int i = 0; i < 3; i++)
	{
		vector[i] = angle * axis[i];
	}
}
void GetAxisAngleFromVector(float* vector, float* axis, float& angle)
{
	angle = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	for (int i = 0; i < 3; i++)
	{
		axis[i] = vector[i] / angle;
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
void PrintEulerAxisAngle(float* axis, float angle)
{
	cout << "This is the Euler principal axis: " << endl;
	cout << "{ ";
	for (int i = 0; i < 3; i++)
	{
		cout << axis[i];
		if (i != 2)cout << ", ";
	}
	cout << " }"<<endl;
	cout << "This is the Euler principal angle: " << endl;
	cout << RADTODEG * angle << endl;
}
void PrintMatrix(float matrix[][3])
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
}
void PrintEulerAngles(float alpha, float beta, float gamma)
{
	cout << "These are the Euler angles: " << endl;
	cout << "ALPHA: " << alpha << endl;
	cout << "BETA: " << beta << endl;
	cout << "GAMMA: " << gamma << endl;
}
void PrintQuaternion(float* quaternion)
{
	cout << "This is the quaternion: " << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << " " << quaternion[i] << " ";
	}
	cout << endl;
}
void PrintVector(float* vector)
{
	cout << "This is the rotation vector: " << endl;
	cout << "{ ";
	for (int i = 0; i < 3; i++)
	{
		cout << vector[i];
		if (i != 2)cout << ", ";
	}
	cout << " }"<<endl;
}