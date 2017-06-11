#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>
#include "BoardFileHandler.h"
#include "MoveFileHandler.h"
#include <list>
#include<vector>
#include <iterator>

using namespace std;

class GameDir
{
public:

private:

	string dir_name;
	int num_of_board_files = 0;
	list< BoardFileHandler*> game_files;
	list< BoardFileHandler*>::iterator  iter;

	void GetAllFiles();

public:

	auto GetCBegin() const
	{
		return game_files.cbegin();
	}
	auto GetCEnd() const
	{
		return game_files.cend();
	}
	bool isFilesNotOver() const
	{
		return (iter != game_files.cend());
	}
	~GameDir() 
	{
		for (auto i : game_files)
			delete i;
	}

	GameDir(const GameDir&) = delete;

	GameDir(string path) : dir_name(path)
	{
		GetAllFiles();
		iter = game_files.begin();
	}

};