#include "Soldier.h"
#include "Cell.h"

using namespace std;

void Soldier::SetSoldierCell(Cell*& _cell)
{
	cell = _cell;
}
Move Soldier::MoveSoldier(Cell*& target)
{
	if (target->GetSoldier() != nullptr)
	{
		if (target->GetSoldier()->GetSoliderSide() == this->GetSoliderSide())
			return Move::Failed;
		bool fight_result = FightSoldier(target->GetSoldier());
		if (fight_result)
		{
			Move dead_soldier = (Move)target->GetSoldier()->GetSoliderNumber();
			target->RemoveSolider();
			target->SetSoldier(this);
			this->GetSoliderCell()->RemoveSolider();
			this->SetSoldierCell(target);
			return dead_soldier;
		}
		else
		{
			Move dead_soldier = (Move)this->GetSoliderNumber();
			this->GetSoliderCell()->RemoveSolider();
			return dead_soldier;
		}
	}
	else
	{
		this->GetSoliderCell()->RemoveSolider();
		this->SetSoldierCell(target);
		this->GetSoliderCell()->SetSoldier(this);
		return Move::OK;
	}
}




bool Soldier::FightSoldier(Soldier * enemy)
{
	//true- this won
	//false- enemy won
	bool fight_result;
	//	bool isReveresd;
	if (enemy->GetSoliderSide() == Side::SideB)
	{
		fight_result = false;
		switch ((int)this->GetSoliderNumber())
		{
		case 1:
			if (enemy->GetSoliderCell()->GetX() != 3 && (9 > enemy->GetSoliderCell()->GetY()))
				fight_result = true;
			break;
		case 2:
			if (((enemy->GetSoliderNumber() == 8) || (enemy->GetSoliderNumber() == 7)) &&
				((enemy->GetSoliderCell()->GetX() == 10) || (enemy->GetSoliderCell()->GetY() == 2) || (enemy->GetSoliderCell()->GetY() == 3)))
				fight_result = true;
			break;
		case 3:
			if ((enemy->GetSoliderCell()->GetX() == 6) || (enemy->GetSoliderCell()->GetY() == 7))
				fight_result = true;
			break;
		default:
			break;
		}
	}
	else
	{
		fight_result = true;
		switch ((int)enemy->GetSoliderNumber())
		{
		case 1:
			if (enemy->GetSoliderCell()->GetX() != 3 && (9 > enemy->GetSoliderCell()->GetY()))
				fight_result = false;
			break;
		case 2:
			if (((this->GetSoliderNumber() == 8) || (this->GetSoliderNumber() == 7)) &&
				((enemy->GetSoliderCell()->GetX() == 10) || (enemy->GetSoliderCell()->GetY() == 2) || (enemy->GetSoliderCell()->GetY() == 3)))
				fight_result = false;
			break;
		case 3:
			if ((enemy->GetSoliderCell()->GetX() == 6) || (enemy->GetSoliderCell()->GetY() == 7))
				fight_result = false;
			break;
		default:
			break;
		}
	}
	return fight_result;

}



void Soldier::Draw()
{
	if (cell)
	{
		gotoxy((StartX + 1) + cell->GetX()*SizeX, (StartY + 1) + cell->GetY()*SizeY);
		if (side == Side::SideA) setTextColor(int(Color::WHITE), int(Color::OLIVE));
		else setTextColor(int(Color::WHITE), int(Color::RED));

		cout << "  " << number << " ";
	}
}

void Soldier::unDraw()
{
	if (cell)
	{
		gotoxy((StartX + 1) + cell->GetX()*SizeX, (StartY + 1) + cell->GetY()*SizeY);
		cout << "    ";
	}
}
