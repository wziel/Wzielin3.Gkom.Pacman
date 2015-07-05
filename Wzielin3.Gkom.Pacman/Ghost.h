#pragma once
#include "Creature.h"
#include "Sphere.h"
#include "Rosette.h"
class Ghost :
	public Creature
{
private:
	Sphere* sphere;
	Rosette* rosette;
public:
	Ghost();
	virtual ~Ghost();

	void virtual draw() const;
	virtual void update();
};

