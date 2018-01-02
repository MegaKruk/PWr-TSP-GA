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

	double mutationRatio;
	double crossoverRatio;
	int popSize;
	int noOfCities;

public:
	tspGA();
	~tspGA();
	int TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize,
		double crossoverRatio, double mutationRatio);
	void popInit(std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, int popSize);
	int calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, int noOfCities, std::vector<std::vector<int>> &parentsPop, int memberPtr);
	int randInt(int l, int r);
	int tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize);
	std::vector<std::vector<int>> getAdjacancyMatrix(void);
	std::vector<std::vector<int>> getParentsPop(void);
	std::vector<std::vector<int>> getChildrenPop(void);
	std::vector<int> getPopMember(void);
	int setPopSize(int popSize);
	double setMutationRatio(double mutationRatio);
	double setCrossoverRatio(double crossoverRatio);
	int getPopSize(void);
	int getNoOfCities(void);
	void start(void);
};