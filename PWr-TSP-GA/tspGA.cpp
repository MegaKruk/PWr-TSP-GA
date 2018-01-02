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
		

		parentsPop[j] = popMember;
		for (int h = 0; h < 1024 * noOfCities; h++)
		{
			int x = randInt(1, noOfCities - 1);
			int y = randInt(1, noOfCities - 1);
			std::swap(popMember[x], popMember[y]);
			
		}
	}
	/*
	for (int k = 0; k < parentsPop.size(); k++)
	{
		for (int l = 0; l < parentsPop[k].size(); l++)
		{
			std::cout << parentsPop[k][l] << "\t";
		}
		std::cout << endl;
	}*/
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
/*
double tspGA::randFraction(void)
{
	return randInt(1, 10000) / 10000;
}*/

// g³owna funkcja programu
int tspGA::TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, 
	int popSize, double crossoverRatio, double mutationRatio)
{
	srand(time(0));

	// best = null
	int bestCost = NULL;
	std::vector<int> bestPath;
	bestPath.clear();
	bestPath.resize(noOfCities + 1);
	int iterations = noOfCities * 4;

	for (int k = 0; k < parentsPop.size(); k++)
	{
		for (int l = 0; l < parentsPop[k].size(); l++)
		{
			std::cout << parentsPop[k][l] << "\t";
		}
		std::cout << endl;
	}

	do
	{
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
			// select 2 random parents
			std::vector<int> parentA;
			parentA.resize(noOfCities + 1);
			int randA = randInt(0, popSize - 1);
			//cout << " A" << randA;
			for (int i = 0; i < noOfCities + 1; i++)
				parentA[i] = parentsPop[randA][i];
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*cout << endl << "a ";
			for (int i = 0; i < noOfCities + 1; i++)
			{
				cout << parentA[i] << " ";
			}*/

			

			std::vector<int> parentB;
			parentB.resize(noOfCities + 1);
			int randB = randInt(0, popSize - 1);
			while (randA == randB)
				randB = randInt(0, popSize - 1);
			for (int i = 0; i < noOfCities + 1; i++)
				parentB[i] = parentsPop[randB][i];
			
			// choose 2 random places to cut parent
			int randCutA = noOfCities / 2;
			std::vector<int> firstHalfA;
			firstHalfA.resize(noOfCities + 1);
			std::vector<int> secondHalfA;
			secondHalfA.resize(noOfCities + 1);
			for (int i = 0; i < randCutA; i++)
				firstHalfA[i] = parentA[i];
			for (int i = randCutA; i < noOfCities + 1; i++)
				secondHalfA[i] = parentA[i];

			int randCutB = noOfCities/2;
			std::vector<int> firstHalfB;
			firstHalfB.resize(noOfCities + 1);
			std::vector<int> secondHalfB;
			secondHalfB.resize(noOfCities + 1);
			for (int i = 0; i < randCutB; i++)
				firstHalfB[i] = parentB[i];
			for (int i = randCutB; i < noOfCities + 1; i++)
				secondHalfB[i] = parentB[i];
			
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
				for (int i = 0; i < randCutA; i++)
					childA[i] = firstHalfA[i];
				for (int i = randCutA; i < noOfCities + 1; i++)
					childA[i] = secondHalfA[i];
				for (int i = 0; i < randCutB; i++)
					childB[i] = firstHalfB[i];
				for (int i = randCutB; i < noOfCities + 1; i++)
					childB[i] = secondHalfB[i];
			}
			else
			{
				for (int i = 0; i < noOfCities + 1; i++)
					childA[i] = parentA[i];
				for (int i = 0; i < noOfCities + 1; i++)
					childB[i] = parentB[i];
			}
			
			// mutation
			if (diceroll < (mutationRatio / 1000.0))
			{
				for (int h = 0; h < noOfCities; h++)
				{
					int x = randInt(1, noOfCities - 1);
					int y = randInt(1, noOfCities - 1);
					std::swap(childA[x], childA[y]);
				}
				for (int h = 0; h < noOfCities; h++)
				{
					int x = randInt(1, noOfCities - 1);
					int y = randInt(1, noOfCities - 1);
					std::swap(childB[x], childB[y]);
				}
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
			
			if (childrenPop.size() == popSize)
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
				//childrenPop.clear();
				//childrenPop.resize(0);
			}

			// P <- Q

			parentA.clear();
			parentA.resize(0);
			parentB.clear();
			parentB.resize(0);
			firstHalfA.clear();
			firstHalfA.resize(0);
			secondHalfA.clear();
			secondHalfA.resize(0);
			firstHalfB.clear();
			firstHalfB.resize(0);
			secondHalfB.clear();
			secondHalfB.resize(0);
			childA.clear();
			childA.resize(0);
			childB.clear();
			childB.resize(0);
		}
		iterations--;
	}
	while (iterations > 0);

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

// wczytanie danych, przygotowanie funkcji TSP
void tspGA::tspInit(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize)
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

		adjacancyMatrix.resize(noOfCities);
		for (int i = 0; i < noOfCities; ++i)
			adjacancyMatrix[i].resize(noOfCities);

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
			}
			else
				std::cout << "\nError! Unsupported format.";
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
		}
		else
			std::cout << "\nError! Unsupported format.";
		myFile.close();

		// main menu
		int option;
		std::cout << endl;
		std::cout << "\n1 - Test algorithm\n2 - Make measurements\n";
		std::cin >> option;
		
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
			adjacancyMatrix.clear();
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
		default:
		{
			std::cout << "Wrong input";
			break;
		}
		}
	}
	else
		std::cout << "Error! No such file in 'data' directory";
}

// gettery
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

// funkcja inicjuj¹ca obiekt
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
