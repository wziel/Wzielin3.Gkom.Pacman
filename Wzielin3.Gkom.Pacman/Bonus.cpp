#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Bonus.h"


const float Bonus::MAX_HEIGHT = 0.8;
const float Bonus::MIN_HEIGHT = 0.2;
const float Bonus::MOVE_SPEED = 0.02;

Bonus::Bonus(int points) : _points(points)
{
	height = 0.5;
	animatingUp = true;
}

int Bonus::getPoints() const
{
	return _points;
}

void Bonus::update()
{
	if (animatingUp)
	{
		height += MOVE_SPEED;
		if (height > MAX_HEIGHT) animatingUp = false;
	}
	else
	{
		height -= MOVE_SPEED;
		if (height < MIN_HEIGHT) animatingUp = true;
	}
}

void Bonus::draw() const
{
	Drawable::draw();
	glTranslatef(0, height, 0);
}


Bonus::~Bonus()
{
}
