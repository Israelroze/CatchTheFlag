#pragma once

#include "GameManager.h"
#include "Game.h"
#include <iostream>
#include "Enums.h"
#include <conio.h>
#include <Windows.h>
#include "GameDir.h"
#include "BoardFileHandler.h"


using namespace std;



GameManager::GameManager(int argc, char * argv[]) : IsReversed(false), PlayerA(new Player("A")), PlayerB(new Player("B")), TheOption(argc, argv)
{
}

void GameManager::RunGamev2()
{
	allFiles = new GameDir(TheOption.GetPath());

	if (this->TheOption.GetFileGBoardExist() == true && this->TheOption.GetIsFileMoveExist() == true)
	{
		RunBoardAndMoveFiles();
	}
	else
	{
		Menu();
	}

}

GameManager::~GameManager()
{
	delete PlayerA;
	delete PlayerB;
	delete allFiles;
}

void GameManager::Menu()
{
	IsGameStop isStop = IsGameStop::No;
	int choice;
	hideCursor();
	while (isStop != IsGameStop::ToExit)
	{
		if (isStop == IsGameStop::No)
		{
			clearScreen();
			setTextColor(int(Color::CYAN));
			gotoxy(10, 2); cout << "_________         __         .__      ___________.__             ___________.__                  " << endl;
			gotoxy(10, 3); cout << "\\_   ___ \\_____ _/  |_  ____ |  |__   \\__    ___/|  |__   ____   \\_   _____/|  | _____     ____  " << endl;
			gotoxy(10, 4); cout << "/    \\  \\/\\__  \\\\   __\\/ ___\\|  |  \\    |    |   |  |  \\_/ __ \\   |    __)  |  | \\__  \\   / ___\\ " << endl;
			gotoxy(10, 5); cout << "\\     \\____/ __ \\|  | \\  \\___|   Y  \\   |    |   |   Y  \\  ___/   |     \\   |  |__/ __ \\_/ /_/  >" << endl;
			gotoxy(10, 6); cout << " \\______  (____  /__|  \\___  >___|  /   |____|   |___|  /\\___  >  \\___  /   |____(____  /\\___  / " << endl;
			gotoxy(10, 7); cout << "        \\/     \\/          \\/     \\/                  \\/     \\/       \\/              \\//_____/  " << endl;

			setTextColor(int(Color::RED));
			gotoxy(50, 10); cout << "1. Choose Names" << endl;
			gotoxy(50, 11); cout << "2. Start Game" << endl;
			gotoxy(50, 12); cout << "3. Start Reverse Game" << endl;
			gotoxy(50, 13); cout << "4. Zeroize Score" << endl;
			if (TheOption.GetIsRecord())
			{
				gotoxy(50, 14); cout << "5. Press To Stop Record Game" << endl;
			}
			else
			{
				gotoxy(50, 14); cout << "5. Press To Record Game" << endl;
			}
			gotoxy(50, 15); cout << "9. Exit" << endl;
			gotoxy(50, 16); cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				GetNames();
				break;
			case 2:
				isStop = Start();
				break;
			case 3:
				ReverseGame();
				isStop = Start();
				break;
			case 4:
				clearScore();
				break;
			case 5:
				TheOption.OnOffRecord();
				break;
			case 9:
				isStop = IsGameStop::ToExit;
				break;
			default:
				break;
			}
		}
		if (isStop == IsGameStop::NewGame)
		{
			isStop = IsGameStop::No;
			isStop = Start();
		}
		if (isStop == IsGameStop::ToMenu)
		{
			isStop = IsGameStop::No;
		}
	}
}

void GameManager::GetNames()
{
	string temp;

	clearScreen();
	gotoxy(50, 10); cout << "Enter Player A Name: ";
	cin >> temp;
	PlayerA->SetPlayerName(temp);
	gotoxy(50, 11); cout << "Enter Player B Name: ";
	cin >> temp;
	PlayerB->SetPlayerName(temp);

}

void GameManager::ReverseGame()
{
	IsReversed = true;
}

IsGameStop GameManager::Start()
{
	clearScreen();
	IsGameStop isGameStoped = IsGameStop::No;
	Side Winner;
	if (this->TheOption.GetFileGBoardExist() == true && this->TheOption.GetIsFileMoveExist() == false)
	{
		Winner = RunBoardFileAndKeyMove(isGameStoped);
	}
	else if (this->TheOption.GetFileGBoardExist() == false && this->TheOption.GetIsFileMoveExist() == false)
	{
		Winner = RunRandomBoardAndKeyMove(isGameStoped);
	}

	ManageScore(isGameStoped, Winner);
	return isGameStoped;
}

