#pragma once


#include "BoardData.h"
#include "Cell.h"
#include "Soldier.h"
#include "GameOption.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Utils.h"

class Board : public BoardData {

private:

	 Cell* cells[13][13];
	 Soldier* soldiers[6];
	const int &turnFromGame;
	const GameOption TheOption;
	pair<int, int> FlgAPos = { 10, 0 };
	pair<int, int> FlgBPos = { 1, 12 };
public:
	Board(const int& turn) : BoardData(), turnFromGame(turn)
	{
		
	}

	void SetSpecialCells();
	void RandomSoldiers();
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
	virtual char charAt(int x, int y) const override {
	//TO DO : TO implement
		return '#';
	}
	
};