#include "wine.h"

Wine::Wine(const char* l, int y, const int yr[], const int bot[])
:
lable(l),
years(y),
bottles(ArrayInt(y), ArrayInt(y))
{
	for (int i = 0; i < y; i++)
	{
		bottles.first[i] = yr[i];
		bottles.second[i] = bot[i];
	}
}

Wine::Wine(const char* l, int y)
:
lable(l),
years(y),
bottles(ArrayInt(y), ArrayInt(y))
{

}

void Wine::GetBottles()
{
	
}

const std::string& Wine::Label()
{
	return "";
}

int Wine::sum()
{
	return 0;
}

