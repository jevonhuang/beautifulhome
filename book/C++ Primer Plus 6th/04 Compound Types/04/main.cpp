#include <iostream>
#include <string>

using namespace std;

int main()
{
	string firstname;
	string lastname;
	string totalname;
	
	cout <<"Enter your first name: ";
	cin >> firstname;
	
	cout << "Enter your last name: ";
	cin >> lastname;
	
	totalname = firstname +  ", " + lastname;
	
	cout << "Here's the infomat in a single string: " << totalname << endl;
}