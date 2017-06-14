#include "Board.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <ostream>

Board::~Board()
{

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
		{
			if (cells[i][j] != nullptr)
				delete cells[i][j];
		}
	for (Soldier*& i : soldiers)
	{
		if (i != nullptr)
			delete i;
	}
	//clearScreen();
}


//////////////////////////////////////////////Random Board Type////////////////////////////////////////////////////////
void Board::SetSpecialCells()
{
	//initialize the FR cells
	int FR[][2] = { { 3,4 },{ 3,5 },{ 3,6 },{ 3,7 },{ 2,7 },{ 1,7 },{ 1,8 },{ 4,6 } ,{ 4,7 } ,{ 4,8 },{ 4,9 } };
	for (auto& i : FR)
	{
		int x = i[0] - 1;
		int y = i[1] - 1;
		cells[x][y] = new Cell(x, y, Type::FR);
		if (!TheOption.GetQuiet()) cells[x][y]->Draw();
	}

	//initialize the SEA cells
	int SEA[][2] = { { 8, 6 },{ 9,5 },{ 9,6 },{ 10,4 },{ 10,5 },{ 10,6 },{ 10,7 },{ 10,8 },{ 10,9 },{ 10,10 },{ 11,7 },{ 11,8 },{ 11,9 },{ 12,8 } };

	for (auto& i : SEA)
	{
		int x = i[0] - 1;
		int y = i[1] - 1;
		cells[x][y] = new Cell(x, y, Type::SEA);
		if (!TheOption.GetQuiet()) cells[x][y]->Draw();

	}
	//initialize the SEA cells

	//FlgA: 11, 1
	cells[10][0] = new Cell(10, 0, Type::FlgA);
	if (!TheOption.GetQuiet()) cells[10][0]->Draw();

	//FlgB: 2,13

	cells[1][12] = new Cell(1, 12, Type::FlgB);
	if (!TheOption.GetQuiet()) cells[1][12]->Draw();

}
void Board::RandomSoldiers()
{

	int cur = 1;
	int x, y;
	int AsoldierNumber[] = { 1, 2, 3 };
	srand(unsigned int(time(time_t(0))));

	soldiers[0] = new Soldier(1, Side::SideA, false, false);
	soldiers[1] = new Soldier(2, Side::SideA, true, true);
	soldiers[2] = new Soldier(3, Side::SideA, true, false);
	soldiers[3] = new Soldier(7, Side::SideB, true, true);
	soldiers[4] = new Soldier(8, Side::SideB, false, true);
	soldiers[5] = new Soldier(9, Side::SideB, false, false);

	for (int i = 0; i < 6; i++)
	{
		bool isFinised = false;
		do {
			x = rand() % 13;
			y = (rand() % 5) + (i >= 3 ? 8 : 0);
			if (cells[x][y] == nullptr)
			{
				isFinised = true;
				cells[x][y] = new Cell(x, y, soldiers[i]);
				cells[x][y]->SetType((Type)((int)Type::S1 + i));
				soldiers[i]->SetSoldierCell(cells[x][y]);
				if (!TheOption.GetQuiet()) cells[x][y]->Draw();
			}
		} while (isFinised != true);
	}
}
void Board::randomize()
{
	SetSpecialCells();
	RandomSoldiers();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////File Board Type//////////////////////////////////////////////////////////

void Board::readfile(string file)
{
	ifstream fstream(file);
	string Violations;
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
					switch (line[col])
					{
						case '1':
							cells[row][col] = new Cell(row, col, Type::S1);
							soldiers[0] = new Soldier(1, Side::SideA, false, false);
							soldiers[0]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[0]);
						break;
						case '2':
							cells[row][col] = new Cell(row, col, Type::S2);
							soldiers[1] = new Soldier(2, Side::SideA, false, false);
							soldiers[1]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[1]);
						break;
						case '3':
							cells[row][col] = new Cell(row, col, Type::S3);
							soldiers[2] = new Soldier(3, Side::SideA, false, false);
							soldiers[2]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[2]); 
						break;
						case '7':
							cells[row][col] = new Cell(row, col, Type::S7);
							soldiers[3] = new Soldier(7, Side::SideB, false, false);
							soldiers[3]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[3]);
						break;
						case '8':
							cells[row][col] = new Cell(row, col, Type::S8);
							soldiers[4] = new Soldier(8, Side::SideB, false, false);
							soldiers[4]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[4]);
						break;
						case '9':
							cells[row][col] = new Cell(row, col, Type::S9);
							soldiers[5] = new Soldier(9, Side::SideB, false, false);
							soldiers[5]->SetSoldierCell(cells[row][col]);
							cells[row][col]->SetSoldier(soldiers[5]);
						break;
						case 'B':
							cells[row][col] = new Cell(row, col, Type::FlgB);
							FlgBPos.first = row;
							FlgBPos.second = col;
						break;
						case 'A':
							cells[row][col] = new Cell(row, col, Type::FlgA);
							FlgAPos.first = row;
							FlgAPos.second = col;
						break;
						case 'T':
							cells[row][col] = new Cell(row, col, Type::FR);
						break;
						case 'S':
							cells[row][col] = new Cell(row, col, Type::SEA);
						break;
					}
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
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Board::IsDeadArmy(Side _side)
{
	int counter = 0;
	int i = (_side == Side::SideA ? 0 : 3);
	for (int j = i; j < i + 3; j++)
	{
		if (soldiers[j] == nullptr)
			counter++;
	}
	return counter == 3 ? true : false;
}

