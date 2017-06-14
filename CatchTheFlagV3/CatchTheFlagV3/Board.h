#pragma once


#include "BoardData.h"
#include "Soldier.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Utils.h"
#include "GameMove.h"
#include "Cell.h"
#include "GameOption.h"



class Board : public BoardData {

private:

	Cell* cells[13][13];
	Soldier* soldiers[6];
	const int &turnFromGame;
	const GameOption TheOption;
	pair<int, int> FlgAPos = { 10, 0 };
	pair<int, int> FlgBPos = { 1, 12 };



	void SetSpecialCells();
	void RandomSoldiers();
	void randomize();


	void readfile(string file);

public:
	Board(const int& turn) : BoardData(), turnFromGame(turn)
	{
		randomize();
	}

	Board(string file_name, const int& turn): BoardData(), turnFromGame(turn)
	{
		readfile(file_name);
	}

	Side ValidateBoard();
	virtual void updateBoard()
	virtual void draw() = 0;
	virtual char charAt(int x, int y) const override {
		//TO DO : TO implement
		return '#';
	}
	
	bool IsDeadArmy(Side const _side);
	Side IsFlagCatched();
	void PlayerMove(Soldier *& sol, Direction const dir);
	Side isAnySideWon();
	void MoveSoldierHelper(Soldier *& sol, int const sourceX, int const  sourceY, int const targetX, int const targetY);
	int GetSoldierIndex(int sol_num) {
		return sol_num >3 ? (sol_num - 4) : (sol_num - 1);
	}
	int GetSoliderNumFromIndex(int sol_num)
	{
		return sol_num > 2 ? sol_num + 4 : sol_num + 1;
	}

	void MovePlayer(Side TheSide, const GameMove& TheMove);
	bool CheckIfValidMove(Side TheSide, const GameMove& TheMove);
	
};	

friend GameEngine;