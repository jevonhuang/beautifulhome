#include <iostream>

const float daphne_interest = 0.1;
const float cleo_interest = 0.05;

int main()
{
	int years = 0;
	double daphne = 100.0;
	double cleo = 100.0;
	while (cleo <= daphne)
	{
		years++;
		
		daphne += 100.0 * daphne_interest;
		cleo += cleo * cleo_interest;
	}
	
	std::cout << "daphne = " << daphne << ", cleo = " << cleo << ", take " << years << std::endl;
}