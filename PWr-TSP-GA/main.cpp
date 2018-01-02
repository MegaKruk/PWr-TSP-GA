/******************************/
/***TSP Simulated Annealing****/
/**Implemented by Filip Mazur**/
/******************************/

#include "tspGA.h"
#include <iostream>

int main()
{
	tspGA *testUnit = new tspGA();
	testUnit->start();
	std::cin.ignore(1);
	return 0;
}