void GameManager::ManageScore(IsGameStop  & isGameStoped, Side & Winner)
{

	if (isGameStoped == IsGameStop::No && Winner != Side::NoSide ) {
		if (((Winner == Side::SideA) && (IsReversed == false)) || ((Winner == Side::SideB) && (IsReversed == true)))
		{
			PlayerA->AddScoreOne();
		}
		{
			PlayerB->AddScoreOne();
		}

		if(!TheOption.GetQuiet()) Sleep(TheOption.GetDelay() * 50);
		if(!TheOption.GetIsFileMoveExist() && Winner == Side::NoSide)
			isGameStoped = IsGameStop::ToExit;
		else
		isGameStoped = IsGameStop::NewGame;
	}
	clearScreen();

}

void GameManager::PrintEndingMessage(string violations)
{
	cout << "Game Summary" << endl;
	cout << "A points : " << PlayerA->GetPlayerScore() << endl;
	cout << "B points : " << PlayerB->GetPlayerScore() << endl;

	if (violations != "")
	{
		cout << "\nFile Violations:" << endl;
		cout << violations;
	}
	cout << "Press Any Key To Continue" << endl;
	_getch();

}

void GameManager::RunBoardAndMoveFiles()
{


	string violations = "";
	IsGameStop isGameStoped = IsGameStop::No;
	Side Winner;
	int gameCouter = 0;
	
	while (allFiles->NumberOfTrioRemaining() > 0)
	{
		if (allFiles->GetCurrentBoardFile() != nullptr)
		{
			allFiles->GetCurrentBoardFile()->ReadBoard();
			if (allFiles->GetCurrentBoardFile()->IsViolations())
			{

				violations += allFiles->GetCurrentBoardFile()->GetViolations();
			}
			else
			{
				// Move an
				if (allFiles->GetCurrentMoveAFile() != nullptr) allFiles->GetCurrentMoveAFile()->Activate();
				if (allFiles->GetCurrentMoveBFile() != nullptr) allFiles->GetCurrentMoveBFile()->Activate();
				Game TheGame(this->PlayerA, this->PlayerB, allFiles->GetCurrentBoardFile()->GetCellList(), TheOption);
				int num_of_turns;
				Winner = TheGame.RunFromFile(num_of_turns, allFiles->GetCurrentMoveAFile(), allFiles->GetCurrentMoveBFile());
				ManageScore(isGameStoped, Winner);
				gameCouter++;
				PrintQuietModeMessage(gameCouter, num_of_turns, Winner);
			}
		}
		allFiles->DeleteCurrentTrioAndMoveToNext();
	}
	this->PrintEndingMessage(violations);
}

Side GameManager::RunBoardFileAndKeyMove(IsGameStop  & isGameStoped)
{
	//GameDir allFiles(TheOption.GetPath());
	Side Winner = Side::NoSide;
	string violation = "";
	if (allFiles->GetCurrentBoardFile() == nullptr && allFiles->isMapNotOver()) allFiles->MoveToNextFilesTrio();
	if (allFiles->GetCurrentBoardFile() == nullptr || !allFiles->isMapNotOver()) return Winner;
	allFiles->GetCurrentBoardFile()->ReadBoard();
	if (allFiles->GetCurrentBoardFile()->IsViolations() == false)
	{
		Game aGame(PlayerA, PlayerB, allFiles->GetCurrentBoardFile()->GetCellList(), TheOption);

		if (TheOption.GetIsRecord() == true)
		{
			allFiles->NewMoveFiles(allFiles->GetCurrentBoardFile()->GetBoardFileName());
			Winner = aGame.RunRecord(isGameStoped, allFiles->GetCurrentBoardFile(), allFiles->GetCurrentMoveAFile(), allFiles->GetCurrentMoveBFile());
		}
		else
		{
			Winner = aGame.Run(isGameStoped);
		}
		allFiles->MoveToNextFilesTrio();
	}
	else
	{
		violation += allFiles->GetCurrentBoardFile()->GetViolations();
	}
	if (!allFiles->isMapNotOver())
	{
		//this->PrintEndingMessage(violation);
		isGameStoped = IsGameStop::ToExit;
	}
	return Winner;
}

Side GameManager::RunRandomBoardAndKeyMove(IsGameStop  & isGameStoped)
{
	GameDir allFiles(TheOption.GetPath());

	Side Winner;
	Game aGame(PlayerA, PlayerB, TheOption);
	if (TheOption.GetIsRecord()== true)
	{
		allFiles.NewTrio();
		Winner = aGame.RunRecord(isGameStoped, allFiles.GetCurrentBoardFile(), allFiles.GetCurrentMoveAFile(), allFiles.GetCurrentMoveBFile());
	}
	else
	{
		Winner = aGame.Run(isGameStoped);
	}
	allFiles.MoveToNextFilesTrio();
	return Winner;
}


void GameManager::clearScore()
{
	PlayerA->ResetScore();
	PlayerB->ResetScore();
}


