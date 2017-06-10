#include "GameOption.h"

void GameOption::UpdateOption(int argc, char * argv[])
{
	string cur;
	for (int i = 1; i < argc; i++)
	{
		cur = argv[i];
		if (cur == "-board" && IsFileGBoardExist == false)
		{
			if (string(argv[i + 1]) == "f") {
				IsFileGBoardExist = true;
				i++;
			}
			else if (string(argv[i + 1]) == "r") i++;

		}
		else if (cur == "-moves" && IsFileMoveExist == false)
		{
			if (string(argv[i + 1]) == "f") {
				IsFileMoveExist = true;
				i++;
			}

			else if (string(argv[i + 1]) == "k") i++;
		}
		else if (cur == "-path" && Path == "")
		{
			i++;
			
			Path = string(argv[i]);

		}
		else if (cur == "-quiet")
		{
			Quiet = true;
			
		}
		else  if (cur == "-delay") 
		{
			i++;
			sscanf_s(argv[i], "%d", &Delay);
			
		}
	}
	if (Path == "") Path = GetDirectoryFromPath(string(argv[0]));
		
	if (!IsFileMoveExist)
		Quiet = false;
}

string GameOption::GetDirectoryFromPath(string _path)
{
	int p = _path.find_last_of('\\');
	_path.erase(_path.begin() + p, _path.end());
	return _path;
}
