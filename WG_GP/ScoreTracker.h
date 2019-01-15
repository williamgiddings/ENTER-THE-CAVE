#pragma once
#include <string>

class ScoreTracker
{
public:
	const std::string hsPath = "./userData.dat";
	
	int GetHighScore();
	int GetHighCoins();
	void SetHighScore(const int score, const int coins);
	inline bool fileExists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
};