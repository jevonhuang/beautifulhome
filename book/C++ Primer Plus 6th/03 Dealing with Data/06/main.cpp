#include <iostream>

int main()
{
	std::cout << "How many miles you have driven: ";
	float miles;
	std::cin >> miles;
	
	std::cout << "How many gallons of gasoline you have used: ";
	float gallons;
	std::cin >> gallons;
	
	std::cout << gallons / miles << " miles per gallon your car has gotten.\n";
	
}