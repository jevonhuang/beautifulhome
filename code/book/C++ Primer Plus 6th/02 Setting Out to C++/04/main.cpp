#include <iostream>

int main()
{
	std::cout << "please enter you age: ";
	int age;
	std::cin >> age;	
	std::cout << "your age in months is " << age * 12 << std::endl;	
}