#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name;
	string dessert;
	
	cout << "Enter your name:\n";	
	getline(cin, name); // reads through newline
	
	cout << "Enter your favorite dessert:\n";
	getline(cin, dessert); // reads through newline	
	
	cout << "I have some delicious " << dessert;	
	cout << " for you, " << name << ".\n";
	
	return 0;
}