#include <iostream>
#include <array>

const int size = 10;

using namespace std;
int main()
{
	cout << "Enter " << size << " donation values." << endl;
	
	array<double, size> donamtions = {0.0};
	
	int index = 0;
	double total = 0.0;
	while (index < size && cin >> donamtions[index])
	{
		total += donamtions[index];
		++index;
	}
	
	if (index == 0)
	{
		return 0;
	}

	int count = 0;	
	double average = total / index;
	for (int i = 0; i < index; ++i)
	{
		if (donamtions[i] > average)
		{
			count++;
		}
	}
	
	cout << "The average of the numbers is " << average << ", " << count << " number larger than it." << endl;
}