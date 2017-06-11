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



GameManager::GameManager(int argc, char * argv[]) : IsReversed(false), TheOption(argc, argv)
{
}

void GameManager::RunGamev2()
{

	if (TheOption.GetFileGBoardExist())
	{
		//allFiles = new GameDir(TheOption.GetPath());
		//TODO
	}
	else
	{

	}
	//RunBoardAndMoveFiles();


}

GameManager::~GameManager()
{
	delete PlayerA;
	delete PlayerB;
	delete allFiles;
}


IsGameStop GameManager::Start()
{
	clearScreen();
	IsGameStop isGameStoped = IsGameStop::No;
	Side Winner;
	if (this->TheOption.GetFileGBoardExist() == true)
	{
		//Winner = RunBoardFileAndKeyMove(isGameStoped);
	}
	else
	{
		//Winner = RunRandomBoardAndKeyMove(isGameStoped);
	}

	ManageScore(isGameStoped, Winner);
	return isGameStoped;
}

void GameManager::ManageScore(IsGameStop  & isGameStoped, Side & Winner)
{

	if (isGameStoped == IsGameStop::No && Winner != Side::NoSide) {
		if (((Winner == Side::SideA) && (IsReversed == false)) || ((Winner == Side::SideB) && (IsReversed == true)))
		{
			ScoreA++;
			//PlayerA->AddScoreOne();
		}
		{
			ScoreB++;
			//PlayerB->AddScoreOne();
		}

		if (!TheOption.GetQuiet())
			Sleep(TheOption.GetDelay() * 50);
		else
			isGameStoped = IsGameStop::NewGame;
	}
	clearScreen();

}

void GameManager::PrintEndingMessage(string violations)
{
	cout << "Game Summary" << endl;
	cout << PlayerA->getName() << " points : " << ScoreA << endl;
	cout << PlayerB->getName() << " points : " << ScoreB << endl;

	if (violations != "")
	{
		cout << "\nFile Violations:" << endl;
		cout << violations;
	}
	cout << "Press Any Key To Continue" << endl;
	_getch();

}



//Side GameManager::RunBoardFileAndKeyMove(IsGameStop  & isGameStoped)
//{
//	//GameDir allFiles(TheOption.GetPath());
//	Side Winner = Side::NoSide;
//	string violation = "";
//	if (allFiles->GetCurrentBoardFile() == nullptr && allFiles->isFilesNotOver()) allFiles->MoveToNextFilesTrio();
//	if (allFiles->GetCurrentBoardFile() == nullptr || !allFiles->isFilesNotOver()) return Winner;
//	allFiles->GetCurrentBoardFile()->ReadBoard();
//	if (allFiles->GetCurrentBoardFile()->IsViolations() == false)
//	{
//		Game aGame(PlayerA, PlayerB, allFiles->GetCurrentBoardFile()->GetCellList(), TheOption);
//
//		if (TheOption.GetIsRecord() == true)
//		{
//			allFiles->NewMoveFiles(allFiles->GetCurrentBoardFile()->GetBoardFileName());
//			Winner = aGame.RunRecord(isGameStoped, allFiles->GetCurrentBoardFile(), allFiles->GetCurrentMoveAFile(), allFiles->GetCurrentMoveBFile());
//		}
//		else
//		{
//			Winner = aGame.Run(isGameStoped);
//		}
//		allFiles->MoveToNextFilesTrio();
//	}
//	else
//	{
//		violation += allFiles->GetCurrentBoardFile()->GetViolations();
//	}
//	if (!allFiles->isFilesNotOver())
//	{
//		//this->PrintEndingMessage(violation);
//		isGameStoped = IsGameStop::ToExit;
//	}
//	return Winner;
//}
//
Side GameManager::RunRandomBoard(IsGameStop  & isGameStoped)
{
	//GameDir allFiles(TheOption.GetPath());

	Side Winner;
	Game aGame(PlayerA, PlayerB, TheOption);
	Winner = aGame.Run(isGameStoped);
	
	
	//allFiles.MoveToNextFilesTrio();// gonna be a list implement
	return Winner;
}


void GameManager::clearScore()
{
	ScoreA = ScoreB = 0;
}


