#ifndef WINE_H_
#define WINE_H_

#include <iostream>
#include <string>
#include <valarray>
#include "pair.h"

class Wine
{
typedef std::valarray<int> ArrayInt;
typedef Pair<ArrayInt, ArrayInt> PairArray;

public:
	Wine() {}
	Wine(const char* l, int y, const int yr[], const int bot[]) : lable(l), years(y), bottles(ArrayInt(y), ArrayInt(y))
	{
		for (int i = 0; i < y; i++)
		{
			bottles.first()[i] = yr[i];
			bottles.second()[i] = bot[i];
		}
	}
	
	
	Wine(const char* l, int y) : lable(l), years(y), bottles(ArrayInt(y), ArrayInt(y))
	{
	}
	
public:
	void GetBottles()
	{
		std::cout << "Enter " << lable << " date for " << years << " years:" << std::endl;
		for (int i = 0; i < years; i++)
		{
			std::cout << "Enter year: ";
			std::cin >> bottles.first()[i];
			
			std::cout << "Enter bottles for that year: ";
			std::cin >> bottles.second()[i];
		}
	}	
	
	const std::string& Label()
	{
		return lable;
	}	
	
	int Sum()
	{
		return bottles.second().sum();
	}
	
	void Show()
	{
		std::cout << "Wine: " << lable << std::endl;
		for (int i = 0; i < years; i++)
		{
			std::cout << "\t" << bottles.first()[i] << "\t" << bottles.second()[i] << std::endl;
		}
	}	
private:
	std::string lable;

	int years;	
	PairArray bottles;
};

#endif