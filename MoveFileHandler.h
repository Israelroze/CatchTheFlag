#pragma once

#include <string>
#include <list>
#include "Cell.h"
#include "Soldier.h"
#include <tuple>
#include <fstream>

#define MOVE_A_EXT ".moves-a_small"
#define MOVE_B_EXT ".moves-b_small"

using namespace std;



class MoveFileHandler
{
private:

	list <tuple<int, int, Direction>> PlayerMoves;
	string FileName;
	fstream MoveFile;
	bool IsRecored;
	bool isPlayerMovesOver;
	Side TheSide;

	MoveFileHandler(const MoveFileHandler& x) = delete;

public:
	MoveFileHandler(string _fileName, bool _isRecored, Side _theSide) :
		FileName(_fileName), IsRecored(_isRecored), TheSide(_theSide)
	{}
	~MoveFileHandler() {
		if (this->MoveFile.is_open())
		{
			this->MoveFile.close();
		}
	}
	//void OpenFileForRecord();
	
	void AddMove(int Turn, int PlayerNumber, Direction dir);
	

	//tuple<int, int, Direction> getNextMove();
	bool GetisPlayerMovesOver() { return isPlayerMovesOver; }
	void Activate();
	tuple<int, int, Direction> GetCurrentMove();
	void NextMove();
	string GetMoveFilename() { return FileName; }
	void CloseFileAfterRecord();
private:
	char ConvertDirectionToChar(Direction dir);
	void GetMovesFromFiles();
	Direction ConvertCharToDirection(char ToConvert);
	bool CheckIfPlayerMovesOver() { return this->isPlayerMovesOver; }
	void PassListToFile();
	


};
