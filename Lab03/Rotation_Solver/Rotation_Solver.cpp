#include <iostream>
#include <math.h>
#include "Globals.h"

using namespace std;
char order;
float eulerAxis[3];
float eulerAngle;
float matrix[3][3];
float alpha;
float beta;
float gamma;
float quaternion[4];
float vector[3];

int main()
{
	cout << "This program is a general-purpose rotation solver that transforms the same rotation in different forms" << endl;
	cout << "First, what do you want to tranform?" << endl;
	cout << "Rotation matrix ---> r" << endl;
	cout << "Euler angles (ALPHA, BETA & GAMMA) ---> e" << endl;
	cout << "Euler principal axis and angle ---> p" << endl;
	cout << "Quaternion ---> q" << endl;
	cout << "Rotation vector ---> v" << endl;
	cin >> order;
	if (order == 'r')
	{
		MatrixInput(matrix);

		GetAxisAngleFromMatrix(matrix, eulerAxis, eulerAngle);
		PrintEulerAxisAngle(eulerAxis, eulerAngle);
		cout << endl;

		GetEulerAnglesFromMatrix(matrix, alpha, beta, gamma);
		PrintEulerAngles(alpha, beta, gamma);
		cout << endl;

		GetQuaternionFromAxisAngle(eulerAxis, eulerAngle, quaternion);
		PrintQuaternion(quaternion);
		cout << endl;

		GetVectorFromAxisAngle(eulerAxis, eulerAngle, vector);
		PrintVector(vector);
		cout << endl;
	}
	if (order == 'e')
	{
		EulerAnglesInput(alpha, beta, gamma);

		GetMatrixFromEulerAngles(alpha, beta, gamma, matrix);
		PrintMatrix(matrix);
		cout << endl;

		GetAxisAngleFromMatrix(matrix, eulerAxis, eulerAngle);
		PrintEulerAxisAngle(eulerAxis, eulerAngle);
		cout << endl;

		GetQuaternionFromAxisAngle(eulerAxis, eulerAngle, quaternion);
		PrintQuaternion(quaternion);
		cout << endl;

		GetVectorFromAxisAngle(eulerAxis, eulerAngle, vector);
		PrintVector(vector);
		
	}
	if (order == 'p')
	{
		AxisAngleInput(eulerAxis, eulerAngle);

		GetMatrixFromAxisAngle(eulerAxis, eulerAngle, matrix);
		PrintMatrix(matrix);
		cout << endl;

		GetEulerAnglesFromMatrix(matrix, alpha, beta, gamma);
		PrintEulerAngles(alpha, beta, gamma);
		cout << endl;

		GetQuaternionFromAxisAngle(eulerAxis, eulerAngle, quaternion);
		PrintQuaternion(quaternion);
		cout << endl;

		GetVectorFromAxisAngle(eulerAxis, eulerAngle, vector);
		PrintVector(vector);
	}
	if (order == 'q')
	{
		InputQuaternion(quaternion);

		GetAxisAngleFromQuaternion(quaternion, eulerAxis, eulerAngle);
		PrintEulerAxisAngle(eulerAxis, eulerAngle);
		cout << endl;

		GetMatrixFromAxisAngle(eulerAxis, eulerAngle, matrix);
		PrintMatrix(matrix);
		cout << endl;

		GetEulerAnglesFromMatrix(matrix, alpha, beta, gamma);
		PrintEulerAngles(alpha, beta, gamma);
		cout << endl;

		GetVectorFromAxisAngle(eulerAxis, eulerAngle, vector);
		PrintVector(vector);
	}
	if (order == 'v')
	{
		InputVector(vector);

		GetAxisAngleFromVector(vector, eulerAxis, eulerAngle);
		PrintEulerAxisAngle(eulerAxis, eulerAngle);
		cout << endl;

		GetMatrixFromAxisAngle(eulerAxis, eulerAngle, matrix);
		PrintMatrix(matrix);
		cout << endl;

		GetEulerAnglesFromMatrix(matrix, alpha, beta, gamma);
		PrintEulerAngles(alpha, beta, gamma);
		cout << endl;

		GetQuaternionFromAxisAngle(eulerAxis, eulerAngle, quaternion);
		PrintQuaternion(quaternion);
	}
	cout << "Imput any key to exit" << endl;
	char end;
	cin >> end;
	cout << "Exiting the program" << endl;
	return 0;
}