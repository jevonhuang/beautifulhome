#include <iostream>

const int len = 32;

int main()
{
	char first_name[len];
	std::cout << "What is your first name? ";
	std::cin.get(first_name, len);
	while(std::cin.get() != '\n')
	{		
	}
	
	char last_name[len];
	std::cout << "What is your last name? ";
	std::cin.get(last_name, len);
	while(std::cin.get() != '\n')
	{		
	}
	
	char grade;
	std::cout << "What letter grade do you deserve? ";
	std::cin >> grade;
	
	int age;
	std::cout << "What is your age? ";
	std::cin >> age;
	
	std::cout << "Name: " << last_name << ", " << first_name << std::endl;
	std::cout << "Grade: " << char(grade + 1) << std::endl;
	std::cout << "Age: " << age << std::endl;
}