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

	double mutationRatio = 5.0;			// w promilach (najlepsze 0.5-1.0%)
	double crossoverRatio = 95.0;			// w procentach (najlepsze 60%, 80-95%)
	int popSize = 30;					// musi byæ parzysta (najlepsze 20-30, 50-100)
	int noOfCities;

public:
	tspGA();
	~tspGA();
	void popInit(std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, int popSize);
	int calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, int noOfCities, std::vector<std::vector<int>> &parentsPop, int memberPtr);
	int randInt(int l, int r);
	//double randFraction(void);
	int TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize, 
		double crossoverRatio, double mutationRatio);
	void tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize);
	std::vector<std::vector<int>> getAdjacancyMatrix(void);
	std::vector<std::vector<int>> getParentsPop(void);
	std::vector<std::vector<int>> getChildrenPop(void);
	std::vector<int> getPopMember(void);
	int getPopSize(void);
	int getNoOfCities(void);
	void start(void);
};