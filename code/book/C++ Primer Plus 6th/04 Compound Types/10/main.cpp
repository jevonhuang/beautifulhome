#include <iostream>
#include <array>

using namespace std;

const int max_dash_tries = 3;

int main()
{
	array<float, max_dash_tries> scores;

	cout << "Your dash times 1#: ";
	cin >> scores[0];
	cout << "Your dash times 2#: ";
	cin >> scores[1];
	cout << "Your dash times 3#: ";
	cin >> scores[2];
	
	cout << "Your average dash times: " << (scores[0] + scores[1] + scores[2]) / 3 << endl;
}
