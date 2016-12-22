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
		for (int j = 0; j < (row - 1) - i; ++j)
		{
			cout << ".";
		}
		
		for (int j = (row - 1) - i; j < row; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}
}