#include <iostream>
#include "wine.h"

using namespace std;

int main()
{
	cout << "Enter name of wine: ";
	char lab[64];
	cin.getline(lab, 64);
	cout << "Enter number of years: ";
	int years;
	cin >> years;

	Wine holding(lab, years);
	holding.GetBottles();
	holding.Show();
	
	const int YRS = 3;
	int y[YRS] = {1993, 1995, 1998};
	int b[YRS] = {48, 60, 72};
	
	Wine more("Gushing Grape Red", YRS, y, b);
	more.Show();
	
	cout << "Total bottles for " << more.Label() << ": " << more.Sum() << endl;
	
	cout << "Bye\n";
	
	return 0;
}

