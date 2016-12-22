#include <iostream>
#include <string>

using namespace std;

struct Car
{
	string make;
	int year;
};

int main()
{
	cout << "How many cars do you wish to catalog? ";
	int nums = 0;
	cin >> nums;
	cin.get();
	
	Car* cars = new Car[nums];
	
	for (int i = 0; i < nums; ++i)
	{
		cout << "Car #" << (i + 1) << ":" << endl;
		cout << "Please enter the make: ";
		getline(cin, cars[i].make);
		cout << "Please enter the year made: ";
		cin >> cars[i].year;
		cin.get();
	}
	
	cout << "Here is your collection:" << endl;
	for (int i = 0; i < nums; ++i)
	{
		cout << cars[i].year << " " << cars[i].make << endl;
	}
	
	delete [] cars;
}