#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Pacman.h"


Pacman::Pacman()
{
	_points = 0;
	isDying = false;
	lives = 100;
	dieFrames = dieFramesDefault;
	frame_no = 0;
	size = 1;

	sphere = new Sphere(1, 10, 20);

	ambient = new GLfloat[4] {1, 1, 0, 1.0};
	specular = new GLfloat[4] {1, 1, 0, 1.0};
	diffuse = new GLfloat[4] {1, 1, 0, 1.0};

	Drawable::setMaterial(ambient, specular, diffuse, 100);
}

Pacman::~Pacman()
{
}

void Pacman::update()
{
	static int frame_dif = -6;

	if (isDying)
	{
		if (dieFrames > 0)
		{
			dieFrames--;
			float deathPercent = (float)dieFrames / dieFramesDefault;
			size = deathPercent;
			setColorStrength(deathPercent);
		}
	}
	else if (getSpeed() > 0)
	{
		if (frame_no <= 0 || frame_no >= 60) frame_dif = -frame_dif;
		frame_no += frame_dif;

		Creature::update();
	}
}

void Pacman::draw() const
{
	glPushMatrix();
	glTranslatef(0.5 + getX(), 0.5, -0.5 + getY());

	auto direction = getCurrentDirection();
	if (direction == Direction::North)
	{
		glRotatef(-90, 0, 1, 0);
	}
	else if (direction == Direction::East)
	{
		glRotatef(-180, 0, 1, 0);
	}
	else if (direction == Direction::South)
	{
		glRotatef(-270, 0, 1, 0);
	}

	Drawable::draw();
	glScalef(size, size, size);
		glPushMatrix();
			glRotatef(-frame_no, 0, 0, 1);
			sphere->draw();
		glPopMatrix();
		glPushMatrix();
			glRotatef(180 + frame_no, 0, 0, 1);
			sphere->draw();
		glPopMatrix();
	glPopMatrix();
}

void Pacman::go(Direction direction)
{
	setRequestedDirection(direction);
}

int Pacman::getPoints() const
{
	return _points;
}

void Pacman::addPoint(int points)
{
	_points += points;
}

void Pacman::kill()
{
	isDying = true;
	setSpeed(0);
}

void Pacman::resurect()
{
	if (--lives > 0)
	{
		//not dying
		isDying = false;
		dieFrames = dieFramesDefault;

		//big as default
		size = 1;

		//color as defaukt
		setColorStrength(1);

		//set default position, direction, speed
		Creature::reset();
	}
}

bool Pacman::isAlive() const
{
	return dieFrames > 0;
}

void Pacman::setColorStrength(float strength)
{
	ambient[0] = specular[0] = diffuse[0] =
	ambient[1] = specular[1] = diffuse[1] =
	ambient[3] = specular[3] = diffuse[3] = strength;
}