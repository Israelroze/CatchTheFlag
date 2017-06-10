#pragma once

#include <string>
#include "AbstractPlayer.h"
using namespace std;
class AlgoPlayer1: public AbstractPlayer{

private:

	int Score;

public:
	AlgoPlayer1(string _name) : AbstractPlayer(), Score(0) {}
	/*const string GetPlayerName() { return Name; }
	void SetPlayerName(string const _name) { Name = _name; }
	*/
	virtual void setPlayer(int player) override; 
	void AddScoreOne() { Score++; }
	void ResetScore() { Score = 0; };
	const int GetPlayerScore() { return Score; }
};