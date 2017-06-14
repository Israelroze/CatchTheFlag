#pragma once

#include "Soldier.h"

using namespace std;

class Soldier;

class Cell {


private:
	//data members
	Type type;
	Soldier* soldier;
	int x;
	int y;

public:
	Cell(int _x, int _y, Type ctype)
	{
		x = _x;
		y = _y;
		type = ctype;
		soldier = nullptr;
	}
	Cell(int _x, int _y, Soldier* sol)
	{
		x = _x;
		y = _y;
		soldier = sol;
		type = Type::Regular;

	}
	void SetType(Type const  _type) { type = _type; }
	void SetSoldier(Soldier* const & _soldier) { soldier = _soldier; }
	Type GetType() { return type; }
	int GetX() { return x; }
	int GetY() { return y; }
	void RemoveSolider() {
		soldier = nullptr;
		if (type >= Type::S1) type = Type::Regular;
	}
	Soldier* GetSoldier() { return soldier; }
	
	void Draw();
};
