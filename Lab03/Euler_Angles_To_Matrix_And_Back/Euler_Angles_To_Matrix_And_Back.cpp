#include <iostream>
#include <math.h>
using namespace std;

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

float alpha;
float beta;
float gamma;

float test;
float rotationMatrix[3][3] = { 0 };
float alphaResult;
float betaResult;
float gammaResult;

void GetRotationFromEulerAngles(float alpha, float beta, float gamma, float result[][3]);
void GetEulerAnglesfromRotation(float matrix[][3], float& alpha, float& beta, float& gamma);


int main()
{
	cout << "This program implements a function to pass from a set of Euler angles to it's rotation matrix" << endl;
	cout << "The second part of this program implements a function that does the inverse process, now using the rotation matrix obtained before" << endl;

	cout << "Introduce the ALPHA (roll) angle:" << endl;
	cin >> alpha;
	alpha *= DEGTORAD;
	cout << "Introduce the BETA (pitch) angle:" << endl;
	cin >> beta;
	beta *= DEGTORAD;
	cout << "Introduce the GAMMA (yaw) angle:" << endl;
	cin >> gamma;
	gamma *= DEGTORAD;
	cout << endl << "Computing the rotation matrix..." << endl<< endl;

	GetRotationFromEulerAngles(alpha, beta, gamma, rotationMatrix);
	cout << "This is the rotation matrix obtained: " << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout <<" " << rotationMatrix[i][j];
		}
		cout << endl;
	}

	cout << "Obtaining the euler angles from the rotation matrix..." << endl;
	GetEulerAnglesfromRotation(rotationMatrix, alphaResult, betaResult, gammaResult);
	cout << "ALPHA: " << alphaResult << endl;
	cout << "BETA: " << betaResult << endl;
	cout << "GAMMA: " << gammaResult << endl;
	cout << "Test: " << test << endl;
	test = sin(test);
	cout << "Sin: " << test << endl;
	test = asin(test);
	cout << "Test: "<<test << endl;
	return 0;
}
void GetRotationFromEulerAngles(float alpha, float beta, float gamma, float result[][3])
{
	result[0][0] = cos(gamma) * cos(beta);
	result[0][1] = cos(gamma) * sin(beta) * sin(alpha) - sin(gamma) * cos(alpha);
	result[0][2] = cos(gamma) * sin(beta) * cos(alpha) + sin(gamma) * sin(alpha);

	result[1][0] = sin(gamma) * cos(beta);
	result[1][1] = sin(gamma) * sin(beta) * sin(alpha) + cos(gamma) * cos(alpha);
	result[1][2] = sin(gamma) * sin(beta) * cos(alpha) - cos(gamma) * sin(alpha);

	result[2][0] = -sin(beta);
	result[2][1] = cos(beta) * sin(alpha);
	result[2][2] = cos(beta) * cos(alpha);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (result[i][j] > -0.01f && result[i][j] < 0.01f) result[i][j] = 0.0f;
		}
	}
}
void GetEulerAnglesfromRotation(float matrix[][3], float &alpha, float &beta, float &gamma)
{
	beta = RADTODEG*(-asin(matrix[2][0]));
	gamma = RADTODEG* atan2f(matrix[0][0] / cos(beta), matrix[1][0] / cos(beta));
	alpha = RADTODEG * atan2f(matrix[2][1] / cos(beta), matrix[2][2] / cos(beta));
	if (alpha < 0) alpha = alpha + 180;
	if (gamma < 0) gamma = gamma + 180;

}