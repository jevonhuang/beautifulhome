#include <iostream>
#include <string>

using namespace std;

struct CandyBar
{
	string brand;
	double weight;
	int calories;
};

int main()
{
	CandyBar snacks[3] = {{"Mocha Munch V1", 2.3, 350},{"Mocha Munch V2", 2.0, 300}, {"Mocha Munch V3", 1.9, 200}};
	cout << "CandyBar:\n";	
	for (int i = 0; i < 3; ++i)
	{
		cout << "brand: " << snacks[i].brand << endl;
		cout << "weight: " << snacks[i].weight << endl;	
		cout << "calories: " << snacks[i].calories << endl;
	}
}