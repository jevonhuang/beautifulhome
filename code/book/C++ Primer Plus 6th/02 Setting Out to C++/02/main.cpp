#include <iostream>
int main()
{
	std::cout << "please enter a distance in furlongs: ";
	float distance = 12.0f;
	std::cin >> distance; //假如输入的格式出错，会帮你做初始化？？？ 
	std::cout << distance << " furlongs is " << distance * 220 << " yards." << std::endl;
}