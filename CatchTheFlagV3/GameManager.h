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
	Player  * PlayerA;
	Player  * PlayerB;
	bool IsReversed;
	bool IsRecord = false;
	bool IsStart = false;
	GameDir * allFiles=nullptr;
	GameMode mode = GameMode::Regular;
	GameOption TheOption;
	void GetNames();
	void ReverseGame();
	void clearScore();
	void ManageScore(IsGameStop  & isGameStoped, Side & Winner);
	void PrintEndingMessage(string violations);
	void RunBoardAndMoveFiles();
	Side RunBoardFileAndKeyMove(IsGameStop  & isGameStoped);
	Side RunRandomBoardAndKeyMove(IsGameStop  & isGameStoped);
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
	void Menu();
};

