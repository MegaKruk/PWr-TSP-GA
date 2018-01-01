#include "Stopwatch.h"
#include "tspGA.h"

void tspGA::popInit(std::vector<int> &popMember, int noOfCities, std::vector<std::vector<int>> &parentsPop, std::vector<std::vector<int>> &childrenPop, int popSize)
{
	parentsPop.clear();
	parentsPop.resize(popSize);
	for (int i = 0; i < popSize; ++i)
		parentsPop[i].resize(popSize);
	
	childrenPop.clear();
	popMember.clear();
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
		for (int h = 0; h < 100 * noOfCities; h++)
		{
			int x = randInt(1, noOfCities - 1);
			int y = randInt(1, noOfCities - 1);
			std::swap(popMember[x], popMember[y]);
		}
	}

	for (int k = 0; k < parentsPop.size(); k++)
	{
		for (int l = 0; l < parentsPop[k].size(); l++)
		{
			//std::cout << parentsPop[k][l] << "\t";
		}
		//std::cout << endl;
	}
}

int tspGA::calculateCost(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities)
{
	int tmpCost = 0;
	for (int i = 0; i < noOfCities; i++)
	{
		//std::cout << endl << seq[i] << endl;
		int a = popMember[i];
		//std::cout << endl << "a= "<< a;
		int b = popMember[i + 1];
		//std::cout << endl << "b= " << b;
		tmpCost += adjacancyMatrix[a][b % (noOfCities)];

	}
	return tmpCost;
}

int tspGA::randInt(int l, int r)
{
	return rand() % (r - l + 1) + l;
}

double tspGA::randFraction(void)
{
	return randInt(1, 10000) / 10000;
}

// g³owna funkcja programu
int tspGA::TSP(std::vector<std::vector<int>> &adjacancyMatrix, std::vector<int> &popMember, int noOfCities)
{
	srand(time(0));

	// best = null
	int bestCost = NULL;

	std::vector<int> bestPath;
	bestPath.clear();
	bestPath.resize(noOfCities + 1);

	/*for (int i = 0; i < noOfCities + 1; i++)
	{
		bestPath[i] = popMember[i];
	}

	// glowna petla
	for (double T = 1; T >= 1E-4; T *= 0.9)
		for (int n = 0; n <= 100 * noOfCities; n++)
		{
			int i = randInt(1, noOfCities - 1);
			int j = randInt(1, noOfCities - 1);
			std::swap(popMember[i], popMember[j]);

			// r - tweak attempt
			int newCost = calculateCost(adjacancyMatrix, popMember, noOfCities);

			if (newCost < currCost || randFraction() < exp((currCost - newCost) / T))
			{
				// s = r
				currCost = newCost;

				// best = s
				if (currCost < bestCost)
				{
					bestCost = currCost;
					for (int i = 0; i < noOfCities + 1; i++)
					{
						bestPath[i] = popMember[i];
					}
				}
			}
			else
				std::swap(popMember[i], popMember[j]);
		}

	std::cout << endl << endl << "Cost:\t" << bestCost << endl;
	std::cout << "Path:\t";
	for (int i = 0; i < noOfCities + 1; i++)
	{
		cout << bestPath[i] << "\t";
	}*/
	bestPath.clear();
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
			popInit(popMember, noOfCities, parentsPop, childrenPop, popSize);
			//TSP(adjacancyMatrix, popMember, noOfCities);
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
				popInit(popMember, noOfCities, parentsPop, childrenPop, popSize);
				//result = TSP(adjacancyMatrix, popMember, noOfCities);
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
