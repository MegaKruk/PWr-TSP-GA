#include "Stopwatch.h"
#include "tspGA.h"

void tspGA::popInit(std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, int popSize)
{
	parentsPop.clear();
	parentsPop.resize(0);
	parentsPop.resize(popSize);
	for (int i = 0; i < popSize; ++i)
		parentsPop[i].resize(noOfCities + 1);

	popMember.clear();
	popMember.resize(0);
	popMember.resize(noOfCities + 1);

	for (int i = 0; i < noOfCities; i++)
	{
		popMember[i] = i;
		if (i == noOfCities - 1)
			popMember[i + 1] = popMember[0];
	}

	for (int j = 0; j < popSize; j++)
	{
		for (int h = 0; h < 1024 * noOfCities; h++)
		{
			int x = randInt(1, noOfCities - 1);
			int y = randInt(1, noOfCities - 1);
			std::swap(popMember[x], popMember[y]);
		}
		parentsPop[j] = popMember;
	}
}

int tspGA::calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, int noOfCities, std::vector<std::vector<int>> &parentsPop, int memberPtr)
{
	int tmpCost = 0;
	for (int i = 0; i < noOfCities; i++)
	{
		//std::cout << endl << seq[i] << endl;
		int a = parentsPop[memberPtr][i];
		//std::cout << endl << "a= "<< a;
		int b = parentsPop[memberPtr][i + 1];
		//std::cout << endl << "b= " << b;
		tmpCost += adjacancyMatrix[a][b % (noOfCities)];

	}
	return tmpCost;
}

