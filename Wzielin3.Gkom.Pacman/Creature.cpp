#include "Creature.h"
#include "Consts.h"

Creature::Creature()
{
	reset();
}

void Creature::reset()
{
	_x = _y = 0;
	_speed = 0;
	_currentDirection = _requestedDirection = Direction::North;
}

Creature::~Creature()
{
}


//getters

float Creature::getSpeed() const
{
	return _speed;
}

float Creature::getX() const
{
	return _x;
}

float Creature::getY() const
{
	return _y;
}

Direction Creature::getCurrentDirection() const
{
	return _currentDirection;
}
Direction Creature::getRequestedDirection() const
{
	return _requestedDirection;
}

///setters

void Creature::setSpeed(float speed)
{
	_speed = speed;
}

void Creature::setX(float x)
{
	_x = x;
}

void Creature::setY(float y)
{
	_y = y;
}

void Creature::setRequestedDirection(Direction requestedDirection)
{
	_requestedDirection = requestedDirection;
}

void Creature::setCurrentDirection(Direction direction)
{
	_currentDirection = direction;
}

//move the creature further
void Creature::update()
{
	if (_speed > 0)
	{
		std::pair<int, int> coordChange = directionToCoordinateChange.find(_currentDirection)->second;
		_x -= coordChange.first * _speed;
		_y += coordChange.second * _speed;
	}
}