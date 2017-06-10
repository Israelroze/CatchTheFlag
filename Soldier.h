#pragma once

#include <iostream>
#include "Utils.h"
#include "Enums.h"

using namespace std;
class Cell;

class Soldier {
	//data members
	int number; //soldier name
	Side side;
	Cell* cell;
	bool isOnWater;
	bool isInForest;

private:
	void SetCell(Cell* newCell)
	{
		cell = newCell;
	}
public:
	Soldier(int _number, Side _side, bool _isOnWater, bool _isInForest, Cell* _cell = nullptr) :
		number(_number),
		side(_side),
		cell(_cell),
		isOnWater(_isOnWater),
		isInForest(_isInForest)
	{}
	bool GetIsOnWater() { return isOnWater; }
	bool GetIsInForest() { return isInForest; }
	int GetSoliderNumber() { return number; }
	Side GetSoliderSide() { return side; }
	Cell* GetSoliderCell() { return cell; }
	void SetSoldierCell(Cell*& cell);
	Move MoveSoldier(Cell*& target);
	bool FightSoldier(Soldier* enemy);
	//void MoveSolider(Direction dir);
	void Draw();
	void unDraw();
};
