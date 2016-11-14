#include <iostream>

float CelsiusToFahrenhei(float celsius);

int main()
{
	std::cout << "Please enter a Celsius value: ";
	float celsius = 0.0f;
	std::cin >> celsius;
	std::cout << celsius << " degrees Celsius is " << CelsiusToFahrenhei(celsius) << " degrees Fahrenheit.\n";
}

float CelsiusToFahrenhei(float celsius)
{
	return 1.8f * celsius + 32.0f;
}