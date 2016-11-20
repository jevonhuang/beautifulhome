#include <iostream>

const float gallon2liters = 3.875f;
const float kilometers2miles = 0.6214f;

float Us2Eu(float);

int main()
{
	std::cout << "Enter gasoline consumption figure in the European style: ";
	float us;
	std::cin >> us;
	
	std::cout << us << " mpg is about " <<  Us2Eu(us) << " l/100km.\n";
}

float Us2Eu(float us)
{
	return  gallon2liters * 100/ (us / kilometers2miles);
}