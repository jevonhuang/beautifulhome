#include <iostream>

using namespace std;

double tax(double income);
int main()
{
	double income = 0.0;	
	cout << "Please enter your income: ";
	cin >> income;
	while (cin and income > 0.0)
	{
		cout << "Your tax is : " << tax(income) << endl;
		cout << "Please enter your income: ";
		cin >> income;
	}
}

double tax(double income)
{
	
	if (income > 35000)
	{
		return 10000 * 0.10 + 20000 * 0.15 + (income - 35000) * 0.20;
	}
	else if (income > 15000)
	{
		return 10000 * 0.10 + (income - 15000) * 0.15;
	}
	else if (income > 5000)
	{
		return (income - 5000) * 0.10;
	}
	else
	{
		return 0.0;
	}
}