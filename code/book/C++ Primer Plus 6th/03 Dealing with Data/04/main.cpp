#include <iostream>

const int m2s = 60;
const int h2m = 60;
const int d2h = 24;

int main()
{
	std::cout << "Enter the number of seconds: ";
	long total_seconds = 0;
	std::cin >> total_seconds;
	
	int day = total_seconds / (d2h * h2m * m2s);
	int hour = total_seconds % (d2h * h2m * m2s) / (h2m * m2s);
	int minutes = total_seconds % (h2m * m2s) / (m2s);
	int seconds = total_seconds % m2s;
	
	
	std::cout << total_seconds << " seconds = ";
	std::cout << day << " days, ";
	std::cout << hour << " hour, ";
	std::cout << minutes << " minutes, ";
	std::cout << seconds << " seconds.\n";
}