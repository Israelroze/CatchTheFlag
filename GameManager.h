#pragma once

#include "Player.h"
#include "Enums.h"
#include <map>
#include <conio.h>
#include <string>
#include "GameOption.h"
#include "GameDir.h"
#include <Windows.h>



class GameManager {
private:
	//AbstractPlayer  * PlayerA = new AlgoPlayer1;// should be null ptr// todo: alorithmRegistration
	//AbstractPlayer  * PlayerB = new AlgoPlayer1; // shuld be null ptr// todo: alorithmRegistration
	bool IsReversed; // probably gonna be cancelled
	bool IsRecord = false;// also, probably gonna be cancelled
	bool IsStart = false;// also, probably gonna be cancelled
	GameDir * allFiles=nullptr;
	int ScoreA = 0;
	int ScoreB = 0;
	GameMode mode = GameMode::Regular; // also, probably gonna be cancelled
	GameOption TheOption;
	//void GetNames(); // also, probably gonna be cancelled
	//void ReverseGame();// also, probably gonna be cancelled
	void clearScore();
	void ManageScore(IsGameStop  & isGameStoped, Side & Winner);
	void PrintEndingMessage(string violations);
	//void RunBoardAndMoveFiles();
	//Side RunBoardFileAndKeyMove(IsGameStop  & isGameStoped);
	Side RunRandomBoard(IsGameStop  & isGameStoped);
	void PrintQuietModeMessage(int cycle, int num_of_turns, Side Winner) 
	{
		cout << "Game cycle : " << cycle << endl;
		cout << "Num moves : " << num_of_turns << endl;
		cout << "Winner :"<<(Winner==Side::SideA? "Player A":"Player B")<<endl;
		Sleep(TheOption.GetDelay() * 50);
	}

public:
	IsGameStop Start();
	GameManager(int argc, char *argv[]);
	void RunGamev2();
	~GameManager();
	//void Menu();
};

