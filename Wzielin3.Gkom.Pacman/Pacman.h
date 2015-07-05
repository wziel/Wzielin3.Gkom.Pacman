#pragma once
#include "Creature.h"
#include "Sphere.h"
class Pacman :
	public Creature
{
private:
	int _points;
	int lives;
	int frame_no;

	bool isDying; 
	int dieFrames;
	float size;

	static const int dieFramesDefault = 250;

	GLfloat* ambient;
	GLfloat* specular;
	GLfloat* diffuse;

	Sphere* sphere;

	//strength is between 0 and 1
	void setColorStrength(float strength);
public:
	Pacman();
	virtual ~Pacman();

	void virtual draw() const;
	void virtual update();

	void go(Direction direction);

	int getPoints() const;
	void addPoint(int points);

	void kill();
	void resurect();
	bool isAlive() const;
};

