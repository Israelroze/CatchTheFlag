#include "GameDir.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <iterator>

bool GameDir::IsFileExist(string filename)
{
	bool result = false;
	for (auto i : game_files)
	{
		if (((i.second->GetBoardFile()!=nullptr)&&(i.second->GetBoardFile()->GetBoardFileName() == filename)) ||
			((i.second->GetMoveAFile() != nullptr) && (i.second->GetMoveAFile()->GetMoveFilename() == filename)) ||
			((i.second->GetMoveBFile() != nullptr) && (i.second->GetMoveBFile()->GetMoveFilename() == filename)))
			result = true;
	}
	return result;
}
void GameDir::NewTrio()
{
	TrioFiles* ntrio = new TrioFiles();
	int random_files = 1;
	string key = dir_name + "random_" + to_string(random_files);
	
	while (IsFileExist(key + ".gboard"))
	{
		random_files++;
		key = dir_name +  "random_" + to_string(random_files);
	}
	
	//create new borad file handler
	string boardfname = key + ".gboard";
	BoardFileHandler* board = new BoardFileHandler(boardfname);
	ntrio->SetBoardFile(board);

	//create new move a file
	string moveAfile = key + ".moves-a_small";
	MoveFileHandler* moveA = new MoveFileHandler(moveAfile, true, Side::SideA);
	ntrio->SetMoveAFile(moveA);

	//create new move b file
	string moveBfile = key + ".moves-b_small";
	MoveFileHandler* moveB = new MoveFileHandler(moveBfile, true, Side::SideB);
	ntrio->SetMoveBFile(moveB);

	//add to game map
	game_files[key] = ntrio;

	iter = game_files.begin();
	for (; iter != GetCEnd() && iter->first != key; ++iter) {}
}

 void GameDir::NewMoveFiles(string boardfile)
{
	//find the right iterator
	iter = game_files.begin();
	for (; iter != game_files.end() && ((iter->second->GetBoardFile() != nullptr) && (iter->second->GetBoardFile()->GetBoardFileName() != boardfile)); ++iter) {}

	if (iter != game_files.end())
	{
		if (iter->second->GetMoveAFile() != nullptr) delete iter->second->GetMoveAFile();
		MoveFileHandler* new_moveA = new MoveFileHandler(dir_name + iter->first + ".moves-a_small", true, Side::SideA);
		iter->second->SetMoveAFile(new_moveA);

		if (iter->second->GetMoveBFile() != nullptr) delete iter->second->GetMoveBFile();
		MoveFileHandler* new_moveB = new MoveFileHandler(dir_name + iter->first + ".moves-b_small", true, Side::SideB);
		iter->second->SetMoveBFile(new_moveB);
	}
}

void GameDir::GetAllFiles()
{

	char buffer[4096] = { ' ' };
	std::string command = "2>NUL dir /a-d /b \"" + dir_name + "\"";
	std::string data_str;
	FILE* fp = _popen(command.c_str(), "r");
	while (fgets(buffer, 4095, fp))
	{
		//get the filename and extension
		data_str = std::string(buffer);
		data_str.erase(remove_if(data_str.end() - 1, data_str.end(), isspace), data_str.end());
		int dot_pos = data_str.find(".");
		string tmp = data_str;
		string full = dir_name + data_str;
		data_str.erase(dot_pos, data_str.npos - (dot_pos));
		string file_name = data_str;
		string file_extension = tmp.erase(0, dot_pos);

		auto search = game_files.find(file_name);
		if (file_extension != ".gboard" && file_extension != ".moves-a_small" && file_extension != ".moves-b_small")
			continue;
		if (search != game_files.end())
		{
			if (file_extension == ".gboard" && search->second->GetBoardFile() == nullptr)
			{
				BoardFileHandler* board = new BoardFileHandler(full);
				search->second->SetBoardFile(board);
				num_of_board_files++;
			}

			else if (file_extension == ".moves-a_small" &&search->second->GetMoveAFile() == nullptr)
			{
				MoveFileHandler* moveA = new MoveFileHandler(full, false, Side::SideA);
				search->second->SetMoveAFile(moveA);
				num_of_a_files++;

			}
			else if (file_extension == ".moves-b_small" && search->second->GetMoveBFile() == nullptr)
			{

				MoveFileHandler* moveB = new MoveFileHandler(full, false, Side::SideB);
				search->second->SetMoveBFile(moveB);
				num_of_b_files++;
			}
		}
		else
		{
			TrioFiles* trio = new TrioFiles();
			if (file_extension == ".gboard")
			{
				BoardFileHandler* board = new BoardFileHandler(full);
				trio->SetBoardFile(board);
				num_of_board_files++;
			}
			else if (file_extension == ".moves-a_small")
			{
				MoveFileHandler* moveA = new MoveFileHandler(full, false, Side::SideA);
				trio->SetMoveAFile(moveA);
				num_of_a_files++;
			}
			else if (file_extension == ".moves-b_small")
			{
				MoveFileHandler* moveB = new MoveFileHandler(full, false, Side::SideB);
				trio->SetMoveBFile(moveB);
				num_of_b_files++;
			}
			game_files[file_name] = trio;
		}
	}
	_pclose(fp);
}



