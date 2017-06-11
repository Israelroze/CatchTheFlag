#include "Cell.h"
#include  <string>


void Cell::Draw()
{
	string toPrint;
	gotoxy((StartX + 1) + x*SizeX, (StartY + 1) + y*SizeY);
	if (soldier == nullptr)
	{
		switch (type)
		{
		case Type::FlgA:
			setTextColor(int(Color::OLIVE), int(Color::WHITE)); toPrint = "FlgA"; break;
		case Type::FlgB:
			setTextColor(int(Color::RED), int(Color::WHITE)); toPrint = "FlgB"; break;
		case Type::FR:
			setTextColor(int(Color::WHITE), int(Color::DARK_GREEN)); toPrint = " FR "; break;
		case Type::SEA:
			setTextColor(int(Color::WHITE), int(Color::BLUE)); toPrint = "SEA "; break;
		case Type::Regular:
			setTextColor(int(Color::WHITE), int(Color::BLACK)); toPrint = "    "; break;
		}
		cout << toPrint;
	}
	else
	{
		soldier->Draw();
	}
}
