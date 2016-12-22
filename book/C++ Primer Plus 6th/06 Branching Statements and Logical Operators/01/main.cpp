#include <iostream>
#include <cctype>

using namespace std;

int main()
{
	cout << "Enter text for analyssis, and type @ to terminate input." << endl;
	
	char ch;
	while ((ch = cin.get()) != '@')
	{
		if (!isdigit(ch))
		{
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					ch = tolower(ch);
					cout << ch;
				}
				else
				{
					ch = toupper(ch);
					cout << ch;
				}
			}
			else
			{
				cout << ch;
			}
		}
	}

}