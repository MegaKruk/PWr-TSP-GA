#pragma once
#include <stdlib.h>
#include <string>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>

class tspGA
{
private:
	std::vector<std::vector<int>> adjacancyMatrix;
	std::vector<std::vector<int>> parentsPop;
	std::vector<std::vector<int>> childrenPop;
	std::vector<int> popMember;

	double mutationRatio;
	double crossoverRatio;
	int popSize;
	int noOfCities;

public:
	tspGA();
	~tspGA();
	int TSP(std::vector<std::vector<int>> &, std::vector<int> &, int, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, int, double, double);
	int tspInit(std::vector<std::vector<int>> &, std::vector<int> &, int, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, int);
	int calculateCost(std::vector<std::vector<int>> &, int , std::vector<std::vector<int>> &, int);
	int randInt(int, int);
	void popInit(std::vector<int> &, int, std::vector<std::vector<int>> &, int, std::vector<std::vector<int>> &);
	void start(void);

	std::vector<std::vector<int>> getAdjacancyMatrix(void);
	std::vector<std::vector<int>> getParentsPop(void);
	std::vector<std::vector<int>> getChildrenPop(void);
	std::vector<int> getPopMember(void);
	int getPopSize(void);
	int getNoOfCities(void);

	double setMutationRatio(double);
	double setCrossoverRatio(double);
	int setPopSize(int);
};