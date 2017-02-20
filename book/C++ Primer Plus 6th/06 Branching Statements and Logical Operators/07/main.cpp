#include <iostream>
#include <cctype>
using namespace std;

int main()
{

	cout << "Ente words(q to quit): " << endl;

	int vowel = 0;
	int consonant = 0;
	int other = 0;

	string word;	
	while (cin >> word && word != "q")
	{
		char& ch = word[0];
		if (isalpha(ch))
		{
			switch(ch)
			{
				case 'a':
				case 'o':
				case 'e':
				case 'i':
				case 'u':
				{
					++ vowel;
					break;
				}										
				default:
				{
					++consonant;	
				}
			}			
		}
		else
		{
			++other;
		}
	}
	
	cout << vowel << " words begining with vowels." << endl;
	cout << consonant << " words begining with consonants." << endl;
	cout << other << " words" << endl;
	
	return 0;
}
