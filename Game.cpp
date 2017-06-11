#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "Soldier.h"
#include <conio.h>
#include <Windows.h>
#include "Utils.h"
#include "BoardFileHandler.h"
#include "AbstractPlayer.h"

using namespace std;

//table functions
void Game::DrawTable()
{
	setTextColor(int(Color::WHITE));
	//draw top line
	gotoxy(StartX, StartY);
	cout << char(218);
	for (int i = StartX + SizeX; i < StartX + Size * SizeX; i = i + SizeX)
	{
		for (int j = 0; j < SizeX - 1; j++) cout << char(196);
		cout << char(194);
	}
	for (int j = 0; j < SizeX - 1; j++) cout << char(196);
	cout << char(191);

	//draw bottom line 
	gotoxy(StartX, StartY + Size * SizeY);
	cout << char(192);
	for (int i = StartX + SizeX; i < StartX + Size * SizeX; i = i + SizeX)
	{
		for (int j = 0; j < SizeX - 1; j++) cout << char(196);
		cout << char(193);
	}
	for (int j = 0; j < SizeX - 1; j++) cout << char(196);
	cout << char(217);

	//draw side lines
	for (int i = StartY + SizeY; i < StartY + Size *SizeY; i = i + SizeY)
	{
		gotoxy(StartX, i);
		cout << char(195);
		gotoxy(StartX + (Size - 1) * SizeX + 1, i);
		for (int j = 0; j < SizeX - 1; j++)cout << char(196);
		cout << char(180);
	}

	//draw inner lines
	for (int j = StartY + SizeY; j < StartY + Size * SizeY; j = j + SizeY)
	{
		gotoxy(StartX + 1, j);
		for (int i = StartX + SizeX; i < StartX + Size * SizeX; i = i + SizeX) {

			for (int j = 0; j < SizeX - 1; j++)cout << char(196);
			cout << char(197);
		}
	}
	//draw inner colums
	for (int i = StartX; i < StartX + (Size + 1) * SizeX; i = i + SizeX) {
		for (int j = StartY; j < StartY + Size * SizeY; j = j + SizeY) {
			gotoxy(i, j + 1);
			cout << char(179);
		}
	}
}
Side Game::RunFromFile(int& num_of_turns,MoveFileHandler  * moveA, MoveFileHandler * moveB)
{
	//start the game
	start();
	num_of_turns = 1;

	// contain the winner side
	Side theWinner = Side::NoSide;
	tuple<int, int, Direction> move;
	//play!
	bool isAOver = false;
	bool isBOver = false;

	while (!isEnd && !(isAOver && isBOver))
	{
		isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);

		if (theWinner == Side::NoSide)//the war still on!
		{
			if (moveA != nullptr && !moveA->GetisPlayerMovesOver())
			{
				move = moveA->GetCurrentMove();
				if (get<0>(move) == num_of_turns)
				{
					int x = GetSoldierIndex(get<1>(move));
					
					if ( 0<=x && x<=5 && soldiers[GetSoldierIndex(get<1>(move))] != nullptr)
					{
						PlayerMove(soldiers[GetSoldierIndex(get<1>(move))], get<2>(move));
					}
					moveA->NextMove();
				}

			}
			else isAOver = true;
			num_of_turns++;
			if (!TheOption.GetQuiet()) Sleep(TheOption.GetDelay());
			isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);
			if (moveB != nullptr && !moveB->GetisPlayerMovesOver())
			{
				move = moveB->GetCurrentMove();
				if (get<0>(move) == num_of_turns)
				{
					int x = GetSoldierIndex(get<1>(move));
					if (0 <= x && x <= 5 && soldiers[GetSoldierIndex(get<1>(move))] != nullptr)
					{
						PlayerMove(soldiers[GetSoldierIndex(get<1>(move))], get<2>(move));
					}
					moveB->NextMove();
				}
			}
			else isBOver = true;
		}
		if (!TheOption.GetQuiet()) Sleep(TheOption.GetDelay());
		if (num_of_turns == 1015)
			cout << "A";
		num_of_turns++;
		if (num_of_turns == 1015)
			cout << "A";
		
	}
	return theWinner;
}
//Side Game::RunRecord(IsGameStop& isGameStop, BoardFileHandler * board, MoveFileHandler * moveA, MoveFileHandler * moveB)
//{
//		//start the game
//		start();
//
//		int num_of_turns = 1;
//		board->WriteBoard(cells);
//		moveA->Activate();
//		moveB->Activate();
//		// contain the winner side
//		Side theWinner = Side::NoSide;
//		Side keySide = Side::NoSide;
//		//soldier and direction
//		//Soldier	* playerASolider = nullptr, *playerBSolider = nullptr;
//		int playerASolider = -1, playerBSolider = -1;
//		Direction PlayerADirection = Direction::NoDirection, PlayerBDirection = Direction::NoDirection;
//		isGameStop = IsGameStop::No;
//		//play!
//		while (!isEnd)
//		{
//			isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);
//
//			if (theWinner == Side::NoSide)//the war still on!
//			{
//
//				if (ChooseSoliderAndDirection(playerASolider, PlayerADirection, playerBSolider, PlayerBDirection))//if not Esc pressed, got soldier and direction
//				{
//					if (playerASolider != -1 && soldiers[playerASolider] != nullptr)
//					{
//						
//						PlayerMove(soldiers[playerASolider], PlayerADirection);
//						moveA->AddMove(num_of_turns,this->GetSoliderNumFromIndex (playerASolider), PlayerADirection);
//					}
//					num_of_turns++;
//					Sleep(TheOption.GetDelay());
//					isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);
//					if (isEnd == false && playerBSolider != -1 && soldiers[playerBSolider] != nullptr)
//					{
//						PlayerMove(soldiers[playerBSolider], PlayerBDirection);
//						moveB->AddMove(num_of_turns, this->GetSoliderNumFromIndex(playerBSolider), PlayerBDirection);
//					}
//				}
//				else
//				{
//					if (!TheOption.GetIsFileMoveExist())	isGameStop = PrintSubMenu();
//
//				}
//				num_of_turns++;
//				Sleep(TheOption.GetDelay());
//			}
//		}
//		
//		moveA->CloseFileAfterRecord();
//		moveB->CloseFileAfterRecord();
//		return theWinner;
//	}
void Game::ClearTable()
{
	clearScreen();
	PrintPlayersNameAndScores();
}
void Game::ReDrawTable()
{
	if (!TheOption.GetQuiet()) DrawTable();
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (cells[i][j] != nullptr)
				if( !TheOption.GetQuiet()) cells[i][j]->Draw();
		}
	}
}

