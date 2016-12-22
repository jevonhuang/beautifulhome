#include <iostream>

int main()
{
	std::cout << "Enter the world's population: ";
	long long all_population;
	std::cin >> all_population;
	
	std::cout << "Enter the usa's population: ";
	long long usa_population;
	std::cin >> usa_population;

	//int / int * double 会先进行整形除法，然后再double乘法。这样会发生截断。
	std::cout << "The population of the usa is " << usa_population / (all_population * 0.01) << "% of the world population.\n";
}
