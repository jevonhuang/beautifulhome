#include <iostream>

const float feet2inches = 12.0f;
const float inches2meters = 0.0254f;
const float kilograms2pounds = 2.2f;

float bmi(float meters, float kilograms);

int main()
{
	using namespace std;
	
	float feet = 0.0f;
	float inches = 0.0f;
	float pounds = 0.0f;
	
	cout << "Enter your height in feet and inches;\n";
	cout << "feet ";
	cin >> feet;
	cout << "inches ";
	cin >> inches;
	
	cout << "Enter your weight in pouns;\n";
	cout << "pounds ";
	cin >> pounds;
	
	float meters = (feet * feet2inches + inches) * inches2meters;
	float kilograms = pounds / kilograms2pounds;
	
	cout << "Finally, you body mass index(BMI) is " << bmi(meters, kilograms) << endl;
}

float bmi(float meters, float kilograms)
{
	return kilograms / (meters * meters);
}