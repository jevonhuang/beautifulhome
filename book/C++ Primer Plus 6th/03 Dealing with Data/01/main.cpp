#include <iostream>

const int feet2inches_ratio = 12;
int main()
{
	std::cout << "Enter your height in inches:____\b\b\b\b";
	int inches = 0;
	std::cin >> inches;
	
	std::cout << "Your height is "; 
	std::cout << inches/feet2inches_ratio;
	std::cout << " and ";
	std::cout << inches%feet2inches_ratio;
	std::cout << std::endl;
}