//ctors and dtors
Game::Game(AbstractPlayer * _PlayerA, AbstractPlayer * _PlayerB, GameOption _theOption)
{
	TheOption = _theOption;
	PlayerA = _PlayerA;
	PlayerB = _PlayerB;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cells[i][j] = nullptr;
		}
	}
	for (Soldier*& i : soldiers)
	{
		i = nullptr;
	}
	if(!TheOption.GetQuiet())	PrintPlayersNameAndScores();
	isEnd = false;
}
Game::Game(AbstractPlayer * _PlayerA, AbstractPlayer * _PlayerB, list<Cell> cells_from_file, GameOption _theOption) :Game(_PlayerA, _PlayerB, _theOption)
{
	
	for (Cell c : cells_from_file)
	{
		cells[c.GetX()][c.GetY()] = new Cell(c);
		switch (c.GetType())
		{
		case Type::S1:
			soldiers[0] = new Soldier(1, Side::SideA, false, false);
			soldiers[0]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[0]);
			break;
		case Type::S2:
			soldiers[1] = new Soldier(2, Side::SideA, true, true);
			soldiers[1]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[1]);
			break;
		case Type::S3:
			soldiers[2] = new Soldier(3, Side::SideA, true, false);
			soldiers[2]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[2]);
			break;
		case Type::S7:
			soldiers[3] = new Soldier(7, Side::SideB, true, true);
			soldiers[3]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[3]);
			break;
		case Type::S8:
			soldiers[4] = new Soldier(8, Side::SideB, false, true);
			soldiers[4]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[4]);
			break;
		case Type::S9:
			soldiers[5] = new Soldier(9, Side::SideB, false, false);
			soldiers[5]->SetSoldierCell(cells[c.GetX()][c.GetY()]);
			cells[c.GetX()][c.GetY()]->SetSoldier(soldiers[5]);
			break;
		case Type::FlgA:
			FlgAPos.first = c.GetX();
			FlgAPos.second = c.GetY();
			break;
		case Type::FlgB:
			FlgBPos.first = c.GetX();
			FlgBPos.second = c.GetY();
			break;
		}
	}
}
Game::~Game()
{
//
//	for (int i = 0; i < 13; i++)
//		for (int j = 0; j < 13; j++)
//		{
//			if (cells[i][j] != nullptr)
//				delete cells[i][j];
//		}
//	for (Soldier*& i : soldiers)
//	{
//		if (i != nullptr)
//			delete i;
//	}
//	//clearScreen();
}