int tspGA::randInt(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

// g�owna funkcja programu
int tspGA::TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop,
	int popSize, double crossoverRatio, double mutationRatio)
{
	srand(time(0));
	// best = null
	int bestCost = NULL;
	std::vector<int> bestPath;
	bestPath.clear();
	bestPath.resize(noOfCities + 1);
	int iterations = 0;
	do
	{
		//for observing populacy
		/*for (int k = 0; k < parentsPop.size(); k++)
		{
			for (int l = 0; l < parentsPop[k].size(); l++)
			{
				std::cout << parentsPop[k][l] << "\t";
			}
			std::cout << endl;
		}*/

		// Assess fitness of every P(i)
		for (int i = 0; i < popSize; i++)
		{
			int currCost = calculateCost(adjacancyMatrix, noOfCities, parentsPop, i);
			//std::cout << currCost << "\t";
			if (bestCost == NULL || currCost < bestCost)
			{
				bestCost = currCost;
				cout << endl << bestCost << endl;
				for (int j = 0; j < noOfCities + 1; j++)
					bestPath[j] = parentsPop[i][j];
			}
		}
		childrenPop.clear();
		childrenPop.resize(0);

		for (int k = 0; k < popSize / 2; k++)
		{
			/*
			// select 2 random parents
			std::vector<int> parentA;
			parentA.resize(noOfCities + 1);
			int randA = randInt(0, popSize - 1);
			//std::cout << " A" << randA;
			for (int i = 0; i < noOfCities + 1; i++)
			{
				parentA[i] = parentsPop[randA][i];
			}

			std::vector<int> parentB;
			parentB.resize(noOfCities + 1);
			int randB = randInt(0, popSize - 1);
			while (randA == randB)
				randB = randInt(0, popSize - 1);
			for (int i = 0; i < noOfCities + 1; i++)
				parentB[i] = parentsPop[randB][i];

			// breeding with chance to cross and to mutate
			std::vector<int> childA;
			childA.resize(noOfCities + 1);
			std::vector<int> childB;
			childB.resize(noOfCities + 1);
			//just breeding. this happens always
			for (int i = 0; i < noOfCities + 1; i++)
				childA[i] = parentA[i];
			for (int i = 0; i < noOfCities + 1; i++)
				childB[i] = parentB[i];

			int genesToCross = randInt(3, noOfCities - 2);
			double diceroll = randInt(1, 10000);
			diceroll = diceroll / 10000;

			// crossover
			if (diceroll < crossoverRatio / 100)
			{
				for (int i = 0; i < genesToCross; i++)
				{
					int geneAPos;
					int geneBPos;
					int randGene = randInt(1, noOfCities - 1);
					for (int j = 1; j < noOfCities; j++)
					{
						if (childA[j] == randGene)
							geneAPos = j;
						if (childB[j] == randGene)
							geneBPos = j;
					}
					//cout << " a" << geneAPos;
					for (int j = 1; j < noOfCities; j++)
					{
						if (j == geneAPos)
							childA.erase(childA.begin() + geneAPos);
						if (j == geneBPos)
							childB.erase(childB.begin() + geneBPos);
					}

					for (int j = 1; j < noOfCities; j++)
					{
						if (j == geneBPos)
							childA.insert(childA.begin() + geneBPos, randGene);
						if (j == geneAPos)
							childB.insert(childB.begin() + geneAPos, randGene);
					}
				}
			}

			// mutation
			double diceroll2 = randInt(1, 10000);
			diceroll2 = diceroll / 10000;
			if (diceroll2 < (mutationRatio / 1000.0))
			{
				int x = randInt(1, noOfCities - 1);
				int y = randInt(1, noOfCities - 1);
				std::swap(childA[x], childA[y]);
				std::swap(childB[x], childB[y]);
			}

			// Q <- Qa, Qb
			childrenPop.push_back(childA);
			childrenPop.push_back(childB);
			*/
			/*if (childrenPop.size() == popSize)
			{
				parentsPop.clear();
				parentsPop.resize(0);
				parentsPop.resize(popSize);
				for (int v = 0; v < popSize; ++v)
					parentsPop[v].resize(noOfCities + 1);

				for (int i = 0; i < popSize; i++)
				{
					for (int j = 0; j < noOfCities + 1; j++)
					{
						parentsPop[i][j] = childrenPop[i][j];
					}
				}
			}*/

			// select 2 random parents
			std::vector<int> parentA;
			parentA.resize(noOfCities + 1);
			int randA = randInt(0, popSize - 1);
			for (int i = 0; i < noOfCities + 1; i++)
				parentA[i] = parentsPop[randA][i];

			std::vector<int> parentB;
			parentB.resize(noOfCities + 1);
			int randB = randInt(0, popSize - 1);
			while (randA == randB)
				randB = randInt(0, popSize - 1);
			for (int i = 0; i < noOfCities + 1; i++)
				parentB[i] = parentsPop[randB][i];

			// choose random place to cut parent
			int randCut = randInt(3, noOfCities - 2);

			std::vector<int> firstHalfA;
			firstHalfA.resize(noOfCities + 1);
			//std::vector<int> secondHalfA;
			//secondHalfA.resize(noOfCities + 1);
			for (int i = 0; i < randCut; i++)
				firstHalfA[i] = parentA[i];
			//for (int i = randCut; i < noOfCities + 1; i++)
			//	secondHalfA[i] = parentA[i];

			std::vector<int> firstHalfB;
			firstHalfB.resize(noOfCities + 1);
			//std::vector<int> secondHalfB;
			//secondHalfB.resize(noOfCities + 1);
			for (int i = 0; i < randCut; i++)
				firstHalfB[i] = parentB[i];
			//for (int i = randCut; i < noOfCities + 1; i++)
			//	secondHalfB[i] = parentB[i];

			// breed with chance to cross and to mutate
			std::vector<int> childA;
			childA.resize(noOfCities + 1);
			std::vector<int> childB;
			childB.resize(noOfCities + 1);

			double diceroll = randInt(1, 10000);
			diceroll = diceroll / 10000;
			// crossover
			if (diceroll < crossoverRatio / 100)
			{
				// Copy elements from first parent up to cut point
				for (int i = 0; i < randCut; i++)
					childA[i] = firstHalfA[i];

				// Add remaining elements from second parent to child while preserving order
				int remaining = noOfCities - randCut;	
				int count = 0;
				for (int i = 0; i < noOfCities; i++)	
				{
					bool found = false;
					for (int j = 0; j <= randCut; j++) 
					{
						// If the city is in the child, exit this loop
						if (childA[j] == parentB[i])
						{
							found = true;
							break;
						}
					}

					// If the city was not found in the child, add it to the child
					if (!found)
					{
						childA[randCut + count] = parentB[i];
						count++;
					}

					// Stop once all of the cities have been added
					if (count == remaining)
						break;
				}
				/******************************************************************************************/

				// Copy elements from second parent up to cut point
				for (int i = 0; i < randCut; i++)
					childB[i] = firstHalfB[i];

				// Add remaining elements from first parent to child while preserving order
				int remainingB = noOfCities - randCut;
				int countB = 0;
				for (int i = 0; i < noOfCities; i++)
				{
					bool foundB = false;
					for (int j = 0; j <= randCut; j++)
					{
						// If the city is in the child, exit this loop
						if (childB[j] == parentA[i])
						{
							foundB = true;
							break;
						}
					}

					// If the city was not found in the child, add it to the child
					if (!foundB)
					{
						
						childB[randCut + countB] = parentA[i];
						countB++;
					}

					// Stop once all of the cities have been added
					if (countB == remainingB)
						break;
				}
			}
			else
			{
				for (int i = 0; i < noOfCities + 1; i++)
					childA[i] = parentA[i];
				for (int i = 0; i < noOfCities + 1; i++)
					childB[i] = parentB[i];
			}

			// mutation
			double diceroll2 = randInt(1, 10000);
			diceroll2 = diceroll2 / 10000;
			if (diceroll2 < (mutationRatio / 1000.0))
			{
					int x = randInt(1, noOfCities - 1);
					int y = randInt(1, noOfCities - 1);
					std::swap(childA[x], childA[y]);

					int z = randInt(1, noOfCities - 1);
					int t = randInt(1, noOfCities - 1);
					std::swap(childB[z], childB[t]);
			}

			/*cout << endl << "a ";
			for (int i = 0; i < noOfCities + 1; i++)
			{
			cout << childA[i] << " ";
			}
			cout << endl << "b ";
			for (int i = 0; i < noOfCities + 1; i++)
			{
			cout << childB[i] << " ";
			}*/

			// Q <- Qa, Qb
			childrenPop.push_back(childA);
			childrenPop.push_back(childB);

			parentA.clear();
			parentA.resize(0);
			parentB.clear();
			parentB.resize(0);
			firstHalfA.clear();
			firstHalfA.resize(0);
			//secondHalfA.clear();
			//secondHalfA.resize(0);
			firstHalfB.clear();
			firstHalfB.resize(0);
			//secondHalfB.clear();
			//secondHalfB.resize(0);
			childA.clear();
			childA.resize(0);
			childB.clear();
			childB.resize(0);

		}

		// P <- Q
		parentsPop.clear();
		parentsPop.resize(0);
		parentsPop.resize(popSize);
		for (int v = 0; v < popSize; ++v)
			parentsPop[v].resize(noOfCities + 1);

		for (int i = 0; i < popSize; i++)
		{
			for (int j = 0; j < noOfCities + 1; j++)
			{
				parentsPop[i][j] = childrenPop[i][j];
			}
		}
		iterations++;
	} while (iterations < cbrt(noOfCities) * 100000/* || bestCost != 10*/);

	//std::cout << endl << endl << "Iterations:\t" << iterations << endl;
	std::cout << endl << endl << "Cost:\t" << bestCost << endl;
	std::cout << "Path:\t";
	for (int i = 0; i < noOfCities + 1; i++)
	{
		cout << bestPath[i] << "\t";
	}
	bestPath.clear();
	bestPath.resize(0);
	childrenPop.clear();
	childrenPop.resize(0);
	parentsPop.clear();
	parentsPop.resize(0);
	return bestCost;
}

