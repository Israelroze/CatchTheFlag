#pragma once
enum class Type { SEA, FR, FlgA, FlgB, Regular, S1, S2, S3, S7, S8, S9 };
enum class GameMode { Regular, BoardMove, Move, Board, Quiet};

enum { StartX = 27, StartY = 2, SizeX = 5, SizeY = 2, Size = 13 };
enum class Move { NoMove = -2, Failed = -1, OK = 0, S1 = 1, S2 = 2, S3 = 3, S7 = 7, S8 = 8, S9 = 9 };
enum class Side { SideA = 1, SideB = 2, NoSide = 0 };
enum class KeyNumber {
	NUM1 = 49, NUM2 = 50, NUM3 = 51
	, NUM7 = 55, NUM8 = 56, NUM9 = 57
	, KEY_X = 120, KEY_W = 119, KEY_A = 97, KEY_D = 100
	, KEY_M = 109, KEY_I = 105, KEY_J = 106, KEY_L = 108
	, NoKey = -1, ESC = 27
};
enum class  Direction { UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8, NoDirection = 0 };
enum class IsGameStop { ToExit = 9, ToMenu = 8, No = 1, NewGame = 2 };
