#pragma once

#include <string>
#include <list>
#include <vector>
#include <tuple>
#include "BoardFileHandler.h"
#include "MoveFileHandler.h"
#include <map>
#include<vector>
#include <iterator>

using namespace std;

class GameDir
{
public:

private:
	class TrioFiles {
	private:
		BoardFileHandler* fboard = nullptr;
		MoveFileHandler*  fmoveA = nullptr;
		MoveFileHandler*  fmoveB = nullptr;
	public:
		~TrioFiles() {
			delete fboard;
			delete fmoveA;
			delete fmoveB;
		}
		void SetBoardFile(BoardFileHandler* _fboard) { fboard = _fboard; }
		void SetMoveAFile(MoveFileHandler* _fmoveA) { fmoveA = _fmoveA; }
		void SetMoveBFile(MoveFileHandler* _fmoveB) { fmoveB = _fmoveB; }
		BoardFileHandler* GetBoardFile() const { return fboard; }
		MoveFileHandler* GetMoveAFile() const { return fmoveA; }
		MoveFileHandler* GetMoveBFile() const { return fmoveB; }
	};
	string dir_name;
	int num_of_board_files = 0;
	int num_of_a_files = 0;
	int num_of_b_files = 0;

	map<string, TrioFiles*> game_files;
	map<string, TrioFiles*>::iterator  iter;

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
	bool isMapNotOver() const
	{
		return (iter != game_files.cend());
	}
	bool IsFileExist(string filename);
	BoardFileHandler* GetCurrentBoardFile() const
	{
		if (iter == game_files.cend())
			return nullptr;
		else
		return iter->second->GetBoardFile();
	}
	MoveFileHandler * GetCurrentMoveAFile() const
	{
		if (iter == game_files.cend())
			return nullptr;
		else
		return iter->second->GetMoveAFile();
	}
	MoveFileHandler* GetCurrentMoveBFile() const
	{
		if (iter == game_files.cend())
			return nullptr;
		else
		return iter->second->GetMoveBFile();
	}
	void MoveToNextFilesTrio()
	{
		if (iter != game_files.end())
			++iter;
	}
	int NumberOfTrioRemaining()
	{
		return game_files.size();
	}
	void DeleteCurrentTrioAndMoveToNext()
	{
		map<string, TrioFiles*>::iterator  temp = iter;
		if (game_files.end() != iter) {
			if (iter->second->GetBoardFile() != nullptr) delete iter->second->GetBoardFile();
			if (iter->second->GetMoveAFile() != nullptr) delete iter->second->GetMoveAFile();
			if (iter->second->GetMoveBFile() != nullptr) delete iter->second->GetMoveBFile();
			iter++;
		}
		game_files.erase(temp);
	}
	~GameDir() {
		for (auto i : game_files)
		{
			delete i.second;
		}
	
	}
	void NewTrio();
	void NewMoveFiles(string boardfile);

	GameDir(const GameDir&) = delete;

	GameDir(string path) : dir_name(path)
	{
		GetAllFiles();
		iter = game_files.begin();
	}

};