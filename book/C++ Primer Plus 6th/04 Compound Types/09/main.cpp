#include <iostream>
#include <string>

using namespace std;

struct CandyBar
{
	string brand;
	double weight;
	int calories;
};

void SetCandyBar(CandyBar& candy, const string& brand, double weight, int calories);

int main()
{
	CandyBar* snacks = new CandyBar[3];
	SetCandyBar(snacks[0], "Mocha Munch V1", 2.3, 350);
	SetCandyBar(snacks[1], "Mocha Munch V2", 2.0, 300);
	SetCandyBar(snacks[2], "Mocha Munch V3", 1.9, 200);

	cout << "CandyBar:\n";	
	for (int i = 0; i < 3; ++i)
	{
		cout << "brand: " << snacks[i].brand << endl;
		cout << "weight: " << snacks[i].weight << endl;	
		cout << "calories: " << snacks[i].calories << endl;
	}
	delete [] snacks;
}

void SetCandyBar(CandyBar& candy, const string& brand, double weight, int calories)
{
	candy.brand = brand;
	candy.weight = weight;
	candy.calories = calories;
}