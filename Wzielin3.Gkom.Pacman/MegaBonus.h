#pragma once
#include "Bonus.h"
class MegaBonus :
	public Bonus
{
	const float _radius;
	static const unsigned int _ballsCount = 6;
	
	float angle;

	float axis[_ballsCount][3];
	float position[_ballsCount][3];
public:
	MegaBonus(float radius);
	~MegaBonus();

	virtual void draw() const;
	virtual void update();
};

