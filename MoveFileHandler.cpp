#include "MoveFileHandler.h"
#include <string>
#include <algorithm>


using namespace std;



void MoveFileHandler::AddMove(int Turn, int PlayerNumber, Direction dir)
{
	this->PlayerMoves.push_back(make_tuple(Turn, PlayerNumber, dir));
}

void MoveFileHandler::Activate()
{
	if (IsRecored == false)
	{
		this->MoveFile.open(FileName, ios::in);
		if (MoveFile.good()) {
			this->isPlayerMovesOver = false;
			this->GetMovesFromFiles();
		}
		else this->isPlayerMovesOver = true;
	}
	else
	{
		this->MoveFile.open(this->FileName, ios::out | ios::trunc);
	}
}

char MoveFileHandler::ConvertDirectionToChar(Direction dir)
{
	switch (dir)
	{
	case Direction::UP:
		return 'U';
		break;
	case Direction::DOWN:
		return 'D';
		break;
	case Direction::LEFT:
		return 'L';
		break;
	case Direction::RIGHT:
		return 'R';
		break;
	case Direction::NoDirection:
		return 'S';
		break;
	default:
		break;
	}
}

void MoveFileHandler::GetMovesFromFiles()
{
	int turn;
	int player;
	Direction dir;
	char Buffer[4096];


	if (MoveFile.good())
	{
		this->isPlayerMovesOver = false;
		while (!MoveFile.eof())
		{
			MoveFile.getline(Buffer, 4095, ','); sscanf_s(Buffer, "%d", &turn);
			MoveFile.getline(Buffer, 4095, ','); player = (int)(*Buffer - '0');
			if (*Buffer != '\0')
			{
				MoveFile.getline(Buffer, 4095); dir = ConvertCharToDirection(Buffer[0]);
				PlayerMoves.push_front(make_tuple(turn, player, dir));
			}
		}
		if (PlayerMoves.size() == 0)
			this->isPlayerMovesOver = true;
	}
	else 
		this->isPlayerMovesOver = true;
}

Direction MoveFileHandler::ConvertCharToDirection(char ToConvert)
{
	switch (ToConvert)
	{
	case 'U':
	case 'u':
		return Direction::UP; break;
	case 'D':
	case 'd':
		return Direction::DOWN; break;
	case 'L':
	case 'l':
		return Direction::LEFT; break;
	case 'r':
	case 'R':
		return Direction::RIGHT; break;
	case 's':
	case 'S':
		return Direction::NoDirection; break;

	}
	return Direction::NoDirection;
}

void MoveFileHandler::PassListToFile()
{
	if (this->MoveFile.is_open())
	{
		while (this->PlayerMoves.size() > 0)
		{
			tuple<int, int, Direction> x = this->PlayerMoves.front();
			this->MoveFile << get<0>(x) << ',' << get<1>(x) << ',' << this->ConvertDirectionToChar(get<2>(x)) << endl << flush;
			this->PlayerMoves.pop_front();
		}
	}
}

tuple<int, int, Direction> MoveFileHandler::GetCurrentMove()
{
	auto x = PlayerMoves.back();
	return x;
}

void MoveFileHandler::NextMove()
{

	PlayerMoves.pop_back();
	if (PlayerMoves.size() == 0)
		this->isPlayerMovesOver = true;
}

void MoveFileHandler::CloseFileAfterRecord()
{
	if (this->MoveFile.is_open())
	{
		if (IsRecored == true)
		{
			this->PassListToFile();
		}
		this->MoveFile.close();
	}
}
