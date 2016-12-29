#include <iostream>

using namespace std;

struct Donor
{
	string name;
	double amount;
};

int main()
{
	cout << "Please Enter then number of contributors: ";
	int donor_number;
	cin >> donor_number;
	cin.get();
	
	Donor* donors = new Donor[donor_number];
	for (int i = 0; i < donor_number; ++i)
	{
		cout << "Donor# ";
		getline(cin, donors[i].name);
		cout << "Amount# ";
		cin >> donors[i].amount;
		cin.get();
	}
	
	int grand_patrons_number = 0;
	cout << "Grand Patrons:" << endl;
	for (int i = 0; i < donor_number; ++i)
	{
		if (donors[i].amount >= 10000)
		{
			cout << donors[i].name << " " << fixed << donors[i].amount << endl;
			grand_patrons_number += 1;
		}
	}
	if (grand_patrons_number == 0)
	{
		cout << "none" << endl;
	}
	
	int patrons_number = 0;
	cout << "Patrons:" << endl;
	for (int i = 0; i < donor_number; ++i)
	{
		if (donors[i].amount < 10000)
		{
			cout << donors[i].name << " " << fixed << donors[i].amount << endl;
			patrons_number += 1;
		}
	}
	if (patrons_number == 0)
	{
		cout << "none" << endl;
	}	 
	
	return 0;
}
