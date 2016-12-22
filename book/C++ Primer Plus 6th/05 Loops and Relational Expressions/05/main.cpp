#include <iostream>

const int size = 12;

const char* month[size] = 
{
	"January", 
	"February", 
	"March", 
	"April", 
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

int main()
{
	std::cout << "Enter the year of monthly sales." << std::endl;
	int sales[size] = {};
	for (int i = 0; i < size; ++i)
	{
		std::cout << month[i] << "# ";
		std::cin >> sales[i];
	}
	
	int total = 0;
	for (int i = 0; i < size; ++i)
	{
		total += sales[i];
	}
	
	std::cout << "The total sales for the year is " << total << std::endl;
}