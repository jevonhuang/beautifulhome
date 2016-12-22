#include <iostream>

int main()
{
	std::cout << "Please enter two integer, min first." << std::endl;
	int min = 0, max = 0, sum = 0;
	std::cin >> min >> max;
	for (int i = min; i <= max; ++i)
	{
		sum += i;
	}
	
	std::cout << "The sum of the integer from " << min << " through " << max << " is " << sum << std::endl; 
}