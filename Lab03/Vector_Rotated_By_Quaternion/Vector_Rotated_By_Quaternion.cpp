#include <iostream>
using namespace std;

float quaternion[4] = { 0 };
float conjugateQuaternion[4] = { 0 };
float vector[3] = { 0 };
float pureQuaternion[4] = { 0 };
float intermediateResultQuaternion[4] = { 0 };
float resultQuaternion[4] = { 0 };

void HamiltonProduct(float* q, float* p, float* result);
int main()
{
	cout << "This program will rotate a vector using the quaternion product" << endl;
	cout << "Introduce the components of the vector" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout<<"Introduce the term number "<<i<<endl;
		cin >> vector[i];
	}
	cout << "Introduce the components of the quaternion" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "Introduce the term number " << i << endl;
		cin >> quaternion[i];
	}
	cout << "Creating the pure quaternion from the vector..." << endl;
	pureQuaternion[0] = 0;
	for (int i = 0; i < 3; i++) pureQuaternion[i + 1] = vector[i];

	cout << "Creating the conjugate from the quaternion..." << endl;
	conjugateQuaternion[0] = quaternion[0];
	for (int i = 1; i < 4; i++) conjugateQuaternion[i] = -quaternion[i];

	HamiltonProduct(quaternion, pureQuaternion, intermediateResultQuaternion);
	cout << "First operation result: " << endl;
	for (int i = 0; i < 4; i++) cout << intermediateResultQuaternion[i] << endl;


	HamiltonProduct(intermediateResultQuaternion, conjugateQuaternion, resultQuaternion);
	cout << "Final quaternion result: " << endl;
	for (int i = 0; i < 4; i++) cout << resultQuaternion[i]<<endl;

	for (int i = 0; i < 3; i++) vector[i] = resultQuaternion[i + 1];

	cout << "The vector after the rotation is: " << endl;
	for (int i = 0; i < 3; i++) cout << vector[i] << endl;
	return 0;
}
void HamiltonProduct(float* q, float* p, float* result)
{
	
	result[0] = q[0] * p[0] - q[1] * p[1] - q[2] * p[2] - q[3] * p[3];
	result[1] = q[0] * p[1] + q[1] * p[0] + q[2] * p[3] - q[3] * p[2];
	result[2] = q[0] * p[2] - q[1] * p[3] + q[2] * p[0] + q[3] * p[1];
	result[3] = q[0] * p[3] + q[1] * p[2] - q[2] * p[1] + q[3] * p[0];
}