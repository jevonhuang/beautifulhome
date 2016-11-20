#include <iostream>

const int min2sec = 60;
const int deg2min = 60;

float degree(float degrees, float minutes, float seconds);

int main()
{
	using namespace std;
	
	cout << "Enter a latitude in degrees, minutes, and seconds:\n";
	cout << "First, enter the degrees: ";
	float degrees;
	cin >> degrees;

	cout << "Next, enter the minutes of arc: ";
	float minutes;
	cin >> minutes;
	
	cout << "Finally, enter the seconds of ard: ";
	float seconds;
	cin >> seconds;
	
	cout << degrees << " degrees, ";
	cout << minutes << " minutes, ";
	cout << seconds << " seconds = ";
	cout << degree(degrees, minutes, seconds) << " degrees.\n"; 
}

float degree(float degrees, float minutes, float seconds)
{
	return degrees + seconds / min2sec / deg2min + minutes / deg2min;
}
