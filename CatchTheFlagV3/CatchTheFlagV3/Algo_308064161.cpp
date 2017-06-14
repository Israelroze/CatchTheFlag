

#include "AlgorithmRegistration.h"
#include "Algo_308064161.h"
#include "GameMove.h"

// in the cpp of Algo_1
Registration algo_1("avishay",[] {return new Algo_308064161(); });
Registration algo_2("israel",[] {return new Algo_308064161(); });

void Algo308064161::chooseMove()
{
	//if attacker not dead
	if ((*Attacker).GetData() == DeadSoldier && )
	{
		Attacker++;
	}
	else
	{

	}
	if ((*Attacker).GetCord.first > EnemyFlagPos.first) //UP
	{
		PossibleMoves[0] = Trio((*Attacker).GetCord.first - 1, (*Attacker).GetCord.second, 0);
	}
	else //DOWN
	{
		PossibleMoves[0] = Trio((*Attacker).GetCord.first + 1, (*Attacker).GetCord.second, 0);
	}

	if ((*Attacker).GetCord.second < EnemyFlagPos.second)//RIGHT
	{
		PossibleMoves[1] = Trio((*Attacker).GetCord.first, (*Attacker).GetCord.second + 1, 0);
	}
	else//LEFT
	{
		PossibleMoves[1] = Trio((*Attacker).GetCord.first, (*Attacker).GetCord.second - 1, 0);
	}
}

void Algo308064161::choosePositions()
{
	int Min_distance = abs(EnemyFlagPos.first - Soldiers[0].GetCord().first)+ abs(EnemyFlagPos.second - Soldiers[0].GetCord().second);

	for(int i=1;i<3;i++)
	{
		int distance= abs(EnemyFlagPos.first - Soldiers[i].GetCord().first) + abs(EnemyFlagPos.second - Soldiers[i].GetCord().second);
		if(distance<Min_distance)
		{
			Trio* tmp;
			*tmp = Soldiers[0];
			Soldiers[0] = Soldiers[i];
			Soldiers[i] = *tmp;
		}
	}
	int second_distance= abs(EnemyFlagPos.first - Soldiers[1].GetCord().first) + abs(EnemyFlagPos.second - Soldiers[1].GetCord().second);
	int third_distance= abs(EnemyFlagPos.first - Soldiers[2].GetCord().first) + abs(EnemyFlagPos.second - Soldiers[2].GetCord().second);
	if (second_distance > third_distance)
	{
		Trio* tmp;
		*tmp = Soldiers[1];
		Soldiers[1] = Soldiers[2];
		Soldiers[2] = *tmp;
	}

	*Attacker = Soldiers[0];
}

int Algo308064161::randomChoice()
{
	srand(unsigned int(time(time_t(0))));
	int num = rand() % 13;
	if (num % 2 == 0) return 0;
	else return 1;
}

void Algo308064161::updateBoard(GameMove & enemymove)
{
	Board[enemymove.to_x-1][enemymove.to_y - 1]=Board[enemymove.from_x - 1][enemymove.from_y - 1];
	Board[enemymove.from_x - 1][enemymove.from_y - 1] = OriginalBoard->charAt(enemymove.from_x, enemymove.from_y);
}

void Algo308064161::init(const BoardData & board)
{
	*(OriginalBoard) = board;
	int detected_soldiers = 0;
	for (int i = 1; i < 14; i++)
	{
		for (int j = 1; j < 14; j++)
		{
			//set board cell
			Board[i - 1][j - 1] = board.charAt(i, j);

			//set flags
			if (Board[i - 1][j - 1] == 'A')
			{
				if (PlayerNum == 1)
					MyFlagPos = { i,j };
				else
					EnemyFlagPos = { i,j };
			}
			else if (Board[i - 1][j - 1] == 'B')
			{
				if (PlayerNum == 1)
					MyFlagPos = { i,j };
				else
					EnemyFlagPos = { i,j };
			}

			//set soldiers
			if ((Board[i - 1][j - 1] >= 1) && (Board[i - 1][j - 1] <= 9))
			{
				Soldiers[detected_soldiers] = Trio(i - 1, j - 1, Board[i - 1][j - 1]);
			}
		}
	}
}

GameMove Algo308064161::play(const GameMove & opponentsMoves)
{
	return GameMove();
}

string Algo308064161::getName() const
{
	return string();
}
