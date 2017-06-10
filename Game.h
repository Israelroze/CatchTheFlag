#pragma once

#include "Cell.h"
#include "Soldier.h"
#include "Player.h"
#include "Enums.h"
#include <list>
#include "GameOption.h"
#include "MoveFileHandler.h"
#include "BoardFileHandler.h"

class Game {
private:
	Cell* cells[13][13];
	Soldier* soldiers[6];
	bool isEnd;
	Player * PlayerA;
	Player * PlayerB;
	pair<int, int> FlgAPos = { 10, 0 };
	pair<int, int> FlgBPos = { 1, 12 };
	GameOption  TheOption;

private:
	void SetSpecialCells();
	void RandomSoldiers();
	bool IsDeadArmy(Side const _side);
	Side IsFlagCatched();
	bool ChooseSoliderAndDirection(int&  PlayerASolider, Direction& dirA, int&  PlayerBSolider, Direction& dirB);
	void PlayerMove(Soldier *& sol, Direction const dir);
	void ClearTable();
	void ReDrawTable();
	IsGameStop PrintSubMenu();
	void MoveSoldierHelper(Soldier *& sol, int const sourceX, int const  sourceY, int const targetX, int const targetY);
	Side isAnySideWon();
	void PrintPlayersNameAndScores();
	void start();
	void DrawTable();
	int GetSoldierIndex(int sol_num) {
		return sol_num >3 ? (sol_num - 4) : (sol_num-1);
	}
	int GetSoliderNumFromIndex(int sol_num)
	{
		return sol_num > 2 ? sol_num + 4 : sol_num + 1;
	}
	void BoardToFile(char(&board)[13][13]);

public:
	Game(Player * _PlayerA, Player * _PlayerB, GameOption  _theOption);
	Game(Player * _PlayerA, Player * _PlayerB, list<Cell> cells_from_file, GameOption _theOption);
	
	~Game();
	Side Run(IsGameStop& theWinner);

	Side RunFromFile(int& num_of_turns,MoveFileHandler *moveA, MoveFileHandler *moveB);
	Side RunRecord(IsGameStop& isGameStop,BoardFileHandler* board,MoveFileHandler *moveA=nullptr, MoveFileHandler *moveB=nullptr);
};