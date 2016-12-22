#include <iostream>
#include <string>
int main()
{
	using namespace std;
	
	cout << "Enter words (to stop, type the word done):" << endl;
	int count = 0;	

	string word;
	cin >> word;
	while(word != "done")
	{
		count++;
		cin >> word;
	}
	
	cout << "You entered a total of " << count << " words." << endl;
}