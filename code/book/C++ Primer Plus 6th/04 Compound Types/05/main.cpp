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
	CandyBar snack = {"Mocha Munch", 2.3, 350};
	cout << "CandyBar:\n";
	cout << "brand: " << snack.brand << endl;
	cout << "weight: " << snack.weight << endl;	
	cout << "calories: " << snack.calories << endl;
}