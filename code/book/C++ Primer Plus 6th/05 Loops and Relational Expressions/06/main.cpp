#include <iostream>

const int size = 12;
const int year = 3;

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
	int sales[year][size] = {};
	for (int i = 0; i < year; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cout << "year#" << (i + 1) << "#" << month[j] << "# ";
			std::cin >> sales[i][j];
		}	
	}
	
	int total_of_all_year = 0;
	for (int i = 0; i < year; ++i)
	{
		int total_of_per_year = 0;
		for (int j = 0; j < size; ++j)
		{
			total_of_all_year += sales[i][j];
			total_of_per_year += sales[i][j];
		}	
		std::cout << "The total sales for the year " << i << " is " << total_of_per_year << std::endl;
	}
		
	std::cout << "The total sales for all year is " << total_of_all_year << std::endl;
}