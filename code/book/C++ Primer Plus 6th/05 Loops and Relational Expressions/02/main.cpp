#include <iostream>
#include <array>

const int max_size = 100;

int main()
{
	std::array<double, max_size> factorials;
	factorials[1] = factorials[0] = 1.0;
	for (int i = 2; i < max_size; ++i)
	{
		factorials[i] = i *  factorials[i - 1]; 
	}
	
	for (int i = 0; i < max_size; ++i)
	{
		std::cout << i << "! = " << factorials[i] << std::endl;
	}	
}