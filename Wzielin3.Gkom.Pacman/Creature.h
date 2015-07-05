#pragma once
#include "Drawable.h"
#include "Enums.h"

class Creature : public Drawable
{
private:
	Direction _currentDirection;
	Direction _requestedDirection;
	float _speed;

	float _x;
	float _y;
public:
	Creature();
	virtual ~Creature();
	void virtual draw() const = 0;

	float getSpeed() const;
	float getX() const;
	float getY() const;
	Direction getCurrentDirection() const;
	Direction getRequestedDirection() const;

	void setX(float x);
	void setY(float Y);
	void setSpeed(float speed);
	void setRequestedDirection(Direction requestedDirection);
	void setCurrentDirection(Direction direction);

	void reset();

	virtual void update();
};

