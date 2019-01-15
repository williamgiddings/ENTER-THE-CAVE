#include "ScoreTracker.h"
#include <fstream>
#include <string>
#include <iostream>

int ScoreTracker::GetHighScore()
{
	std::ifstream dataFile(hsPath);
	int store;
	std::string data;
	if (dataFile.is_open())
	{
		while (std::getline(dataFile, data, ','))
		{
			store = stoi(data);
			dataFile.close();
		}
	}
	else
	{
		return 0;
	}
	return store;
}


int ScoreTracker::GetHighCoins()
{
	std::ifstream dataFile(hsPath);
	int check = 0;
	int store;
	std::string data;
	if (dataFile.is_open())
	{
		while (std::getline(dataFile, data, ','))
		{
			store = stoi(data);
			if (check == 1)
			{
				store = stoi(data);
				dataFile.close();
			}
			check++;
		}
		
	}
	else
	{
		return 0;
	}
	return store;
}

void ScoreTracker::SetHighScore(const int score, const int coins)
{
	std::ofstream dataFile;
	dataFile.open(hsPath, std::ofstream::trunc);

	if (dataFile.is_open())
	{
		dataFile << score << "," << coins;
		dataFile.close();
	}

}