//init function


void Game::start() {
	if (!TheOption.GetQuiet()) DrawTable();
	if (!TheOption.GetFileGBoardExist())
	{
		SetSpecialCells();
		RandomSoldiers();
	}
	else
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (cells[i][j] != nullptr)
					if (!TheOption.GetQuiet()) cells[i][j]->Draw();
			}
		}
	}
}
//Side Game::Run(IsGameStop& isGameStop)
//{
//	//start the game
//	start();
//	int num_of_turns = 0;
//
//	// contain the winner side
//	Side theWinner = Side::NoSide;
//	Side keySide = Side::NoSide;
//	//soldier and direction
//	//Soldier	* playerASolider = nullptr, *playerBSolider = nullptr;
//	int playerASolider = -1, playerBSolider = -1;
//	Direction PlayerADirection = Direction::NoDirection, PlayerBDirection = Direction::NoDirection;
//	isGameStop = IsGameStop::No;
//	//play!
//	while (!isEnd)
//	{
//		isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);
//
//		if (theWinner == Side::NoSide)//the war still on!
//		{
//
//			if (ChooseSoliderAndDirection(playerASolider, PlayerADirection, playerBSolider, PlayerBDirection))//if not Esc pressed, got soldier and direction
//			{
//				if (playerASolider != -1 && soldiers[playerASolider] != nullptr)
//					PlayerMove(soldiers[playerASolider], PlayerADirection);
//				isEnd = ((theWinner = isAnySideWon()) != Side::NoSide);
//				Sleep(TheOption.GetDelay());
//				if (isEnd == false && playerBSolider != -1 && soldiers[playerBSolider] != nullptr)
//					PlayerMove(soldiers[playerBSolider], PlayerBDirection);
//
//			}
//			else
//			{
//				if (!TheOption.GetIsFileMoveExist())	isGameStop = PrintSubMenu();
//
//			}
//			Sleep(TheOption.GetDelay());
//		}
//	}
//
//	return theWinner;
//}
template<class T, class S>
Side Run(IsGameStop& theWinner, T PlayerA, S playerB)
{
	//start the game
	start();
	int num_of_turns = 0;

	// contain the winner side
	Side theWinner = Side::NoSide;
	Side keySide = Side::NoSide;
	//soldier and direction
	int playerASolider = -1, playerBSolider = -1;
	Board GameBoard;
	Direction PlayerADirection = Direction::NoDirection, PlayerBDirection = Direction::NoDirection;
	isGameStop = IsGameStop::No;
	GameMove MoveA(-1, -1, -1, -1), MoveB(-1, -1, -1, -1);
	AlgoPlayer1 * a;
	//play!
	while ( theWinner== Side::NoSide)
	{
		theWinner = isAnySideWon();
		
		if (theWinner == Side::NoSide)//the war still on!
		{
			MoveA = a->play(MoveB);
			
			if (ChooseSoliderAndDirection(playerASolider, PlayerADirection, playerBSolider, PlayerBDirection))//if not Esc pressed, got soldier and direction
			{
	
					
				theWinner = isAnySideWon();
				Sleep(TheOption.GetDelay());
				if (theWinner==Side::NoSide && playerBSolider != -1 && soldiers[playerBSolider] != nullptr)
					PlayerMove(soldiers[playerBSolider], PlayerBDirection);

			}
			else
			{
				if (!TheOption.GetIsFileMoveExist())	isGameStop = PrintSubMenu();

			}
			Sleep(TheOption.GetDelay());
		}
	}

	return theWinner;
}

