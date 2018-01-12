/******************************/
/****TSP Genetic Algorithm*****/
/**Implemented by Filip Mazur**/
/******************************/

#include "tspGA.h"
#include <iostream>

int main()
{
	tspGA *testUnit = new tspGA();
	testUnit->start();
	delete(testUnit);
	std::cin.ignore(1);
	return 0;
}