// load data, prepare TSP function
int tspGA::tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize)
{
	mutationRatio = 10;			// w promilach (najlepsze 0.5-1.0%)
	crossoverRatio = 90;		// w procentach (najlepsze 60%, 80-95%)
	popSize = 30;				// musi by� parzysta (najlepsze 20-30, 50-100)

		// main menu
	while (1)
	{
		int option;
		std::cout << "\n1 - Test algorithm\n2 - Make measurements\n3 - Change parametres\n4 - Load data\n0 - Quit\n";
		std::cin >> option;
		std::cout << endl;

		switch (option)
		{
		case 1:
		{
			Stopwatch *timer = new Stopwatch();
			timer->point1 = chrono::high_resolution_clock::now();
			popInit(popMember, noOfCities, parentsPop, popSize);
			TSP(adjacancyMatrix, popMember, noOfCities, parentsPop, childrenPop, popSize, crossoverRatio, mutationRatio);
			std::cout << endl << timer->countTimeDiff() << " nanosecs to complete this action\n";
			popMember.clear();
			break;

		}
		case 2:
		{
			ofstream myOutput("output.txt");
			int result = 0;
			Stopwatch *timer = new Stopwatch();

			for (int i = 0; i < 51; i++)
			{
				timer->point1 = chrono::high_resolution_clock::now();
				popInit(popMember, noOfCities, parentsPop, popSize);
				result = TSP(adjacancyMatrix, popMember, noOfCities, parentsPop, childrenPop, popSize, crossoverRatio, mutationRatio);
				myOutput << timer->countTimeDiff() << "\t" << result << endl;
				popMember.clear();
				std::cout << endl << (i + 1) * 100 / 51 << " % done";
			}
			adjacancyMatrix.clear();
			break;
		}
		case 3:
		{
			std::cout << "Parametres are now set to: " << "\nPopulation size: " << popSize << "\nCrossover rate: " << crossoverRatio << " %" << "\nMutation rate: " << mutationRatio << " %." << endl;
			popSize = setPopSize(popSize);
			crossoverRatio = setCrossoverRatio(crossoverRatio);
			mutationRatio = setMutationRatio(mutationRatio);
			std::cout << "\nParametres are now set to: " << "\nPopulation size: " << popSize << "\nCrossover rate: " << crossoverRatio << " %" << "\nMutation rate: " << mutationRatio << " %." << endl;
			break;
		}
		case 4:
		{
			string filename, filePointer;
			ifstream myFile;
			std::cout << "Enter filename. Must be in 'data' folder: \n";
			std::cin >> filename;
			myFile.open("data/" + filename);
			if (myFile.is_open())
			{
				do myFile >> filePointer;
				while (filePointer != "DIMENSION:");

				myFile >> filePointer;
				noOfCities = atoi(filePointer.c_str());

				adjacancyMatrix.clear();
				adjacancyMatrix.resize(noOfCities);
				for (int i = 0; i < noOfCities; ++i)
					adjacancyMatrix[i].resize(noOfCities);

				popMember.clear();
				popMember.resize(noOfCities + 1);

				do myFile >> filePointer;
				while (filePointer != "EDGE_WEIGHT_TYPE:");
				myFile >> filePointer;


				if (filePointer == "EXPLICIT")
				{
					do myFile >> filePointer;
					while (filePointer != "EDGE_WEIGHT_FORMAT:");
					myFile >> filePointer;

					if (filePointer == "FULL_MATRIX")
					{
						do myFile >> filePointer;
						while (filePointer != "EDGE_WEIGHT_SECTION");

						for (int i = 0; i < noOfCities; i++)
						{
							std::cout << "\n";
							for (int j = 0; j < noOfCities; j++)
							{
								myFile >> adjacancyMatrix[i][j];
								std::cout << adjacancyMatrix[i][j] << "\t";
							}
						}
						break;
					}
					else {
						std::cout << "\nError! Unsupported format.";
						myFile.close();
						break;
					}
				}
				else if (filePointer == "EUC_2D")
				{
					std::vector<double> xVect;
					xVect.clear();
					std::vector<double> yVect;
					yVect.clear();

					do myFile >> filePointer;
					while (filePointer != "NODE_COORD_SECTION");

					for (int i = 0; i < noOfCities; i++)
					{
						myFile >> filePointer;
						std::cout << endl << filePointer << "\t";

						myFile >> filePointer;
						xVect.push_back(atof(filePointer.c_str()));
						std::cout << xVect[i] << "\t";

						myFile >> filePointer;
						yVect.push_back(atof(filePointer.c_str()));
						std::cout << yVect[i] << endl;
					}
					std::cout << endl;

					for (int i = 0; i < noOfCities; i++)
					{
						for (int j = 0; j < noOfCities; j++)
						{
							if (i != j)
							{
								double xDiff = xVect.at(i) - xVect.at(j);
								double yDiff = yVect.at(i) - yVect.at(j);
								int cost = std::nearbyint(sqrt(xDiff * xDiff + yDiff * yDiff));
								adjacancyMatrix[i][j] = cost;
							}
							if (i == j)
							{
								adjacancyMatrix[i][j] = 0;
							}
						}
					}
					break;
				}
				else {
					std::cout << "\nError! Unsupported format.";
					myFile.close();
					break;
				}
			}
			else {
				std::cout << "Error! No such file in 'data' directory";
				break;
			}
		}
		case 0:
		{
			adjacancyMatrix.clear();
			return 0;
		}
		default:
		{
			std::cout << "Wrong input";
			break;
		}
		}
	}
}

