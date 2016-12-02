#include <iostream>

int main()
{
	int sum = 0;
	int num = 0;
	
	std::cout << "Please enter a number, and I will report the sum of them." << std::endl;
	do
	{
		std::cout << "num = ";
		std::cin >> num;
		sum += num;
		std::cout << "sum = " << sum << std::endl;
	}
	while(num != 0);
}