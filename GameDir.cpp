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

		if (file_extension != ".gboard")
			continue;
		else
		{
			BoardFileHandler* board = new BoardFileHandler(full);
			num_of_board_files++;
		}
	}

	_pclose(fp);
}