//from file funtions
//void Game::BoardToFile(char(&board)[13][13])
//{
//	for (int i = 0; i < 13; i++)
//	{
//		for (int j = 0; j < 13; j++)
//		{
//			if (cells[i][j] == nullptr)
//			{
//				board[j][i] = ' ';
//			}
//			else
//			{
//				switch (cells[i][j]->GetType())
//				{
//				case Type::FlgA:
//					board[j][i] = 'A';
//					break;
//				case Type::FlgB:
//					board[j][i] = 'B';
//					break;
//				case Type::FR:
//					board[j][i] = 'T';
//					break;
//				case Type::SEA:
//					board[j][i] = 'S';
//					break;
//				case Type::S1:
//					board[j][i] = '1';
//					break;
//				case Type::S2:
//					board[j][i] = '2';
//					break;
//				case Type::S3:
//					board[j][i] = '3';
//					break;
//				case Type::S7:
//					board[j][i] = '7';
//					break;
//				case Type::S8:
//					board[j][i] = '8';
//					break;
//				case Type::S9:
//					board[j][i] = '9';
//					break;
//				case Type::Regular:
//					board[j][i] = ' ';
//					break;
//				}
//			}
//		}
//	}
//}

//logical functions



//print functions
//IsGameStop Game::PrintSubMenu()
//{
//	int choice;
//	bool isGoodChoice;
//	IsGameStop res;
//	ClearTable();
//
//	setTextColor(int(Color::BLUE), int(Color::BLACK));
//	gotoxy(50, 10); cout << "1. Go Back To The Same Game." << endl;
//	gotoxy(50, 11); cout << "2. Start New Game (Same Settings)" << endl;
//	gotoxy(50, 12); cout << "8. Go Back To Main Menu" << endl;
//	gotoxy(50, 13); cout << "9. Exit" << endl;
//	gotoxy(50, 15); cout << "Enter Your Choice: ";
//	do {
//		isGoodChoice = true;
//		cin >> choice;
//		switch (choice)
//		{
//		case 1:
//		{
//			clearScreen();
//			PrintPlayersNameAndScores();
//			ClearTable();
//			if (!TheOption.GetQuiet()) ReDrawTable();
//			res = IsGameStop::No;
//			break;
//		}
//		case 2:
//		{
//			isEnd = true;
//			res = IsGameStop::NewGame;
//			break;
//		}
//		case 8:
//		{
//			isEnd = true;
//			res = IsGameStop::ToMenu;
//			break;
//		}
//		case 9:
//		{
//			isEnd = true;
//			res = IsGameStop::ToExit;
//			break;
//		}
//		default:
//			isGoodChoice = false;
//			cout << "Wrong Input...Enter New Input: ";
//			break;
//		}
//	} while (isGoodChoice == false);
//	return res;
//}
void Game::PrintPlayersNameAndScores()
{
	/*gotoxy(3, 1); cout << PlayerA->GetPlayerName();
	gotoxy(3, 2); cout << PlayerA->GetPlayerScore();
	gotoxy(105, 1); cout << PlayerB->GetPlayerName();
	gotoxy(105, 2); cout << PlayerB->GetPlayerScore();*/
}

//move functions
//bool Game::ChooseSoliderAndDirection(int&  PlayerASolider, Direction& dirA, int&  PlayerBSolider, Direction& dirB)
//{
//
//	int keyPressed;
//	if (_kbhit()) {
//
//		keyPressed = _getch();
//		if (keyPressed == int(KeyNumber::ESC)) return false;
//		switch (keyPressed)
//		{
//		case int(KeyNumber::NUM1) : PlayerASolider = 0; dirA = Direction::NoDirection; break;
//		case int(KeyNumber::NUM2) : PlayerASolider = 1;  dirA = Direction::NoDirection; break;
//		case int(KeyNumber::NUM3) : PlayerASolider = 2; dirA = Direction::NoDirection; break;
//		case int(KeyNumber::KEY_A) : dirA = Direction::LEFT;  break;
//		case int(KeyNumber::KEY_D) : dirA = Direction::RIGHT; break;
//		case int(KeyNumber::KEY_X) : dirA = Direction::DOWN; break;
//		case int(KeyNumber::KEY_W) : dirA = Direction::UP;  break;
//		case int(KeyNumber::NUM7) : PlayerBSolider = 3; dirB = Direction::NoDirection; break;
//		case int(KeyNumber::NUM8) : PlayerBSolider = 4; dirB = Direction::NoDirection;  break;
//		case int(KeyNumber::NUM9) : PlayerBSolider = 5; dirB = Direction::NoDirection; break;
//		case int(KeyNumber::KEY_L) : dirB = Direction::RIGHT;  break;
//		case int(KeyNumber::KEY_J) : dirB = Direction::LEFT;  break;
//		case int(KeyNumber::KEY_M) : dirB = Direction::DOWN;  break;
//		case int(KeyNumber::KEY_I) : dirB = Direction::UP; break;
//		}
//
//	}
//
//	return true;
//}


