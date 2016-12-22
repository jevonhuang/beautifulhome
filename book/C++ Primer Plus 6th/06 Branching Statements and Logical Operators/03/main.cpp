#include <iostream>

using namespace std;
int main()
{
	cout << "Please enter one of the following choices:\n";
	cout << "c) carnivore              p)pianist\n";
	cout << "t) tree                   g)game\n";
	
	char ch;	
	cout << "Please enter a c, p, t, or g: ";
	while (cin >> ch)
	{
		switch(ch)
		{
			case 'c':
			{
				cout << "A lion is carnivore.\n";
				return 0;				
			}
			case 'p':
			{
				cout << "Lanlan is pianist.\n";
				return 0;
			}
			case 't':
			{
				cout << "A maple is a tree.\n";
				return 0;
			}
			case 'g':
			{
				cout << "A wow is a game.\n";
				return 0;
			}
			default:
			{
				cout << "Please enter a c, p, t, or g: ";
			}
		}
	}	
}