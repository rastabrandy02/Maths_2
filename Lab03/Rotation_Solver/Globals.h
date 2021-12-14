#pragma once
#include <iostream>
#include <math.h>
using namespace std;
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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
	while (angle * RADTODEG > 360) angle -= 360 * DEGTORAD;

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
			matrixVectorProduct[i][j] = (matrix[i][j] - transposed[i][j]) / (2 * sin(angle));
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
		quaternion[i + 1] = axis[i] * sin(angle / 2);
	}
}
void GetAxisAngleFromQuaternion(float* quaternion, float* axis, float& angle)
{

	angle = 2 * acos(quaternion[0]);
	while (angle * RADTODEG > 360) angle -= 360 * DEGTORAD;
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
	while (angle*RADTODEG > 360) angle -= 360*DEGTORAD;
	for (int i = 0; i < 3; i++)
	{
		axis[i] = vector[i] / angle;
	}
}
void GetMatrixFromEulerAngles(float alpha, float beta, float gamma, float matrix[][3])
{
	matrix[0][0] = cos(gamma) * cos(beta);
	matrix[0][1] = cos(gamma) * sin(beta) * sin(alpha) - sin(gamma) * cos(alpha);
	matrix[0][2] = cos(gamma) * sin(beta) * cos(alpha) + sin(gamma) * sin(alpha);

	matrix[1][0] = sin(gamma) * cos(beta);
	matrix[1][1] = sin(gamma) * sin(beta) * sin(alpha) + cos(gamma) * cos(alpha);
	matrix[1][2] = sin(gamma) * sin(beta) * cos(alpha) - cos(gamma) * sin(alpha);

	matrix[2][0] = -sin(beta);
	matrix[2][1] = cos(beta) * sin(alpha);
	matrix[2][2] = cos(beta) * cos(alpha);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (matrix[i][j] > -0.01f && matrix[i][j] < 0.01f) matrix[i][j] = 0.0f;
		}
	}
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
	cout << " }" << endl;
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
			cout << " " << matrix[i][j] << " ";
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
	cout << "{ ";
	for (int i = 0; i < 4; i++)
	{
		cout << quaternion[i];
		if (i != 3)cout << ", ";
	}
	cout << " }" << endl;
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
	cout << " }" << endl;
}
void MatrixInput(float matrix[][3])
{
	bool loop = true;

	int imput = 0;
	cout << "Introduce the values for the matrix:" << endl;
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
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
}
void EulerAnglesInput(float& alpha, float& beta, float& gamma)
{
	cout << "The input of the angles is expected to be in degrees" << endl;
	cout << "Introduce the value of ALPHA: ";
	cin >> alpha;
	alpha *= DEGTORAD;
	cout << endl;
	cout << "Introduce the value of BETA: ";
	cin >> beta;
	beta *= DEGTORAD;
	cout << endl;
	cout << "Introduce the value of GAMMA: ";
	cin >> gamma;
	gamma *= DEGTORAD;
	cout << endl;
}
void AxisAngleInput(float* axis, float& angle)
{
	cout << "The input of the angle is expected to be in degrees" << endl;
	cout << "Introduce the values for the axis: " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "Introduce the term number " << i << ": "<< endl;
		cin >> axis[i];
	}
	cout << "Introduce the value of the angle: " << endl;
	cin >> angle;
	angle *= DEGTORAD;
}
void InputQuaternion(float* quaternion)
{
	cout << "Introduce the values for the quaternion: " << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "Introduce the term number " << i << ": " << endl;
		cin >> quaternion[i];
	}
}
void InputVector(float* vector)
{
	cout << "Introduce the values for the rotation vector: " << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "Introduce the term number " << i << ": " << endl;
		cin >> vector[i];
	}
}