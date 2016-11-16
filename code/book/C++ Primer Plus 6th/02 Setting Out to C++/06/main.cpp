#include <iostream>

double lightyears2astronomical(double lightyears);
int main()
{
	using namespace std;
	
	cout << "Enter the number of lights years: ";
	double lightyears = 0.0;
	cin >> lightyears;
	cout << lightyears << " light years = " << lightyears2astronomical(lightyears) << " astronomical units.\n";
}

double lightyears2astronomical(double lightyears)
{
	return 63240 * lightyears;
}