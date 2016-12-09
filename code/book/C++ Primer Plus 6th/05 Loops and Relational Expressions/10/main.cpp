#include <iostream>
#include <string>

int main()
{
	using namespace std;
	
	cout << "Enter number of rows: ";
	int row = 0;	
	cin >> row;
	
	for (int i = 0; i < row; ++i)
	{
		for (int j = row - 1; j >= 0; --j)
		{
			if (j > i)
			{
				cout << ".";
			}
			else
			{
				cout << "*";
			}
		}
		cout << endl;
	}
}