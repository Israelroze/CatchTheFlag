#pragma once

#include "Cell.h"
#include "Soldier.h"
#include "Player.h"
#include "Enums.h"
#include <list>
#include "GameOption.h"
#include "MoveFileHandler.h"
#include "BoardFileHandler.h"
#include "Board.h"
class Game {
private:
	/*Cell* cells[13][13];
	Soldier* soldiers[6];*/
	
	bool isEnd;
	AbstractPlayer * PlayerA;
	AbstractPlayer * PlayerB;
	
	GameOption  TheOption;
	Board GameBorad;

private:
	/*void SetSpecialCells();
	void RandomSoldiers();*/
	/*bool IsDeadArmy(Side const _side);*/
	/*Side IsFlagCatched();*/
	//bool ChooseSoliderAndDirection(int&  PlayerASolider, Direction& dirA, int&  PlayerBSolider, Direction& dirB);
	
	void ClearTable();
	void ReDrawTable();
	//IsGameStop PrintSubMenu();
	/*Side isAnySideWon();*/
	void PrintPlayersNameAndScores();
	void start();
	void DrawTable();
	
	//void BoardToFile(char(&board)[13][13]);

public:
	Game(AbstractPlayer * _PlayerA, AbstractPlayer * _PlayerB, GameOption  _theOption);
	Game(AbstractPlayer * _PlayerA, AbstractPlayer * _PlayerB, list<Cell> cells_from_file, GameOption _theOption);
	
	~Game();
	template<class T, class S>
	Side Run(IsGameStop& theWinner,T PlayerA, S playerB);

	Side RunFromFile(int& num_of_turns,MoveFileHandler *moveA, MoveFileHandler *moveB);
	Side RunRecord(IsGameStop& isGameStop,BoardFileHandler* board,MoveFileHandler *moveA=nullptr, MoveFileHandler *moveB=nullptr);
};