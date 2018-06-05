#ifndef WINE_H_
#define WINE_H_

#include <string>
#include <valarray>
#include "pair.h"

class Wine
{
typedef std::valarray<int> ArrayInt;
typedef Pair<ArrayInt, ArrayInt> PairArray;

public:
	Wine() {}
	Wine(const char* l, int y, const int yr[], const int bot[]);
	Wine(const char* l, int y);
	
public:
	void GetBottles();
	const std::string& Label();
	int sum();
private:
	std::string lable;

	int years;	
	PairArray bottles;
};

#endif