// setters
int tspGA::setPopSize(int popSize)
{
	std::cout << "Enter population size: " << endl;
	std::cin >> popSize;
	return popSize;
}

double tspGA::setMutationRatio(double mutationRatio)
{
	std::cout << "Enter mutation ratio (in %.): " << endl;
	std::cin >> mutationRatio;
	return mutationRatio;
}

double tspGA::setCrossoverRatio(double crossoverRatio)
{
	std::cout << "Enter crossover ratio (in %): " << endl;
	std::cin >> crossoverRatio;
	return crossoverRatio;
}

// getters
std::vector<std::vector<int>> tspGA::getAdjacancyMatrix(void)
{
	return std::vector<std::vector<int>>(adjacancyMatrix);
}

std::vector<std::vector<int>> tspGA::getParentsPop(void)
{
	return std::vector<std::vector<int>>(parentsPop);
}

std::vector<std::vector<int>> tspGA::getChildrenPop(void)
{
	return std::vector<std::vector<int>>(childrenPop);
}

std::vector<int> tspGA::getPopMember(void)
{
	return std::vector<int>(popMember);
}

int tspGA::getPopSize(void)
{
	return popSize;
}

int tspGA::getNoOfCities(void)
{
	return noOfCities;
}

// object init
void tspGA::start(void)
{
	tspInit(getAdjacancyMatrix(), getPopMember(), getNoOfCities(), getParentsPop(), getChildrenPop(), getPopSize());
}

tspGA::tspGA()
{

}

tspGA::~tspGA()
{

}
