#pragma once

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include "Cell.h"

using namespace std;

class BoardFileHandler
{
private:
	//string Directory;
	string FileName;
	string Violations = "";
	char Board[13][13] = { ' ' };
	int BoardCounters[8] = { 0 };
	enum { s1, s2, s3, s7, s8, s9, Aflags, Bflags };
	list<Cell> Cells;
	void UpdateBoardCounters(char ch);
	Type GetCellType(char ch);
	void ValidateBoardCounters();
	void GetBoard();
	void updateBoard(Cell* (&cells)[13][13]);
	void toString(string & str, char * arr, int size);
public:
	enum class Player { PlayerA };
	BoardFileHandler(string _fileName) : FileName(_fileName) {}
	void ReadBoard();
	void WriteBoard(Cell* (&cells)[13][13]);
	bool IsViolations() {
		if (Violations != "") return true;
		return false;
	}
	void SetBoard(char _board[13][13]);
	
	string GetViolations() const { return Violations; }
	string GetBoardFileName() const { return FileName; }

	list<Cell> GetCellList() const { return this->Cells; }

};