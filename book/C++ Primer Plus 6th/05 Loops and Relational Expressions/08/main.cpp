#include <iostream>
#include <cstring>
int main()
{
	using namespace std;
	
	cout << "Enter words (to stop, type the word done):" << endl;
	int count = 0;	

	char word[32];	
	cin >> word;
	while(strcmp(word, "done"))
	{
		count++;
		cin >> word;
	}
	
	cout << "You entered a total of " << count << " words." << endl;
}