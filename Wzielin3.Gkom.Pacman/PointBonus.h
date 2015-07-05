#pragma once
#include "Bonus.h"
class PointBonus :
	public Bonus
{
private:
public:
	PointBonus();
	virtual ~PointBonus();

	virtual void draw() const;
};

