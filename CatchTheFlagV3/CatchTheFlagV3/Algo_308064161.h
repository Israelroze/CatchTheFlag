#pragma once

#include <string>
#include "AbstractPlayer.h"
#include "BoardData.h"
#include <stdlib.h>
#include <time.h>


using namespace std;
class Algo308064161 : public AbstractPlayer{
private:
	class Trio
	{
		pair<int, int> cord;
		int data;
		public:
		Trio(int _x, int _y, int _data) :data(_data) {
			cord = { _x,_y };
		}
		void SetData(int _data) { data = _data; }
		int GetData() { return data; }
		pair<int, int> GetCord() { return cord; }
	};
	
	enum{DeadSoldier=-3,NoMove=-2,EnemySpoted=1,Obsticle=-1,Free=2};
	BoardData* OriginalBoard;
	char Board[13][13];
	int Score;
	int PlayerNum; // can be 1 or 2

	string Name;
	GameMove Move;
	pair<int, int> MyFlagPos; 
	pair<int, int> EnemyFlagPos; 

	Trio PossibleMoves[2];
	Trio Soldiers[3];
	Trio* Attacker;


	void chooseMove();
	void choosePositions();

	int randomChoice();
	void updateBoard(GameMove& enemymove);
	
public:
	Algo308064161(): AbstractPlayer(), Score(0) {}
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