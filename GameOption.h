#pragma once

#include <string>
using namespace std;

class GameOption {
	bool IsFileMoveExist = false;
	bool IsFileGBoardExist = false;
	string Path = "";
	int Delay = 20;
	bool Quiet = false;
	bool IsRecord = false;

public:
	GameOption(int argc, char *argv[])
	{
		UpdateOption(argc, argv);
	}
	GameOption() {}
	bool GetIsFileMoveExist() const
	{
		return IsFileMoveExist;
	}
	bool GetIsRecord() const
	{
		return IsRecord;
	}
	void OnOffRecord() 
	{
		IsRecord=!IsRecord;
	}
	bool GetFileGBoardExist() const
	{
		return IsFileGBoardExist;
	}
	int GetDelay() const
	{
		return Delay;
	}
	bool GetQuiet() const
	{
		return Quiet;
	}
	string GetPath() const
	{
		return Path;
	}


private:
	void UpdateOption(int argc, char *argv[]);
	string  GetDirectoryFromPath(string _path);
};



