#pragma once

#include <string>
#include "AbstractPlayer.h"
#include "BoardData.h"
using namespace std;
class AlgoPlayer1: public AbstractPlayer{

private:

	int Score;
	int PlayerNum; // can be 1 or 2
	BoardData  * Board;
	string Name;


	 
public:
	AlgoPlayer1(): AbstractPlayer(), Score(0) {}
	const string GetPlayerName() { return Name; }
	void SetPlayerName(string const _name) { Name = _name; }
	virtual void setPlayer(int player) override 
	{
		PlayerNum = (player == 1 || player == 2 ? player : 0);
	};
	virtual void init (const BoardData& board) override;
	virtual GameMove play(const GameMove& opponentsMoves)	override;
	virtual string getName()  const override;
	void AddScoreOne() { Score++; }
	void ResetScore() { Score = 0; };
	const int GetPlayerScore() { return Score; }
};