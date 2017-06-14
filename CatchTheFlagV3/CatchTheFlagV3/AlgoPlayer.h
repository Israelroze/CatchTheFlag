#include "AbstractPlayer.h"
#include "BoardData.h"
#include <string>
class AlgoPlayer : public AbstractPlayer
{ 
	private:
		BoardData* _board;
		int _side;
		string _name;
		GameMove play(const GameMove& opponentsMove);
		void init(const BoardData& board) { *(_board) = board; }
		void SetPlayer(int player) { _side = player; }


};