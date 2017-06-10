#include "BoardFileHandler.h"

void BoardFileHandler::UpdateBoardCounters(char ch)
{
	switch (ch)
	{
	case '1':
		BoardCounters[s1]++;
		break;
	case '2':
		BoardCounters[s2]++;
		break;
	case '3':
		BoardCounters[s3]++;
		break;
	case '7':
		BoardCounters[s7]++;
		break;
	case '8':
		BoardCounters[s8]++;
		break;
	case '9':
		BoardCounters[s9]++;
		break;
	case 'B':
		BoardCounters[Bflags]++;
		break;
	case 'A':
		BoardCounters[Aflags]++;
		break;
	}
}
Type BoardFileHandler::GetCellType(char ch)
{
	switch (ch)
	{
	case '1':
		return Type::S1;
		break;
	case '2':
		return Type::S2;
		break;
	case '3':
		return Type::S3;
		break;
	case '7':
		return Type::S7;
		break;
	case '8':
		return Type::S8;
		break;
	case '9':
		return Type::S9;
		break;
	case 'B':
		return Type::FlgB;
		break;
	case 'A':
		return Type::FlgA;
		break;
	case 'T':
		return Type::FR;
		break;
	case 'S':
		return Type::SEA;
		break;
	}
	return Type::Regular;
}
void BoardFileHandler::ValidateBoardCounters()
{
	string f_name = "";
	string buffer = "";
	int index = 1;
	while (FileName[FileName.length() - index] != '/' && FileName[FileName.length() - index] != '\\')
	{
		buffer += FileName[FileName.length() - index];
		index++;
	}
	for (int i = (buffer.length() - 1); i >= 0; i--) f_name += buffer[i];
	if (BoardCounters[Aflags] != 1) Violations += "Wrong character on board: A in file:" + f_name + "\n";
	if (BoardCounters[Bflags] != 1) Violations += "Wrong character on board: B in file:" + f_name + "\n";
	if ((BoardCounters[s1] != 1) || (BoardCounters[s2] != 1) || (BoardCounters[s3] != 1)) Violations += "Wrong settings for player A tools in file:" + f_name + "\n";
	if ((BoardCounters[s7] != 1) || (BoardCounters[s8] != 1) || (BoardCounters[s9] != 1)) Violations += "Wrong settings for player A tools in file:" + f_name + "\n";
}
void BoardFileHandler::ReadBoard()
{
	ifstream fstream(FileName);
	if (fstream.is_open())
	{
		string line;
		int row = 0;
		while (getline(fstream, line) && row<13)
		{
			for (int col = 0; col<13; col++)
			{
				if (line[col] != ' ')
				{
					Board[col][row] = line[col];
					UpdateBoardCounters(line[col]);
				}
			}
			row++;
		}
		ValidateBoardCounters();
		fstream.close();
	}
	else
	{
		Violations = Violations + "Error reading board file.\n";
	}
	GetBoard();
}

void BoardFileHandler::WriteBoard(Cell* (&cells)[13][13])
{
	updateBoard(cells);
	ofstream ofstream(FileName, ios_base::out |ios_base::trunc);
	if (ofstream.is_open())
	{
		string line="";
		for (int i = 0; i < 13; i++)
		{
			line = "";
			toString(line,Board[i],13);
			//line = Board[i];
			//cout << line << endl;
			ofstream << line + "# " + to_string(i)  <<endl<<flush;
			//ofstream.write(line.c_str(), line.length());
		}
		ofstream << "-------------"<< endl<<flush;
		ofstream << "abcdefghijklm" << endl<<flush;


		ofstream.close();
	}
	else cout << "error opening board file to write." << endl;
}



void BoardFileHandler::SetBoard(char _board[13][13])
{

}

void BoardFileHandler::GetBoard()
{

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (Board[i][j] != ' ' && Board[i][j] != '\0') // TODO: replace with Switch Case all of correct option
			{
				Cells.push_back(Cell(i, j, GetCellType(Board[i][j])));
			}
		}
	}
}

void BoardFileHandler::updateBoard(Cell* (&cells)[13][13])
{
	for (int j = 0; j < 13; j++)
	{
		for (int i = 0; i < 13; i++)
		{
			if (cells[j][i] == nullptr)
			{
				Board[i][j] = ' ';
			}
			else
			{
				switch (cells[j][i]->GetType())
				{
				case Type::FlgA:
					Board[i][j] = 'A';
					break;
				case Type::FlgB:
					Board[i][j] = 'B';
					break;
				case Type::FR:
					Board[i][j] = 'T';
					break;
				case Type::SEA:
					Board[i][j] = 'S';
					break;
				case Type::S1:
					Board[i][j] = '1';
					break;
				case Type::S2:
					Board[i][j] = '2';
					break;
				case Type::S3:
					Board[i][j] = '3';
					break;
				case Type::S7:
					Board[i][j] = '7';
					break;
				case Type::S8:
					Board[i][j] = '8';
					break;
				case Type::S9:
					Board[i][j] = '9';
					break;
				case Type::Regular:
					Board[i][j] = ' ';
					break;
				}
			}
		}
	}
}


void BoardFileHandler::toString(string & str, char * arr, int size)
{
	
	for (int i=0; i < size; i++)
		str += arr[i];

}