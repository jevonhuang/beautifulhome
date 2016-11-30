#include <iostream>
#include <string>

using namespace std;

const int name_max_length = 64;
struct Pizza
{
	char company[name_max_length];
	float diameter;
	int weight;
};

void GetPizzaInfo(Pizza& pizza);
void PutPizzaInfo(const Pizza& pizza);

int main()
{
	Pizza* pizza = new Pizza;
	GetPizzaInfo(*pizza);
	PutPizzaInfo(*pizza);
}

void GetPizzaInfo(Pizza& pizza)
{
	cout << "Enter Pizza Info:\n";
	cout << "company: ";
	cin.get(pizza.company, name_max_length);
	while(cin.get() != '\n');
	
	cout << "diameter: ";
	cin >> pizza.diameter;
	while(cin.get() != '\n');	
	
	cout << "weight: ";
	cin >> pizza.weight;
	while(cin.get() != '\n');	
}

void PutPizzaInfo(const Pizza& pizza)
{
	cout << "Your pizza Infp:\n";
	cout << "company: " << pizza.company << endl;
	cout << "diameter: " << pizza.diameter << endl;
	cout << "weight: " << pizza.weight << endl;
}