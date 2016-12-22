#include <iostream>

using namespace std;

const int strsize = 32;
struct bop
{
	char fullname[strsize];
	char title[strsize];
	char bopname[strsize];
	int preference;
};

int main()
{
	bop members[5] = {{"1", "a", "10", 1}, {"2", "b", "20", 2}, {"3", "c", "30", 0}, {"4", "c", "40", 1}, {"5", "d", "50", 2}};
	cout << "Benevolent Order of Programmers Report" << endl;
	cout << "a. display by name          b. display by title" << endl;
	cout << "c. display by bopname       d. display by preference" << endl;
	cout << "q. quit" << endl;
	
	char ch;
	
	cout << "Enter your choice: ";
	cin >> ch;
	while (ch != 'q')
	{
		switch(ch)
		{
			case 'a':
			{
				for (int i = 0; i < 5; ++i)
				{
					cout << members[i].fullname << endl;
				}
				break;
			}
			case 'b':
			{
				for (int i = 0; i < 5; ++i)
				{
					cout << members[i].title << endl;
				}	
				break;
			}
			case 'c':
			{
				for (int i = 0; i < 5; ++i)
				{
					cout << members[i].bopname << endl;
				}	
				break;
			}
			case 'd':
			{
				for (int i = 0; i < 5; ++i)
				{
					switch(members[i].preference)
					{
						case 0:
						{
							cout << members[i].fullname << endl;
							break;
						}
						case 1:
						{
							cout << members[i].title << endl;
							break;
						}
						case 2:
						{
							cout << members[i].bopname << endl;
							break;
						}
					}		
				}				
			}
		}
		cout << "Enter your choice: ";
		cin >> ch;		
	}
		
}