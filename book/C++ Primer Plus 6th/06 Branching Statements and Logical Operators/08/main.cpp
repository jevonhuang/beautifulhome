#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char* argv[])
{
	ifstream fin;
	fin.open("test.txt");
	char ch;
	while (fin.get(ch))
	{
		cout << ch;
	}
	fin.close();
	
	cin.get();
	return 0;
}
