#pragma once
#include<stdlib.h>
#include<string>
#include<limits.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<vector>

class tspGA
{
private:
	std::vector<std::vector<int>> adjacancyMatrix;
	std::vector<std::vector<int>> parentsPop;
	std::vector<std::vector<int>> childrenPop;
	std::vector<int> popMember;
	int noOfCities;
	const static int popSize = 30;

public:
	tspGA();
	~tspGA();
	void popInit(std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize);
	int calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities);
	int randInt(int l, int r);
	double randFraction(void);
	int TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities);
	void tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize);
	std::vector<std::vector<int>> getAdjacancyMatrix(void);
	std::vector<std::vector<int>> getParentsPop(void);
	std::vector<std::vector<int>> getChildrenPop(void);
	std::vector<int> getPopMember(void);
	int getPopSize(void);
	int getNoOfCities(void);
	void start(void);
};