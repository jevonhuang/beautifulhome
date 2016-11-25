#include <iostream>
#include <cstring>

using namespace std;

const int LEN = 32;

int main()
{
	char firstname[LEN];
	char lastname[LEN];
	char totalname[LEN * 2];
	
	cout <<"Enter your first name: ";
	cin >> firstname;
	
	cout << "Enter your last name: ";
	cin >> lastname;
	
	strcpy(totalname, firstname);
	strcat(totalname, ", ");
	strcat(totalname, lastname);
	
	cout << "Here's the infomat in a single string: " << totalname << endl;
}