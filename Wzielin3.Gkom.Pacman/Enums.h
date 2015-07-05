#pragma once
enum Direction
{
	North = 0,
	South = 1,
	East = 2,
	West = 3,
};

enum CameraMovemement
{
	Up,
	Down,
	RotLeft,
	RotRight,
	Further,
	Closer,
	Forward,
	Backward,
	Left,
	Right,
	Reset
};

enum KeyEvent
{
	Pressed,
	Released
};