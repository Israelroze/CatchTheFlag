#include "Player.h"

#include "AlgorithmRegistration.h"




void AlgoPlayer1::setPlayer(int player)
{
}

void AlgoPlayer1::init(const BoardData & board)
{
}

GameMove AlgoPlayer1::play(const GameMove & opponentsMoves)
{
	//return GameMove();
}

string AlgoPlayer1::getName() const
{
	return string();
}


// in the cpp of Algo_1
Registration algo_1("algo_1",
	[] {return new AlgoPlayer1(); });
Registration algo_1("algo_2",
	[] {return new AlgoPlayer1(); });