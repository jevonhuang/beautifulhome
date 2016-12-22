#include <iostream>

void format_time(int hour, int min);
int main()
{
	std::cout << "Enter the number of hours: ";
	int hour = 0;
	std::cin >> hour;
	
	std::cout << "Enter the number of min: ";
	int min = 0;
	std::cin >> min;
	
	format_time(hour, min);
}

void format_time(int hour, int min)
{
	std::cout << "Time: ";
	if (hour < 10)
	{
		std::cout << "0" << hour;		
	}
	else
	{
		std::cout << hour;		
	}
	
	std::cout << ":";
	
	if (min < 10)
	{
		std::cout << "0" << min;		
	}
	else
	{
		std::cout << min;		
	}
	
	std::cout << std::endl;
}