Side Board::IsFlagCatched()
{
	if ((cells[FlgAPos.first][FlgAPos.second]->GetSoldier() != nullptr) && cells[FlgAPos.first][FlgAPos.second]->GetSoldier()->GetSoliderSide() == Side::SideB)
	{

		return Side::SideB;
	}
	else if ((cells[FlgBPos.first][FlgBPos.second]->GetSoldier() != nullptr) && cells[FlgBPos.first][FlgBPos.second]->GetSoldier()->GetSoliderSide() == Side::SideA)
	{

		return Side::SideA;
	}
	return Side::NoSide;
}
Side Board::isAnySideWon()
{
	Side result = Side::NoSide;
	if ((result = IsFlagCatched()) != Side::NoSide) {}
	else if (IsDeadArmy(Side::SideA)) result = Side::SideB;
	else if (IsDeadArmy(Side::SideB)) result = Side::SideA;

	return result;
}
void Board::MoveSoldierHelper(Soldier*& sol, int sourceX, int sourceY, int targetX, int targetY)
{
	//if move to new cell secsseeded then return true
	Cell *& TargetCell = cells[targetX][targetY];
	Cell *& sourceCell = cells[sourceX][sourceY];

	Move soldier_input = Move::NoMove;

	if (TargetCell == nullptr)
	{
		TargetCell = new Cell(targetX, targetY, Type::Regular);
		soldier_input = sol->MoveSoldier(TargetCell);
	}
	else
		switch (TargetCell->GetType())
		{
		case Type::SEA:
			if (sol->GetIsOnWater() == true)
				soldier_input = sol->MoveSoldier(TargetCell);
			break;
		case Type::FR:
			if (sol->GetIsInForest() == true)
				soldier_input = sol->MoveSoldier(TargetCell);
			break;
		case Type::FlgA:
			if (sol->GetSoliderSide() == Side::SideB)
				soldier_input = sol->MoveSoldier(TargetCell);
			break;
		case Type::FlgB:
			if (sol->GetSoliderSide() == Side::SideA)
				soldier_input = sol->MoveSoldier(TargetCell);
			break;
		case Type::Regular:
		case Type::S1:
		case Type::S2:
		case Type::S3:
		case Type::S7:
		case Type::S8:
		case Type::S9:
			soldier_input = sol->MoveSoldier(TargetCell);
			break;
		}




	if (soldier_input != Move::NoMove && soldier_input != Move::Failed)
	{
		if (!TheOption.GetQuiet()) sourceCell->Draw();
		if (!TheOption.GetQuiet()) TargetCell->Draw();
	}

	if (soldier_input != Move::OK && soldier_input != Move::Failed && soldier_input != Move::NoMove) //dead soldier 
	{
		int index = ((int)soldier_input < 6) ? ((int)soldier_input - 1) : ((int)soldier_input - 4);
		//if (sol->GetSoliderNumber() == soldiers[index]->GetSoliderNumber())
		//sol = nullptr;
		delete soldiers[index];
		soldiers[index] = nullptr;
	}

}
void Board::MovePlayer(Side TheSide, const GameMove & TheMove)
{
	char sourceCellChar = charAt(TheMove.from_x, TheMove.from_y);
	int soliderNumber = ('1' <= sourceCellChar && sourceCellChar <= '3' || '7' <= sourceCellChar && sourceCellChar <= '9') ? int(sourceCellChar - '0') : 0;
	if (soliderNumber != 0 &&CheckIfValidMove(TheSide, TheMove) )
	{
		MoveSoldierHelper(soldiers[GetSoldierIndex(soliderNumber)], TheMove.from_x, TheMove.from_y, TheMove.to_x, TheMove.to_y);
	}
}
bool Board::CheckIfValidMove(Side TheSide, const GameMove & TheMove)
{

	char sourceCellChar = charAt(TheMove.from_x, TheMove.from_y);
	if (sourceCellChar != '1' &&sourceCellChar != '2' &&sourceCellChar != '3' &&sourceCellChar != '7' &&sourceCellChar != '8' &&sourceCellChar != '9')
		return false;
	if (TheSide == Side::SideB && (sourceCellChar == '1' || sourceCellChar == '2' || sourceCellChar == '3'))
		return false;
	if (TheSide == Side::SideA && (sourceCellChar == '7' || sourceCellChar == '8' || sourceCellChar == '9'))
		return false;
	if ((TheMove.from_x != TheMove.to_x) && (TheMove.from_y != TheMove.to_y))
		return false;
	if (abs(TheMove.from_x - TheMove.to_x) > 1)
		return false;
	if (abs(TheMove.from_y - TheMove.to_y) > 1)
		return false;
	if (1 <= TheMove.to_x  && TheMove.to_x <= 13 && 1 <= TheMove.to_y &&  TheMove.to_y <= 13)
		return true;
}
void Board::PlayerMove(Soldier *& sol, Direction dir)
{
	int x = sol->GetSoliderCell()->GetX();
	int y = sol->GetSoliderCell()->GetY();
	switch (dir)
	{
	case Direction::UP:
		if (0 < y) {
			MoveSoldierHelper(sol, x, y, x, y - 1);
		}
		break;
	case Direction::DOWN:
		if (y < 12) {
			MoveSoldierHelper(sol, x, y, x, y + 1);
		}
		break;
	case Direction::LEFT:
		if (0 < x) {
			MoveSoldierHelper(sol, x, y, x - 1, y);
		}
		break;
	case Direction::RIGHT:
		if (x < 12) {
			MoveSoldierHelper(sol, x, y, x + 1, y);
		}
		break;
	}
}